/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: voltage_controller_code_generation.h
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

#ifndef RTW_HEADER_voltage_controller_code_generation_h_
#define RTW_HEADER_voltage_controller_code_generation_h_
#ifndef voltage_controller_code_generation_COMMON_INCLUDES_
#define voltage_controller_code_generation_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "gen_types.h"

#endif                 /* voltage_controller_code_generation_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_V_C RT_MODEL_V_C;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T TappedDelay_X_V_C[100];       /* '<S1>/Tapped Delay' */
  real_T I_peak_previous_DSTATE_V_C;   /* '<S2>/I_peak_previous' */
  real_T UnitDelay_DSTATE_V_C;         /* '<S2>/Unit Delay' */
  real_T sum;
} DW_V_C;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T V_DC_V_C;                     /* '<Root>/V_DC' */
  real_T Vref_V_C;                     /* '<Root>/Vref' */
} ExtU_V_C;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T I_peak_ref_V_C;               /* '<Root>/I_peak_ref' */
} ExtY_V_C;

/* Real-time Model Data Structure */
struct tag_RTM_V_C {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW_V_C rtDW_V_C;

/* External inputs (root inport signals with default storage) */
extern ExtU_V_C rtU_V_C;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_V_C rtY_V_C;

/* Model entry point functions */
extern void voltage_controller_code_generation_initialize(float initial_voltage);
extern void voltage_controller_code_generation_step(void);

/* Real-time Model object */
extern RT_MODEL_V_C *const rtM_V_C;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S3>/Data Type Duplicate' : Unused code path elimination
 * Block '<S3>/Data Type Propagation' : Unused code path elimination
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
 * '<Root>' : 'voltage_controller_code_generation'
 * '<S1>'   : 'voltage_controller_code_generation/voltage controller'
 * '<S2>'   : 'voltage_controller_code_generation/voltage controller/phase PI controller'
 * '<S3>'   : 'voltage_controller_code_generation/voltage controller/phase PI controller/Saturation Dynamic'
 */
#endif                    /* RTW_HEADER_voltage_controller_code_generation_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
