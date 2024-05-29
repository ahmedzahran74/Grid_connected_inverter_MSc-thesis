#ifndef RTW_HEADER_RHO_code_generation_h_
#define RTW_HEADER_RHO_code_generation_h_

#ifndef RHO_code_generation_COMMON_INCLUDES_
#define RHO_code_generation_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                /* RHO_code_generation_COMMON_INCLUDES_ */



/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T W_id;                         /* '<Root>/W_id' */
} ExtU_c;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T RHO;                          /* '<Root>/RHO' */

} ExtY_j;

/* External inputs (root inport signals with default storage) */
extern ExtU_c rRU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_j rRY;

/* Model entry point functions */
extern void RHO_code_generation_initialize(void);
extern void RHO_code_generation_step(void);

#endif                                 /* RTW_HEADER_RHO_code_generation_h_ */

