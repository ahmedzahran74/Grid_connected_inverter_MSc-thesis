/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: current_controller_AC_code_generation.h
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

#ifndef RTW_HEADER_current_controller_AC_code_generation_h_
#define RTW_HEADER_current_controller_AC_code_generation_h_
#ifndef current_controller_AC_code_generation_COMMON_INCLUDES_
#define current_controller_AC_code_generation_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif              /* current_controller_AC_code_generation_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay_DSTATE_C_C;         /* '<S1>/Unit Delay' */
  real_T UnitDelay_DSTATE_o_C_C;       /* '<S3>/Unit Delay' */
  real_T UnitDelay1_DSTATE_C_C;        /* '<S3>/Unit Delay1' */
} DW_C_C;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T inductor_current_C_C;         /* '<Root>/inductor_current' */
  real_T reference_current_C_C;        /* '<Root>/reference_current' */
  real_T U_DC_C_C;                     /* '<Root>/U_DC' */
  real_T sin_value_C_C;                /* '<Root>/sin_value' */
  real_T cos_value_C_C;                /* '<Root>/cos_value' */
} ExtU_C_C;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uint32_T CMP1A_C_C;                  /* '<Root>/CMP1A' */
  uint32_T CMP2A_C_C;                  /* '<Root>/CMP2A' */
  real_T Uinv_C_C;                     /* '<Root>/Uinv' */
} ExtY_C_C;

/* Block signals and states (default storage) */
extern DW_C_C rtDW_C_C;

/* External inputs (root inport signals with default storage) */
extern ExtU_C_C rtU_C_C;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_C_C rtY_C_C;

/* Model entry point functions */
extern void current_controller_AC_code_generation_initialize(float);
extern void current_controller_AC_code_generation_step(void);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S4>/Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/Data Type Propagation' : Unused code path elimination
 * Block '<S3>/Scope' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'current_controller_AC_code_generation'
 * '<S1>'   : 'current_controller_AC_code_generation/current_controller'
 * '<S2>'   : 'current_controller_AC_code_generation/current_controller/UinvtoCMPx'
 * '<S3>'   : 'current_controller_AC_code_generation/current_controller/current_controller'
 * '<S4>'   : 'current_controller_AC_code_generation/current_controller/current_controller/Saturation Dynamic'
 */
#endif                 /* RTW_HEADER_current_controller_AC_code_generation_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
