/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: buck_code_generation.h
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

#ifndef RTW_HEADER_buck_code_generation_h_
#define RTW_HEADER_buck_code_generation_h_
#ifndef buck_code_generation_COMMON_INCLUDES_
#define buck_code_generation_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                               /* buck_code_generation_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_buck RT_MODEL_buck;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T I_peak_previous_DSTATE_buck;  /* '<S2>/I_peak_previous' */
  real_T I_peak_previous_DSTATE_f_buck;/* '<S3>/I_peak_previous' */
  real_T UnitDelay_DSTATE_buck;        /* '<S3>/Unit Delay' */
  real_T UnitDelay1_DSTATE_buck;       /* '<S2>/Unit Delay1' */
  real_T UnitDelay_DSTATE_n_buck;      /* '<S2>/Unit Delay' */
} DW_buck;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T V_op_buck;                    /* '<Root>/V_op' */
  real_T V_ref_buck;                   /* '<Root>/V_ref' */
  real_T IL_buck;                      /* '<Root>/IL' */
  real_T V_high_buck;                  /* '<Root>/V_high' */
} ExtU_buck;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uint32_T CMPA_buck;                  /* '<Root>/CMPA' */
  real_T Iref_buck;                    /* '<Root>/Iref' */
} ExtY_buck;

/* Real-time Model Data Structure */
struct tag_RTM_buck {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW_buck rtDW_buck;

/* External inputs (root inport signals with default storage) */
extern ExtU_buck rtU_buck;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_buck rtY_buck;

/* Model entry point functions */
extern void buck_code_generation_initialize(void);
extern void buck_code_generation_step(void);

/* Real-time Model object */
extern RT_MODEL_buck *const rtM_buck;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S4>/Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/Data Type Propagation' : Unused code path elimination
 * Block '<S5>/Data Type Duplicate' : Unused code path elimination
 * Block '<S5>/Data Type Propagation' : Unused code path elimination
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
 * '<Root>' : 'buck_code_generation'
 * '<S1>'   : 'buck_code_generation/Subsystem'
 * '<S2>'   : 'buck_code_generation/Subsystem/phase PI controller'
 * '<S3>'   : 'buck_code_generation/Subsystem/phase PI controller1'
 * '<S4>'   : 'buck_code_generation/Subsystem/phase PI controller/Saturation Dynamic'
 * '<S5>'   : 'buck_code_generation/Subsystem/phase PI controller1/Saturation Dynamic'
 */
#endif                                 /* RTW_HEADER_buck_code_generation_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
