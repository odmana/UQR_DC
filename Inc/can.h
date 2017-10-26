/*
 * can.h
 *
 *  Created on: 21Oct.,2017
 *      Author: Ovindu
 */

#ifndef CAN_H_
#define CAN_H_

#define CAN2_FILTER_START 14
#define CAN_QUEUE_SIZE 2

#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "debug.h"

struct {
	uint8_t queuePosition;
	CanRxMsgTypeDef queue[CAN_QUEUE_SIZE];
} typedef CanQueue;


// Motor controller CAN base address and packet offsets
#define	MC_L_CAN_BASE	0x400		// High = Serial Number             Low = "TRIa" string
#define	MC_R_CAN_BASE	0x420		// High = Serial Number             Low = "TRIa" string
#define MC_LIMITS		0x01		// High = Active Motor/CAN counts   Low = Error & Limit flags
#define	MC_BUS			0x02		// High = Bus Current               Low = Bus Voltage
#define MC_VELOCITY		0x03		// High = Velocity (m/s)            Low = Velocity (rpm)
#define MC_PHASE		0x04		// High = Phase A Current           Low = Phase B Current
#define MC_V_VECTOR		0x05		// High = Vd vector                 Low = Vq vector
#define MC_I_VECTOR		0x06		// High = Id vector                 Low = Iq vector
#define MC_BEMF_VECTOR	0x07		// High = BEMFd vector              Low = BEMFq vector
#define MC_RAIL1		0x08		// High = 15V                       Low = Unused
#define MC_RAIL2		0x09		// High = 3.3V                      Low = 1.9V
#define MC_FAN			0x0A		// High = Reserved                  Low = Reserved
#define MC_TEMP1		0x0B		// High = Heatsink Phase C Temp     Low = Motor Temp
#define MC_TEMP2		0x0C		// High = Heatsink Phase B Temp     Low = CPU Temp
#define MC_TEMP3		0x0D		// High = Heatsink Phase A Temp     Low = Unused
#define MC_CUMULATIVE	0x0E		// High = DC Bus AmpHours           Low = Odometer

// Driver controls CAN base address and packet offsets
#define DC_CAN_BASE		0x500
#define DC_DRIVE		0x01
#define DC_POWER		0x02
#define DC_RESET		0x03
#define DC_DRIVE_INT	0x04
#define DC_SWITCH		0x05
#define DC_MOTOR_INT	0x06
#define DC_PEDAL_INT	0x07
#define DC_MOTOR_L		0x08
#define DC_MOTOR_R		0x09
#define DC_BMS_SOC		0x0A
#define DC_BOOTLOAD		22			// 0x16

// Tritium battery management system
#define BMS_CAN_BASE	0x600		//
#define BMS_SOC			0x0F4		//
#define BMS_BL_SOC		0x0F5		//
#define BMS_CHARGER		0x0F6		//
#define BMS_PRE_CHRG	0x0F7		//
#define BMS_CELL_V		0x0F8		//
#define BMS_CELL_TEMP	0x0F9		//
#define BMS_PACK_VI		0x0FA		//
#define BMS_PACK_STS	0x0FB		//
#define BMS_PACK_FAN	0x0FC		//
#define BMS_PACK_EX_STS	0x0FD		//

// Motec Dash
#define DASH_CAN_BASE	0x550		// ????
#define DASH_SWITCHES   0			// Dash switches broadcast
#define DASH_BRAKES		1			// Dash brake readings


#endif /* CAN_H_ */
