/*
 * ADC.c
 *
 *  Created on: 2016 márc. 20
 *      Author: Szako
 *
 *  Modified by: AFU, 2016.mar.30.
 */


#include "ADC.h"
#include <stddef.h>
#include "usefulmacros.h"
void ADC_Init(void)
{
  // Configure ADC
  EALLOW;
  AdcRegs.ADCCTL1.bit.ADCBGPWD  = 1;      // Power ADC BG
  AdcRegs.ADCCTL1.bit.ADCREFPWD = 1;      // Power reference
  AdcRegs.ADCCTL1.bit.ADCPWDN   = 1;      // Power ADC
  AdcRegs.ADCCTL1.bit.ADCENABLE = 1;      // Enable ADC
  AdcRegs.ADCCTL1.bit.ADCREFSEL = 0;      // Select interal BG
  EDIS;

  DELAY_US(ADC_usDELAY);         // Delay before converting ADC channels

  EALLOW;
  AdcRegs.ADCCTL2.bit.CLKDIV2EN = 1;                                                        // why not using same clock frequency
  EDIS;

  DELAY_US(ADC_usDELAY);         // Delay before converting ADC channels

  EALLOW;

  AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 1;   // Enable non-overlap mode                           // what is the overlab?
  AdcRegs.ADCCTL1.bit.INTPULSEPOS  = 1;    // ADCINT1 trips after AdcResults latch
  AdcRegs.INTSEL1N2.bit.INT1E     = 1;     // Enabled ADCINT1
  AdcRegs.INTSEL1N2.bit.INT1CONT  = 0;     // Disable ADCINT1 Continuous mode
  AdcRegs.INTSEL1N2.bit.INT1SEL   = 0x03;  // setup EOC06 to trigger ADCINT1 to fire            //i changed it to 6 because we measure 7 channels(0 to 6)
  AdcRegs.ADCSOC0CTL.bit.CHSEL   = 1;      // I AC
  AdcRegs.ADCSOC1CTL.bit.CHSEL   = 3;      // I AC offset
  AdcRegs.ADCSOC2CTL.bit.CHSEL   = 5;      // I DC
  AdcRegs.ADCSOC3CTL.bit.CHSEL   = 4;      // I DC offset
  AdcRegs.ADCSOC4CTL.bit.CHSEL   = 0;      // V AC
  AdcRegs.ADCSOC5CTL.bit.CHSEL   = 2;      // V DC internal
  AdcRegs.ADCSOC6CTL.bit.CHSEL   = 6;      // V buck (capacitor voltage)
  //AdcRegs.ADCSOC7CTL.bit.CHSEL   = 7;      // set SOC7 channel select to ADCINA7  (unused)
//due to round-robin SOC0 converts first then SOC1
  AdcRegs.ADCSOC0CTL.bit.TRIGSEL   = 0x05;  // set SOC0 start trigger on EPWM4A         set SOC0 start trigger on EPWM1A
  AdcRegs.ADCSOC1CTL.bit.TRIGSEL   = 0x05;  // set SOC1 to software only trigger        set SOC0 start trigger on EPWM1A
  AdcRegs.ADCSOC2CTL.bit.TRIGSEL   = 0x05;  // set SOC2 to software only trigger        set SOC0 start trigger on EPWM1A
  AdcRegs.ADCSOC3CTL.bit.TRIGSEL   = 0x05;  // set SOC3 to software only trigger        set SOC0 start trigger on EPWM1A
  AdcRegs.ADCSOC4CTL.bit.TRIGSEL   = 0x05;  // set SOC4 to software only trigger        set SOC0 start trigger on EPWM1A
  AdcRegs.ADCSOC5CTL.bit.TRIGSEL   = 0x05;  // set SOC5 to software only trigger        set SOC0 start trigger on EPWM1A
  AdcRegs.ADCSOC6CTL.bit.TRIGSEL   = 0x05;  // set SOC6 to software only trigger        set SOC0 start trigger on EPWM1A
  //AdcRegs.ADCSOC7CTL.bit.TRIGSEL   = 0x00;  // set SOC7 to software only trigger
  AdcRegs.ADCSOC0CTL.bit.ACQPS   = 6;  // set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
  AdcRegs.ADCSOC1CTL.bit.ACQPS   = 6;  // set SOC1 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
  AdcRegs.ADCSOC2CTL.bit.ACQPS   = 6;  // set SOC2 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
  AdcRegs.ADCSOC3CTL.bit.ACQPS   = 6;  // set SOC3 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
  AdcRegs.ADCSOC4CTL.bit.ACQPS   = 6;  // set SOC4 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
  AdcRegs.ADCSOC5CTL.bit.ACQPS   = 6;  // set SOC5 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
  AdcRegs.ADCSOC6CTL.bit.ACQPS   = 6;  // set SOC6 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
  AdcRegs.ADCSOC7CTL.bit.ACQPS   = 6;  // set SOC7 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
  AdcRegs.ADCSOC8CTL.bit.ACQPS   = 6;  // set SOC8 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)


}
fprt_g adc_fptr=NULL;

 void adc_isr_assign_function(fprt_g fptr_recieved)
{
    adc_fptr=fptr_recieved;
}
Uint32 ConversionCount;

#pragma CODE_SECTION(adc_isr, "ramfuncs");
__interrupt void  adc_isr(void)
{
    ConversionCount++;
    GpioDataRegs.GPACLEAR.bit.GPIO23 = 1;  // uncomment if --> Set Low initially
    if(adc_fptr!=NULL)
    {
        adc_fptr();
    }
    bbx_trigger();

    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;       //Clear ADCINT1 flag reinitialize for next SOC
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE
    return;
}

