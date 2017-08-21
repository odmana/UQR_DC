/*
 * pedal.c
 *
 *  Created on: 21Aug.,2017
 *      Author: Ovindu
 */

#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "main.h"
#include "debug.h"
#include "pedal.h"

extern ADC_HandleTypeDef hadc1;
// uint16_t adcValues[4]; //ADC Readings

void pedal_init() {
	// -- Enables ADC and starts conversion of the regular channels.
	if (HAL_ADC_Start(&hadc1) != HAL_OK)
		Error_Handler();

	// -- Enables ADC DMA request
	if (HAL_ADC_Start_DMA(&hadc1, (uint32_t*) pedalData.adcValues, 4) != HAL_OK)
		Error_Handler();
}

void pedal_debug() {
	for (;;) {
		debug_log("Pedal Values - T1:[%d] \t T2:[%d] \t B1:[%d] \t B2:[%d]",
				pedalData.pedals.throttle1, pedalData.pedals.throttle2, pedalData.pedals.brake1, pedalData.pedals.brake2);
		osDelay(1000);
	}
}
