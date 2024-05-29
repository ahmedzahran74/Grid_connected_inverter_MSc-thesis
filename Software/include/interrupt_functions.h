/*
 * interrupt_functions.h
 *
 *  Created on: May 2, 2024
 *      Author: RTX
 */

#ifndef INCLUDE_INTERRUPT_FUNCTIONS_H_
#define INCLUDE_INTERRUPT_FUNCTIONS_H_
#include "F2806x_Device.h"
#include "inic.h"
#include "bbx.h"
#include "HiMon.h"
#include "Term_defs.h"
#include "C28x_FPU_FastRTS.h"
#include "ADC.h"
#include "CLA_shared.h"
#include "CLA.h"
#include "RHO_code_generation.h"
#include "PLL_controller.h"
#include "current_controller_AC_code_generation.h"
#include "voltage_controller_code_generation.h"
#include "buck_code_generation.h"
#include "boost_code_generation.h"
//#include "current_controller_code_generation.h"
void adc_isr_PLL_init (void);
void adc_isr_PLL_start (void);
void adc_isr_PLL_start_control (void);

void epwm4_isr_100us_PLL_init (void);
void epwm4_isr_100us_PLL_start (void);
void epwm4_isr_100us_PLL_start_control (void);
void epwm4_isr_100us_DC_voltage_check (void);

void cpu_timer1_PLL_init (void);
void cpu_timer1_PLL_start (void);
void cpu_timer1_PLL_start_control (void);




#endif /* INCLUDE_INTERRUPT_FUNCTIONS_H_ */
