/*
 * state_machine.h
 *
 *  Created on: May 2, 2024
 *      Author: RTX
 */

#ifndef INCLUDE_STATE_MACHINE_H_
#define INCLUDE_STATE_MACHINE_H_
#include "stddef.h"
#include "F2806x_Device.h"
#include "usefulmacros.h"
#include "interrupt_functions.h"
#include "PWM.h"
#include "ADC.h"
#include "PLL_controller.h"
#include "main.h"
extern float VAC;
extern float V_err;
typedef enum {
    handled,
    ignored,
    transition
}event_staus;
typedef enum
{
    ENTRY,
    EXIT,
    DO,
    COUNT_40,
    RISING_EDGE,
    CHECK_WAIT,
    CHECK,
    MAX_EVENTS
}inverter_events;
typedef enum
{
    PLL_PEAK_ID,
    PLL_THETA_ID,
    PLL_START,
    GRID_OK,
    MAX_STATES
}inverter_state;
typedef struct {
    Uint32 count;
    Uint32 rising_edge;
    float  peak_ID;
    Uint32 theta;
    Uint32 check;
    Uint32 PLL_count;
    inverter_state inverter_state;

}inverter_state_machine_t;

typedef event_staus(*state_machine_fun)();



event_staus PLL_peak_ID_entery();
event_staus PLL_peak_ID_do();
event_staus PLL_peak_ID_count_40();
event_staus PLL_theta_ID_entry();
event_staus PLL_theta_ID_do();
event_staus PLL_theta_ID_rising_edge( );
event_staus PLL_start_entry( );
event_staus PLL_start_exit( );
event_staus PLL_start_do( );
event_staus PLL_start_check_wait( );
event_staus grid_ok_entry( );
event_staus grid_ok_exit( );
event_staus grid_ok_do( );
event_staus grid_not_ok_check( );




event_staus PLL_peak_ID_events();
event_staus PLL_theta_ID_events();
event_staus PLL_start_events();
event_staus grid_ok_events();



void inverter_state_machine_dispatcher(void);
void inverter_state_machine_init(void);

//extra useful functions
Uint32 check_PLL_ok(void);
#endif /* INCLUDE_STATE_MACHINE_H_ */
