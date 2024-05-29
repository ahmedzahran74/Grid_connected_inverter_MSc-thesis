/*
 * CLA.h
 *
 *  Created on: 2017 máj. 24
 *      Author: A. Futo
 */

  #ifndef INCLUDE_CLA_H_
  #define INCLUDE_CLA_H_

#include "F2806x_Cla_typedefs.h"// F2806x CLA Type definitions
#include "F2806x_Device.h"      // F2806x Headerfile Include File
#include "F2806x_Cla_defines.h"
#include "CLA_shared.h"

#define CLA_ADC_ISR_RUNNING ( Cla1Regs.MIRUN.bit.INT1)
#define CLA_ADC_ISR_STOPPED (!Cla1Regs.MIRUN.bit.INT1)


extern void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr);

void CLA_Init(void);                             //initialize CLA and start task 8 to clear message RAM.
void CLA_Wait_for_Cla1ToCpuMsgRAM_cleared(void); //wait for CLA to finish clearing message RAM.
                                                 //Needs to be called after CLA_Init, before enabling ADC interrupt.


#endif /* INCLUDE_CLA_H_ */
