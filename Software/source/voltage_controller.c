/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: voltage_controller_code_generation.c
 *
 * Code generated for Simulink model 'voltage_controller_code_generation'.
 *
 * Model version                  : 1.0
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Sun May 12 20:31:02 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "voltage_controller_code_generation.h"
#include "rtwtypes.h"
extern float VDC;
/* Block signals and states (default storage) */
DW_V_C rtDW_V_C;

/* External inputs (root inport signals with default storage) */
ExtU_V_C rtU_V_C;

/* External outputs (root outports fed by signals with default storage) */
ExtY_V_C rtY_V_C;

/* Real-time model */
static RT_MODEL_V_C rtM_V_C_;
RT_MODEL_V_C *const rtM_V_C = &rtM_V_C_;

/* Model step function */
float average;
void voltage_controller_code_generation_step(void)
{
  real_T rtb_Sum1_V_C;
  real_T rtb_Sum_V_C;
  static int i=0;

  /* Sum: '<S1>/Sum of Elements' incorporates:
   *  S-Function (sfix_udelay): '<S1>/Tapped Delay'
   */
  rtDW_V_C.sum = rtDW_V_C.sum - rtDW_V_C.TappedDelay_X_V_C[i];
  rtDW_V_C.TappedDelay_X_V_C[i] = rtU_V_C.V_DC_V_C;
  rtDW_V_C.sum = rtDW_V_C.sum + rtDW_V_C.TappedDelay_X_V_C[i];

  i++;
  if (i > 99)
  {
      i = 0;
  }

  average=rtDW_V_C.sum/100;
  /* End of Sum: '<S1>/Sum of Elements' */

  /* Sum: '<S1>/Sum' incorporates:
   *  Gain: '<S1>/Gain'
   *  Inport: '<Root>/Vref'
   */

  rtb_Sum_V_C = rtU_V_C.Vref_V_C - 0.01 * rtDW_V_C.sum;

  /* Sum: '<S2>/Sum1' incorporates:
   *  Gain: '<S2>/Gain7'
   *  Gain: '<S2>/Gain9'
   *  Sum: '<S2>/Sum4'
   *  UnitDelay: '<S2>/I_peak_previous'
   *  UnitDelay: '<S2>/Unit Delay'
   */
    rtb_Sum1_V_C = (0.00123 * rtb_Sum_V_C + rtDW_V_C.I_peak_previous_DSTATE_V_C) +
            (rtb_Sum_V_C - rtDW_V_C.UnitDelay_DSTATE_V_C) * 0.19684;

  /* Switch: '<S3>/Switch2' incorporates:
   *  Constant: '<S1>/Constant'
   *  Constant: '<S1>/Constant1'
   *  RelationalOperator: '<S3>/LowerRelop1'
   *  RelationalOperator: '<S3>/UpperRelop'
   *  Switch: '<S3>/Switch'
   */
  if (rtb_Sum1_V_C > 7.5) {
    rtb_Sum1_V_C = 7.5;
  } else if (rtb_Sum1_V_C < 0.0) {
    /* Switch: '<S3>/Switch' incorporates:
     *  Constant: '<S1>/Constant'
     */
    rtb_Sum1_V_C = 0.0;
  }

  /* End of Switch: '<S3>/Switch2' */

  /* Outport: '<Root>/I_peak_ref' */
  rtY_V_C.I_peak_ref_V_C = rtb_Sum1_V_C;

  /* Update for S-Function (sfix_udelay): '<S1>/Tapped Delay' incorporates:
   *  Inport: '<Root>/V_DC'
   */


  /* End of Update for S-Function (sfix_udelay): '<S1>/Tapped Delay' */

  /* Update for UnitDelay: '<S2>/I_peak_previous' */
  rtDW_V_C.I_peak_previous_DSTATE_V_C = rtb_Sum1_V_C;

  /* Update for UnitDelay: '<S2>/Unit Delay' */
  rtDW_V_C.UnitDelay_DSTATE_V_C = rtb_Sum_V_C;

}

/* Model initialize function */
void voltage_controller_code_generation_initialize(float initial_voltage)
{
  {
    int16_T i_V_C;

    /* InitializeConditions for S-Function (sfix_udelay): '<S1>/Tapped Delay' */
    for (i_V_C = 0; i_V_C < 100; i_V_C++) {
      rtDW_V_C.TappedDelay_X_V_C[i_V_C] = initial_voltage;
    }
    rtDW_V_C.sum=initial_voltage*100;

    /* End of InitializeConditions for S-Function (sfix_udelay): '<S1>/Tapped Delay' */
    rtU_V_C.Vref_V_C=75;
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
