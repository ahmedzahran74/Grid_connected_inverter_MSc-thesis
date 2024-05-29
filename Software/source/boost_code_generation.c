/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: boost_code_generation.c
 *
 * Code generated for Simulink model 'boost_code_generation'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Fri May 17 01:11:51 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "boost_code_generation.h"
#include "rtwtypes.h"

/* Block signals and states (default storage) */
DW_boost rtDW_boost;

/* External inputs (root inport signals with default storage) */
ExtU_boost rtU_boost;

/* External outputs (root outports fed by signals with default storage) */
ExtY_boost rtY_boost;

/* Real-time model */
static RT_MODEL_boost rtM_boost_;
RT_MODEL_boost *const rtM_boost = &rtM_boost_;

/* Model step function */
void boost_code_generation_step(void)
{
  real_T rtb_Sum1_boost;
  real_T rtb_Sum1_d_boost;
  real_T rtb_Sum1_k_boost;
  real_T rtb_error_boost;

  /* Sum: '<S1>/Sum1' incorporates:
   *  Inport: '<Root>/V_op'
   *  Inport: '<Root>/Vref'
   */
  rtb_Sum1_boost = rtU_boost.Vref_boost - rtU_boost.V_op_boost;

  /* Sum: '<S3>/Sum1' incorporates:
   *  Gain: '<S3>/Gain7'
   *  Gain: '<S3>/Gain9'
   *  Sum: '<S3>/Sum4'
   *  UnitDelay: '<S3>/I_peak_previous'
   *  UnitDelay: '<S3>/Unit Delay'
   */
  rtb_Sum1_k_boost = (0.0004872 * rtb_Sum1_boost +
                      rtDW_boost.I_peak_previous_DSTATE_boost) + (rtb_Sum1_boost
    - rtDW_boost.UnitDelay_DSTATE_boost) * 0.0002148;

  /* Switch: '<S6>/Switch2' incorporates:
   *  Constant: '<S1>/Constant'
   *  Constant: '<S1>/Constant1'
   *  RelationalOperator: '<S6>/LowerRelop1'
   *  RelationalOperator: '<S6>/UpperRelop'
   *  Switch: '<S6>/Switch'
   */
  if (rtb_Sum1_k_boost > 10.0) {
    rtb_Sum1_k_boost = 10.0;
  } else if (rtb_Sum1_k_boost < 0.0) {
    /* Switch: '<S6>/Switch' incorporates:
     *  Constant: '<S1>/Constant'
     */
    rtb_Sum1_k_boost = 0.0;
  }

  /* End of Switch: '<S6>/Switch2' */

  /* Outputs for Atomic SubSystem: '<S1>/Discrete controller' */
  /* Sum: '<S2>/Sum' incorporates:
   *  Gain: '<S2>/Gain7'
   *  Gain: '<S2>/Multiply'
   *  Inport: '<Root>/IL'
   *  Sum: '<S2>/Sum1'
   *  UnitDelay: '<S2>/Unit Delay'
   */
  rtb_error_boost = (-rtU_boost.IL_boost + rtDW_boost.UnitDelay_DSTATE_h_boost) *
    0.5 - rtb_Sum1_k_boost;

  /* Sum: '<S4>/Sum1' incorporates:
   *  Gain: '<S4>/Gain7'
   *  Gain: '<S4>/Gain9'
   *  Sum: '<S4>/Sum4'
   *  UnitDelay: '<S4>/Unit Delay'
   *  UnitDelay: '<S4>/Unit Delay1'
   */
  rtb_Sum1_d_boost = (0.0307 * rtb_error_boost +
                      rtDW_boost.UnitDelay1_DSTATE_boost) + (rtb_error_boost -
    rtDW_boost.UnitDelay_DSTATE_d_boost) * 7.678;

  /* Switch: '<S5>/Switch2' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Inport: '<Root>/V_op'
   *  RelationalOperator: '<S5>/LowerRelop1'
   *  RelationalOperator: '<S5>/UpperRelop'
   *  Switch: '<S5>/Switch'
   */
  if (rtb_Sum1_d_boost > rtU_boost.V_op_boost) {
    rtb_Sum1_d_boost = rtU_boost.V_op_boost;
  } else if (rtb_Sum1_d_boost < 0.0) {
    /* Switch: '<S5>/Switch' incorporates:
     *  Constant: '<S2>/Constant1'
     */
    rtb_Sum1_d_boost = 0.0;
  }

  /* End of Switch: '<S5>/Switch2' */

  /* Update for UnitDelay: '<S4>/Unit Delay' */
  rtDW_boost.UnitDelay_DSTATE_d_boost = rtb_error_boost;

  /* Update for UnitDelay: '<S2>/Unit Delay' incorporates:
   *  Gain: '<S2>/Multiply'
   *  Inport: '<Root>/IL'
   */
  rtDW_boost.UnitDelay_DSTATE_h_boost = -rtU_boost.IL_boost;

  /* Update for UnitDelay: '<S4>/Unit Delay1' */
  rtDW_boost.UnitDelay1_DSTATE_boost = rtb_Sum1_d_boost;

  /* Outport: '<Root>/CMP_B' incorporates:
   *  Constant: '<S1>/Constant3'
   *  Constant: '<S2>/Constant2'
   *  Inport: '<Root>/V_op'
   *  Product: '<S1>/Divide1'
   *  Product: '<S2>/Divide'
   *  Sum: '<S2>/Sum2'
   */
  rtY_boost.CMP_B_boost = (uint32_T)((1.0 - rtb_Sum1_d_boost /
    rtU_boost.V_op_boost) * 800.0);

  /* End of Outputs for SubSystem: '<S1>/Discrete controller' */

  /* Outport: '<Root>/Iref' */
  rtY_boost.Iref_boost = rtb_Sum1_k_boost;

  /* Update for UnitDelay: '<S3>/I_peak_previous' */
  rtDW_boost.I_peak_previous_DSTATE_boost = rtb_Sum1_k_boost;

  /* Update for UnitDelay: '<S3>/Unit Delay' */
  rtDW_boost.UnitDelay_DSTATE_boost = rtb_Sum1_boost;
}

/* Model initialize function */
void boost_code_generation_initialize(void)
{
  /* (no initialization code required) */
    rtU_boost.Vref_boost=65;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
