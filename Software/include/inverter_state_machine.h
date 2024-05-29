/*
 * inverter_state_machine.h
 *
 *  Created on: May 6, 2024
 *      Author: RTX
 */

#ifndef INCLUDE_INVERTER_STATE_MACHINE_H_
#define INCLUDE_INVERTER_STATE_MACHINE_H_
#include "stddef.h"
#include "F2806x_Device.h"
#include "usefulmacros.h"
#include "interrupt_functions.h"
#include "PWM.h"
#include "ADC.h"
#include "PLL_controller.h"
#include "main.h"
#include "service_function.h"
#include "current_controller_AC_code_generation.h"
#include "voltage_controller_code_generation.h"
//#include "state_machine.h"
typedef enum {
    handled_inverter,
    ignored_inverter,
    transition_inverter
}inverter_state_machine_event_staus;
typedef enum
{
    ENTRY_inverter,
    EXIT_inverter,
    DO_inverter,
    GRID_OK_INVERTER,
    VDC_OK,
    GRID_NOT_OK,
    INVERTER_MAX_EVENTS
}inverter_state_machine_events;
typedef enum
{
    NOT_READY,
    CHECKS_AND_INITIAL_CONDITION,
    START_CONTROL,
    INVERTER_MAX_STATES
}inverter_state_machine_state;
typedef struct {

    inverter_state_machine_state inverter_state;

}state_machine_inverter_t;

typedef inverter_state_machine_event_staus(*inverter_state_machine_fun)();
inverter_state_machine_event_staus not_ready_entry();
inverter_state_machine_event_staus not_ready_grid_ok();
inverter_state_machine_event_staus checks_and_initial_condition_entry ();
inverter_state_machine_event_staus checks_and_initial_condition_exit();
inverter_state_machine_event_staus checks_and_initial_condition_VDC_ok();
inverter_state_machine_event_staus checks_and_initial_condition_grid_not_ok ();
inverter_state_machine_event_staus start_control_entry();
inverter_state_machine_event_staus start_control_exit();
inverter_state_machine_event_staus start_control_grid_not_ok();

inverter_state_machine_event_staus NOT_ready_events();
inverter_state_machine_event_staus checks_and_initial_condition_events();
inverter_state_machine_event_staus start_control_events();


void state_machine_dispatcher_inverter(void);
void state_machine_init_inverter(void);
Uint32 V_DC_OK(void);
void setting_initial_condition(void);




#endif /* INCLUDE_INVERTER_STATE_MACHINE_H_ */
