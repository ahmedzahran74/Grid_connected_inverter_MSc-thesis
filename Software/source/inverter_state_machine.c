/*
 * inverter_state_machine.c
 *
 *  Created on: May 6, 2024
 *      Author: RTX
 */
#include "inverter_state_machine.h"
inverter_state_machine_fun state_table_inveter[INVERTER_MAX_STATES][INVERTER_MAX_EVENTS]={
{not_ready_entry,NULL,NULL,not_ready_grid_ok,NULL,NULL},
{checks_and_initial_condition_entry,checks_and_initial_condition_exit,NULL,NULL,checks_and_initial_condition_VDC_ok,checks_and_initial_condition_grid_not_ok},
{start_control_entry,start_control_exit,NULL,NULL,NULL,start_control_grid_not_ok}
};
inverter_state_machine_fun state_table_inveter_events[INVERTER_MAX_STATES]={NOT_ready_events,checks_and_initial_condition_events,start_control_events};
extern Uint32 Grid_OK;

// extern inverter_state_machine_t inverter_PLL;
extern float VDC;
extern float VAC;
state_machine_inverter_t inverter_state;
void state_machine_init_inverter(void)
{
    inverter_state.inverter_state=NOT_READY;
    inverter_state_machine_events event=ENTRY_inverter;
    if(state_table_inveter[inverter_state.inverter_state][event]!=NULL)
    {
        state_table_inveter[inverter_state.inverter_state][event]();
    }
}
Uint32 EXIT_flag;
void state_machine_dispatcher_inverter(void)
{
    inverter_state_machine_event_staus status;
    if(state_table_inveter[inverter_state.inverter_state][DO_inverter]!=NULL)
    {
        state_table_inveter[inverter_state.inverter_state][DO_inverter]();
    }
    inverter_state_machine_state source_state=inverter_state.inverter_state;
    status=state_table_inveter_events[inverter_state.inverter_state]();
    if(status==transition_inverter)
    {
        inverter_state_machine_state destination_state=inverter_state.inverter_state;
        inverter_state.inverter_state=source_state;
        inverter_state_machine_events event=EXIT_inverter;
        EXIT_flag++;
        if(state_table_inveter[inverter_state.inverter_state][event]!=NULL)
        {
            state_table_inveter[inverter_state.inverter_state][event]();
        }
        inverter_state.inverter_state=destination_state;
        event=ENTRY_inverter;
        if(state_table_inveter[inverter_state.inverter_state][event]!=NULL)
        {
            state_table_inveter[inverter_state.inverter_state][event]();
        }
    }
}
Uint32 not_ready_entry_flag,not_ready_grid_ok_flag,checks_and_initial_condition_entry_flag,checks_and_initial_condition_exit_flag,checks_and_initial_condition_VDC_ok_flag,
checks_and_initial_condition_grid_not_ok_flag,start_control_entry_flag,start_control_exit_flag,start_control_grid_not_ok_flag,NOT_ready_events_flag,
checks_and_initial_condition_events_flag,start_control_events_flag;
inverter_state_machine_event_staus not_ready_entry()
{
    not_ready_entry_flag++;
    inverter_state_machine_event_staus status=handled_inverter;
    inverter_enable_tripzone_SW_event();
    pull_up_relay();
    return status;
}
inverter_state_machine_event_staus not_ready_grid_ok()
{
    not_ready_grid_ok_flag++;
    inverter_state_machine_event_staus status;
    status=transition_inverter;
    inverter_state.inverter_state=CHECKS_AND_INITIAL_CONDITION;
    return status;
}

inverter_state_machine_event_staus checks_and_initial_condition_entry ()
{
    checks_and_initial_condition_entry_flag++;
    inverter_state_machine_event_staus status;
    //here we have to give the 10khz interrupt a function that stores the new VDC
    epwm4_isr_assign_function(epwm4_isr_100us_DC_voltage_check);
    pull_down_relay();

    status=handled_inverter;
    return status;
}

inverter_state_machine_event_staus checks_and_initial_condition_exit()
{
    checks_and_initial_condition_exit_flag++;
    inverter_state_machine_event_staus status;
    status=handled_inverter;
    return status;
}
inverter_state_machine_event_staus checks_and_initial_condition_VDC_ok()
{
    checks_and_initial_condition_VDC_ok_flag++;
    inverter_state_machine_event_staus status;
    setting_initial_condition();
    status=transition_inverter;
    inverter_state.inverter_state=START_CONTROL;
    return status;
}
inverter_state_machine_event_staus checks_and_initial_condition_grid_not_ok ()
{
    checks_and_initial_condition_grid_not_ok_flag++;
    inverter_state_machine_event_staus status;
    status=transition_inverter;
    inverter_state.inverter_state=NOT_READY;
    return status;
}


inverter_state_machine_event_staus start_control_entry()
{
    start_control_entry_flag++;
    inverter_state_machine_event_staus status;
    adc_isr_assign_function(adc_isr_PLL_start_control);
    epwm4_isr_assign_function(epwm4_isr_100us_PLL_start_control);
    cpu_timer1_assign_function(cpu_timer1_PLL_start_control);
    inverter_clear_tripzone_SW_event();
    status=handled_inverter;
    return status;
}
inverter_state_machine_event_staus start_control_exit()
{
    start_control_exit_flag++;
    inverter_state_machine_event_staus status;
    inverter_enable_tripzone_SW_event();
    pull_up_relay();
    status=handled_inverter;
    return status;
}
inverter_state_machine_event_staus start_control_grid_not_ok()
{
    start_control_grid_not_ok_flag++;
    inverter_state_machine_event_staus status;
    status=transition_inverter;
    inverter_state.inverter_state=NOT_READY;
    return status;
}

inverter_state_machine_event_staus NOT_ready_events()
{
    NOT_ready_events_flag++;
    inverter_state_machine_event_staus status=handled_inverter;
    if(Grid_OK==1)
    {
        status=state_table_inveter[inverter_state.inverter_state][GRID_OK_INVERTER]();
    }
    return status;
}
inverter_state_machine_event_staus checks_and_initial_condition_events()
{
    checks_and_initial_condition_events_flag++;
    inverter_state_machine_event_staus status=handled_inverter;
    if(Grid_OK!=1)
    {
        status=state_table_inveter[inverter_state.inverter_state][GRID_NOT_OK]();
        return status;
    }
    if(V_DC_OK())
    {
        status=state_table_inveter[inverter_state.inverter_state][VDC_OK]();
        return status;
    }
    return status;
}

inverter_state_machine_event_staus start_control_events()
{
    start_control_events_flag++;
    inverter_state_machine_event_staus status=handled_inverter;
    if(Grid_OK!=1)
    {
        status=state_table_inveter[inverter_state.inverter_state][GRID_NOT_OK]();
        return status;
    }
    return status;

}
Uint32 V_DC_OK(void)
{
    if(VDC>0.9*rtY.Ugrid_peak)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void setting_initial_condition()
{

    current_controller_AC_code_generation_initialize(rtY.UgridID);
    //voltage_controller_initialization should be here;
    voltage_controller_code_generation_initialize(VDC);
    //boost_code_generation_initialize();
    //buck_code_generation_initialize();

}
