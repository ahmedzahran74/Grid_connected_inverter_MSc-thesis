#include "inic.h"
#include "RHO_code_generation.h"
#include"PLL_controller.h"
#pragma CODE_SECTION(InitFlash, "ramfuncs");

extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;

extern Uint16 FPUmathTablesLoadStart, FPUmathTablesLoadEnd, FPUmathTablesRunStart;
extern Uint16 rts2800_fpu32_RAM_loadstart, rts2800_fpu32_RAM_loadend, rts2800_fpu32_RAM_runstart;


volatile struct SCI_REGS *sci_ptr_terminal;
extern __interrupt void  adc_isr(void);
extern __interrupt void  epwm4_isr_100us(void);
extern __interrupt void cpu_timer1_isr(void);
__interrupt void  epwm5_isr_1ms(void);
//--------------------------------------------------------------------
//  Configure Device for target Application Here
//--------------------------------------------------------------------

void DeviceInit(void)
{
  WDogDisable();   // Disable the watchdog initially
  DINT;      // Global Disable all Interrupts
  IER = 0x0000;  // Disable CPU interrupts
  IFR = 0x0000;  // Clear all CPU interrupt flags


  // The Device_cal function, which copies the ADC & oscillator calibration values
  // from TI reserved OTP into the appropriate trim registers, occurs automatically
  // in the Boot ROM. If the boot ROM code is bypassed during the debug process, the
  // following function MUST be called for the ADC and oscillators to function according
  // to specification.
  EALLOW;
  SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1; // Enable ADC peripheral clock
  (*Device_cal)();                      // Auto-calibrate from TI OTP
  SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 0; // Return ADC clock to original state
  EDIS;

  // Switch to Internal Oscillator 1 and turn off all other clock
  // sources to minimize power consumption
  EALLOW;
SysCtrlRegs.CLKCTL.bit.OSCCLKSRC2SEL=0;
  SysCtrlRegs.CLKCTL.bit.OSCCLKSRCSEL=1;  // Clk Src = XTAL
  SysCtrlRegs.CLKCTL.bit.XTALOSCOFF=0;    // Turn on XTALOSC
  SysCtrlRegs.CLKCTL.bit.WDCLKSRCSEL = 1; //WD source to xtal
  SysCtrlRegs.CLKCTL.bit.INTOSC1OFF = 1;
  SysCtrlRegs.CLKCTL.bit.XCLKINOFF=1;     // Turn off XCLKIN
  SysCtrlRegs.CLKCTL.bit.INTOSC2OFF=1;    // Turn off INTOSC2
  EDIS;


  // SYSTEM CLOCK speed based on internal oscillator = 10 MHz
  // 0x10=  80  MHz    (16)
  // 0xF =  75  MHz    (15)
  // 0xE =  70  MHz    (14)
  // 0xD =  65  MHz    (13)
  // 0xC =  60  MHz    (12)
  // 0xB =  55  MHz    (11)
  // 0xA =  50  MHz    (10)
  // 0x9 =  45  MHz    (9)
  // 0x8 =  40  MHz    (8)
  // 0x7 =  35  MHz    (7)
  // 0x6 =  30  MHz    (6)
  // 0x5 =  25  MHz    (5)
  // 0x4 =  20  MHz    (4)
  // 0x3 =  15  MHz    (3)
  // 0x2 =  10  MHz    (2)

  PLLset( 0x10 );  // choose from options above

  // Initialise interrupt controller and Vector Table
  // to defaults for now. Application ISR mapping done later.
  EALLOW;  // This is needed to write to EALLOW protected register
  InitPieCtrl();
  InitPieVectTable();
  EDIS;    // This is needed to disable write to EALLOW protected registers

  EALLOW;  // This is needed to write to EALLOW protected register
  PieVectTable.TINT1 = &cpu_timer1_isr;
  PieVectTable.ADCINT1 = &adc_isr;

  PieVectTable.EPWM4_INT= &epwm4_isr_100us;                                   /////////////////////added
  PieVectTable.EPWM5_INT= &epwm5_isr_1ms;


  EDIS;    // This is needed to disable write to EALLOW protected registers

  MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
  MemCopy(&FPUmathTablesLoadStart, &FPUmathTablesLoadEnd, &FPUmathTablesRunStart);
  MemCopy(&rts2800_fpu32_RAM_loadstart, &rts2800_fpu32_RAM_loadend, &rts2800_fpu32_RAM_runstart);

  InitFlash();

  EALLOW; // below registers are "protected", allow access.

// LOW SPEED CLOCKS prescale register settings

  SysCtrlRegs.LOSPCP.all = LSPCLK_DIVIDER;    //See inic.h
  SysCtrlRegs.XCLK.bit.XCLKOUTDIV=0; // Sysclk / 4 (20 MHz)

  // PERIPHERAL CLOCK ENABLES
  //---------------------------------------------------
  // If you are not using a peripheral you may want to switch
  // the clock off to save power, i.e. set to =0
  //
  // Note: not all peripherals are available on all 280x derivates.
  // Refer to the datasheet for your particular device.

  SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;    // ADC
  //------------------------------------------------
  SysCtrlRegs.PCLKCR3.bit.COMP1ENCLK = 0;  // COMP1
  SysCtrlRegs.PCLKCR3.bit.COMP2ENCLK = 0;  // COMP2
  SysCtrlRegs.PCLKCR3.bit.COMP3ENCLK = 0;  // COMP3
  //------------------------------------------------
  SysCtrlRegs.PCLKCR0.bit.I2CAENCLK = 1;   // I2C
  //------------------------------------------------
  SysCtrlRegs.PCLKCR0.bit.MCBSPAENCLK = 0; // McBSP-A
  //------------------------------------------------
  SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 1;   // SCI-A
  SysCtrlRegs.PCLKCR0.bit.SCIBENCLK = 1;   // SCI-B
  //------------------------------------------------
  SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 0;  // eCAP1
  SysCtrlRegs.PCLKCR1.bit.ECAP2ENCLK = 0;  // eCAP2
  SysCtrlRegs.PCLKCR1.bit.ECAP3ENCLK = 0;  // eCAP3
  //------------------------------------------------
  SysCtrlRegs.PCLKCR3.bit.DMAENCLK = 0;    // DMA
  //------------------------------------------------
  SysCtrlRegs.PCLKCR3.bit.CLA1ENCLK = 1;   // CLA
  //------------------------------------------------

  // Step 4. Initialize the Device Peripheral. This function can be
  //         found in F2806x_CpuTimers.c
  InitCpuTimers();   // For this example, only initialize the Cpu Timers // !!! felesleges

  // Configure CPU-Timer 0 to interrupt every 1 milisecond:                                          ////////////////////////timer 1 not 0
  // 80MHz CPU Freq, 1 milisecond Period (in uSeconds)

  ConfigCpuTimer(&CpuTimer1, 80, 1000);
  CpuTimer1Regs.TCR.all = 0x4000; // Use write-only instruction to set TSS bit = 0 !!!

  CLA_Init();

  EALLOW;

  //--------------------------------------------------------------------------------------
  // GPIO (GENERAL PURPOSE I/O) CONFIG
  //--------------------------------------------------------------------------------------
  //-----------------------
  // QUICK NOTES on USAGE:
  //-----------------------
  // If GpioCtrlRegs.GP?MUX?bit.GPIO?= 1, 2 or 3 (i.e. Non GPIO func), then leave
  //  rest of lines commented
  // If GpioCtrlRegs.GP?MUX?bit.GPIO?= 0 (i.e. GPIO func), then:
  //  1) uncomment GpioCtrlRegs.GP?DIR.bit.GPIO? = ? and choose pin to be IN or OUT
  //  2) If IN, can leave next to lines commented
  //  3) If OUT, uncomment line with ..GPACLEAR.. to force pin LOW or
  //         uncomment line with ..GPASET.. to force pin HIGH or
  //--------------------------------------------------------------------------------------
  //--------------------------------------------------------------------------------------
  //  GPIO-00 - PIN FUNCTION = --GPIO Output EPWM1A--  //
  GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;     // 0=GPIO, 1=EPWM1A, 2=Reserved, 3=Reserved
  //GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;    // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;  // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO0 = 1;    // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-01 - PIN FUNCTION = --GPIO Output EPWM1A--
  GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;     // 0=GPIO, 1=EPWM1B, 2=Reserved, 3=COMP1OUT
  //GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;    // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;  // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO1 = 1;    // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-02 - PIN FUNCTION = --GPIO Output EPWM2A--
  GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;     // 0=GPIO, 1=EPWM2A, 2=Reserved, 3=Reserved
  //GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;    // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;  // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO2 = 1;    // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-03 - PIN FUNCTION = --GPIO Output EPWM2B--
  GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;     // 0=GPIO, 1=EPWM2B, 2=SPISOMIA, 3=COMP2OUT
  //GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;    // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;  // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO3 = 1;    // uncomment if --> Set High initially
  //---------------------------PinHeaderStart--------------------------------------
  //  GPIO-04 - PIN FUNCTION = --GPIO Output EPWM3A--
  GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;     // 0=GPIO, 1=EPWM3A, 2=Reserved, 3=Reserved
  GpioCtrlRegs.GPADIR.bit.GPIO4 = 0;    // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;  // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO4 = 1;    // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-05 - PIN FUNCTION = --GPIO Output EPWM3B--
  GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;     // 0=GPIO, 1=EPWM3B, 2=SPISIMOA, 3=ECAP1
  GpioCtrlRegs.GPADIR.bit.GPIO5 = 0;    // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;  // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO5 = 1;    // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-06 - PIN FUNCTION = --Spare--
  GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;     // 0=GPIO, 1=EPWM4A, 2=EPWMSYNCI, 3=EPWMSYNCO
  GpioCtrlRegs.GPADIR.bit.GPIO6 = 0;    // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;  // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO6 = 1;    // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-07 - PIN FUNCTION = --Spare--
  GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;     // 0=GPIO, 1=EPWM4B, 2=SCIRXDA, 3=ECAP2
  GpioCtrlRegs.GPADIR.bit.GPIO7 = 0;    // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;  // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO7 = 1;    // uncomment if --> Set High initially
  //----------------------------------------------------------------------
  //  GPIO-08 - PIN FUNCTION = --Spare--
  GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;     // 0=GPIO, 1=EPWM5A, 2=Reserved, 3=#ADCSOCAO
  GpioCtrlRegs.GPADIR.bit.GPIO8 = 0;    // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO8 = 1;  // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO8 = 1;    // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-09 - PIN FUNCTION = --Spare--
  GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;     // 0=GPIO, 1=EPWM5B, 2=SCITXDB, 3=ECAP3
  GpioCtrlRegs.GPADIR.bit.GPIO9 = 0;    // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;  // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO9 = 1;    // uncomment if --> Set High initially
  //------------------------------PinHeaderEnd-------------------------------------------
  //------------------------------UnUsedPin-------------------------------------------
  //  GPIO-10 - PIN FUNCTION = --Spare--
  GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;    // 0=GPIO, 1=EPWM6A, 2=Reserved, 3=#ADCSOCBO
  GpioCtrlRegs.GPADIR.bit.GPIO10 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO10 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO10 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-11 - PIN FUNCTION = --Spare--
  GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;    // 0=GPIO, 1=EPWM6B, 2=SCIRXDB, 3=ECAP1
  GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;   // 1=OUTput,  0=INput
  GpioDataRegs.GPACLEAR.bit.GPIO11 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO11 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-12 - PIN FUNCTION = --Spare--
  GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;    // 0=GPIO, 1=#TZ1, 2=SCITXDA, 3=SPISIMOB
  //GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO12 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO12 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-13 - PIN FUNCTION = --Spare--
  GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 1;    // 0=GPIO, 1=#TZ2, 2=Reserved, 3=SPISOMIB
  //GpioCtrlRegs.GPADIR.bit.GPIO13 = 1;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO13 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO13 = 1;   // uncomment if --> Set High initially
  //--------------------------UnUsedPin-----------------------------------------------
  //  GPIO-14 - PIN FUNCTION = --GPIO Output Fan--
  GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;    // 0=GPIO, 1=#TZ3, 2=SCITXDB, 3=SPICLKB
  GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO14 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO14 = 1;   // uncomment if --> Set High initially
  //--------------------------UnUsedPin------------------------------------------------------------
  //  GPIO-15 - PIN FUNCTION = --Spare--
  GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;    // 0=GPIO, 1=ECAP2, 2=SCIRXDB, 3=#SPISTEB
  GpioCtrlRegs.GPADIR.bit.GPIO15 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO15 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO15 = 1;   // uncomment if --> Set High initially
  //--------------------------PinHeaderStart-------------------------------------------------
  //  GPIO-16 - PIN FUNCTION = --Spare--
  GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;    // 0=GPIO, 1=SPISIMOA, 2=Reserved, 3=#TZ2
  GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO16 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO16 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-17 - PIN FUNCTION = --Spare--
  GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;    // 0=GPIO, 1=SPISOMIA, 2=Reserved, 3=#TZ3
  GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO17 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO17 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-18 - PIN FUNCTION = --Spare--
  GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 0;    // 0=GPIO, 1=SPICLKA, 2=SCITXDB, 3=XCLKOUT
  GpioCtrlRegs.GPADIR.bit.GPIO18 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO18 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO18 = 1;   // uncomment if --> Set High initially
  //----------------------------PinHeaderEnd--------------------------------------------
  //----------------------------UnusedPin-----------------------------------------------
  //  GPIO-19 - PIN FUNCTION = --Spare--
  GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;    // 0=GPIO/XCLKIN, 1=#SPISTEA, 2=SCIRXDB, 3=ECAP1
  GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO19 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO19 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-20 - PIN FUNCTION = --precharge relay--
  GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0;    // 0=GPIO, 1=EQEP1A, 2=MDXA, 3=COMP1OUT
  GpioCtrlRegs.GPADIR.bit.GPIO20 = 1;   // 1=OUTput,  0=INput
  GpioDataRegs.GPACLEAR.bit.GPIO20 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO20 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-21 - PIN FUNCTION = --UnusedPin--
  GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 0;    // 0=GPIO, 1=EQEP1B, 2=MDRA, 3=COMP2OUT
  GpioCtrlRegs.GPADIR.bit.GPIO21 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO21 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO21 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-22 - PIN FUNCTION = --UnusedPin--
  GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;    // 0=GPIO, 1=EQEP1S, 2=MCLKXA, 3=SCITXDB
  GpioCtrlRegs.GPADIR.bit.GPIO22 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO22 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO22 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-23 - PIN FUNCTION = --PrechargeRealyDCSide--
  GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;    // 0=GPIO, 1=EQEP1I, 2=MFSXA, 3=SCIRXDB
  GpioCtrlRegs.GPADIR.bit.GPIO23 = 1;   // 1=OUTput,  0=INput
  GpioDataRegs.GPACLEAR.bit.GPIO23 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO23 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-24 - PIN FUNCTION = --UnusedPin--
  GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;    // 0=GPIO, 1=ECAP1, 2=EQEP2A, 3=SPISIMOB
  GpioCtrlRegs.GPADIR.bit.GPIO24 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO24 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO24 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-25 - PIN FUNCTION = --PinHeaderNetLabel31--
  GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;    // 0=GPIO, 1=ECAP2, 2=EQEP2B, 3=SPISOMIB
  GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO25 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO25 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-26 - PIN FUNCTION = --UnusedPin--
  GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;    // 0=GPIO, 1=ECAP3, 2=EQEP2I, 3=SPICLKB
  GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO26 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO26 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-27 - PIN FUNCTION = --UnusedPin--
  GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;    // 0=GPIO, 1=HRCAP2, 2=EQEP2S, 3=#SPISTEB
  GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO27 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO27 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-28 - PIN FUNCTION = --SCIRXDA--
  GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;    // 0=GPIO, 1=SCIRXDA, 2=SDAA, 3=#TZ2
  //GpioCtrlRegs.GPADIR.bit.GPIO28 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO28 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO28 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-29 - PIN FUNCTION = --SCITXDA--
  GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;    // 0=GPIO, 1=SCITXDA, 2=SCLA, 3=#TZ3
  //GpioCtrlRegs.GPADIR.bit.GPIO29 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO29 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO29 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-30 - PIN FUNCTION = --CANRXA--
  GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;    // 0=GPIO, 1=CANRXA, 2=EQEP2I, 3=EPWM7A
  //GpioCtrlRegs.GPADIR.bit.GPIO30 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO30 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO30 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-31 - PIN FUNCTION = --CANTXA--
  GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;    // 0=GPIO, 1=CANTXA, 2=EQEP2S, 3=EPWM8A
  //GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPACLEAR.bit.GPIO31 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPASET.bit.GPIO31 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-32 - PIN FUNCTION = --UnUsedPin--
  GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;    // 0=GPIO, 1=SDAA, 2=EPWMSYNCI, 3=#ADCSOCAO
  GpioCtrlRegs.GPBDIR.bit.GPIO32 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPBSET.bit.GPIO32 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-33 - PIN FUNCTION = --UnUsedPin--
  GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;    // 0=GPIO, 1=SCLA, 2=EPWMSYNCO, 3=#ADCSOCBO
  GpioCtrlRegs.GPBDIR.bit.GPIO33 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPBSET.bit.GPIO33 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-34 - PIN FUNCTION = --Spare--
  GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;    // 0=GPIO, 1=COMP2OUT, 2=Reserved, 3=COMP3OUT
  //GpioCtrlRegs.GPBDIR.bit.GPIO34 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPBSET.bit.GPIO34 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-35 - PIN FUNCTION = --UnUsedPin--
  GpioCtrlRegs.GPBMUX1.bit.GPIO35 = 0;    // 0=GPIO (TDI), 1=Reserved, 2=Reserved, 3=Reserved
  GpioCtrlRegs.GPBDIR.bit.GPIO35 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO35 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPBSET.bit.GPIO35 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-36 - PIN FUNCTION = --Spare--
  GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 0;    // 0=GPIO (TMS), 1=Reserved, 2=Reserved, 3=Reserved
  //GpioCtrlRegs.GPBDIR.bit.GPIO36 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO36 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPBSET.bit.GPIO36 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-37 - PIN FUNCTION = --Spare--
  GpioCtrlRegs.GPBMUX1.bit.GPIO37 = 0;    // 0=GPIO (TDO), 1=Reserved, 2=Reserved, 3=Reserved
  //GpioCtrlRegs.GPBDIR.bit.GPIO37 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO37 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPBSET.bit.GPIO37 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-38 - PIN FUNCTION = --Spare--
  GpioCtrlRegs.GPBMUX1.bit.GPIO38 = 0;    // 0=GPIO/XCLKIN (TCK), 1=Reserved, 2=Reserved, 3=Reserved
  //GpioCtrlRegs.GPBDIR.bit.GPIO38 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO38 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPBSET.bit.GPIO38 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-39 - PIN FUNCTION = --PinHeaderNetLabel19--
  GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;    // 0=GPIO, 1=Reserved, 2=Reserved, 3=Reserved
  GpioCtrlRegs.GPBDIR.bit.GPIO39 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPBSET.bit.GPIO39 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-40 - PIN FUNCTION = --PinHeaderNetLabel21--
  GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 0;    // 0=GPIO, 1=EPWM7A, 2=SCITXDB, 3=Reserved
  GpioCtrlRegs.GPBDIR.bit.GPIO40 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO40 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPBSET.bit.GPIO40 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-41 - PIN FUNCTION = --UnusedPin--
  GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 0;    // 0=GPIO, 1=EPWM7B, 2=SCIRXDB, 3=Reserved
  GpioCtrlRegs.GPBDIR.bit.GPIO41 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPBSET.bit.GPIO41 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-42 - PIN FUNCTION = --PWM3A--
  GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 1;    // 0=GPIO, 1=EPWM8A, 2=#TZ1, 3=COMP1OUT
  //GpioCtrlRegs.GPBDIR.bit.GPIO42 = 1;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO42 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPBSET.bit.GPIO42 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-43 - PIN FUNCTION = --PWM3B--
  GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 1;    // 0=GPIO, 1=EPWM8B, 2=#TZ2, 3=COMP2OUT
  //GpioCtrlRegs.GPBDIR.bit.GPIO43 = 1;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO43 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPBSET.bit.GPIO43 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-44 - PIN FUNCTION = --PinHeaderNetLabel15--
  GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;    // 0=GPIO, 1=MFSRA, 2=SCIRXDB, 3=EPWM7B
  GpioCtrlRegs.GPBDIR.bit.GPIO44 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPBSET.bit.GPIO44 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-50 - PIN FUNCTION = --GPIO OUTput LEDRed--
  GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 0;    // 0=GPIO, 1=EQEP1A, 2=MDXA, 3=#TZ1
  GpioCtrlRegs.GPBDIR.bit.GPIO50 = 1;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO50 = 1; // uncomment if --> Set Low initially
  GpioDataRegs.GPBSET.bit.GPIO50 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-51 - PIN FUNCTION = --GPIO OUTput LEDGreen--
  GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 0;    // 0=GPIO, 1=EQEP1B, 2=MDRA, 3=#TZ2
  GpioCtrlRegs.GPBDIR.bit.GPIO51 = 1;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO51 = 1; // uncomment if --> Set Low initially
  GpioDataRegs.GPBSET.bit.GPIO51 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-52 - PIN FUNCTION = --PinHeaderNetLabel12--
  GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 0;    // 0=GPIO, 1=EQEP1S, 2=MCLKXA, 3=#TZ3
  GpioCtrlRegs.GPBDIR.bit.GPIO52 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO52 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPBSET.bit.GPIO52 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-53 - PIN FUNCTION = --PinHeaderNetLabel18--
  GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 0;    // 0=GPIO, 1=EQEP1I, 2=MFSXA, 3=Reserved
  GpioCtrlRegs.GPBDIR.bit.GPIO53 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO53 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPBSET.bit.GPIO53 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-54 - PIN FUNCTION = --PinHeaderNetLabel25--
  GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 0;    // 0=GPIO, 1=SPISIMOA, 2=EQEP2A, 3=HRCAP1
  GpioCtrlRegs.GPBDIR.bit.GPIO54 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO54 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPBSET.bit.GPIO54 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-55 - PIN FUNCTION = --PinHeaderNetLabel20--
  GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 0;    // 0=GPIO, 1=SPISOMIA, 2=EQEP2B, 3=HRCAP2
  GpioCtrlRegs.GPBDIR.bit.GPIO55 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO55 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPBSET.bit.GPIO55 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-56 - PIN FUNCTION = --PinHeaderNetLabel22--
  GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 0;    // 0=GPIO, 1=SPICLKA, 2=EQEP2I, 3=HRCAP3
  GpioCtrlRegs.GPBDIR.bit.GPIO56 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO56 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPBSET.bit.GPIO56 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-57 - PIN FUNCTION = --PinHeaderNetLabel23--
  GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 0;    // 0=GPIO, 1=#SPISTEA, 2=EQEP2S, 3=HRCAP4
  GpioCtrlRegs.GPBDIR.bit.GPIO57 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO57 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPBSET.bit.GPIO57 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
  //  GPIO-58 - PIN FUNCTION = --PinHeaderNetLabel24--
  GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 0;    // 0=GPIO, 1=MCLKRA, 2=SCITXDB, 3=EPWM7A
  GpioCtrlRegs.GPBDIR.bit.GPIO58 = 0;   // 1=OUTput,  0=INput
  //GpioDataRegs.GPBCLEAR.bit.GPIO58 = 1; // uncomment if --> Set Low initially
  //GpioDataRegs.GPBSET.bit.GPIO58 = 1;   // uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------

  PWM_Init();
  //current_controller_AC_code_generation_initialize();
  //RHO_code_generation_initialize();
  //PLL_controller_initialize();
  CLA_Wait_for_Cla1ToCpuMsgRAM_cleared(); //wait for CLA to finish clearing message RAM before initializing ADC IT
  ADC_Init();

  EALLOW;
  SetSCITMSmon(&SciaRegs);  //Setup HiTerm communications port

  EDIS;  // Disable register access
}

/******************************************************************************/
// A TMSmon protokolhoz megfeleoen all�tja be a soros portot.
void SetSCITMSmon(volatile struct SCI_REGS *ptr)
{
  sci_ptr_terminal = ptr;

  sci_ptr_terminal->SCICCR.all = 7;  //1 stop bit,no parity, no test, idle�line protocol, 8bits

  sci_ptr_terminal->SCICTL2.bit.RXBKINTENA=0;
  sci_ptr_terminal->SCICTL2.bit.TXINTENA=0;

  sci_ptr_terminal->SCIPRI.bit.FREE = 0;
  sci_ptr_terminal->SCIPRI.bit.SOFT = 0;

  sci_ptr_terminal->SCICTL1.bit.RXERRINTENA=0;
  sci_ptr_terminal->SCICTL1.bit.SWRESET=0;

  sci_ptr_terminal->SCICTL1.bit.TXWAKE=0;
  sci_ptr_terminal->SCICTL1.bit.SLEEP=0;
  sci_ptr_terminal->SCICTL1.bit.TXENA=1;
  sci_ptr_terminal->SCICTL1.bit.RXENA=1;

  sci_ptr_terminal->SCILBAUD = (((20*1000000L)/57600-8)/8) & 0xff;
  sci_ptr_terminal->SCIHBAUD = (((20*1000000L)/57600-8)/8) >> 8;

  sci_ptr_terminal->SCICTL1.bit.RXERRINTENA=0;
  sci_ptr_terminal->SCICTL1.bit.SWRESET=1;

  sci_ptr_terminal->SCICTL1.bit.TXWAKE=0;
  sci_ptr_terminal->SCICTL1.bit.SLEEP=0;
  sci_ptr_terminal->SCICTL1.bit.TXENA=1;
  sci_ptr_terminal->SCICTL1.bit.RXENA=1;

  sci_ptr_terminal->SCIFFTX.bit.SCIFFENA = 1;
  sci_ptr_terminal->SCIFFTX.all=0xE000;
  sci_ptr_terminal->SCICTL1.all = 0x0023;     // Relinquish SCI from Reset
  sci_ptr_terminal->SCIFFTX.bit.TXFIFOXRESET = 1;

// FIFO
  sci_ptr_terminal->SCIFFRX.bit.RXFFOVRCLR = 1;
  sci_ptr_terminal->SCIFFRX.bit.RXFIFORESET = 0; // Clear and disable receiver FIFO
  sci_ptr_terminal->SCIFFRX.bit.RXFFINTCLR = 1;

  sci_ptr_terminal->SCIFFRX.bit.RXFIFORESET = 1; // Reenable FIFO
  sci_ptr_terminal->SCIFFRX.bit.RXFFIENA = 1;  // Receive FIFO interrupt enable
  sci_ptr_terminal->SCIFFRX.bit.RXFFIL = 1;   // Receive FIFO interrupt level: 1 b�jt j�tt

}
/******************************************************************************/



//============================================================================
// NOTE:
// IN MOST APPLICATIONS THE FUNCTIONS AFTER THIS POINT CAN BE LEFT UNCHANGED
// THE USER NEED NOT REALLY UNDERSTAND THE BELOW CODE TO SUCCESSFULLY RUN THIS
// APPLICATION.
//============================================================================

void WDogDisable(void)
{
  EALLOW;
  SysCtrlRegs.WDCR= 0x0068;
  EDIS;
}

// This function initializes the PLLCR register.
//void InitPll(Uint16 val, Uint16 clkindiv)
void PLLset(Uint16 val)
{
  volatile Uint16 iVol;

  // Make sure the PLL is not running in limp mode
  if (SysCtrlRegs.PLLSTS.bit.MCLKSTS != 0)
  {
    EALLOW;
    // OSCCLKSRC1 failure detected. PLL running in limp mode.
    // Re-enable missing clock logic.
    SysCtrlRegs.PLLSTS.bit.MCLKCLR = 1;
    EDIS;
    // Replace this line with a call to an appropriate
    // SystemShutdown(); function.
    asm("        ESTOP0");     // Uncomment for debugging purposes
  }

   // DIVSEL MUST be 0 before PLLCR can be changed from
   // 0x0000. It is set to 0 by an external reset XRSn
   // This puts us in 1/4
   if (SysCtrlRegs.PLLSTS.bit.DIVSEL != 0)
   {
       EALLOW;
       SysCtrlRegs.PLLSTS.bit.DIVSEL = 0;
       EDIS;
   }

   // Change the PLLCR
   if (SysCtrlRegs.PLLCR.bit.DIV != val)
   {

      EALLOW;
      // Before setting PLLCR turn off missing clock detect logic
      SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1;
      SysCtrlRegs.PLLCR.bit.DIV = val;
      EDIS;

      // Optional: Wait for PLL to lock.
      // During this time the CPU will switch to OSCCLK/2 until
      // the PLL is stable.  Once the PLL is stable the CPU will
      // switch to the new PLL value.
      //
      // This time-to-lock is monitored by a PLL lock counter.
      //
      // Code is not required to sit and wait for the PLL to lock.
      // However, if the code does anything that is timing critical,
      // and requires the correct clock be locked, then it is best to
      // wait until this switching has completed.

      // Wait for the PLL lock bit to be set.
      // The watchdog should be disabled before this loop, or fed within
      // the loop via ServiceDog().

    // Uncomment to disable the watchdog
      WDogDisable();

    while(SysCtrlRegs.PLLSTS.bit.PLLLOCKS != 1) {}

      EALLOW;
      SysCtrlRegs.PLLSTS.bit.MCLKOFF = 0;
    EDIS;
  }

    //divide down SysClk by 2 to increase stability
  EALLOW;
  SysCtrlRegs.PLLSTS.bit.DIVSEL = 2;
  EDIS;
}

// This function initializes the Flash Control registers

//                   CAUTION
// This function MUST be executed out of RAM. Executing it
// out of OTP/Flash will yield unpredictable results

void InitFlash(void)
{
   EALLOW;
   //Enable Flash Pipeline mode to improve performance
   //of code executed from Flash.
   FlashRegs.FOPT.bit.ENPIPE = 1;

   //                CAUTION
   //Minimum waitstates required for the flash operating
   //at a given CPU rate must be characterized by TI.
   //Refer to the datasheet for the latest information.

   //Set the Paged Waitstate for the Flash
   FlashRegs.FBANKWAIT.bit.PAGEWAIT = 2;

   //Set the Random Waitstate for the Flash
   FlashRegs.FBANKWAIT.bit.RANDWAIT = 2;

   //Set the Waitstate for the OTP
   FlashRegs.FOTPWAIT.bit.OTPWAIT = 4;

   //                CAUTION
   //ONLY THE DEFAULT VALUE FOR THESE 2 REGISTERS SHOULD BE USED
   FlashRegs.FSTDBYWAIT.bit.STDBYWAIT = 0x01FF;
   FlashRegs.FACTIVEWAIT.bit.ACTIVEWAIT = 0x01FF;
   EDIS;

   //Force a pipeline flush to ensure that the write to
   //the last register configured occurs before returning.

   asm(" RPT #7 || NOP");
}


// This function will copy the specified memory contents from
// one location to another.
//
//  Uint16 *SourceAddr        Pointer to the first word to be moved
//                          SourceAddr < SourceEndAddr
//  Uint16* SourceEndAddr     Pointer to the last word to be moved
//  Uint16* DestAddr          Pointer to the first destination word
//
// No checks are made for invalid memory locations or that the
// end address is > then the first start address.

void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr)
{
  while(SourceAddr < SourceEndAddr)
  {
    *DestAddr++ = *SourceAddr++;
  }
  return;
}
