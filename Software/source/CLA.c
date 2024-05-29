/*
 * CLA.c
 *
 *  Created on: 2017 máj. 24
 *      Author: A. Futo
 */

#include "CLA.h"

#define CLA_PROG_ENABLE      0x0001
#define CLARAM0_ENABLE       0x0010
#define CLARAM1_ENABLE       0x0020
#define CLARAM2_ENABLE       0x0040
#define CLA_RAM0CPUE         0x0100
#define CLA_RAM1CPUE         0x0200
#define CLA_RAM2CPUE         0x0400

//#define HARDWARE 1

//
// These are defined by the linker file and used to copy
// the CLA code from its load address to its run address
// in CLA program memory
//
extern Uint16 Cla1funcsLoadStart;
extern Uint16 Cla1funcsLoadEnd;
extern Uint16 Cla1funcsLoadSize;
extern Uint16 Cla1funcsRunStart;
extern Uint16 Cla1Prog_Start;
//
// These are defined by the linker file and used to copy
// the CLA math tables from its load address to its run address
// into one of the CLA data RAMs
//
extern Uint16 Cla1mathTablesLoadStart;
extern Uint16 Cla1mathTablesLoadEnd;
extern Uint16 Cla1mathTablesLoadSize;
extern Uint16 Cla1mathTablesRunStart;

extern Uint16 Cla1ConstLoadStart;
extern Uint16 Cla1ConstLoadEnd;
extern Uint16 Cla1ConstLoadSize;
extern Uint16 Cla1ConstRunStart;


//CLA ISRs
__interrupt void cla1_task1_isr( void );
__interrupt void cla1_task2_isr( void );
__interrupt void cla1_task3_isr( void );
__interrupt void cla1_task4_isr( void );
__interrupt void cla1_task5_isr( void );
__interrupt void cla1_task6_isr( void );
__interrupt void cla1_task7_isr( void );
__interrupt void cla1_task8_isr( void );





void CLA_Init(void)
{
  // Configure CLA

    /*  Assign user defined ISR to the PIE vector table */
     EALLOW;
    PieVectTable.CLA1_INT1  = &cla1_task1_isr;
    PieVectTable.CLA1_INT2  = &cla1_task2_isr;
    PieVectTable.CLA1_INT3  = &cla1_task3_isr;
    PieVectTable.CLA1_INT4  = &cla1_task4_isr;
    PieVectTable.CLA1_INT5  = &cla1_task5_isr;
    PieVectTable.CLA1_INT6  = &cla1_task6_isr;
    PieVectTable.CLA1_INT7  = &cla1_task7_isr;
    PieVectTable.CLA1_INT8  = &cla1_task8_isr;
     EDIS;

     //Copy over the CLA code(if running in standalone mode from FLASH)
     MemCopy(&Cla1funcsLoadStart, &Cla1funcsLoadEnd, &Cla1funcsRunStart);

     //Copy over the CLA math tables(if running in standalone mode from FLASH
     //and using the CLAMath Library)
     MemCopy(&Cla1mathTablesLoadStart, &Cla1mathTablesLoadEnd, &Cla1mathTablesRunStart);
     //Copy const_cla initialized constant data
     MemCopy(&Cla1ConstLoadStart, &Cla1ConstLoadEnd, &Cla1ConstRunStart);

     /*  Compute all CLA task vectors */

      EALLOW;
      Cla1Regs.MVECT1 = (Uint16)((Uint32)&Cla1Task1 -(Uint32)&Cla1Prog_Start);
      Cla1Regs.MVECT2 = (Uint16)((Uint32)&Cla1Task2 -(Uint32)&Cla1Prog_Start);
      Cla1Regs.MVECT3 = (Uint16)((Uint32)&Cla1Task3 -(Uint32)&Cla1Prog_Start);
      Cla1Regs.MVECT4 = (Uint16)((Uint32)&Cla1Task4 -(Uint32)&Cla1Prog_Start);
      Cla1Regs.MVECT5 = (Uint16)((Uint32)&Cla1Task5 -(Uint32)&Cla1Prog_Start);
      Cla1Regs.MVECT6 = (Uint16)((Uint32)&Cla1Task6 -(Uint32)&Cla1Prog_Start);
      Cla1Regs.MVECT7 = (Uint16)((Uint32)&Cla1Task7 -(Uint32)&Cla1Prog_Start);
      Cla1Regs.MVECT8 = (Uint16)((Uint32)&Cla1Task8 -(Uint32)&Cla1Prog_Start);
      EDIS;

      //  Step 3 : Mapping CLA tasks
      /*  All tasks are enabled and will be started by an ePWM trigger
       *  Map CLA program memory to the CLA and enable software breakpoints
       */

      EALLOW;
      Cla1Regs.MPISRCSEL1.bit.PERINT1SEL  = CLA_INT1_ADCINT1;
      Cla1Regs.MPISRCSEL1.bit.PERINT2SEL  = CLA_INT2_NONE;
      Cla1Regs.MPISRCSEL1.bit.PERINT3SEL  = CLA_INT3_NONE;
      Cla1Regs.MPISRCSEL1.bit.PERINT4SEL  = CLA_INT4_NONE;
      Cla1Regs.MPISRCSEL1.bit.PERINT5SEL  = CLA_INT5_NONE;
      Cla1Regs.MPISRCSEL1.bit.PERINT6SEL  = CLA_INT6_NONE;
      Cla1Regs.MPISRCSEL1.bit.PERINT7SEL  = CLA_INT7_NONE;
      Cla1Regs.MPISRCSEL1.bit.PERINT8SEL  = CLA_INT8_NONE;
      Cla1Regs.MIER.all                   = 0x00FF; //enable all 8 tasks
      EDIS;

      /*  Enable CLA interrupts at the group and subgroup levels */
      PieCtrlRegs.PIEIER11.all       = 0xFFFF;  //enable all 8 task interrupts for main CPU
      IER |= M_INT11;   //enable CPU interrupt 11.

      /* Switch the CLA program space to the CLA and enable software forcing
       * Also switch over CLA data ram 0,1 and 2
       * CAUTION: The RAMxCPUE bits can only be enabled by writing to the register
       * and not the individual bit field. Furthermore, the status of these bitfields
       * is not reflected in either the watch or register views - they always read as
       * zeros. This is a known bug and the user is advised to test CPU accessibilty
       * first before proceeding
       */

      EALLOW;
      Cla1Regs.MMEMCFG.all = CLA_PROG_ENABLE|CLARAM0_ENABLE|CLARAM1_ENABLE|CLARAM2_ENABLE|CLA_RAM0CPUE|CLA_RAM1CPUE|CLA_RAM2CPUE;
      Cla1Regs.MCTL.bit.IACKE = 1; //enable start from software
      EDIS;

      Cla1ToCpuMsgRAM_cleared = 0;  //set flag to enable clearing of Cla1ToCpuMsgRAM
      Cla1ForceTask8();             //This will start Task 8 for clearing the Cla1ToCpuMsgRAM
}

void CLA_Wait_for_Cla1ToCpuMsgRAM_cleared(void)
{
    while(Cla1Regs.MIRUN.bit.INT8 == 1); //wait for CLA to finish clearing message RAM
    return;
}
