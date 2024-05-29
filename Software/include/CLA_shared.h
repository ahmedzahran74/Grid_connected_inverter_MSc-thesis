//###########################################################################
// Description:
//
// Declare shared variables
//
//###########################################################################

#ifndef CLA_SHARED_H_
#define CLA_SHARED_H_
#ifdef __cplusplus
extern "C" {
#endif

#define Cla1ToCpuMsgRAM_START   0x001480    //For TMS320C28069. Start address of Cla1ToCpuMsgRAM to be cleared by CLA during initialization
#define Cla1ToCpuMsgRAM_END     0x001500    //For TMS320C28069. End address of Cla1ToCpuMsgRAM. RAM at this address will not be cleared.

#include "ADC.h"

#define M_PI ((float) 3.1415926535897932384626433832795)
#define M_SQRT2 ((float) 1.4142135623730950488016887242097)
#define M_SQRT3 ((float) 1.7320508075688772935274463415059)

#define I1_AC_ADC_RESULT AdcResult.ADCRESULT1
#define I2_AC_ADC_RESULT AdcResult.ADCRESULT2
#define I_DC_ADC_RESULT AdcResult.ADCRESULT9
#define U_AC_ADC_RESULT AdcResult.ADCRESULT0
#define U_DC_ADC_RESULT AdcResult.ADCRESULT3
#define U_OUT_ADC_RESULT AdcResult.ADCRESULT4
#define U_OUT_PROTECTED_ADC_RESULT AdcResult.ADCRESULT5

#define I_GAIN 27.5455f
#define U_DC_GAIN 15.5047f
#define U_AC_GAIN 24.2424f
#define ADC_REF_VOLTAGE 3.3f

#define MAX(A,B) ((A > B) ? A:B)
#define MIN(A,B) ((A < B) ? A:B)

//PI controller structure;
typedef struct {
    float x;
    float x_old;
    float AP;
    float I;
    float max;
    float min;
    float y;
} CLA_PI_type;

//Task 1 (C) Variables
extern Uint32 Cla1ToCpuMsgRAM_cleared; //used during initialization, do not remove!

extern Meas_t I1_AC_MES;
extern Meas_t I2_AC_MES;
extern Meas_t I_DC_MES;
extern Meas_t U_AC_MES;
extern Meas_t U_DC_MES;
extern Meas_t U_OUT_MES;
extern Meas_t U_OUT_MES_PROTECTED;

extern CLA_PI_type output_current_controller;
extern CLA_PI_type output_voltage_controller;
extern float i_dc_out_ref;
extern float u_dc_out_ref;
extern Uint32 enableOutputController;





//Task 2 (C) Variables

//Task 3 (C) Variables

//Task 4 (C) Variables

//Task 5 (C) Variables

//Task 6 (C) Variables

//Task 7 (C) Variables

//Task 8 (C) Variables

//Common (C) Variables

//CLA C Tasks
__interrupt void Cla1Task1();
__interrupt void Cla1Task2();
__interrupt void Cla1Task3();
__interrupt void Cla1Task4();
__interrupt void Cla1Task5();
__interrupt void Cla1Task6();
__interrupt void Cla1Task7();
__interrupt void Cla1Task8();

//C Function Prototypes


#ifdef __cplusplus
}
#endif /* extern "C" */
#endif /*CLA_SHARED_H_*/
