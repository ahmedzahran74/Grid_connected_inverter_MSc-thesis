//###########################################################################
// Description:
//
// Declare shared memory variables and assign them to specific CLA-accessible
// memory locations
//
//! \b Memory \b Allocation \n
//!  - CLA1 Data RAM 0 (RAML1) : Cla1DataRam0
//!  - CLA1 Data RAM 1 (RAML2) : Cla1DataRam1
//!  - CLA1 Data RAM 2 (RAML0) : Cla1DataRam2
//!  - CLA1 to CPU Message RAM : Cla1ToCpuMsgRAM
//!  - CPU to CLA1 Message RAM : CpuToCla1MsgRAM
//
//###########################################################################

#include "F2806x_Cla_typedefs.h"// F2806x CLA Type definitions
#include "F2806x_Device.h"      // F2806x Headerfile Include File
#include "CLA_shared.h"


//GLobal Data
 //Ensure that all data is placed in the data rams

//Task 1 (C) Variables




//#pragma DATA_SECTION(Valtozo,"Cla1ToCpuMsgRAM");
//tipus Valtozo;
//#pragma DATA_SECTION(I1_AC_MES,"Cla1DataRam0");
//
//#pragma DATA_SECTION(I2_AC_MES,"Cla1DataRam0");
//
//#pragma DATA_SECTION(I_DC_MES,"Cla1DataRam0");
//
//#pragma DATA_SECTION(U_AC_MES,"Cla1DataRam0");
//
//#pragma DATA_SECTION(U_DC_MES,"Cla1DataRam0");
//
//#pragma DATA_SECTION(U_OUT_MES,"Cla1DataRam0");
//
//#pragma DATA_SECTION(U_OUT_MES_PROTECTED,"Cla1DataRam0");
//
//
//#pragma DATA_SECTION(enableOutputController,"CpuToCla1MsgRAM");
//
//#pragma DATA_SECTION(output_current_controller,"Cla1DataRam0");
//
//#pragma DATA_SECTION(output_voltage_controller,"Cla1DataRam0");
//
//#pragma DATA_SECTION(i_dc_out_ref,"Cla1DataRam0");
//
//#pragma DATA_SECTION(u_dc_out_ref,"Cla1DataRam0");

//Task 2 (C) Variables

//Task 3 (C) Variables

//Task 4 (C) Variables

//Task 5 (C) Variables

//Task 6 (C) Variables

//Task 7 (C) Variables

//Task 8 (C) Variables
#pragma DATA_SECTION(Cla1ToCpuMsgRAM_cleared,"Cla1DataRam1");
Uint32 Cla1ToCpuMsgRAM_cleared = 1;

//Common (C) Variables


