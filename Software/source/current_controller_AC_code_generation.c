/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: current_controller_AC_code_generation.c
 *
 * Code generated for Simulink model 'current_controller_AC_code_generation'.
 *
 * Model version                  : 1.1
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Sun May 12 17:15:49 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "current_controller_AC_code_generation.h"
#include "rtwtypes.h"

/* Block signals and states (default storage) */
DW_C_C rtDW_C_C;

/* External inputs (root inport signals with default storage) */
ExtU_C_C rtU_C_C;

/* External outputs (root outports fed by signals with default storage) */
ExtY_C_C rtY_C_C;

/* Model step function */
void current_controller_AC_code_generation_step(void)
{
  real_T rtb_Multiply_C_C;
  real_T rtb_Sum2_C_C;
  real_T rtb_Sum_C_C;
  real_T rtb_Sum_g_C_C;
  real_T rtb_proportional_gain_C_C;

  /* Gain: '<S3>/proportional_gain' incorporates:
   *  Gain: '<S1>/Gain7'
   *  Inport: '<Root>/inductor_current'
   *  Inport: '<Root>/reference_current'
   *  Inport: '<Root>/sin_value'
   *  Product: '<S1>/multibly'
   *  Sum: '<S1>/Sum1'
   *  Sum: '<S1>/Sum2'
   *  UnitDelay: '<S1>/Unit Delay'
   */
  rtb_proportional_gain_C_C = ((rtU_C_C.inductor_current_C_C +
    rtDW_C_C.UnitDelay_DSTATE_C_C) * 0.5 - rtU_C_C.reference_current_C_C *
    rtU_C_C.sin_value_C_C) * 9.65;

  /* Gain: '<S3>/proportional_gain1' */
  rtb_Sum2_C_C = 0.0307 * rtb_proportional_gain_C_C;

  /* Sum: '<S3>/Sum' incorporates:
   *  Inport: '<Root>/sin_value'
   *  Product: '<S3>/multibly'
   *  UnitDelay: '<S3>/Unit Delay'
   */
  rtb_Sum_C_C = rtb_Sum2_C_C * rtU_C_C.sin_value_C_C +
    rtDW_C_C.UnitDelay_DSTATE_o_C_C;

  /* Sum: '<S3>/Sum2' incorporates:
   *  Inport: '<Root>/cos_value'
   *  Product: '<S3>/multibly2'
   *  UnitDelay: '<S3>/Unit Delay1'
   */
  rtb_Sum2_C_C = rtb_Sum2_C_C * rtU_C_C.cos_value_C_C +
    rtDW_C_C.UnitDelay1_DSTATE_C_C;

  /* Sum: '<S3>/Sum1' incorporates:
   *  Inport: '<Root>/cos_value'
   *  Inport: '<Root>/sin_value'
   *  Product: '<S3>/multibly1'
   *  Product: '<S3>/multibly4'
   */
  rtb_proportional_gain_C_C = (rtb_Sum_C_C * rtU_C_C.sin_value_C_C +
    rtb_proportional_gain_C_C) + rtb_Sum2_C_C * rtU_C_C.cos_value_C_C;

  /* Switch: '<S4>/Switch2' incorporates:
   *  Inport: '<Root>/U_DC'
   *  RelationalOperator: '<S4>/LowerRelop1'
   */
  if (rtb_proportional_gain_C_C > rtU_C_C.U_DC_C_C) {
    rtb_Multiply_C_C = rtU_C_C.U_DC_C_C;
  } else {
    /* Gain: '<S3>/Multiply' */
    rtb_Multiply_C_C = -rtU_C_C.U_DC_C_C;

    /* Switch: '<S4>/Switch' incorporates:
     *  Gain: '<S3>/Multiply'
     *  RelationalOperator: '<S4>/UpperRelop'
     */
    if (!(rtb_proportional_gain_C_C < -rtU_C_C.U_DC_C_C)) {
      rtb_Multiply_C_C = rtb_proportional_gain_C_C;
    }

    /* End of Switch: '<S4>/Switch' */
  }

  /* End of Switch: '<S4>/Switch2' */

  /* Sum: '<S2>/Sum1' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Constant: '<S2>/Constant2'
   *  Inport: '<Root>/U_DC'
   *  Product: '<S2>/Divide'
   *  Product: '<S2>/Divide1'
   */
  rtb_Sum_g_C_C = rtb_Multiply_C_C / rtU_C_C.U_DC_C_C * 0.5 + 0.5;

  /* Outport: '<Root>/CMP1A' incorporates:
   *  Constant: '<S2>/Constant3'
   *  Product: '<S2>/Divide2'
   */
  rtY_C_C.CMP1A_C_C = (uint32_T)(800.0 * rtb_Sum_g_C_C);

  /* Outport: '<Root>/CMP2A' incorporates:
   *  Constant: '<S2>/Constant'
   *  Constant: '<S2>/Constant4'
   *  Product: '<S2>/Divide3'
   *  Sum: '<S2>/Sum'
   */
  rtY_C_C.CMP2A_C_C = (uint32_T)((1.0 - rtb_Sum_g_C_C) * 800.0);

  /* Outport: '<Root>/Uinv' */
  rtY_C_C.Uinv_C_C = rtb_Multiply_C_C;

  /* Sum: '<S3>/Sum3' */
  rtb_Multiply_C_C = rtb_proportional_gain_C_C - rtb_Multiply_C_C;

  /* Update for UnitDelay: '<S1>/Unit Delay' incorporates:
   *  Inport: '<Root>/inductor_current'
   */
  rtDW_C_C.UnitDelay_DSTATE_C_C = rtU_C_C.inductor_current_C_C;

  /* Update for UnitDelay: '<S3>/Unit Delay' incorporates:
   *  Inport: '<Root>/sin_value'
   *  Product: '<S3>/multibly3'
   *  Sum: '<S3>/Sum4'
   */
  rtDW_C_C.UnitDelay_DSTATE_o_C_C = rtb_Sum_C_C - rtU_C_C.sin_value_C_C *
    rtb_Multiply_C_C;

  /* Update for UnitDelay: '<S3>/Unit Delay1' incorporates:
   *  Inport: '<Root>/cos_value'
   *  Product: '<S3>/multibly5'
   *  Sum: '<S3>/Sum5'
   */
  rtDW_C_C.UnitDelay1_DSTATE_C_C = rtb_Sum2_C_C - rtb_Multiply_C_C *
    rtU_C_C.cos_value_C_C;
}
//
/* Model initialize function */
void current_controller_AC_code_generation_initialize(float sin_initial_cond)
{
    //rtU_C_C.reference_current_C_C=1;
    rtDW_C_C.UnitDelay_DSTATE_o_C_C=sin_initial_cond;

    //rtU_C_C.reference_current_C_C=1.5;
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
