/*
 * state_machines.h
 *
 *  Created on: May 6, 2024
 *      Author: RTX
 */

#ifndef INCLUDE_STATE_MACHINES_H_
#define INCLUDE_STATE_MACHINES_H_
#include "state_machine.h"
#include "inverter_state_machine.h"
extern void inverter_state_machine_dispatcher(void);
extern void state_machine_dispatcher_inverter(void);

void state_machines(void);


#endif /* INCLUDE_STATE_MACHINES_H_ */
