/*
 * PWM.c
 *
 *  Created on: 2016 márc. 13
 *      Author: Szako
 */

#include "PWM.h"
#include "usefulmacros.h"
#include <stddef.h>
//#include <studio>
#define BOOST
void PWM_Init(void)
{
  PWM_Init_Clocks();


  PWM_Init_Master();           //1. Half bridge EPWM1
  PWM_Init_Slave(&EPwm2Regs);  //2. Half bridge EPWM2
  PWM_Init_Slave_2();//DCDC     //EPWM8
  inverter_enable_tripzone_SW_event();
  PWM_Init_4();    //EPWM4 for 10kHz IT generation
  PWM_Init_5();    //EPWM3 for 1kHz IT generation
  //PWM_VCO_Identifier(&EPwm3Regs);
  //PWM_Init_Slave(&EPwm3Regs);  //
  //PWM_Init_Slave_ADC_trig(&EPwm4Regs);  //ADC mintavételezés
//  PWM_Init_I_AC_Error(&EPwm5Regs);
//  PWM_Init_I_DC_Error(&EPwm6Regs);
//  PWM_Init_U_Error(&EPwm7Regs);
// PWM_Init_GPIOs();
}

void PWM_Init_Clocks(void)
{
  SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;  // ePWM1
  SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;  // ePWM2
  SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 1;  // ePWM3
  SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = 1;  // ePWM4
  SysCtrlRegs.PCLKCR1.bit.EPWM5ENCLK = 1;  // ePWM5
  SysCtrlRegs.PCLKCR1.bit.EPWM6ENCLK = 1;  // ePWM6
  SysCtrlRegs.PCLKCR1.bit.EPWM7ENCLK = 1;  // ePWM7
  SysCtrlRegs.PCLKCR1.bit.EPWM8ENCLK = 1;  // ePWM8
  SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;   // Enable TBCLK
}

void PWM_Init_GPIOs(void)
{
  EALLOW;
  //--------------------------------------------------------------------------------------
  //  GPIO-00 - PIN FUNCTION = --EPWM1A--
  GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;     // 0=GPIO, 1=EPWM1A, 2=Reserved, 3=Reserved
  //GpioCtrlRegs.GPADIR.bit.GPIO0 = 0;    // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;  // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO0 = 1;    // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-01 - PIN FUNCTION = --EPWM1B--
  GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;     // 0=GPIO, 1=EPWM1B, 2=Reserved, 3=COMP1OUT
  //GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;    // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;  // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO1 = 1;    // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-02 - PIN FUNCTION = --EPWM2A--
  GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;     // 0=GPIO, 1=EPWM2A, 2=Reserved, 3=Reserved
  //GpioCtrlRegs.GPADIR.bit.GPIO2 = 0;    // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;  // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO2 = 1;    // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-03 - PIN FUNCTION = --EPWM2B--
  GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;     // 0=GPIO, 1=EPWM2B, 2=SPISOMIA, 3=COMP2OUT
  //GpioCtrlRegs.GPADIR.bit.GPIO3 = 0;    // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;  // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO3 = 1;    // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-04 - PIN FUNCTION = --EPWM3A--
  GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;     // 0=GPIO, 1=EPWM3A, 2=Reserved, 3=Reserved
  //GpioCtrlRegs.GPADIR.bit.GPIO4 = 0;    // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;  // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO4 = 1;    // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-05 - PIN FUNCTION = --EPWM3B--
  GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;     // 0=GPIO, 1=EPWM3B, 2=SPISIMOA, 3=ECAP1
  //GpioCtrlRegs.GPADIR.bit.GPIO5 = 0;    // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;  // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO5 = 1;    // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-06 - PIN FUNCTION = --EPWM4A--
  //GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;     // 0=GPIO, 1=EPWM4A, 2=EPWMSYNCI, 3=EPWMSYNCO
  //GpioCtrlRegs.GPADIR.bit.GPIO6 = 0;    // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;  // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO6 = 1;    // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-07 - PIN FUNCTION = --EPWM4B--
  //GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;     // 0=GPIO, 1=EPWM4B, 2=SCIRXDA, 3=ECAP2
  //GpioCtrlRegs.GPADIR.bit.GPIO7 = 0;    // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;  // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO7 = 1;    // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-50 - PIN FUNCTION = --#TZ1--
  //GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 3;    // 0=GPIO, 1=EQEP1A, 2=MDXA, 3=#TZ1
  //GpioCtrlRegs.GPBDIR.bit.GPIO50 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO50 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPBSET.bit.GPIO50 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  EDIS;
}

void PWM_Init_Master(void)
{
  EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // count updown
  EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;         // Master module
  EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
  EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;     // Sync down-stream module
  EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;        //TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
  EPwm1Regs.TBCTL.bit.CLKDIV =TB_DIV1;            //TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
  EPwm1Regs.ETSEL.bit.SOCAEN = 1;                 //enable SOC on A group
  EPwm1Regs.ETSEL.bit.SOCASEL=ET_CTR_PRDZERO;     //SOC Enable event time-base counter equal to zero or period
  EPwm1Regs.ETPS.bit.SOCAPRD = 1;                 // Generate pulse on 1st event
//  EPwm1Regs.ETSEL.bit.INTEN = 1;                 //enable interrupt
//    EPwm1Regs.ETSEL.bit.INTSEL=ET_CTR_PRDZERO;     //interrupt event time-base counter equal to zero or period
//  EPwm1Regs.ETPS.bit.INTPRD = 1;
  EPwm1Regs.CMPA.half.CMPA = 100;                   // Set compare A value                    // changed from 1 to 100
  EPwm1Regs.TBPRD = 800;                         // Set period for ePWM1 (75kHz)
  //Counter Compare
  EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
  EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
  EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
  //Action Qualifier
  EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWM1A
  EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
  //EPwm1Regs.AQCTLB.bit.CAU = AQ_SET; // set actions for EPWM1B
  //EPwm1Regs.AQCTLB.bit.CAD = AQ_CLEAR;
  EPwm1Regs.AQSFRC.bit.RLDCSF = 2 ; // Load AQCSFRC on event CTR = Zero or PRD
  // Dead-Band generator
  EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL; // A rising edge delay
  EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // Dead Band Mode Control
  EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; // Polarity Select Control: high active output
  EPwm1Regs.DBRED = 16; // Dead-band rising edge delay DBT_PERIOD 1 step = 12.5ns @ TBCLK = 80MHz
  EPwm1Regs.DBFED = 16; // Dead-band falling edge delay DBT_PERIOD 1 step = 12.5s @ TBCLK = 80MHz
  EPwm1Regs.TZSEL.bit.OSHT1 = TZ_ENABLE;//TZ_ENABLE;
  EPwm1Regs.TZSEL.bit.OSHT2 = TZ_ENABLE;
  EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_LO;
  EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO;
  EPwm1Regs.TZFRC.bit.OST = TZ_ENABLE;//TZ_ENABLE;
  EALLOW;
  EDIS;
}


void PWM_Init_Slave(volatile struct EPWM_REGS *EPwmxRegs)
{
  EPwmxRegs->TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // count updown
  EPwmxRegs->TBCTL.bit.PHSEN = TB_ENABLE;          // Slave module
  EPwmxRegs->TBPHS.half.TBPHS=0;                   //modified!
  EPwmxRegs->TBCTL.bit.PRDLD = TB_SHADOW;
  EPwmxRegs->TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // Sync down-stream module
  EPwmxRegs->TBCTL.bit.HSPCLKDIV = TB_DIV1;        //TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
  EPwmxRegs->TBCTL.bit.CLKDIV =TB_DIV1;            //TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
  //EPwmxRegs->ETSEL.bit.SOCAEN = 0;                 // Enable SOC on A group                       //ADC(later)
  //EPwmxRegs->ETSEL.bit.SOCASEL = ET_CTRU_CMPA;     // Select SOC from CMPA on upcount
  //EPwmxRegs->ETPS.bit.SOCAPRD = 1;                 // Generate pulse on 1st event
  EPwmxRegs->CMPA.half.CMPA = 100;                   // Set compare A value
  EPwmxRegs->TBPRD = 800;                         // Set period for ePWM1 (75kHz)
  //Counter Compare
  EPwmxRegs->CMPCTL.bit.SHDWAMODE = CC_SHADOW;
  EPwmxRegs->CMPCTL.bit.SHDWBMODE = CC_SHADOW;
  EPwmxRegs->CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
  //Action Qualifier
  EPwmxRegs->AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWMxAAQ_SET
  EPwmxRegs->AQCTLA.bit.CAD = AQ_SET;
  //EPwmxRegs->AQCTLB.bit.CAU = AQ_SET; // set actions for EPWM1B
  //EPwmxRegs->AQCTLB.bit.CAD = AQ_CLEAR;
  EPwmxRegs->AQSFRC.bit.RLDCSF = 2 ; // Load AQCSFRC on event CTR = Zero or PRD
  // Dead-Band generator
  EPwmxRegs->DBCTL.bit.IN_MODE = DBA_ALL; // A rising edge delay
  EPwmxRegs->DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // Dead Band Mode Control
  EPwmxRegs->DBCTL.bit.POLSEL = DB_ACTV_HIC; // Polarity Select Control: high active output
  // Setup DeadTime
  EPwmxRegs->DBRED = 16; // Rising edge delay DBT_PERIOD 1 step = 12.5ns @ TBCLK = 80MHz
  EPwmxRegs->DBFED = 16; // Falling edge delay DBT_PERIOD 1 step = 12.5ns @ TBCLK = 80MHz

  EPwmxRegs->TZSEL.bit.OSHT1 = TZ_ENABLE;
  EPwmxRegs->TZSEL.bit.OSHT2 = TZ_ENABLE;
//  EPwmxRegs->TZSEL.bit.DCAEVT1 = TZ_ENABLE;
  EPwmxRegs->TZCTL.bit.TZA = TZ_FORCE_LO;
  EPwmxRegs->TZCTL.bit.TZB = TZ_FORCE_LO;
  EPwmxRegs->TZFRC.bit.OST = TZ_ENABLE;
  //EPwmxRegs->TZFRC.bit.OST = TZ_ENABLE;

  //TZ3 trükközés DC submodul-al
  EALLOW;
//  EPwmxRegs->TZEINT.bit.OST = TZ_ENABLE;
//  EPwmxRegs->DCTRIPSEL.bit.DCAHCOMPSEL = 0x2; //TZ3 bemenet
//  EPwmxRegs->TZDCSEL.bit.DCAEVT1 = TZ_DCAH_HI; //HIGH = 1 LOW = DONT CARE
//  EPwmxRegs->DCTRIPSEL.bit.DCBHCOMPSEL = 0x2; //TZ3 bemenet
//  EPwmxRegs->TZDCSEL.bit.DCBEVT1 = TZ_DCBH_HI; //HIGH = 1 LOW = DONT CARE
////  EPwmxRegs->DCACTL.bit.EVT1SRCSEL = 0;
////  EPwmxRegs->DCACTL.bit.EVT1FRCSYNCSEL = 1;
////  EPwmxRegs->DCBCTL.bit.EVT1SRCSEL = 0;
////  EPwmxRegs->DCBCTL.bit.EVT1FRCSYNCSEL = 1;
//  EPwmxRegs->TZSEL.bit.DCAEVT1 = 1;
//  EPwmxRegs->TZSEL.bit.DCBEVT1 = 1;
  EDIS;
}
                                                    /////////////////////////////////////////
/*void PWM_VCO_Identifier(volatile struct EPWM_REGS *EPwmxRegs)
{
    EPwmxRegs->TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwmxRegs->TBCTL.bit.PHSEN = TB_ENABLE;          // Slave module
    EPwmxRegs->TBPHS.half.TBPHS=0;
    EPwmxRegs->CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwmxRegs->TBCTL.bit.HSPCLKDIV = TB_DIV1;           //TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
    EPwmxRegs->TBCTL.bit.CLKDIV =TB_DIV1;               //TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
    EPwmxRegs->CMPA.half.CMPA = 0;                      // Set compare A value
    EPwmxRegs->CMPB = 0;                                // Set compare B value
    EPwmxRegs->TBPRD = 532;
    EPwmxRegs->CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwmxRegs->CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwmxRegs->CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
    EPwmxRegs->AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWMxAAQ_SET
    EPwmxRegs->AQCTLA.bit.CAD = AQ_SET;
    EPwmxRegs->AQCTLB.bit.CAU = AQ_CLEAR; // set actions for EPWM1B
    EPwmxRegs->AQCTLB.bit.CAD = AQ_SET;
    // Dead-Band generator
    EPwmxRegs->DBCTL.bit.OUT_MODE = DB_DISABLE; // Dead Band Mode Control

}*/
void PWM_Init_Slave_2(void)
{
      EPwm8Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // count updown
      EPwm8Regs.TBCTL.bit.PHSEN = TB_ENABLE;          // Slave module
      EPwm8Regs.TBPHS.half.TBPHS=0;                   //modified!
      EPwm8Regs.TBCTL.bit.PRDLD = TB_SHADOW;
      EPwm8Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // Sync down-stream module
      EPwm8Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;        //TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
      EPwm8Regs.TBCTL.bit.CLKDIV =TB_DIV1;            //TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
      //EPwmxRegs->ETSEL.bit.SOCAEN = 0;                 // Enable SOC on A group
      //EPwmxRegs->ETSEL.bit.SOCASEL = ET_CTRU_CMPA;     // Select SOC from CMPA on upcount
      //EPwmxRegs->ETPS.bit.SOCAPRD = 1;                 // Generate pulse on 1st event
#ifdef BOOST
      EPwm8Regs.CMPA.half.CMPA = 100;                   // Set compare A value
      EPwm8Regs.CMPB=0;
#elif defined(BUCK)
      EPwm8Regs.CMPA.half.CMPA = 0;                   // Set compare A value
      EPwm8Regs.CMPB=0;
#endif
      EPwm8Regs.TBPRD = 800;                         // Set period for ePWM1 (50kHz)
      //Counter Compare
      EPwm8Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
      EPwm8Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
      EPwm8Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
      //Action Qualifier
      EPwm8Regs.AQCTLA.bit.CAU = AQ_CLEAR; // set actions for EPWMxAAQ_SET
      EPwm8Regs.AQCTLA.bit.CAD = AQ_SET;

      EPwm8Regs.AQCTLB.bit.CBU=AQ_CLEAR;                                            //added_for_buck
      EPwm8Regs.AQCTLB.bit.CBD=AQ_CLEAR;                                            //added_for_buck

      //EPwmxRegs->AQCTLB.bit.CAU = AQ_SET; // set actions for EPWM1B
      //EPwmxRegs->AQCTLB.bit.CAD = AQ_CLEAR;
      EPwm8Regs.AQSFRC.bit.RLDCSF = 2 ; // Load AQCSFRC on event CTR = Zero or PRD
      // Dead-Band generator
      EPwm8Regs.DBCTL.bit.IN_MODE = DBA_ALL; // A rising edge delay
#ifdef BOOST
      EPwm8Regs.DBCTL.bit.OUT_MODE = DB_DISABLE; // Dead Band Mode Control
#elif defined(BUCK)
      EPwm8Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
#endif
      EPwm8Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; // Polarity Select Control: high active output
      // Setup DeadTime
      EPwm8Regs.DBRED = 16; // Rising edge delay DBT_PERIOD 1 step = 12.5ns @ TBCLK = 80MHz
      EPwm8Regs.DBFED = 16; // Falling edge delay DBT_PERIOD 1 step = 12.5ns @ TBCLK = 80MHz

      EPwm8Regs.TZSEL.bit.OSHT1 = TZ_ENABLE;
      EPwm8Regs.TZSEL.bit.OSHT2 = TZ_ENABLE;
    //  EPwmxRegs->TZSEL.bit.DCAEVT1 = TZ_ENABLE;
      EPwm8Regs.TZCTL.bit.TZA = TZ_FORCE_LO;
      EPwm8Regs.TZCTL.bit.TZB = TZ_FORCE_LO;
      EPwm8Regs.TZFRC.bit.OST = TZ_ENABLE;
}

//the following function is used to configure an interrupt every 1ms in which we will call all state machines we have
void PWM_Init_5(void)
{
  EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;  // count up
  EPwm5Regs.TBCTL.bit.PHSEN = TB_DISABLE;         // Master module
  EPwm5Regs.TBCTL.bit.PRDLD = TB_SHADOW;
  EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;        //TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
  EPwm5Regs.TBCTL.bit.CLKDIV =TB_DIV2;            //TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
  EPwm5Regs.ETSEL.bit.INTEN = 1;                 //enable interrupt
  EPwm5Regs.ETSEL.bit.INTSEL=ET_CTR_ZERO;     //interrupt event time-base counter equal to zero  ///////////////////////////////
  EPwm5Regs.ETPS.bit.INTPRD = 1;                                                                               //added for epwm interrupt
  EPwm5Regs.TBPRD = 40000;                         // Set period for ePWM4 (1kHz)
}
void PWM_Init_4(void)
{
  EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;  // count up
  EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE;         // Master module
  EPwm4Regs.TBCTL.bit.PRDLD = TB_SHADOW;
  EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;        //TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
  EPwm4Regs.TBCTL.bit.CLKDIV =TB_DIV1;            //TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
  EPwm4Regs.ETSEL.bit.INTEN = 1;                 //enable interrupt
  EPwm4Regs.ETSEL.bit.INTSEL=ET_CTR_ZERO;     //interrupt event time-base counter equal to zero    ///////////////////////////////
  EPwm4Regs.ETPS.bit.INTPRD = 1;                                                                               //added for epwm interrupt
  EPwm4Regs.TBPRD = 8000;                         // Set period for ePWM4 (10kHz)
}
void inverter_enable_tripzone_SW_event(void)
{
    DINT;
    EALLOW;
    EPwm1Regs.TZFRC.bit.OST=1;
    EPwm2Regs.TZFRC.bit.OST=1;
    EPwm8Regs.TZFRC.bit.OST=1;
    EDIS;
    EINT;
}
Uint32 trip_zone_clear_flag;;
void inverter_clear_tripzone_SW_event(void)
{
    trip_zone_clear_flag++;
    DINT;
    EALLOW;
    EPwm1Regs.TZCLR.bit.OST=1;
    EPwm2Regs.TZCLR.bit.OST=1;
    //EPwm8Regs.TZCLR.bit.OST=1;
    EDIS;
    EINT;
}
void epwm1_set_CMPA(Uint32 CMPA)
{
    EPwm1Regs.CMPA.half.CMPA = CMPA;
}
void epwm2_set_CMPA(Uint32 CMPA)
{
    EPwm2Regs.CMPA.half.CMPA = CMPA;
}
void epwm8_set_CMPA(Uint32 CMPA)
{
    EPwm8Regs.CMPA.half.CMPA = CMPA;
}
void epwm8_set_CMPB(Uint32 CMPB)
{
    EPwm8Regs.CMPB = CMPB;
}
Uint32 sw_timer_100us;
Uint32 state_machine_timer_1ms;
fprt_g epwm4_fptr=NULL;
fprt_g epwm5_fptr=NULL;
void epwm4_isr_assign_function(fprt_g fptr_recieved)
{
    epwm4_fptr=fptr_recieved;
}

#pragma CODE_SECTION(epwm4_isr_100us, "ramfuncs");
__interrupt void  epwm4_isr_100us(void)
{
    IER = M_INT1 | M_INT3 | M_INT11; //enable INT1 (group 1.x, ADC), enable INT11 (CLA)     // Set global priority by adjusting IER
    EnableInterrupts();
    //Begin actual interrupt
    sw_timer_100us++;
    if(epwm4_fptr!=NULL)
    {
        epwm4_fptr();
    }
    //Clears the ETFLG[INT] flag bit and enable further interrupts pulses to be generated
    EPwm4Regs.ETCLR.bit.INT=1;

    DINT;
     //IER does not need to be restored, as it was automatically saved on stack by HW.
}
void epwm5_isr_assign_function(fprt_g fptr_recieved)
{
    epwm5_fptr=fptr_recieved;
}

#pragma CODE_SECTION(epwm5_isr_1ms, "ramfuncs");
__interrupt void  epwm5_isr_1ms(void)
{
    IER = M_INT1 | M_INT3 | M_INT11; //enable INT1 (group 1.x, ADC), enable INT11 (CLA)     // Set global priority by adjusting IER
    EnableInterrupts();
    //Begin actual interrupt
    state_machine_timer_1ms++;
    if(epwm5_fptr!=NULL)
    {
        epwm5_fptr();
    }
    //Clears the ETFLG[INT] flag bit and enable further interrupts pulses to be generated
    EPwm5Regs.ETCLR.bit.INT=1;

    DINT;
     //IER does not need to be restored, as it was automatically saved on stack by HW.
}

/*
void PWM_Init_Slave_ADC_trig(volatile struct EPWM_REGS *EPwmxRegs)
{
  EPwmxRegs->TBCTL.bit.CTRMODE = TB_COUNT_UP;  // count up
  EPwmxRegs->TBCTL.bit.PHSEN = TB_ENABLE;          // Master module
  EPwmxRegs->TBCTL.bit.PRDLD = TB_SHADOW;
  EPwmxRegs->TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // Sync down-stream module
  EPwmxRegs->TBCTL.bit.HSPCLKDIV = TB_DIV1;        //TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
  EPwmxRegs->TBCTL.bit.CLKDIV =TB_DIV1;            //TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
  EPwmxRegs->ETSEL.bit.SOCAEN = 1;                 // Enable SOC on A group
  EPwmxRegs->ETSEL.bit.SOCASEL = ET_CTRU_CMPA;     // Select SOC from CMPA on upcount
  EPwmxRegs->ETPS.bit.SOCAPRD = 1;                 // Generate pulse on 1st event
  EPwmxRegs->CMPA.half.CMPA = 532;                   // Set compare A value
  EPwmxRegs->TBPRD = 1064;                         // Set period for ePWM4 (75kHz)
  //Counter Compare
  EPwmxRegs->CMPCTL.bit.SHDWAMODE = CC_SHADOW;
  EPwmxRegs->CMPCTL.bit.SHDWBMODE = CC_SHADOW;
  EPwmxRegs->CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
  //Action Qualifier
  EPwmxRegs->AQCTLA.bit.CAU = AQ_NO_ACTION; // set actions for EPWM1A
  EPwmxRegs->AQCTLA.bit.ZRO = AQ_NO_ACTION;
  //EPwmxRegs->AQCTLB.bit.CAU = AQ_SET; // set actions for EPWM1B
  //EPwmxRegs->AQCTLB.bit.CAD = AQ_CLEAR;
  EPwmxRegs->AQSFRC.bit.RLDCSF = 2 ; // Load AQCSFRC on event CTR = Zero or PRD
  // Dead-Band generator
  EPwmxRegs->DBCTL.bit.IN_MODE = DBA_ALL; // A rising edge delay
  EPwmxRegs->DBCTL.bit.OUT_MODE = 0x00; // Dead Band Mode Control mintavételezéshez nem kell deadband
  EPwmxRegs->DBCTL.bit.POLSEL = DB_ACTV_HIC; // Polarity Select Control: high active output
  // Setup DeadTime
  EPwmxRegs->DBRED = 80; // Dead-band rising edge delay DBT_PERIOD 1 step = 12.5ns @ TBCLK = 80MHz
  EPwmxRegs->DBFED = 80; // Dead-band falling edge delay DBT_PERIOD 1 step = 12.5ns @ TBCLK = 80MHz

  EPwmxRegs->TZSEL.bit.OSHT1 = TZ_DISABLE;
  EPwmxRegs->TZSEL.bit.OSHT2 = TZ_DISABLE;
  EPwmxRegs->TZCTL.bit.TZA = TZ_FORCE_LO;
  EPwmxRegs->TZCTL.bit.TZB = TZ_FORCE_LO;
  EPwmxRegs->TZFRC.bit.OST = TZ_DISABLE;
//  EALLOW;
//  EPwmxRegs->TZEINT.bit.OST = TZ_ENABLE;
//  EDIS;
}

void PWM_Init_I_AC_Error(volatile struct EPWM_REGS *EPwmxRegs)
{
    EPwmxRegs->TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // count updown
    EPwmxRegs->TBCTL.bit.PHSEN = TB_ENABLE;          // Master module
    EPwmxRegs->TBCTL.bit.PRDLD = TB_SHADOW;
    EPwmxRegs->TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // Sync down-stream module
    EPwmxRegs->TBCTL.bit.HSPCLKDIV = TB_DIV1;        //TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
    EPwmxRegs->TBCTL.bit.CLKDIV =TB_DIV1;            //TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
    EPwmxRegs->ETSEL.bit.SOCAEN = 0;                 // Enable SOC on A group
    EPwmxRegs->ETSEL.bit.SOCASEL = ET_CTRU_CMPA;     // Select SOC from CMPA on upcount
    EPwmxRegs->ETPS.bit.SOCAPRD = 1;                 // Generate pulse on 1st event
    EPwmxRegs->CMPA.half.CMPA = 1;                   // Set compare A value
    EPwmxRegs->TBPRD = 532;                         // Set period for ePWM1 (75kHz)
    //Counter Compare
    EPwmxRegs->CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwmxRegs->CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwmxRegs->CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
    //Action Qualifier
    EPwmxRegs->AQCTLA.bit.CAU = AQ_NO_ACTION; // set actions for EPWM1A
    EPwmxRegs->AQCTLA.bit.CAD = AQ_NO_ACTION;
    //EPwmxRegs->AQCTLB.bit.CAU = AQ_SET; // set actions for EPWM1B
    //EPwmxRegs->AQCTLB.bit.CAD = AQ_CLEAR;
    EPwmxRegs->AQSFRC.bit.RLDCSF = 2 ; // Load AQCSFRC on event CTR = Zero or PRD
    // Dead-Band generator
    EPwmxRegs->DBCTL.bit.IN_MODE = DBA_ALL; // A rising edge delay
    EPwmxRegs->DBCTL.bit.OUT_MODE = DB_DISABLE; // Dead Band Mode Control
    EPwmxRegs->DBCTL.bit.POLSEL = DB_ACTV_HIC; // Polarity Select Control: high active output
    // Setup DeadTime
    EPwmxRegs->DBRED = 64; // Dead-band rising edge delay DBT_PERIOD 1 step = 12.5ns @ TBCLK = 80MHz
    EPwmxRegs->DBFED = 64; // Dead-band falling edge delay DBT_PERIOD 1 step = 12.5ns @ TBCLK = 80MHz

    EPwmxRegs->TZSEL.bit.OSHT1 = TZ_ENABLE;
    EPwmxRegs->TZSEL.bit.OSHT2 = TZ_DISABLE;
    EPwmxRegs->TZSEL.bit.DCAEVT1 = TZ_DISABLE;
    EPwmxRegs->TZCTL.bit.TZA = TZ_NO_CHANGE;
    EPwmxRegs->TZCTL.bit.TZB = TZ_NO_CHANGE;
    EPwmxRegs->TZFRC.bit.OST = TZ_DISABLE;
}

void PWM_Init_I_DC_Error(volatile struct EPWM_REGS *EPwmxRegs)
{
    EPwmxRegs->TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // count updown
    EPwmxRegs->TBCTL.bit.PHSEN = TB_ENABLE;          // Master module
    EPwmxRegs->TBCTL.bit.PRDLD = TB_SHADOW;
    EPwmxRegs->TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // Sync down-stream module
    EPwmxRegs->TBCTL.bit.HSPCLKDIV = TB_DIV1;        //TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
    EPwmxRegs->TBCTL.bit.CLKDIV =TB_DIV1;            //TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
    EPwmxRegs->ETSEL.bit.SOCAEN = 0;                 // Enable SOC on A group
    EPwmxRegs->ETSEL.bit.SOCASEL = ET_CTRU_CMPA;     // Select SOC from CMPA on upcount
    EPwmxRegs->ETPS.bit.SOCAPRD = 1;                 // Generate pulse on 1st event
    EPwmxRegs->CMPA.half.CMPA = 1;                   // Set compare A value
    EPwmxRegs->TBPRD = 532;                         // Set period for ePWM1 (75kHz)
    //Counter Compare
    EPwmxRegs->CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwmxRegs->CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwmxRegs->CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
    //Action Qualifier
    EPwmxRegs->AQCTLA.bit.CAU = AQ_NO_ACTION; // set actions for EPWM1A
    EPwmxRegs->AQCTLA.bit.CAD = AQ_NO_ACTION;
    //EPwmxRegs->AQCTLB.bit.CAU = AQ_SET; // set actions for EPWM1B
    //EPwmxRegs->AQCTLB.bit.CAD = AQ_CLEAR;
    EPwmxRegs->AQSFRC.bit.RLDCSF = 2 ; // Load AQCSFRC on event CTR = Zero or PRD
    // Dead-Band generator
    EPwmxRegs->DBCTL.bit.IN_MODE = DBA_ALL; // A rising edge delay
    EPwmxRegs->DBCTL.bit.OUT_MODE = DB_DISABLE; // Dead Band Mode Control
    EPwmxRegs->DBCTL.bit.POLSEL = DB_ACTV_HIC; // Polarity Select Control: high active output
    // Setup DeadTime
    EPwmxRegs->DBRED = 64; // Dead-band rising edge delay DBT_PERIOD 1 step = 12.5ns @ TBCLK = 80MHz
    EPwmxRegs->DBFED = 64; // Dead-band falling edge delay DBT_PERIOD 1 step = 12.5ns @ TBCLK = 80MHz

    EPwmxRegs->TZSEL.bit.OSHT1 = TZ_DISABLE;
    EPwmxRegs->TZSEL.bit.OSHT2 = TZ_ENABLE;
    EPwmxRegs->TZSEL.bit.DCAEVT1 = TZ_DISABLE;
    EPwmxRegs->TZCTL.bit.TZA = TZ_NO_CHANGE;
    EPwmxRegs->TZCTL.bit.TZB = TZ_NO_CHANGE;
    EPwmxRegs->TZFRC.bit.OST = TZ_DISABLE;
}

void PWM_Init_U_Error(volatile struct EPWM_REGS *EPwmxRegs)
{
    EPwmxRegs->TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // count updown
    EPwmxRegs->TBCTL.bit.PHSEN = TB_ENABLE;          // Master module
    EPwmxRegs->TBCTL.bit.PRDLD = TB_SHADOW;
    EPwmxRegs->TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // Sync down-stream module
    EPwmxRegs->TBCTL.bit.HSPCLKDIV = TB_DIV1;        //TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
    EPwmxRegs->TBCTL.bit.CLKDIV =TB_DIV1;            //TBCLK = SYSCLKOUT / (HSPCLKDIV × CLKDIV)
    EPwmxRegs->ETSEL.bit.SOCAEN = 0;                 // Enable SOC on A group
    EPwmxRegs->ETSEL.bit.SOCASEL = ET_CTRU_CMPA;     // Select SOC from CMPA on upcount
    EPwmxRegs->ETPS.bit.SOCAPRD = 1;                 // Generate pulse on 1st event
    EPwmxRegs->CMPA.half.CMPA = 1;                   // Set compare A value
    EPwmxRegs->TBPRD = 532;                         // Set period for ePWM1 (75kHz)
    //Counter Compare
    EPwmxRegs->CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwmxRegs->CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwmxRegs->CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
    //Action Qualifier
    EPwmxRegs->AQCTLA.bit.CAU = AQ_NO_ACTION; // set actions for EPWM1A
    EPwmxRegs->AQCTLA.bit.CAD = AQ_NO_ACTION;
    //EPwmxRegs->AQCTLB.bit.CAU = AQ_SET; // set actions for EPWM1B
    //EPwmxRegs->AQCTLB.bit.CAD = AQ_CLEAR;
    EPwmxRegs->AQSFRC.bit.RLDCSF = 2 ; // Load AQCSFRC on event CTR = Zero or PRD
    // Dead-Band generator
    EPwmxRegs->DBCTL.bit.IN_MODE = DBA_ALL; // A rising edge delay
    EPwmxRegs->DBCTL.bit.OUT_MODE = DB_DISABLE; // Dead Band Mode Control
    EPwmxRegs->DBCTL.bit.POLSEL = DB_ACTV_HIC; // Polarity Select Control: high active output
    // Setup DeadTime
    EPwmxRegs->DBRED = 64; // Dead-band rising edge delay DBT_PERIOD 1 step = 12.5ns @ TBCLK = 80MHz
    EPwmxRegs->DBFED = 64; // Dead-band falling edge delay DBT_PERIOD 1 step = 12.5ns @ TBCLK = 80MHz1 step = 12.5ns @ TBCLK = 80MHz

    EPwmxRegs->TZSEL.bit.OSHT1 = TZ_DISABLE;
    EPwmxRegs->TZSEL.bit.OSHT2 = TZ_DISABLE;
    EPwmxRegs->TZSEL.bit.DCAEVT1 = TZ_ENABLE;
    EPwmxRegs->TZCTL.bit.TZA = TZ_NO_CHANGE;
    EPwmxRegs->TZCTL.bit.TZB = TZ_NO_CHANGE;
    EPwmxRegs->TZFRC.bit.OST = TZ_DISABLE;

    //TZ3 trükközés DC submodul-al
    EALLOW;
    EPwmxRegs->TZEINT.bit.OST = TZ_ENABLE;
    EPwmxRegs->DCTRIPSEL.bit.DCAHCOMPSEL = 0x2; //TZ3 bemenet
    EPwmxRegs->TZDCSEL.bit.DCAEVT1 = TZ_DCAH_HI; //HIGH = 1 LOW = DONT CARE
    EPwmxRegs->DCTRIPSEL.bit.DCBHCOMPSEL = 0x2; //TZ3 bemenet
    EPwmxRegs->TZDCSEL.bit.DCBEVT1 = TZ_DCBH_HI; //HIGH = 1 LOW = DONT CARE
  //  EPwmxRegs->DCACTL.bit.EVT1SRCSEL = 0;
  //  EPwmxRegs->DCACTL.bit.EVT1FRCSYNCSEL = 1;
  //  EPwmxRegs->DCBCTL.bit.EVT1SRCSEL = 0;
  //  EPwmxRegs->DCBCTL.bit.EVT1FRCSYNCSEL = 1;
    EPwmxRegs->TZSEL.bit.DCAEVT1 = 1;
    EPwmxRegs->TZSEL.bit.DCBEVT1 = 1;
    EDIS;
}

void PWM_ErrorACK(void)
{
  EALLOW;
  GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;     // 0=GPIO, 1=EPWM1A, 2=Reserved, 3=Reserved
  GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;    // 1=OUTput,  0=INput
  GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;  // uncomment if --> Set Low initially

  GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;     // 0=GPIO, 1=EPWM1A, 2=Reserved, 3=Reserved
  GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;    // 1=OUTput,  0=INput
  GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;  // uncomment if --> Set Low initially


  GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;     // 0=GPIO, 1=EPWM1A, 2=Reserved, 3=Reserved
  GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;    // 1=OUTput,  0=INput
  GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;  // uncomment if --> Set Low initially

  GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;     // 0=GPIO, 1=EPWM1A, 2=Reserved, 3=Reserved
  GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;    // 1=OUTput,  0=INput
  GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;  // uncomment if --> Set Low initially


  GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;     // 0=GPIO, 1=EPWM1A, 2=Reserved, 3=Reserved
  GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;    // 1=OUTput,  0=INput
  GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;  // uncomment if --> Set Low initially

  GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;     // 0=GPIO, 1=EPWM1A, 2=Reserved, 3=Reserved
  GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;    // 1=OUTput,  0=INput
  GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;  // uncomment if --> Set Low initially


  GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;     // 0=GPIO, 1=EPWM1A, 2=Reserved, 3=Reserved
  GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;    // 1=OUTput,  0=INput
  GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;  // uncomment if --> Set Low initially

  GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;     // 0=GPIO, 1=EPWM1A, 2=Reserved, 3=Reserved
  GpioCtrlRegs.GPADIR.bit.GPIO7 = 1;    // 1=OUTput,  0=INput
  GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;  // uncomment if --> Set Low initially
  EDIS;

  DELAY_US(15);

  GpioDataRegs.GPASET.bit.GPIO0 = 1;  //
  GpioDataRegs.GPASET.bit.GPIO2 = 1;  //
  GpioDataRegs.GPASET.bit.GPIO4 = 1;  //
  GpioDataRegs.GPASET.bit.GPIO6 = 1;  //

  DELAY_US(1);

  GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;  //
  GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;  //
  GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;  //
  GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;  //

  PWM_Init_GPIOs();
}
*/
