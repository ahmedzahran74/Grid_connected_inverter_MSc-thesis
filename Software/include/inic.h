#ifndef __INIC_H_
  #define __INIC_H_
  #include "F2806x_Device.h"
  #include "F2806x_GlobalPrototypes.h"
  #include "F2806x_usDelay.h"
  #include "ADC.h"
  #include "PWM.h"
//  #include "QEP_BUTT.h"
//  #include "CPLDHandler.h"
  #include "CLA.h"

  #define Device_cal (void   (*)(void))0x3D7C80
  extern volatile struct SCI_REGS *sci_ptr_terminal;



  #define LSPCLK_DIVIDER_1	0
  #define LSPCLK_DIVIDER_2	1
  #define LSPCLK_DIVIDER_4	2
  #define LSPCLK_DIVIDER_6	3
  #define LSPCLK_DIVIDER_8	4
  #define LSPCLK_DIVIDER_10	5
  #define LSPCLK_DIVIDER_12 6
  #define LSPCLK_DIVIDER_14	7


  #define SYSCLKOUT 80000000L
  #define LSPCLK_DIVIDER LSPCLK_DIVIDER_4
  #define LSPCLK SYSCLKOUT/LSPCLK_DIVIDER

  /* Function declarations */
  void DeviceInit(void);
  void SetSCITMSmon(volatile struct SCI_REGS *ptr);
  void WDogDisable(void);
  void PLLset(Uint16 val);
  void InitFlash(void);
  void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr);
#endif
