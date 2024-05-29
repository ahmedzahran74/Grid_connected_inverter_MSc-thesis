/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: current_controller_code_generation.h
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

#ifndef RTW_HEADER_current_controller_code_generation_h_
#define RTW_HEADER_current_controller_code_generation_h_
#ifndef current_controller_code_generation_COMMON_INCLUDES_
#define current_controller_code_generation_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                 /* current_controller_code_generation_COMMON_INCLUDES_ */

/* Model Code Variants */

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T sin_value;                    /* '<Root>/sin_value' */
  real_T UDC;                          /* '<Root>/UDC' */
} ExtU_cs;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uint32_T CMP1A;                      /* '<Root>/CMP1A' */
  uint32_T CMP2A;                      /* '<Root>/CMP2A' */
} ExtY_jz;

/* External inputs (root inport signals with default storage) */
extern ExtU_cs rtU_m;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_jz rtY_h;

/* Model entry point functions */
extern void current_controller_code_generation_initialize(void);
extern void current_controller_code_generation_step(void);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S4>/Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/Data Type Propagation' : Unused code path elimination
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
 * '<Root>' : 'current_controller_code_generation'
 * '<S1>'   : 'current_controller_code_generation/Subsystem1'
 * '<S2>'   : 'current_controller_code_generation/Subsystem1/UinvtoCMPx'
 * '<S3>'   : 'current_controller_code_generation/Subsystem1/current_controller'
 * '<S4>'   : 'current_controller_code_generation/Subsystem1/current_controller/Saturation Dynamic'
 */
#endif                    /* RTW_HEADER_current_controller_code_generation_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
