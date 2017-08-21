/*
 * pedal.h
 *
 *  Created on: 21Aug.,2017
 *      Author: Ovindu
 */

#ifndef PEDAL_H_
#define PEDAL_H_

#include "stdint.h"

union PedalData {
	uint16_t adcValues[4];
	struct {
		uint16_t throttle2, brake1, brake2, throttle1;
	} pedals;
} pedalData;

void pedal_init();
void pedal_debug();

#endif /* PEDAL_H_ */
