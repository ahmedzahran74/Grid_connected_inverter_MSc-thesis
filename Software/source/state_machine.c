/*
 * state_machine.c
 *
 *  Created on: May 2, 2024
 *      Author: RTX
 */
#include "state_machine.h"

state_machine_fun inveter_state_table[MAX_STATES][MAX_EVENTS]={
{PLL_peak_ID_entery,NULL,PLL_peak_ID_do,PLL_peak_ID_count_40,NULL,NULL,NULL},
{PLL_theta_ID_do,NULL,PLL_theta_ID_do,NULL,PLL_theta_ID_rising_edge,NULL,NULL},
{PLL_start_entry,PLL_start_exit,PLL_start_do,NULL,NULL,PLL_start_check_wait,NULL},
{grid_ok_entry,grid_ok_exit,grid_ok_do,NULL,NULL,NULL,grid_not_ok_check},
};
Uint32 PLL_peak_entry_flag,PLL_peak_do_flag,PLL_peak_count_40_flag,PLL_theta_entry_flag,PLL_theta_do_flag,PLL_theta_rising_edge_flag,PLL_start_entry_flag,
PLL_start_do_flag,PLL_start_exit_flag,grid_ok_entry_flag,grid_ok_do_flag,grid_ok_exit_flag,grid_not_ok_flag,PLL_start_check_wait_flag;
inverter_state_machine_t inverter_PLL;
state_machine_fun inverter_events_state_table[MAX_STATES]={PLL_peak_ID_events,PLL_theta_ID_events,PLL_start_events,grid_ok_events};
extern float V_err;
Uint32 Grid_OK;
void inverter_state_machine_init() //should be called at the main before any interrupt is enabled
{
    inverter_events event=ENTRY;
    inverter_PLL.inverter_state=PLL_PEAK_ID;
    if(inveter_state_table[inverter_PLL.inverter_state][event]!=NULL)
    inveter_state_table[inverter_PLL.inverter_state][event]();
}
void inverter_state_machine_dispatcher()
{
    event_staus status;
    inverter_state source_state=inverter_PLL.inverter_state;
    if(inveter_state_table[inverter_PLL.inverter_state][DO]!=NULL)
    {
        status=inveter_state_table[inverter_PLL.inverter_state][DO]();
    }
    status=inverter_events_state_table[inverter_PLL.inverter_state]();

    if(status==transition)
    {
        inverter_state destination_state=inverter_PLL.inverter_state;
        inverter_PLL.inverter_state=source_state;
        if(inveter_state_table[inverter_PLL.inverter_state][EXIT]!=NULL)
        {
        inveter_state_table[inverter_PLL.inverter_state][EXIT]();
        }

        inverter_PLL.inverter_state=destination_state;
        if(inveter_state_table[inverter_PLL.inverter_state][ENTRY]!=NULL)
        {
        inveter_state_table[inverter_PLL.inverter_state][ENTRY]();
        }
    }
}

event_staus PLL_peak_ID_entery( )
{
    PLL_peak_entry_flag++;

    event_staus status;
    //
    inverter_PLL.peak_ID=0;
    inverter_PLL.theta=0;
    inverter_PLL.count=0;
    adc_isr_assign_function(adc_isr_PLL_init);
    epwm4_isr_assign_function(epwm4_isr_100us_PLL_init);
    cpu_timer1_assign_function(cpu_timer1_PLL_init);
    status= handled;
    return status;
}
event_staus PLL_peak_ID_do( )
{
    PLL_peak_do_flag++;
    event_staus status;
    //
    inverter_PLL.count++;
    if(VAC>inverter_PLL.peak_ID)
    {
        inverter_PLL.peak_ID=VAC;
    }
    status=handled;
    return status;
}
event_staus PLL_peak_ID_count_40( )
{
    PLL_peak_count_40_flag++;
    event_staus status;
    //
    inverter_PLL.inverter_state=PLL_THETA_ID;
    status=transition;
    return status;
}
event_staus PLL_theta_ID_entry( )
{
    PLL_theta_entry_flag++;
    inverter_PLL.rising_edge=0;
    return handled;
}

event_staus PLL_theta_ID_do( )
{
    PLL_theta_do_flag++;
    event_staus status;
    //
    static float Vac_previous=0;
    static float Vac_current=0;
    Vac_previous=Vac_current;
    Vac_current=VAC;
    if(Vac_previous<0&&Vac_current>0)
    {
        inverter_PLL.rising_edge=1;
    }
    status=handled;
    return status;
}
event_staus PLL_theta_ID_rising_edge( )
{
    PLL_theta_rising_edge_flag++;
    event_staus status;
    //
    inverter_PLL.theta=0;
    inverter_PLL.inverter_state=PLL_START;
    status=transition;
    return status;
}
event_staus PLL_start_entry( )
{
    PLL_start_entry_flag++;
    event_staus status;
    //
    inverter_PLL.check=0;
    inverter_PLL.PLL_count=0;

    PLL_controller_initialize(inverter_PLL.peak_ID);
    RHO_code_generation_initialize();
    adc_isr_assign_function(adc_isr_PLL_start);
    epwm4_isr_assign_function(epwm4_isr_100us_PLL_start);
    cpu_timer1_assign_function(cpu_timer1_PLL_start);
    status=handled;
    return status;
}
event_staus PLL_start_exit( )
{
    PLL_start_exit_flag++;
    event_staus status;
    //
    //inverter_clear_tripzone_SW_event();//this function clear the tripzone s.w event
    status=handled;
    return status;
}
event_staus PLL_start_do( )
{
    PLL_start_do_flag++;
    event_staus status;
    //
    if(inverter_PLL.PLL_count<1000)
    {
        inverter_PLL.PLL_count++;
    }
    else if(inverter_PLL.PLL_count>=1000)
    {
        inverter_PLL.check=check_PLL_ok();
    }

    status=handled;
    return status;
}
event_staus PLL_start_check_wait( )
{
    PLL_start_check_wait_flag++;
    event_staus status;
    //

    inverter_PLL.inverter_state=GRID_OK;
    status=transition;
    return status;
}
event_staus grid_ok_entry( )
{
    grid_ok_entry_flag++;
    Grid_OK=1;
    event_staus status;
    //
    //adc_isr_assign_function(adc_isr_PLL_grid_ok);
    //epwm4_isr_assign_function(epwm4_isr_100us_PLL_grid_ok);
    //cpu_timer1_assign_function(cpu_timer1_PLL_grid_ok);
    status=handled;
    return status;
}
event_staus grid_ok_exit( )
{
    grid_ok_exit_flag++;
    event_staus status;
    Grid_OK=0;
    //inverter_enable_tripzone_SW_event();//this function enable the tripzone s.w event
    status=handled;
    return status;
}
event_staus grid_ok_do( )
{
    grid_ok_do_flag++;
    event_staus status;
    //
    inverter_PLL.check=check_PLL_ok();
    status=handled;
    return status;
}
event_staus grid_not_ok_check( )
{
    grid_not_ok_flag++;
    event_staus status;
    inverter_PLL.inverter_state=PLL_PEAK_ID;
    status=transition;
    return status;
}
float V_err_filter=0, freq_filter;
Uint32 check_bad_counter,check_ok_counter;
Uint32 check_PLL_ok()
{
    Uint32 check=0;

    V_err_filter+=(fabs(V_err)-V_err_filter)*(1.0/20.0);
    freq_filter +=(rtY.frequency-freq_filter)*(1.0/20.0);

    if((V_err_filter<(0.1*rtY.Ugrid_peak))&&(freq_filter<51.0)&&(freq_filter>49.0))
    {
        check_ok_counter++;
        check=1;
    }
    else
    {
        check_bad_counter++;
        check=0;
    }
    return check;
}


event_staus PLL_peak_ID_events( )
{
    event_staus status=handled;
    if (inverter_PLL.count>=40)
    {
        status=inveter_state_table[inverter_PLL.inverter_state][COUNT_40]();
    }
    return status;
}
event_staus PLL_theta_ID_events( )
{
    event_staus status=handled;
    if(inverter_PLL.rising_edge==1)
    {
        status=inveter_state_table[inverter_PLL.inverter_state][RISING_EDGE]();
    }
    return status;
}
event_staus PLL_start_events( )
{
    event_staus status=handled;
    if(inverter_PLL.PLL_count>=1000&&inverter_PLL.check==1)
    {
        status=inveter_state_table[inverter_PLL.inverter_state][CHECK_WAIT]();
    }
    return status;
}
event_staus grid_ok_events( )
{

    event_staus status=handled;
    if(inverter_PLL.check!=1)
    {
        status=inveter_state_table[inverter_PLL.inverter_state][CHECK]();
    }
    return status;
}




/*
if(inverter->inverter_state==PLL_PEAK_ID)
{
   if (inverter->count>=40)
   {
       status=inveter_state_table[inverter->inverter_state][COUNT_40](inverter);
   }

}
else if(inverter->inverter_state==PLL_THETA_ID)
{
   if(inverter->rising_edge==1)
   {
       status=inveter_state_table[inverter->inverter_state][RISING_EDGE](inverter);
   }

}
else if(inverter->inverter_state==PLL_START)
{
   if(inverter->PLL_count>=1000&&inverter->check==1)
   {
       status=inveter_state_table[inverter->inverter_state][CHECK_WAIT](inverter);
   }

}
else if(inverter->inverter_state==GRID_OK)
{
   if(inverter->check!=1)
   {
       status=inveter_state_table[inverter->inverter_state][CHECK](inverter);
   }

}
*/
