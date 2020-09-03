/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: motor_EXTI.c
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
#include "motor_EXTI.h"

#define motor_IN_NO_ACTIVE_CHILD       ((uint8_T)0U)
#define motor_IN_S1                    ((uint8_T)1U)
#define motor_IN_S2                    ((uint8_T)2U)
#define motor_IN_S3                    ((uint8_T)3U)
#define motor_IN_S4                    ((uint8_T)4U)

/* Exti function pointer array */
void (*EXTI_Callback[16])(void) = { NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

/**
 * @brief  EXTI line detection callbacks.
 * @param  GPIO_Pin Specifies the pins connected EXTI line
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  uint16_t pinNum = 0;
  switch (GPIO_Pin) {
   case GPIO_PIN_1 :
    pinNum = 1;
    break;

   case GPIO_PIN_2 :
    pinNum = 2;
    break;

   case GPIO_PIN_3 :
    pinNum = 3;
    break;

   case GPIO_PIN_4 :
    pinNum = 4;
    break;

   case GPIO_PIN_5 :
    pinNum = 5;
    break;

   case GPIO_PIN_6 :
    pinNum = 6;
    break;

   case GPIO_PIN_7 :
    pinNum = 7;
    break;

   case GPIO_PIN_8 :
    pinNum = 8;
    break;

   case GPIO_PIN_9 :
    pinNum = 9;
    break;

   case GPIO_PIN_10 :
    pinNum = 10;
    break;

   case GPIO_PIN_11 :
    pinNum = 11;
    break;

   case GPIO_PIN_12 :
    pinNum = 12;
    break;

   case GPIO_PIN_13 :
    pinNum = 13;
    break;

   case GPIO_PIN_14 :
    pinNum = 14;
    break;

   case GPIO_PIN_15 :
    pinNum = 15;
    break;

   default:
    pinNum = 0;
    break;
  }

  if (EXTI_Callback[pinNum] != NULL) {
    (*EXTI_Callback[pinNum])();
  }
}

/*******************************************************************************
 * Function Name  : EXTI0_Callback
 * Description    : Callback for External Interrupt connected to Pin0
 * Input          : -
 *******************************************************************************/
void EXTI0_Callback()
{
  {
    /* Output and update for function-call system: '<Root>/Change Setpoint' */
    if (((uint32_T)motor_DW.is_active_c5_motor) == 0U) {
      motor_DW.is_active_c5_motor = 1U;
      motor_DW.is_c5_motor = motor_IN_S1;
      motor_B.y = 150.0;
    } else {
      switch (motor_DW.is_c5_motor) {
       case motor_IN_S1:
        motor_DW.is_c5_motor = motor_IN_S2;
        motor_B.y = 300.0;
        break;

       case motor_IN_S2:
        motor_DW.is_c5_motor = motor_IN_S3;
        motor_B.y = 450.0;
        break;

       case motor_IN_S3:
        motor_DW.is_c5_motor = motor_IN_S4;
        motor_B.y = 600.0;
        break;

       default:
        /* case IN_S4: */
        motor_DW.is_c5_motor = motor_IN_S1;
        motor_B.y = 150.0;
        break;
      }
    }

    {
      HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
    }

    switch (motor_DW.RateTransition5_read_buf) {
     case 0:
      motor_DW.RateTransition5_write_buf = 1;
      break;

     case 1:
      motor_DW.RateTransition5_write_buf = 0;
      break;

     default:
      motor_DW.RateTransition5_write_buf = (int8_T)
        ((motor_DW.RateTransition5_last_buf_wr == 0) ? 1 : 0);
      break;
    }

    if (motor_DW.RateTransition5_write_buf != 0) {
      motor_DW.RateTransition5_Buffer1 = motor_B.y;
    } else {
      motor_DW.RateTransition5_Buffer0 = motor_B.y;
    }

    motor_DW.RateTransition5_last_buf_wr = motor_DW.RateTransition5_write_buf;
    motor_DW.RateTransition5_write_buf = -1;
  }
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] motor_EXTI.c
 */
