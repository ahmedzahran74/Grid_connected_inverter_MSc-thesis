/*
 * service_function.c
 *
 *  Created on: May 6, 2024
 *      Author: RTX
 */

#include "service_function.h"
Uint32 pull_up_relay_flag,pull_down_relay_flag;
void pull_up_relay(void)
{
    pull_up_relay_flag++;
    GpioDataRegs.GPACLEAR.bit.GPIO20 = 1;

}
void pull_down_relay(void)
{
    pull_down_relay_flag++;
    GpioDataRegs.GPASET.bit.GPIO20 = 1;
}


