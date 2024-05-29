/*
 * PWM.h
 *
 *  Created on: 2016 márc. 13
 *      Author: Szako
 */

#ifndef INCLUDE_PWM_H_
  #define INCLUDE_PWM_H_

  #include "F2806x_Device.h"
  #include "F2806x_GlobalPrototypes.h"
  #include "F2806x_EPwm_defines.h"
  #include "F2806x_usDelay.h"
  #include "gen_types.h"
#include "usefulmacros.h"
  #define TIMEBASE 2000

  /* Function declarations */
  void PWM_Init(void);
  void PWM_Init_Clocks(void);
  void PWM_Init_GPIOs(void);
  void PWM_Init_Master(void);
  void PWM_Init_Slave(volatile struct EPWM_REGS *EPwmxRegs);
  void PWM_Init_Slave_2(void);
  void PWM_Init_Slave_ADC_trig(volatile struct EPWM_REGS *EPwmxRegs);
  void PWM_Init_I_AC_Error(volatile struct EPWM_REGS *EPwmxRegs);
  void PWM_Init_I_DC_Error(volatile struct EPWM_REGS *EPwmxRegs);
  void PWM_Init_U_Error(volatile struct EPWM_REGS *EPwmxRegs);
  void PWM_ErrorACK(void);
  void PWM_Init_4(void);
  void PWM_Init_5(void);
  void epwm1_set_CMPA(Uint32 CMPA);
  void epwm2_set_CMPA(Uint32 CMPA);
  void epwm4_isr_assign_function(fprt_g fptr_recieved);
  void epwm5_isr_assign_function(fprt_g fptr_recieved);
  void inverter_clear_tripzone_SW_event(void);
  void inverter_enable_tripzone_SW_event(void);
#endif /* INCLUDE_PWM_H_ */
