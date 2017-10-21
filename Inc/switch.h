/*
 * switch.h
 *
 *  Created on: 9Oct.,2017
 *      Author: Ovindu
 */

#ifndef SWITCH_H_
#define SWITCH_H_

#include "stdint.h"

// Driver controls switch position packet bitfield positions
#define SW_DRIVE	0x0001
#define SW_HV		0x0002
#define SW_AUX		0x0004

void readSwitches(uint16_t *state, uint16_t *difference);

#endif /* SWITCH_H_ */
