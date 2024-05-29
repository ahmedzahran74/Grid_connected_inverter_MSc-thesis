
/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PLL_controller.c
 *
 * Code generated for Simulink model 'PLL_controller'.
 *
 * Model version                  : 1.0
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Tue Apr 30 14:27:47 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "PLL_controller.h"
#include "rtwtypes.h"

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;
/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* Model step function */
void PLL_controller_step(void)
{
  real_T rtb_Multibly2;
  real_T rtb_Sum1;
  real_T rtb_Sum1_p;
  real_T rtb_UnitDelay;

  /* Outputs for Atomic SubSystem: '<Root>/PLL_control' */
  /* Sum: '<S1>/Sum' incorporates:
   *  UnitDelay: '<S1>/Unit Delay1'
   *  UnitDelay: '<S1>/Unit Delay2'
   */
  rtb_UnitDelay = rtDW.UnitDelay1_DSTATE - rtDW.UnitDelay2_DSTATE;

  /* Sum: '<S2>/Sum1' incorporates:
   *  Gain: '<S2>/Gain9'
   *  Inport: '<Root>/sinRHO'
   *  Product: '<S1>/Multibly1'
   *  UnitDelay: '<S2>/Unit Delay1'
   */
  rtb_Sum1 = rtb_UnitDelay * rtU.sinRHO * 0.04 + rtDW.UnitDelay1_DSTATE_n;

  /* Switch: '<S4>/Switch2' incorporates:
   *  Constant: '<S1>/Constant'
   *  Constant: '<S1>/Constant1'
   *  RelationalOperator: '<S4>/LowerRelop1'
   *  RelationalOperator: '<S4>/UpperRelop'
   *  Switch: '<S4>/Switch'
   */
  if (rtb_Sum1 > 60.0) {
    rtb_Sum1 = 60.0;
  } else if (rtb_Sum1 < 2.0) {
    /* Switch: '<S4>/Switch' incorporates:
     *  Constant: '<S1>/Constant'
     */
    rtb_Sum1 = 2.0;
  }

  /* End of Switch: '<S4>/Switch2' */

  /* Product: '<S1>/Multibly2' incorporates:
   *  Inport: '<Root>/sinRHO'
   */
  rtb_Multibly2 = rtb_Sum1 * rtU.sinRHO;

  /* Product: '<S1>/Divide' incorporates:
   *  Inport: '<Root>/cosRHO'
   *  Product: '<S1>/Multibly'
   */
  rtb_UnitDelay = rtb_UnitDelay * rtU.cosRHO / rtb_Sum1;

  /* Sum: '<S3>/Sum1' incorporates:
   *  Gain: '<S3>/Gain7'
   *  Gain: '<S3>/Gain9'
   *  Sum: '<S3>/Sum4'
   *  UnitDelay: '<S3>/Unit Delay'
   *  UnitDelay: '<S3>/Unit Delay1'
   */
  rtb_Sum1_p = (0.090099 * rtb_UnitDelay + rtDW.UnitDelay1_DSTATE_ns)
    + (rtb_UnitDelay - rtDW.UnitDelay_DSTATE) * 36.5;

  /* Switch: '<S5>/Switch2' incorporates:
   *  Constant: '<S1>/Constant2'
   *  Constant: '<S1>/Constant3'
   *  RelationalOperator: '<S5>/LowerRelop1'
   *  RelationalOperator: '<S5>/UpperRelop'
   *  Switch: '<S5>/Switch'
   */
  if (rtb_Sum1_p > 400.0) {
    rtb_Sum1_p = 400.0;
  } else if (rtb_Sum1_p < 250.0) {
    /* Switch: '<S5>/Switch' incorporates:
     *  Constant: '<S1>/Constant2'
     */
    rtb_Sum1_p = 250.0;
  }

  /* End of Switch: '<S5>/Switch2' */

  /* Update for UnitDelay: '<S1>/Unit Delay1' incorporates:
   *  Inport: '<Root>/grid_voltage'
   */
  rtDW.UnitDelay1_DSTATE = rtU.grid_voltage;

  /* Update for UnitDelay: '<S1>/Unit Delay2' */
  rtDW.UnitDelay2_DSTATE = rtb_Multibly2;

  /* Update for UnitDelay: '<S2>/Unit Delay1' */
  rtDW.UnitDelay1_DSTATE_n = rtb_Sum1;

  /* Update for UnitDelay: '<S3>/Unit Delay1' */
  rtDW.UnitDelay1_DSTATE_ns = rtb_Sum1_p;

  /* Update for UnitDelay: '<S3>/Unit Delay' */
  rtDW.UnitDelay_DSTATE = rtb_UnitDelay;

  /* Outport: '<Root>/frequency' incorporates:
   *  Gain: '<S1>/Multiply'
   */
  rtY.frequency = 0.15915 * rtb_Sum1_p;

  /* End of Outputs for SubSystem: '<Root>/PLL_control' */

  /* Outport: '<Root>/UgridID' */
  rtY.UgridID = rtb_Multibly2;

  /* Outport: '<Root>/Wid' */
  rtY.Wid = rtb_Sum1_p;

  /* Outport: '<Root>/Ugrid_peak' */
  rtY.Ugrid_peak = rtb_Sum1;
}

/* Model initialize function */
void PLL_controller_initialize(float V_peak_ID)
{
  /* SystemInitialize for Atomic SubSystem: '<Root>/PLL_control' */
  /* InitializeConditions for UnitDelay: '<S2>/Unit Delay1' */
  rtDW.UnitDelay1_DSTATE_n = V_peak_ID;

  /* InitializeConditions for UnitDelay: '<S3>/Unit Delay1' */
  rtDW.UnitDelay1_DSTATE_ns = 314.1592;

  /* End of SystemInitialize for SubSystem: '<Root>/PLL_control' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
