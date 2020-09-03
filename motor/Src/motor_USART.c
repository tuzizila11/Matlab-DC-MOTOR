/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: motor_USART.c
 *
 * Code generated for Simulink model :motor.
 *
 * Model version      : 1.127
 * Simulink Coder version    : 9.3 (R2020a) 18-Nov-2019
 * TLC version       : 9.3 (May 28 2020)
 * C/C++ source code generated on  : Wed Sep  2 01:54:35 2020
 *
 * Target selection: stm32.tlc
 * Embedded hardware selection: STMicroelectronics->STM32 32-bit Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 *    3. MISRA C:2012 guidelines
 * Validation result: Not run
 *
 *
 *
 * ******************************************************************************
 * * attention
 * *
 * * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 * *
 * ******************************************************************************
 */

#include "motor.h"
#include "motor_USART.h"
#include "main.h"

/* USART3 Tx polling timeout value. Number of Solver loop. (can be changed)*/
uint32_t G_USART3_TxPollTimeOut = 10;

/* Number of USART/UART configured for send. */
uint16_t G_SERIAL_TX_Count = 0;

/* Array of USART/UART send data information. */
SERIAL_TxConfTypeDef* G_SERIAL_TX_Conf[1];
void* G_SERIAL_TX_Handler[1];

/* USART3 ring data send buffer. */
static uint8_t USART3_TxDataBuffer[512];

/* USART3 send data structure information. */
SERIAL_TxConfTypeDef USART3_TxConf;

/*******************************************************************************
 * Function Name  : TX_CopyData
 * Description    : Copy msg to send to ring buffer (if possible)
 * Input          : pointer to data to send , length(number) of data to send and
 *                  ring buffer context
 *******************************************************************************/
void TX_CopyData(struct SERIAL_TxConf* pConf, uint8_t* pSrc, uint16_t dataLength)
{
  uint16_t msgSize = 0;
  uint16_t idx;

  /* Copy msg to send to ring buffer */
  for (idx = 0; idx < dataLength; idx++) {
    if ((pConf->pTx_W == pConf->pTx_R) && (pConf->nb2Send!=0))
      break;                           /* Ring Buffer is full. */
    *pConf->pTx_W++ = *pSrc++;
    msgSize++;
    if (pConf->pTx_W == pConf->pTx_R)
      break;                           /* Ring Buffer is full. */
    if (pConf->pTx_W == pConf->pTx_BuffEnd) {
      /* Revolve buffer. */
      pConf->pTx_W = pConf->pTx_BuffStart;
    }
  }

  /* Update number of data to send. */
  /* Access locked. */
  pConf->txLock = 1;
  pConf->nb2Send += msgSize;

  /* If end of send interrupt mode arrived during last instruction. */
  if (pConf->txLock == 2)
    pConf->nb2Send -= pConf->nbSent;

  /* Unlock access. */
  pConf->txLock = 0;
  if (msgSize < dataLength)
    pConf->nbMsgLost++;                /* Message not all sent. */
}

/**
 * @brief Tx Transfer completed callback.
 * @param huart UART handle.
 * @retval None
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  SERIAL_TxConfTypeDef* pConf = G_SERIAL_TX_Conf[0];
  UART_HandleTypeDef* pHandler = (UART_HandleTypeDef*)G_SERIAL_TX_Handler[0];
  if (pHandler == huart) {
    pConf->txStatus = SERIAL_TX_OK;
    pConf->pTx_R += pConf->nbSent;
    if (pConf->pTx_R >= pConf->pTx_BuffEnd) {
      pConf->pTx_R = pConf->pTx_BuffStart;
    }

    if (pConf->txLock == 0) {
      pConf->nb2Send -= pConf->nbSent;
    } else {
      pConf->txLock = 2;
    }
  }
}

/*******************************************************************************
 * Function Name  : USART3_TX_SendData
 * Description    : Send ring buffer management
 * Input          : Ring buffer context
 *******************************************************************************/
void USART3_TX_SendData(struct SERIAL_TxConf* pConf)
{
  uint16_t msgSize;

  /* If USART is not already running and data to send */
  if ((pConf->txStatus != SERIAL_TX_ON) && pConf->nb2Send) {
    pConf->txStatus = SERIAL_TX_ON;
    msgSize = (uint32_t)pConf->pTx_BuffEnd - (uint32_t)pConf->pTx_R;

    /* Send all msg or end of ring buffer */
    if (pConf->nb2Send <= msgSize) {
      pConf->nbSent = pConf->nb2Send;

      /* USART3 polling send mode*/
      HAL_UART_Transmit(&huart3, pConf->pTx_R, pConf->nb2Send,
                        G_USART3_TxPollTimeOut);

      /* Update info. Always consider data has been sent*/
      pConf->txStatus = SERIAL_TX_OK;
      pConf->pTx_R += pConf->nbSent;
      if (pConf->pTx_R >= pConf->pTx_BuffEnd) {
        pConf->pTx_R = pConf->pTx_BuffStart;
      }

      pConf->nb2Send -= pConf->nbSent;
    } else {
      pConf->nbSent = msgSize;

      /* USART3 polling send mode*/
      HAL_UART_Transmit(&huart3, pConf->pTx_R, msgSize, G_USART3_TxPollTimeOut);

      /* Update info. Always consider data has been sent*/
      pConf->txStatus = SERIAL_TX_OK;
      pConf->pTx_R += pConf->nbSent;
      if (pConf->pTx_R >= pConf->pTx_BuffEnd) {
        pConf->pTx_R = pConf->pTx_BuffStart;
      }

      pConf->nb2Send -= pConf->nbSent;
    }
  }
}

/*******************************************************************************
 * Function Name  : USART3_Tx_Initialization
 * Description    : Send Initialization of USART3
 * Input          : -
 *******************************************************************************/
void USART3_Tx_Initialization(void)
{
  /* Store USART3 send configuration and its handler. */

  /* Initialize ring buffer information. */
  USART3_TxConf.nb2Send = 0;
  USART3_TxConf.nbSent = 0;
  USART3_TxConf.nbMsgLost = 0;
  USART3_TxConf.buffSize = 512;
  USART3_TxConf.pTx_BuffStart = &USART3_TxDataBuffer[0];
  USART3_TxConf.pTx_BuffEnd = &USART3_TxDataBuffer[512];
  USART3_TxConf.pTx_W = USART3_TxDataBuffer;
  USART3_TxConf.pTx_R = USART3_TxDataBuffer;
  USART3_TxConf.CopyData = TX_CopyData;
  USART3_TxConf.SendData = USART3_TX_SendData;
  USART3_TxConf.txStatus = SERIAL_TX_OFF;
  USART3_TxConf.txLock = 0;

  /* Register this USART3 in global configuration stores. */
  G_SERIAL_TX_Conf[G_SERIAL_TX_Count] = &USART3_TxConf;
  G_SERIAL_TX_Handler[G_SERIAL_TX_Count] = (void*)&huart3;
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] motor_USART.c
 */
