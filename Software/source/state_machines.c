/*
 * state_machines.c
 *
 *  Created on: May 6, 2024
 *      Author: RTX
 */

#include "state_machines.h"

void state_machines(void)
{
    inverter_state_machine_dispatcher();
    state_machine_dispatcher_inverter();
}
