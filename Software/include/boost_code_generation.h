/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: boost_code_generation.h
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

#ifndef RTW_HEADER_boost_code_generation_h_
#define RTW_HEADER_boost_code_generation_h_
#ifndef boost_code_generation_COMMON_INCLUDES_
#define boost_code_generation_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                              /* boost_code_generation_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_boost RT_MODEL_boost;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T I_peak_previous_DSTATE_boost; /* '<S3>/I_peak_previous' */
  real_T UnitDelay_DSTATE_boost;       /* '<S3>/Unit Delay' */
  real_T UnitDelay_DSTATE_d_boost;     /* '<S4>/Unit Delay' */
  real_T UnitDelay_DSTATE_h_boost;     /* '<S2>/Unit Delay' */
  real_T UnitDelay1_DSTATE_boost;      /* '<S4>/Unit Delay1' */
} DW_boost;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T V_op_boost;                   /* '<Root>/V_op' */
  real_T Vref_boost;                   /* '<Root>/Vref' */
  real_T IL_boost;                     /* '<Root>/IL' */
} ExtU_boost;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uint32_T CMP_B_boost;                /* '<Root>/CMP_B' */
  real_T Iref_boost;                   /* '<Root>/Iref' */
} ExtY_boost;

/* Real-time Model Data Structure */
struct tag_RTM_boost {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW_boost rtDW_boost;

/* External inputs (root inport signals with default storage) */
extern ExtU_boost rtU_boost;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_boost rtY_boost;

/* Model entry point functions */
extern void boost_code_generation_initialize(void);
extern void boost_code_generation_step(void);

/* Real-time Model object */
extern RT_MODEL_boost *const rtM_boost;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S5>/Data Type Duplicate' : Unused code path elimination
 * Block '<S5>/Data Type Propagation' : Unused code path elimination
 * Block '<S2>/Scope1' : Unused code path elimination
 * Block '<S6>/Data Type Duplicate' : Unused code path elimination
 * Block '<S6>/Data Type Propagation' : Unused code path elimination
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
 * '<Root>' : 'boost_code_generation'
 * '<S1>'   : 'boost_code_generation/Subsystem'
 * '<S2>'   : 'boost_code_generation/Subsystem/Discrete controller'
 * '<S3>'   : 'boost_code_generation/Subsystem/phase PI controller1'
 * '<S4>'   : 'boost_code_generation/Subsystem/Discrete controller/Discrete PI controller2'
 * '<S5>'   : 'boost_code_generation/Subsystem/Discrete controller/Discrete PI controller2/Saturation Dynamic'
 * '<S6>'   : 'boost_code_generation/Subsystem/phase PI controller1/Saturation Dynamic'
 */
#endif                                 /* RTW_HEADER_boost_code_generation_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
