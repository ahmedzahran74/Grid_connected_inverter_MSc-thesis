

#include "RHO_code_generation.h"
#include <rtwtypes.h>
#include "C28x_FPU_FastRTS.h"


/* External inputs (root inport signals with default storage) */
ExtU_c rRU;

/* External outputs (root outports fed by signals with default storage) */
ExtY_j rRY;



/* Model step function */
#pragma CODE_SECTION(RHO_code_generation_step, "ramfuncs");
void RHO_code_generation_step(void)
{
    rRY.RHO += rRU.W_id * 1.0E-5;

  if (rRY.RHO >= 6.2831) {

      rRY.RHO -= 6.2831;
  }

}

/* Model initialize function */
void RHO_code_generation_initialize(void)
{
    rRU.W_id=314.16;
}
