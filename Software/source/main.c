#include "F2806x_Device.h"
#include "inic.h"
#include "bbx.h"
#include "HiMon.h"
#include "Term_defs.h"
#include "C28x_FPU_FastRTS.h"
#include "ADC.h"
#include "CLA_shared.h"
#include "CLA.h"
#include "PLL_controller.h"
#include "RHO_code_generation.h"
#include "usefulmacros.h"
#include <stddef.h>
#include "main.h"
#include "state_machines.h"

//////////VCO constant////////////
#define PI          (3.14F)
#define RHO_MIN     (0.0F)
#define RHO_MAX     (2*PI)
#define TS          (1/(75*10e3))/2         //half the periodic time of the triangular wave


/* Timer variables for 10ms 100ms and 1s tasks */
Uint16 sw_timer_1ms;
Uint16 sw_timer_10ms;
Uint16 sw_timer_100ms;
Uint16 sw_timer_1s;
Uint16 start_time;

Uint16 time_10ms;
Uint16 time_100ms;
Uint16 time_1000ms;

/* Variables for task runtime measurements */
Uint16 t10ms, t100ms;


//Uint16 emode, ecim, eadat;

uint16_t error_code = 0;

void ISR_ILLEGAL(void);
void error(Uint16 e_code);

//###########################################################################
// CLA ISRs: run when a specific task is finished.
//###########################################################################
Uint32 CLA_IT_CNT = 0;
__interrupt void cla1_task1_isr( void)
{
    //when this interrupt is started, adc_isr is already finished.
    CLA_IT_CNT++;



    AdcRegs.ADCINTFLGCLR.bit.ADCINT2 = 1;     //Clear ADCINT2 flag reinitialize for next SOC
    PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

__interrupt void cla1_task2_isr( void)
{
    PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

__interrupt void cla1_task3_isr( void)
{
    PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

__interrupt void cla1_task4_isr( void)
{
    PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

__interrupt void cla1_task5_isr( void)
{
    PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

__interrupt void cla1_task6_isr( void)
{
    PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

__interrupt void cla1_task7_isr( void)
{
    PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

__interrupt void cla1_task8_isr( void)
{
    Cla1ToCpuMsgRAM_cleared = 2;        //test interrupt after RAM cleared
    PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

//###########################################################################
// CPU ADC ISR: starts immediately on ADCINT1, at the same time as Cla1Task1!
//###########################################################################
Uint16 cpu_timer_interrupt_running = 0;
/////////////////////////////////////////////////////
fprt_g cpu_timer1_fptr=NULL;
void cpu_timer1_assign_function(fprt_g fptr_recieved)
{
    cpu_timer1_fptr=fptr_recieved;
}
#pragma CODE_SECTION(cpu_timer1_isr, "ramfuncs");
__interrupt void cpu_timer1_isr(void)				//1ms timer interrupt
{
    IER = M_INT1 | M_INT3 | M_INT11; //enable INT1 (group 1.x, ADC), enable INT11 (CLA)     // Set global priority by adjusting IER
    CpuTimer1Regs.TCR.bit.TIF = 1;  //clear interrupt flag. If the flag is 1 while "cpu_timer_interrupt_running", that means that the 1ms task has not been finished within 1ms.
    cpu_timer_interrupt_running = 1;

    EnableInterrupts();
    //Begin actual interrupt
    if(cpu_timer1_fptr!=NULL)
    {
        cpu_timer1_fptr();
    }

    sw_timer_1ms++;
    // Restore original state:
    cpu_timer_interrupt_running = 0;
    DINT;
    //IER does not need to be restored, as it was automatically saved on stack by HW.
}

                                                              ///////VCO implementation/////////
                                                       ////////////////////////////////////////////
/*VCO_EPWM_Compare_Reg_Modify(float Sin_value,volatile struct EPWM_REGS *EPwmxRegs)
{
    REG_A_Value=(Uint16)((1+Sin_Value)*532);
    REG_B_Value=(Uint16)(1-Sin_Value)*532;
    EPwmxRegs->CMPA=REG_A_Value;
    EPwmxRegs->CMPB=REG_B_Value;

}*/


/*Uint32 sw_timer_100us;
#pragma CODE_SECTION(epwm_isr, "ramfuncs");
__interrupt void  epwm4_isr_100us(void)
{
    IER = M_INT1 | M_INT3 | M_INT11; //enable INT1 (group 1.x, ADC), enable INT11 (CLA)     // Set global priority by adjusting IER

    EnableInterrupts();
    //Begin actual interrupt
    sw_timer_100us++;

    VAC=(((float)(AdcResult.ADCRESULT4)*(3.3/4095))-1.65)*(266.67/5.0);
    VDC=(((float)(AdcResult.ADCRESULT5)*(3.3/4095)*((91.0+3.3)/3.3)));

    VDC_buck=(((float)(AdcResult.ADCRESULT6)*3.3/4095)*((47.0+3.0)/3.0));

    //Clears the ETFLG[INT] flag bit and enable further interrupts pulses to be generated
    EPwm4Regs.ETCLR.bit.INT=1;

    DINT;
     //IER does not need to be restored, as it was automatically saved on stack by HW.
}*/
/*#pragma CODE_SECTION(adc_isr, "ramfuncs");
__interrupt void  adc_isr(void)
{
    // Debug functions
    ConversionCount++;
    GpioDataRegs.GPACLEAR.bit.GPIO23 = 1;  // uncomment if --> Set Low initially
    V3V3A_for_IAC = (float)(AdcResult.ADCRESULT1) * (3.3/ 4095 * ((3.3+1.8) / 3.3));
    Iac = (((float)AdcResult.ADCRESULT0 * 3.3/ 4095 - V3V3A_for_IAC / 2.0) / 0.11);  /////////////////////////////////////////////////
    V3V3A_for_IDC=(float)(AdcResult.ADCRESULT3) * (3.3/ 4095 * ((3.3+1.8) / 3.3));
    IDC =((((float)(AdcResult.ADCRESULT2))*(3.3/ 4095)-(V3V3A_for_IDC/2))/0.055);
   //set the input structure
   rRU.W_id=rtY.Wid;
   //call the RHO step function
   RHO_code_generation_step();
   //get the PLL output

   bbx_trigger();

    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;		//Clear ADCINT1 flag reinitialize for next SOC
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE
    //asm("NOP");
    return;
}*/


interrupt void ISR_ILLEGAL(void)   // Illegal operation TRAP
{
    // Insert ISR Code here

    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    asm("          ESTOP0");
    for(;;);
}

Uint16 back_ground_counter;
void main(void) {
    EALLOW;
    DeviceInit();	// Device Life support & GPIO mux settings
    inverter_state_machine_init();
    state_machine_init_inverter();
    epwm5_isr_assign_function(state_machines);
    inverter_enable_tripzone_SW_event();
    // Enable ADCINT1 in PIE
    IER |= M_INT1; 						// Enable CPU Interrupt 1
    IER |= M_INT13; 					// Enable CPU Interrupt 13
    IER|=M_INT3;                        ///////////////////////////////////////added for the PWM interrupt
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;	// Enable INT 1.1 in the PIE
    PieCtrlRegs.PIEIER3.bit.INTx4 = 1;  ///////////////////////////////////////added for the PWM interrupt I  NT3.4 51 0x0000 0D66 2 EPWM4_INT (EPWM4)
    PieCtrlRegs.PIEIER3.bit.INTx5 = 1;  ///////////////////////////////////////added for the PWM interrupt I  NT3.5 51 0x0000 0D66 2 EPWM5_INT (EPWM5)
    //PieCtrlRegs.PIEIER1.bit.INTx7 = 1;	// Enable TINT0 in the PIE: Group 1 interrupt 7

    GpioDataRegs.GPBCLEAR.bit.GPIO51=1;

//    EINT;          						// Enable Global interrupt INTM
//    ERTM;          						// Enable Global realtime interrupt DBGM

    InitTermVars();


    for(;;)
    {
        back_ground_counter++;
        if(!back_ground_counter) GpioDataRegs.GPBTOGGLE.bit.GPIO51 = 1;

        Serial_mng();
        bbx_background();
        if ((signed)(sw_timer_1ms-time_10ms) > 0)
        {
            time_10ms = sw_timer_1ms + 10 - 1;	// megengedjuk, hogy csusszon a 10ms -os taszk -1, hogy tényleg 10ms-onként fusson, ha nem csúszik.
            start_time = sw_timer_1ms;
            sw_timer_10ms++;
            /* Start of 10ms task */

            /* End of 10ms task */
            t10ms = sw_timer_1ms - start_time;
        }
        else if ((signed)(sw_timer_1ms-time_100ms) > 0)
        {
            time_100ms = sw_timer_1ms + 100 - 1;	// megengedjuk, hogy csusszon a 100ms -os taszk -1, hogy tényleg 100ms-onként fusson, ha nem csúszik.
            start_time = sw_timer_1ms;
            sw_timer_100ms++;
            /* Start of 100ms task */

            /* End of 100ms task */
            t100ms = sw_timer_1ms - start_time;
        }
        else if ((signed)(sw_timer_1ms-time_1000ms) > 0)
        {
            sw_timer_1s++;
            time_1000ms += 1000;
            /* Start of 1s task */

            /* End of 1s task */
        }
    }
}


