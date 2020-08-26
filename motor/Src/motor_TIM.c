/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: motor_TIM.c
 *
 * Code generated for Simulink model :motor.
 *
 * Model version      : 1.123
 * Simulink Coder version    : 9.3 (R2020a) 18-Nov-2019
 * TLC version       : 9.3 (May 28 2020)
 * C/C++ source code generated on  : Tue Aug 25 20:41:46 2020
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
#include "motor_TIM.h"

/* Number of configured TIMER. */
uint16_t G_TIM_Count = 0;

/* Array of TIMER information. */
TIM_ConfTypeDef* G_TIM_Conf[3];
TIM_HandleTypeDef* G_TIM_Handler[3];

/* TIM4 informations. */
TIM_ConfTypeDef TIM4_Conf;

/* TIM4 polling timeout value. Number of Solver loop. (can be changed). */
uint32_t G_TIM4_PollTimeOut = 10;

/* TIM3 informations. */
TIM_ConfTypeDef TIM3_Conf;

/* TIM7 informations. */
TIM_ConfTypeDef TIM7_Conf;

/* TIM7 polling timeout value. Number of Solver loop. (can be changed). */
uint32_t G_TIM7_PollTimeOut = 10;

/**
 * @brief  Input Capture callback in non-blocking mode
 * @param  htim TIM IC handle
 * @retval None
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  TIM_ConfTypeDef* pConf = G_TIM_Conf[0];
  TIM_HandleTypeDef* pHandler = G_TIM_Handler[0];

  {
    uint16_t idx = 0;
    for (idx = 0; idx < 3; idx++) {
      pHandler = G_TIM_Handler[idx];
      if (pHandler == htim) {
        pConf = G_TIM_Conf[idx];
        break;
      }
    }
  }

  if (pHandler == htim) {
    /* Test for channel 1. */
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
      if (pConf->CH1_type == INPUT_CAPTURE) {
        /* Process It for current received channel. */
        if (pConf->ICC1CaptureNumber == 1) {
          /* Get Input Capture value. */
          pConf->ICC1ReadValue1 = (uint16_t) (htim->Instance->CCR1);
          pConf->ICC1CaptureNumber = 3;

          /*RP MODIF */
          if (pConf->ICC1ReadValue1 >= pConf->ICC1ReadValue3) {
            pConf->ICC1Duty = (pConf->ICC1ReadValue1 -
                               pConf->ICC1ReadValue3);
          } else {
            pConf->ICC1Duty = ((0xFFFF - pConf->ICC1ReadValue3) +
                               pConf->ICC1ReadValue1);
          }
        } else if (pConf->ICC1CaptureNumber == 3) {
          /* Get Input Capture value. */
          pConf->ICC1ReadValue3 = (uint16_t) (htim->Instance->CCR1);
          pConf->ICC1CaptureNumber = 1;

          /*RP MODIF */
          if (pConf->ICC1ReadValue3 >= pConf->ICC1ReadValue1) {
            pConf->ICC1Duty = (pConf->ICC1ReadValue3 -
                               pConf->ICC1ReadValue1);
          } else {
            pConf->ICC1Duty = ((0xFFFF - pConf->ICC1ReadValue1) +
                               pConf->ICC1ReadValue3);
          }
        }
      } else if (pConf->CH1_type == INPUT_PWM) {
        /* Get Input Capture value for freq*/
        pConf->ICC1ReadValue1 = (uint16_t) (htim->Instance->CCR1);

        /* Get Input Capture value for duty*/
        pConf->ICC1ReadValue2 = (uint16_t) (htim->Instance->CCR2);
      }
    }

    /* Test for channel 2. */
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
      if (pConf->CH2_type == INPUT_CAPTURE) {
        /* Process It for current received channel. */
        if (pConf->ICC2CaptureNumber == 1) {
          /* Get Input Capture value. */
          pConf->ICC2ReadValue1 = (uint16_t) (htim->Instance->CCR2);
          pConf->ICC2CaptureNumber = 3;
        } else if (pConf->ICC2CaptureNumber == 3) {
          /* Get Input Capture value. */
          pConf->ICC2ReadValue3 = (uint16_t) (htim->Instance->CCR2);
          pConf->ICC2CaptureNumber = 1;
        }
      } else if (pConf->CH2_type == INPUT_PWM) {
        /* Get Input Capture value for freq*/
        pConf->ICC2ReadValue1 = (uint16_t) (htim->Instance->CCR1);

        /* Get Input Capture value for duty*/
        pConf->ICC2ReadValue2 = (uint16_t) (htim->Instance->CCR2);
      }
    }

    /* Test for channel 3. */
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3) {
      if (pConf->CH3_type == INPUT_CAPTURE) {
        /* Process It for current received channel. */
        if (pConf->ICC3CaptureNumber == 1) {
          /* Get Input Capture value. */
          pConf->ICC3ReadValue1 = (uint16_t) (htim->Instance->CCR3);
          pConf->ICC3CaptureNumber = 3;
        } else if (pConf->ICC3CaptureNumber == 3) {
          /* Get Input Capture value. */
          pConf->ICC3ReadValue3 = (uint16_t) (htim->Instance->CCR3);
          pConf->ICC3CaptureNumber = 1;
        }
      }
    }

    /* Test for channel 4. */
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4) {
      if (pConf->CH4_type == INPUT_CAPTURE) {
        /* Process It for current received channel. */
        if (pConf->ICC4CaptureNumber == 1) {
          /* Get Input Capture value. */
          pConf->ICC4ReadValue1 = (uint16_t) (htim->Instance->CCR4);
          pConf->ICC4CaptureNumber = 3;
        } else if (pConf->ICC4CaptureNumber == 3) {
          /* Get Input Capture value. */
          pConf->ICC4ReadValue3 = (uint16_t) (htim->Instance->CCR4);
          pConf->ICC4CaptureNumber = 1;
        }
      }
    }
  }
}

/*******************************************************************************
 * Function Name  : TIM_PeriodElapsedCustomCallback
 * Description    : Timer callback for update event
 * Input          : TIM_HandleTypeDef*   TIM IC handle
 *******************************************************************************/
void TIM_PeriodElapsedCustomCallback(TIM_HandleTypeDef *htim)
{
  TIM_ConfTypeDef * pConf = G_TIM_Conf[0];
  TIM_HandleTypeDef* pHandler = G_TIM_Handler[0];

  {
    uint16_t idx = 0;
    for (idx = 0;idx < 3;idx++) {
      pHandler = G_TIM_Handler[idx];
      if (pHandler == htim) {
        pConf = G_TIM_Conf[idx];
        break;
      }
    }
  }

  if (pHandler == htim) {
    if (pConf->ItUpFcn != NULL) {
      /* Call update function for TIM3. */
      pConf->ItUpFcn();
    }
  }
}

/*******************************************************************************
 * Function Name  : TIM3_ItUpFcn
 * Description    : TIM3 update interrupt
 * Input          : None
 * TIM3_ItUpFcn is called from TIM_PeriodElapsedCustomCallback function
 * in motor_TIM.c file.
 *******************************************************************************/
void TIM3_ItUpFcn()
{
  /* Output and update for function-call system: '<Root>/PID Loop' */
  {
    real_T rtb_NProdOut;
    real_T rtb_IProdOut;
    real_T rtb_ZeroGain;
    boolean_T rtb_NotEqual;
    uint32_T PIDLoop_ELAPS_T;
    real_T tmp;
    uint32_T PIDLoop_ELAPS_T_tmp;
    PIDLoop_ELAPS_T_tmp = motor_M->Timing.clockTick0;
    PIDLoop_ELAPS_T = PIDLoop_ELAPS_T_tmp - motor_DW.PIDLoop_PREV_T;
    motor_DW.PIDLoop_PREV_T = PIDLoop_ELAPS_T_tmp;

    {
      motor_B.PRESCALER_TIM3 = TIM3->PSC;
    }

    rtb_NProdOut = HAL_RCC_GetPCLK1Freq();

    {
      motor_B.PERIOD_TIM3 = TIM3->CCR1;
    }

    motor_B.Divide = ((1.0 / (motor_B.PRESCALER_TIM3 + 1.0)) * (2.0 *
      rtb_NProdOut)) / motor_B.PERIOD_TIM3;
    motor_B.Add1 = 455.0 - motor_B.Divide;
    rtb_NProdOut = ((motor_B.Add1 * 30.0) - motor_DW.Filter_DSTATE) * 100.0;
    rtb_IProdOut = ((motor_B.Add1 * 2.0) + motor_DW.Integrator_DSTATE) +
      rtb_NProdOut;
    if (rtb_IProdOut > 1000.0) {
      motor_B.Saturation = 1000.0;
    } else if (rtb_IProdOut < 0.0) {
      motor_B.Saturation = 0.0;
    } else {
      motor_B.Saturation = rtb_IProdOut;
    }

    motor_B.Gain1 = 0.080808080808080815 * motor_B.Saturation;
    rtb_ZeroGain = floor(motor_B.PERIOD_TIM3);
    if ((rtIsNaN(rtb_ZeroGain)) || (rtIsInf(rtb_ZeroGain))) {
      rtb_ZeroGain = 0.0;
    } else {
      rtb_ZeroGain = fmod(rtb_ZeroGain, 4.294967296E+9);
    }

    motor_B.DataTypeConversion = (rtb_ZeroGain < 0.0) ? ((uint32_T)((int32_T)
      (-((int32_T)((uint32_T)((real_T)(-rtb_ZeroGain))))))) : ((uint32_T)
      rtb_ZeroGain);
    rtb_ZeroGain = 0.0 * rtb_IProdOut;
    if (rtb_IProdOut > 1000.0) {
      rtb_IProdOut -= 1000.0;
    } else {
      if (rtb_IProdOut >= 0.0) {
        rtb_IProdOut = 0.0;
      }
    }

    rtb_NotEqual = (rtb_ZeroGain != rtb_IProdOut);
    if (rtb_IProdOut < 0.0) {
      rtb_IProdOut = -1.0;
    } else if (rtb_IProdOut > 0.0) {
      rtb_IProdOut = 1.0;
    } else if (rtb_IProdOut == 0.0) {
      rtb_IProdOut = 0.0;
    } else {
      rtb_IProdOut = (rtNaN);
    }

    if (rtIsNaN(rtb_IProdOut)) {
      rtb_ZeroGain = 0.0;
    } else {
      rtb_ZeroGain = fmod(rtb_IProdOut, 256.0);
    }

    rtb_IProdOut = motor_B.Add1 * 0.8;
    if (rtb_IProdOut < 0.0) {
      tmp = -1.0;
    } else if (rtb_IProdOut > 0.0) {
      tmp = 1.0;
    } else if (rtb_IProdOut == 0.0) {
      tmp = 0.0;
    } else {
      tmp = (rtNaN);
    }

    if (rtIsNaN(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 256.0);
    }

    if (rtb_NotEqual && (((int32_T)((int8_T)((rtb_ZeroGain < 0.0) ? ((int32_T)
             ((int8_T)(-((int8_T)((uint8_T)((real_T)(-rtb_ZeroGain))))))) :
            ((int32_T)((int8_T)((uint8_T)rtb_ZeroGain)))))) == ((tmp < 0.0) ?
          ((int32_T)((int8_T)(-((int8_T)((uint8_T)((real_T)(-tmp))))))) :
          ((int32_T)((int8_T)((uint8_T)tmp)))))) {
      rtb_IProdOut = 0.0;
    }

    {
      HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
    }

    rtb_ZeroGain = 0.2 * ((real_T)PIDLoop_ELAPS_T);
    motor_DW.Integrator_DSTATE += rtb_ZeroGain * rtb_IProdOut;
    motor_DW.Filter_DSTATE += rtb_ZeroGain * rtb_NProdOut;

    {
      if (motor_B.Gain1 != TIM4_Conf.CH1_duty) {
        TIM4_Conf.CH1_duty = motor_B.Gain1;
        if (motor_B.Gain1 >= 0) {
          /* Channel1 duty cycle is an input port. */
          __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,(uint32_t)(motor_B.Gain1 *
            (&htim4)->Instance->ARR / 100));
        }
      }
    }
  }
}

/*******************************************************************************
 * Function Name  : TIM7_ItUpFcn
 * Description    : TIM7 update interrupt
 * Input          : None
 * TIM7_ItUpFcn is called from TIM_PeriodElapsedCustomCallback function
 * in motor_TIM.c file.
 *******************************************************************************/
void TIM7_ItUpFcn()
{
  {
    switch (motor_DW.RateTransition4_write_buf) {
     case 0:
      motor_DW.RateTransition4_read_buf = 1;
      break;

     case 1:
      motor_DW.RateTransition4_read_buf = 0;
      break;

     default:
      motor_DW.RateTransition4_read_buf = motor_DW.RateTransition4_last_buf_wr;
      break;
    }

    if (motor_DW.RateTransition4_read_buf != 0) {
      motor_B.RateTransition4 = motor_DW.RateTransition4_Buffer1;
    } else {
      motor_B.RateTransition4 = motor_DW.RateTransition4_Buffer0;
    }

    motor_DW.RateTransition4_read_buf = -1;
    switch (motor_DW.RateTransition3_write_buf) {
     case 0:
      motor_DW.RateTransition3_read_buf = 1;
      break;

     case 1:
      motor_DW.RateTransition3_read_buf = 0;
      break;

     default:
      motor_DW.RateTransition3_read_buf = motor_DW.RateTransition3_last_buf_wr;
      break;
    }

    if (motor_DW.RateTransition3_read_buf != 0) {
      motor_B.RateTransition3 = motor_DW.RateTransition3_Buffer1;
    } else {
      motor_B.RateTransition3 = motor_DW.RateTransition3_Buffer0;
    }

    motor_DW.RateTransition3_read_buf = -1;
    switch (motor_DW.RateTransition2_write_buf) {
     case 0:
      motor_DW.RateTransition2_read_buf = 1;
      break;

     case 1:
      motor_DW.RateTransition2_read_buf = 0;
      break;

     default:
      motor_DW.RateTransition2_read_buf = motor_DW.RateTransition2_last_buf_wr;
      break;
    }

    if (motor_DW.RateTransition2_read_buf != 0) {
      motor_B.RateTransition2 = motor_DW.RateTransition2_Buffer1;
    } else {
      motor_B.RateTransition2 = motor_DW.RateTransition2_Buffer0;
    }

    motor_DW.RateTransition2_read_buf = -1;
    switch (motor_DW.RateTransition_write_buf) {
     case 0:
      motor_DW.RateTransition_read_buf = 1;
      break;

     case 1:
      motor_DW.RateTransition_read_buf = 0;
      break;

     default:
      motor_DW.RateTransition_read_buf = motor_DW.RateTransition_last_buf_wr;
      break;
    }

    if (motor_DW.RateTransition_read_buf != 0) {
      motor_B.RateTransition = motor_DW.RateTransition_Buffer1;
    } else {
      motor_B.RateTransition = motor_DW.RateTransition_Buffer0;
    }

    motor_DW.RateTransition_read_buf = -1;
    motor_B.RateTransition1 = motor_B.DataTypeConversion;

    /* Output and update for function-call system: '<Root>/Send Data' */
    {
      char_T string[50];
      static const char_T stringFormat[29] = "%u,%5.2f,%5.2f,%5.2f,%5.2f\r\n";
      snprintf(string, 50, stringFormat, motor_B.RateTransition1,
               motor_B.RateTransition3, motor_B.RateTransition2,
               motor_B.RateTransition, motor_B.RateTransition4);
      motor_B.buff = getBuffPtr(string);
      motor_B.nbChar = 46U;

      {
        if (motor_B.nbChar != 0) {
          /* Copy data to send. */
          TX_CopyData(&USART3_TxConf, (uint8_t*)motor_B.buff, (uint16_t)
                      motor_B.nbChar);
        }

        if (USART3_TxConf.nb2Send) {
          motor_B.USART_Send = 0;
          USART3_TX_SendData(&USART3_TxConf);
        }

        if (USART3_TxConf.txStatus != SERIAL_TX_ON) {
          motor_B.USART_Send = USART3_TxConf.nbSent;
        }
      }
    }
  }
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] motor_TIM.c
 */
