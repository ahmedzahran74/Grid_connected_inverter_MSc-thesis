;// TI File $Revision: /main/2 $ 
;// Checkin $Date: January 4, 2011   10:10:05 $ 
;//###########################################################################
;//
;// FILE:  F2806x_CodeStartBranch.asm	
;//
;// TITLE: Branch for redirecting code execution after boot. 
;//
;// For these examples, code_start is the first code that is executed after
;// exiting the boot ROM code. 
;//
;// The codestart section in the linker cmd file is used to physically place
;// this code at the correct memory location.  This section should be placed 
;// at the location the BOOT ROM will re-direct the code to.  For example, 
;// for boot to FLASH this code will be located at 0x3f7ff6. 
;//
;// In addition, the example F2806x projects are setup such that the codegen
;// entry point is also set to the code_start label.  This is done by linker 
;// option -e in the project build options.  When the debugger loads the code,
;// it will automatically set the PC to the "entry point" address indicated by
;// the -e linker option.  In this case the debugger is simply assigning the PC, 
;// it is not the same as a full reset of the device. 
;// 
;// The compiler may warn that the entry point for the project is other then
;//  _c_init00.  _c_init00 is the C environment setup and is run before 
;// main() is entered. The code_start code will re-direct the execution 
;// to _c_init00 and thus there is no worry and this warning can be ignored. 
;// 
;//###########################################################################
;// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V135 $ 
;// $Release Date: Sep 8, 2012 $ 
;//###########################################################################

***********************************************************************

WD_DISABLE	.set	1		;set to 1 to disable WD, else set to 0

    .ref _c_int00
    .global code_start

***********************************************************************
* Function: codestart section
*
* Description: Branch to code starting point
***********************************************************************

    .sect "codestart"

code_start:
    .if WD_DISABLE == 1
        LB wd_disable       ;Branch to watchdog disable code
    .else
        LB ram2null         ;Branch to ram2null
    .endif

;end codestart section

***********************************************************************
* Function: wd_disable
*
* Description: Disables the watchdog timer
***********************************************************************
    .if WD_DISABLE == 1

    .text
wd_disable:
    SETC OBJMODE        ;Set OBJMODE for 28x object code
    EALLOW              ;Enable EALLOW protected register access
    MOVZ DP, #7029h>>6  ;Set data page for WDCR register
    MOV @7029h, #0068h  ;Set WDDIS bit in WDCR to disable WD
    EDIS                ;Disable EALLOW protected register access
    LB ram2null         ;Branch to ram2null

    .endif

;end wd_disable

ram2null:
    SETC OBJMODE        ;Set OBJMODE for 28x object code

		MOV		@AL,#0

		MOVL	XAR1,#0
		MOV		@AH,#800h-1
		RPT		@AH || 
		MOV		*XAR1++,AL

		MOVL	XAR1,#8000h
		MOV		@AH,#8000h-1
		RPT		@AH || 
		MOV		*XAR1++,AL

		MOVL	XAR1,#10000h
		MOV		@AH,#4000h-1
		RPT		@AH || 
		MOV		*XAR1++,AL
		
    LB _c_int00         ;Branch to start of boot.asm in RTS library	
	.end
	
;//===========================================================================
;// End of file.
;//===========================================================================