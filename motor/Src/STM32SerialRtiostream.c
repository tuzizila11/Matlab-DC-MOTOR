/* STM32SerialRtiostream.c
 *
 * Specifies rtiostream functions to implement serial external mode
 *
 * NOTES:
 *  - rtIOStreamSend & rtIOStreamRecv functions send and receive
 *    8-bit characters.
 *
 * Copyright 2011 The MathWorks, Inc.
 */

/* Include header files */
#include <stdlib.h>
#include <stdio.h>

#include "STM32SerialRtiostream.h"
/* STM32SerialRtiostream_Config.h is generated with definitions
depending on USART selection */
#include "STM32SerialRtiostream_Config.h"

/* Set when current send operation is terminated */
static volatile uint8_t TxCplt = 0;

/* Function prototypes. */
void USARTx_IRQHandler(void);

#define BUF_RCV_LEN 512
static uint8_t buffRcv[BUF_RCV_LEN];
static uint8_t rcvOn;   /* Receive on going. */
static uint8_t * ptSet; /* Pointer to received char. */
static uint8_t * ptGet; /* Pointer to char to process. */
static uint32_t nbRcv;  /* Nb of received char. */



/* Function: rtIOStreamOpen ================================================= */
/* Configuration of USART for rtIOStream =====================================*/
int rtIOStreamOpen(int argc, void * argv[])
{
    (void)argc;
    (void)argv;

    ptSet = buffRcv;
    ptGet = buffRcv;
    nbRcv = 0;
    /* Start Receive (to be ready to receive something). */
    rcvOn = 1;
    HAL_UART_Receive_IT(EXT_MODE_USART_HANDLE, ptSet, (uint16_t)1);

    return SERVER_STREAM_ID;
}


/* Function: rtIOStreamClose ================================================ */
int rtIOStreamClose(int streamID)
{
    /* Stop Receive. */
    rcvOn = 0;

    return RTIOSTREAM_NO_ERROR;
}

uint8_t stateSend = 0;

/* Function: rtIOStreamSend ================================================ */
int rtIOStreamSend(int streamID, const void * src, size_t size, size_t * sizeSent)
{
    (void)streamID;
    HAL_StatusTypeDef status;
    TxCplt = 0;

    /* Nothing sent. */
    *sizeSent = 0;

    if (HAL_OK == HAL_UART_Transmit_IT(EXT_MODE_USART_HANDLE, (uint8_t *)src, (uint16_t)size))
    {
        stateSend = HAL_UART_GetState(EXT_MODE_USART_HANDLE);

        /* Wait for end of Tx. */
        while (!TxCplt && ((HAL_UART_GetState(EXT_MODE_USART_HANDLE) == HAL_UART_STATE_BUSY_TX)
                           || (HAL_UART_GetState(EXT_MODE_USART_HANDLE) == HAL_UART_STATE_BUSY_TX_RX)));

        if (TxCplt)
        {
            *sizeSent = size;
        }
    }

    /* Verify at end of send if rcv has been stopped. */
    if (rcvOn == 0)
    {
        /* Re-start rcv. */
        rcvOn = 1;
        /* Rcv one more. */
        status = HAL_UART_Receive_IT(EXT_MODE_USART_HANDLE, (uint8_t *)ptSet, (uint16_t)1);

        /* Test if ask for Rcv can't be done. */
        if (status != HAL_OK)
        {
            rcvOn = 0;

            if (EXT_MODE_USART_HANDLE->Lock == HAL_UNLOCKED && HAL_UART_GetState(EXT_MODE_USART_HANDLE) == HAL_UART_STATE_BUSY_RX)
            {
                HAL_UART_Init(EXT_MODE_USART_HANDLE);
            }
        }
    }

    return RTIOSTREAM_NO_ERROR;
}

/* Function: rtIOStreamRecv ================================================ */
int rtIOStreamRecv(int streamID, void * dst, size_t size, size_t * sizeRecv)
{
    (void)streamID;
    HAL_StatusTypeDef status;
    size_t size2Rcv = size;

    char * ptDst = (char *)dst;

    /* Nothing received. */
    *sizeRecv = 0;

    if (size2Rcv >= BUF_RCV_LEN)
    {
        size2Rcv = BUF_RCV_LEN;
    }

    if (ptGet != ptSet)
    {
        do
        {
            *ptDst++ = *ptGet++;

            if (ptGet == &buffRcv[BUF_RCV_LEN])
            {
                ptGet = buffRcv;
            }

            *sizeRecv += 1;
            size2Rcv--;
            nbRcv--;
        }
        while (nbRcv > 0 && (ptGet != ptSet) && size2Rcv > 0);
    }

    if (rcvOn == 0)
    {
        /* Re-start rcv. */
        rcvOn = 1;
        status = HAL_UART_Receive_IT(EXT_MODE_USART_HANDLE, (uint8_t *)ptSet, (uint16_t)1);

        /* Test if ask for Rcv can't be done. */
        if (status != HAL_OK)
        {
            rcvOn = 0;

            if (EXT_MODE_USART_HANDLE->Lock == HAL_UNLOCKED && HAL_UART_GetState(EXT_MODE_USART_HANDLE) == HAL_UART_STATE_BUSY_RX)
            {
                HAL_UART_Init(EXT_MODE_USART_HANDLE);
            }
        }
    }

    return RTIOSTREAM_NO_ERROR;
}

/*******************************************************************************
* Function Name  : HAL_UART_RxCpltCallback
* Description    : Rx Transfer completed callbacks.
* Input          : UART handle
*******************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart)
{
    HAL_StatusTypeDef status;

    /* Increment pointer on receive buffer. */
    ptSet++;

    /* Increment number of receive char. */
    nbRcv++;

    /* Test end of receive buffer. */
    if (ptSet == &buffRcv[BUF_RCV_LEN])
    {
        ptSet = buffRcv;
    }

    if (ptSet == ptGet)
    {
        /* Stop Rcv. */
        rcvOn = 0;
    }
    else
    {
        rcvOn = 1;
        /* Rcv one more. */
        status = HAL_UART_Receive_IT(EXT_MODE_USART_HANDLE, ptSet, (uint16_t)1);

        /* Test if ask for Rcv can't be done. */
        if (status != HAL_OK)
        {
            rcvOn = 0;

            if (EXT_MODE_USART_HANDLE->Lock == HAL_UNLOCKED && HAL_UART_GetState(EXT_MODE_USART_HANDLE) == HAL_UART_STATE_BUSY_RX)
            {
                HAL_UART_Init(EXT_MODE_USART_HANDLE);
            }
        }
    }
}

/*******************************************************************************
* Function Name  : HAL_UART_TxCpltCallback
* Description    : Tx Transfer completed callbacks.
* Input          : UART handle
*******************************************************************************/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef * huart)
{
    HAL_StatusTypeDef status;

    /* Tx complete. */
    TxCplt = 1;

    /* Test if we tried to receive one more during send. */
    if (rcvOn == 0)
    {
        rcvOn = 1;
        /* Rcv one more. */
        status = HAL_UART_Receive_IT(EXT_MODE_USART_HANDLE, ptSet, (uint16_t)1);

        /* Test if ask for Rcv can't be done. */
        if (status != HAL_OK)
        {
            rcvOn = 0;

            if (EXT_MODE_USART_HANDLE->Lock == HAL_UNLOCKED && HAL_UART_GetState(EXT_MODE_USART_HANDLE) == HAL_UART_STATE_BUSY_RX)
            {
                HAL_UART_Init(EXT_MODE_USART_HANDLE);
            }
        }
    }
}

/*******************************************************************************
* Function Name  : HAL_UART_ErrorCallback
* Description    : Callback called for USART Rx/Tx errors like Overrun etc...
* Input          : UART handle
*******************************************************************************/
void HAL_UART_ErrorCallback(UART_HandleTypeDef * huart)
{
    HAL_StatusTypeDef status;
	
    /* Try to receive one char again. */
    status = HAL_UART_Receive_IT(EXT_MODE_USART_HANDLE, (uint8_t *)ptSet, (uint16_t)1);

    /* Test if ask for Rcv can't be done. */
    if (status != HAL_OK)
    {
        if (EXT_MODE_USART_HANDLE->Lock == HAL_UNLOCKED && HAL_UART_GetState(EXT_MODE_USART_HANDLE) == HAL_UART_STATE_BUSY_RX)
        {
            HAL_UART_Init(EXT_MODE_USART_HANDLE);
        }
    }

    /* Received error. */
    rcvOn = 0;
}

