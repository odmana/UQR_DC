/*
 * switch.c
 *
 *  Created on: 9Oct.,2017
 *      Author: Ovindu
 */

#include "main.h"
#include "switch.h"
#include "stm32f4xx_hal.h"

void readSwitches(uint16_t *state, uint16_t *difference) {
	uint16_t oldState = *state;

	if (HAL_GPIO_ReadPin(SW_Drive_GPIO_Port, SW_Drive_Pin) == GPIO_PIN_SET)
		*state |= SW_DRIVE;
	else
		*state &= !SW_DRIVE;

	if (HAL_GPIO_ReadPin(SW_HV_GPIO_Port, SW_HV_Pin) == GPIO_PIN_SET)
		*state |= SW_HV;
	else
		*state &= !SW_HV;

	if (HAL_GPIO_ReadPin(SW_Aux_GPIO_Port, SW_Aux_Pin) == GPIO_PIN_SET)
		*state |= SW_AUX;
	else
		*state &= !SW_AUX;

	// Update changed switches
	*difference = *state ^ oldState;
}
