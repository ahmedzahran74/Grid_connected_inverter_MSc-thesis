/*
 * interrupt_functions.c
 *
 *  Created on: May 2, 2024
 *      Author: RTX
 */
float Iac, V3V3A_for_IAC,IDC,V3V3A_for_IDC,VAC,VDC,VDC_buck;
float V_err;
float vpeak_ID;
#include"interrupt_functions.h"
float current_phase_shift=0;
#pragma CODE_SECTION(adc_isr_PLL_init, "ramfuncs");
void adc_isr_PLL_init (void)
{
    VAC=(((float)(AdcResult.ADCRESULT4)*(3.3/4095))-1.65)*(266.67/5.0);
}
#pragma CODE_SECTION(adc_isr_PLL_start, "ramfuncs");

void adc_isr_PLL_start (void)
{
    VAC=(((float)(AdcResult.ADCRESULT4)*(3.3/4095))-1.65)*(266.67/5.0);
    VDC=(((float)(AdcResult.ADCRESULT5)*(3.3/4095)*((91.0+3.3)/3.3)));
    //set the input structure
    rRU.W_id=rtY.Wid;
    //call the RHO step function
    RHO_code_generation_step();
    //get the PLL output here
}
Uint32 current_controller_begin,current_controller_end,adc_isr_PLL_start_control_flag;

#pragma CODE_SECTION(adc_isr_PLL_start_control, "ramfuncs");

void adc_isr_PLL_start_control (void)
{
    adc_isr_PLL_start_control_flag++;
    current_controller_begin=EPwm1Regs.TBCTR;
    V3V3A_for_IAC = (float)(AdcResult.ADCRESULT1) * (3.3/ 4095 * ((3.3+1.8) / 3.3));
    Iac = (((float)AdcResult.ADCRESULT0 * 3.3/ 4095 - V3V3A_for_IAC / 2.0) / 0.11);
    V3V3A_for_IDC=(float)(AdcResult.ADCRESULT3) * (3.3/ 4095 * ((3.3+1.8) / 3.3));
    IDC =((((float)(AdcResult.ADCRESULT2))*(3.3/ 4095)-(V3V3A_for_IDC/2))/0.055);
    VDC=(((float)(AdcResult.ADCRESULT5)*(3.3/4095)*((91.0+3.3)/3.3)));
    VDC_buck=(((float)(AdcResult.ADCRESULT6)*3.3/4095)*((47.0+3.0)/3.0));
     //set the input structure
     rRU.W_id=rtY.Wid;
     //rRU.W_id=314.15926535;
     //call the RHO step function
     RHO_code_generation_step();
     //get RHO outputs here
     //rtU_C_C.reference_current_C_C=1.5;
     /*rtU_C_C.U_DC_C_C=VDC;
     rtU_C_C.inductor_current_C_C=Iac;

     rtU_C_C.sin_value_C_C=rRY.sinRHO;
     rtU_C_C.cos_value_C_C=rRY.cosRHO;
     current_controller_AC_code_generation_step();
     epwm1_set_CMPA(rtY_C_C.CMP1A_C_C);
     epwm2_set_CMPA(rtY_C_C.CMP2A_C_C);
     */
     /*
     rtU_m.sin_value=rRY.sinRHO;
     rtU_m.UDC=VDC;
     current_controller_code_generation_step();
     epwm1_set_CMPA(rtY_h.CMP1A);
     epwm2_set_CMPA(rtY_h.CMP2A);
*/
     rtU_C_C.U_DC_C_C=VDC;
     rtU_C_C.inductor_current_C_C=Iac;
     //rtU_C_C.sin_value_C_C=rRY.sinRHO;
     //rtU_C_C.cos_value_C_C=rRY.cosRHO;
     sincos(rRY.RHO+current_phase_shift,&(rtU_C_C.sin_value_C_C),&(rtU_C_C.cos_value_C_C));
     current_controller_AC_code_generation_step();
     epwm1_set_CMPA(rtY_C_C.CMP1A_C_C);
     epwm2_set_CMPA(rtY_C_C.CMP2A_C_C);
     current_controller_end=EPwm1Regs.TBCTR;

     //current controllers are executed here
     /*
     rtU_boost.V_op_boost=VDC;
     rtU_boost.IL_boost=IDC;

     boost_code_generation_step();
     epwm8_set_CMPB(rtY_boost.CMP_B_boost);
     */


   /* rtU_buck.V_high_buck=VDC;
    rtU_buck.V_ref_buck=VDC_buck;
    rtU_buck.IL_buck=IDC;
    buck_code_generation_step();
    epwm8_set_CMPA(rtY_buck.CMPA_buck);
    */

}
#pragma CODE_SECTION(epwm4_isr_100us_PLL_init, "ramfuncs");

void epwm4_isr_100us_PLL_init (void)
{
    //do nothing
}
#pragma CODE_SECTION(epwm4_isr_100us_PLL_start, "ramfuncs");

void epwm4_isr_100us_PLL_start (void)
{

    // do nothing
}
Uint32 VDC_counter;
#pragma CODE_SECTION(epwm4_isr_100us_PLL_start_control, "ramfuncs");

void epwm4_isr_100us_PLL_start_control(void)
{
    // voltage controllers
    VDC_counter++;
    VAC=(((float)(AdcResult.ADCRESULT4)*(3.3/4095))-1.65)*(266.67/5.0);
    VDC=(((float)(AdcResult.ADCRESULT5)*(3.3/4095)*((91.0+3.3)/3.3)));

//    rtU_V_C.V_DC_V_C=VDC;
//    voltage_controller_code_generation_step();

    //set the input of the voltage_controller
    rtU_V_C.V_DC_V_C=VDC;
    //call the voltage_controller_step_function
    voltage_controller_code_generation_step();
    //update_I ref of the current_controller here
    //rtU_C_C.reference_current_C_C=rtY_V_C.I_peak_ref_V_C;

}
#pragma CODE_SECTION(epwm4_isr_100us_DC_voltage_check, "ramfuncs");

void epwm4_isr_100us_DC_voltage_check (void)
{
    VDC=(((float)(AdcResult.ADCRESULT5)*(3.3/4095)*((91.0+3.3)/3.3)));
}
#pragma CODE_SECTION(cpu_timer1_PLL_init, "ramfuncs");

void cpu_timer1_PLL_init (void)
{
    //do nothing
    //VAC=(((float)(AdcResult.ADCRESULT4)*(3.3/4095))-1.65)*(266.67/5.0);

}
#pragma CODE_SECTION(cpu_timer1_PLL_start, "ramfuncs");

void cpu_timer1_PLL_start (void)
{
    VAC=(((float)(AdcResult.ADCRESULT4)*(3.3/4095))-1.65)*(266.67/5.0);
    //update the input structure
    rtU.grid_voltage=VAC;
    //rtU.sinRHO=rRY.sinRHO;
    //rtU.cosRHO=rRY.cosRHO;
    sincos(rRY.RHO,&(rtU.sinRHO),&(rtU.cosRHO));
    //call the PLL step function
    PLL_controller_step();
    //get the output here
    V_err=rtY.UgridID-VAC;
}
#pragma CODE_SECTION(cpu_timer1_PLL_start_control, "ramfuncs");

void cpu_timer1_PLL_start_control(void)
{
    VAC=(((float)(AdcResult.ADCRESULT4)*(3.3/4095))-1.65)*(266.67/5.0);
    //update the input structure
    rtU.grid_voltage=VAC;
    //rtU.sinRHO=rRY.sinRHO;
    //rtU.cosRHO=rRY.cosRHO;
    sincos(rRY.RHO,&(rtU.sinRHO),&(rtU.cosRHO));
    //call the PLL step function
    PLL_controller_step();
    //get the output here
    V_err=rtY.UgridID-VAC;
}


