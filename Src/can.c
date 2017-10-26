/*
 * can.c
 *
 *  Created on: 21Oct.,2017
 *      Author: Ovindu
 */

#include "can.h"

extern CAN_HandleTypeDef hcan1;

osMessageQId osQueue1;
osMessageQId osQueue2;
CanQueue canQueue1;
CanQueue canQueue2;

void Handle_Can1_Meesage(CanRxMsgTypeDef *CanRxMessage) {}


void Handle_Can2_Meesage(CanRxMsgTypeDef *CanRxMessage) {}


void Can1_Recieve_Init() {
	CAN_FilterConfTypeDef sFilterConfig;
	static CanRxMsgTypeDef RxMessage;

	hcan1.pRxMsg = &RxMessage;

	// Setup CAN filter
	sFilterConfig.FilterNumber = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x500 << 5;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0xFFF << 5;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.BankNumber = CAN2_FILTER_START;

	if(HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
	{
		/* Filter configuration Error */
		Error_Handler();
	}

	// Setup CAN filter
	sFilterConfig.FilterNumber = 1;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x501 << 5;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0xFFF << 5;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.BankNumber = CAN2_FILTER_START;

	if(HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
	{
		/* Filter configuration Error */
		Error_Handler();
	}

	// Turn on CAN receiving
	if (HAL_CAN_Receive_IT(&hcan1, CAN_FIFO0) != HAL_OK) {
		/* Reception Error */
		Error_Handler();
	}
}


void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* CanHandle) {
	osMessageQId* osQueue;
	CanQueue* canQueue;
	uint8_t queuePos;

	// Pick which queue to dump message into
	if (CanHandle->Instance == CAN1) {
		osQueue = &osQueue1;
		canQueue = &canQueue1;
	} else {
		osQueue = &osQueue2;
		canQueue = &canQueue2;
	}

	// Save a copy of the message
	queuePos = canQueue->queuePosition;
	canQueue->queue[queuePos] = *CanHandle->pRxMsg;
	uint32_t pointer = &canQueue->queue[queuePos];
    if (osMessagePut(*osQueue, pointer, 0) != osOK)
    {
    	Error_Handler();
    }
    canQueue->queuePosition = (queuePos + 1) % CAN_QUEUE_SIZE;

	// Receive
	if (HAL_CAN_Receive_IT(CanHandle, CAN_FIFO0) != HAL_OK) {
		/* Reception Error */
		Error_Handler();
	}
}


void Can_Recieve_Start() {
	osEvent event;
	CanRxMsgTypeDef *CanRxMessage;

	// Init OS queues
	osMessageQDef(osqueue1, CAN_QUEUE_SIZE, uint32_t);
	osQueue1 = osMessageCreate(osMessageQ(osqueue1), NULL);
	osMessageQDef(osqueue2, CAN_QUEUE_SIZE, uint32_t);
	osQueue2 = osMessageCreate(osMessageQ(osqueue2), NULL);

	Can1_Recieve_Init();
	// Can2_Recieve_Init();

	for (;;) {
		// Check CAN1 queue for messages
		event = osMessageGet(osQueue1, 100);
	    if (event.status == osEventMessage)
	    {
	    	CanRxMessage = (CanRxMsgTypeDef*) event.value.v;
	    	debug_log("CAN packet received from %X on CAN1: [%X]", CanRxMessage->StdId, CanRxMessage->Data);
	    	Handle_Can1_Meesage(CanRxMessage);
	    }

	    // Check CAN2 queue for messages
		event = osMessageGet(osQueue2, 100);
	    if (event.status == osEventMessage)
	    {
	    	CanRxMessage = (CanRxMsgTypeDef*) event.value.v;
	    	debug_log("CAN packet received from %X on CAN2: [%X]", CanRxMessage->StdId, CanRxMessage->Data);
	    	Handle_Can1_Meesage(CanRxMessage);
	    }
	}

}
