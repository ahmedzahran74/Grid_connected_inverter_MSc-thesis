/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: current_controller_code_generation.c
 *
 * Code generated for Simulink model 'current_controller_code_generation'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Sun May 12 14:41:01 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "current_controller_code_generation.h"
#include "rtwtypes.h"

/* External inputs (root inport signals with default storage) */
ExtU_cs rtU_m;

/* External outputs (root outports fed by signals with default storage) */
ExtY_jz rtY_h;

/* Model step function */
void current_controller_code_generation_step(void)
{
  real_T rtb_multibly1;

  /* Product: '<S3>/multibly1' incorporates:
   *  Constant: '<S3>/Constant'
   *  Inport: '<Root>/sin_value'
   */
  rtb_multibly1 = 17.0 * rtU_m.sin_value;

  /* Switch: '<S4>/Switch2' incorporates:
   *  Gain: '<S3>/Multiply'
   *  Inport: '<Root>/UDC'
   *  RelationalOperator: '<S4>/LowerRelop1'
   *  RelationalOperator: '<S4>/UpperRelop'
   *  Switch: '<S4>/Switch'
   */
  if (rtb_multibly1 > rtU_m.UDC) {
    rtb_multibly1 = rtU_m.UDC;
  } else if (rtb_multibly1 < -rtU_m.UDC) {
    /* Switch: '<S4>/Switch' incorporates:
     *  Gain: '<S3>/Multiply'
     */
    rtb_multibly1 = -rtU_m.UDC;
  }

  /* End of Switch: '<S4>/Switch2' */

  /* Sum: '<S2>/Sum1' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Constant: '<S2>/Constant2'
   *  Inport: '<Root>/UDC'
   *  Product: '<S2>/Divide'
   *  Product: '<S2>/Divide1'
   */
  rtb_multibly1 = rtb_multibly1 / rtU_m.UDC * 0.5 + 0.5;

  /* Outport: '<Root>/CMP2A' incorporates:
   *  Constant: '<S2>/Constant'
   *  Constant: '<S2>/Constant4'
   *  Product: '<S2>/Divide3'
   *  Sum: '<S2>/Sum'
   */
  rtY_h.CMP2A = (uint32_T)((1.0 - rtb_multibly1) * 800.0);

  /* Outport: '<Root>/CMP1A' incorporates:
   *  Constant: '<S2>/Constant3'
   *  Product: '<S2>/Divide2'
   */
  rtY_h.CMP1A = (uint32_T)(800.0 * rtb_multibly1);
}

/* Model initialize function */
void current_controller_code_generation_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
