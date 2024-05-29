/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PLL_controller.h
 *
 * Code generated for Simulink model 'PLL_controller'.
 *
 * Model version                  : 1.0
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Thu Apr 25 21:52:45 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_PLL_controller_h_
#define RTW_HEADER_PLL_controller_h_
#ifndef PLL_controller_COMMON_INCLUDES_
#define PLL_controller_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* PLL_controller_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */

typedef struct {
  real_T UnitDelay1_DSTATE;            /* '<S1>/Unit Delay1' */
  real_T UnitDelay2_DSTATE;            /* '<S1>/Unit Delay2' */
  real_T UnitDelay1_DSTATE_n;          /* '<S2>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_ns;         /* '<S3>/Unit Delay1' */
  real_T UnitDelay_DSTATE;             /* '<S3>/Unit Delay' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T grid_voltage;                 /* '<Root>/grid_voltage' */
  real_T sinRHO;                       /* '<Root>/sinRHO' */
  real_T cosRHO;                       /* '<Root>/cosRHO' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T frequency;                    /* '<Root>/frequency' */
  real_T UgridID;                      /* '<Root>/UgridID' */
  real_T Wid;                          /* '<Root>/Wid' */
  real_T Ugrid_peak;                   /* '<Root>/Ugrid_peak' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Model entry point functions */
void PLL_controller_initialize(float V_peak_ID);
extern void PLL_controller_step(void);
/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Display' : Unused code path elimination
 * Block '<S4>/Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/Data Type Propagation' : Unused code path elimination
 * Block '<S1>/Scope' : Unused code path elimination
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
 * '<Root>' : 'PLL_controller'
 * '<S1>'   : 'PLL_controller/PLL_control'
 * '<S2>'   : 'PLL_controller/PLL_control/Amplitude I controller'
 * '<S3>'   : 'PLL_controller/PLL_control/phase PI controller'
 * '<S4>'   : 'PLL_controller/PLL_control/Amplitude I controller/Saturation Dynamic'
 * '<S5>'   : 'PLL_controller/PLL_control/phase PI controller/Saturation Dynamic'
 */
#endif                                 /* RTW_HEADER_PLL_controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
