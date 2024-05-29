/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: buck_code_generation.c
 *
 * Code generated for Simulink model 'buck_code_generation'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Fri May 17 00:44:10 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "buck_code_generation.h"
#include "rtwtypes.h"

/* Block signals and states (default storage) */
DW_buck rtDW_buck;

/* External inputs (root inport signals with default storage) */
ExtU_buck rtU_buck;

/* External outputs (root outports fed by signals with default storage) */
ExtY_buck rtY_buck;

/* Real-time model */
static RT_MODEL_buck rtM_buck_;
RT_MODEL_buck *const rtM_buck = &rtM_buck_;

/* Model step function */
void buck_code_generation_step(void)
{
  real_T rtb_Sum1_buck;
  real_T rtb_Sum1_j_buck;
  real_T rtb_Sum_buck;
  real_T rtb_error_buck;

  /* Sum: '<S1>/Sum1' incorporates:
   *  Inport: '<Root>/V_op'
   *  Inport: '<Root>/V_ref'
   */
  rtb_error_buck = rtU_buck.V_ref_buck - rtU_buck.V_op_buck;

  /* Sum: '<S3>/Sum1' incorporates:
   *  Gain: '<S3>/Gain7'
   *  Gain: '<S3>/Gain9'
   *  Sum: '<S3>/Sum4'
   *  UnitDelay: '<S3>/I_peak_previous'
   *  UnitDelay: '<S3>/Unit Delay'
   */
  rtb_Sum1_buck = (0.0004872 * rtb_error_buck +
                   rtDW_buck.I_peak_previous_DSTATE_f_buck) + (rtb_error_buck -
    rtDW_buck.UnitDelay_DSTATE_buck) * 0.0002148;

  /* Switch: '<S5>/Switch2' incorporates:
   *  Constant: '<S1>/Constant4'
   *  Constant: '<S1>/Constant5'
   *  RelationalOperator: '<S5>/LowerRelop1'
   *  RelationalOperator: '<S5>/UpperRelop'
   *  Switch: '<S5>/Switch'
   */
  if (rtb_Sum1_buck > 10.0) {
    rtb_Sum1_buck = 10.0;
  } else if (rtb_Sum1_buck < 0.0) {
    /* Switch: '<S5>/Switch' incorporates:
     *  Constant: '<S1>/Constant4'
     */
    rtb_Sum1_buck = 0.0;
  }

  /* End of Switch: '<S5>/Switch2' */

  /* Sum: '<S2>/Sum' incorporates:
   *  Gain: '<S2>/Gain1'
   *  Inport: '<Root>/IL'
   *  Sum: '<S2>/Sum2'
   *  UnitDelay: '<S2>/Unit Delay1'
   */
  rtb_Sum_buck = rtb_Sum1_buck - (rtU_buck.IL_buck +
    rtDW_buck.UnitDelay1_DSTATE_buck) * 0.5;

  /* Sum: '<S2>/Sum1' incorporates:
   *  Gain: '<S2>/Gain7'
   *  Gain: '<S2>/Gain9'
   *  Sum: '<S2>/Sum4'
   *  UnitDelay: '<S2>/I_peak_previous'
   *  UnitDelay: '<S2>/Unit Delay'
   */
  rtb_Sum1_j_buck = (0.0307 * rtb_Sum_buck +
                     rtDW_buck.I_peak_previous_DSTATE_buck) + (rtb_Sum_buck -
    rtDW_buck.UnitDelay_DSTATE_n_buck) * 7.678;

  /* Switch: '<S4>/Switch2' incorporates:
   *  Constant: '<S2>/Constant'
   *  Inport: '<Root>/V_high'
   *  RelationalOperator: '<S4>/LowerRelop1'
   *  RelationalOperator: '<S4>/UpperRelop'
   *  Switch: '<S4>/Switch'
   */
  if (rtb_Sum1_j_buck > rtU_buck.V_high_buck) {
    rtb_Sum1_j_buck = rtU_buck.V_high_buck;
  } else if (rtb_Sum1_j_buck < 0.0) {
    /* Switch: '<S4>/Switch' incorporates:
     *  Constant: '<S2>/Constant'
     */
    rtb_Sum1_j_buck = 0.0;
  }

  /* End of Switch: '<S4>/Switch2' */

  /* Outport: '<Root>/CMPA' incorporates:
   *  Constant: '<S1>/Constant3'
   *  Inport: '<Root>/V_high'
   *  Product: '<S1>/Divide'
   *  Product: '<S1>/Divide1'
   */
  rtY_buck.CMPA_buck = (uint32_T)(rtb_Sum1_j_buck / rtU_buck.V_high_buck * 800.0);

  /* Outport: '<Root>/Iref' */
  rtY_buck.Iref_buck = rtb_Sum1_buck;

  /* Update for UnitDelay: '<S2>/I_peak_previous' */
  rtDW_buck.I_peak_previous_DSTATE_buck = rtb_Sum1_j_buck;

  /* Update for UnitDelay: '<S3>/I_peak_previous' */
  rtDW_buck.I_peak_previous_DSTATE_f_buck = rtb_Sum1_buck;

  /* Update for UnitDelay: '<S3>/Unit Delay' */
  rtDW_buck.UnitDelay_DSTATE_buck = rtb_error_buck;

  /* Update for UnitDelay: '<S2>/Unit Delay1' incorporates:
   *  Inport: '<Root>/IL'
   */
  rtDW_buck.UnitDelay1_DSTATE_buck = rtU_buck.IL_buck;

  /* Update for UnitDelay: '<S2>/Unit Delay' */
  rtDW_buck.UnitDelay_DSTATE_n_buck = rtb_Sum_buck;
}

/* Model initialize function */
void buck_code_generation_initialize(void)
{
  /* (no initialization code required) */
    rtU_buck.V_ref_buck=30;
}
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
