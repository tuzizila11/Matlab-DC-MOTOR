/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: motor.c
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
#include "motor_private.h"

/* Named constants for Chart: '<S1>/Chart' */
#define motor_IN_NO_ACTIVE_CHILD       ((uint8_T)0U)
#define motor_IN_S1                    ((uint8_T)1U)
#define motor_IN_S2                    ((uint8_T)2U)
#define motor_IN_S3                    ((uint8_T)3U)
#define motor_IN_S4                    ((uint8_T)4U)

/* Block signals (default storage) */
B_motor motor_B;

/* Block states (default storage) */
DW_motor motor_DW;

/* Real-time model */
RT_MODEL_motor motor_M_;
RT_MODEL_motor *const motor_M = &motor_M_;

/* Model step function */
void motor_step(void)
{
  switch (motor_DW.RateTransition5_write_buf) {
   case 0:
    motor_DW.RateTransition5_read_buf = 1;
    break;

   case 1:
    motor_DW.RateTransition5_read_buf = 0;
    break;

   default:
    motor_DW.RateTransition5_read_buf = motor_DW.RateTransition5_last_buf_wr;
    break;
  }

  if (motor_DW.RateTransition5_read_buf != 0) {
    motor_B.RateTransition5 = motor_DW.RateTransition5_Buffer1;
  } else {
    motor_B.RateTransition5 = motor_DW.RateTransition5_Buffer0;
  }

  motor_DW.RateTransition5_read_buf = -1;
  switch (motor_DW.RateTransition_read_buf) {
   case 0:
    motor_DW.RateTransition_write_buf = 1;
    break;

   case 1:
    motor_DW.RateTransition_write_buf = 0;
    break;

   default:
    motor_DW.RateTransition_write_buf = (int8_T)
      ((motor_DW.RateTransition_last_buf_wr == 0) ? 1 : 0);
    break;
  }

  if (motor_DW.RateTransition_write_buf != 0) {
    motor_DW.RateTransition_Buffer1 = motor_B.Divide;
  } else {
    motor_DW.RateTransition_Buffer0 = motor_B.Divide;
  }

  motor_DW.RateTransition_last_buf_wr = motor_DW.RateTransition_write_buf;
  motor_DW.RateTransition_write_buf = -1;
  switch (motor_DW.RateTransition2_read_buf) {
   case 0:
    motor_DW.RateTransition2_write_buf = 1;
    break;

   case 1:
    motor_DW.RateTransition2_write_buf = 0;
    break;

   default:
    motor_DW.RateTransition2_write_buf = (int8_T)
      ((motor_DW.RateTransition2_last_buf_wr == 0) ? 1 : 0);
    break;
  }

  if (motor_DW.RateTransition2_write_buf != 0) {
    motor_DW.RateTransition2_Buffer1 = motor_B.Saturation;
  } else {
    motor_DW.RateTransition2_Buffer0 = motor_B.Saturation;
  }

  motor_DW.RateTransition2_last_buf_wr = motor_DW.RateTransition2_write_buf;
  motor_DW.RateTransition2_write_buf = -1;
  switch (motor_DW.RateTransition3_read_buf) {
   case 0:
    motor_DW.RateTransition3_write_buf = 1;
    break;

   case 1:
    motor_DW.RateTransition3_write_buf = 0;
    break;

   default:
    motor_DW.RateTransition3_write_buf = (int8_T)
      ((motor_DW.RateTransition3_last_buf_wr == 0) ? 1 : 0);
    break;
  }

  if (motor_DW.RateTransition3_write_buf != 0) {
    motor_DW.RateTransition3_Buffer1 = motor_B.Add1;
  } else {
    motor_DW.RateTransition3_Buffer0 = motor_B.Add1;
  }

  motor_DW.RateTransition3_last_buf_wr = motor_DW.RateTransition3_write_buf;
  motor_DW.RateTransition3_write_buf = -1;
  switch (motor_DW.RateTransition4_read_buf) {
   case 0:
    motor_DW.RateTransition4_write_buf = 1;
    break;

   case 1:
    motor_DW.RateTransition4_write_buf = 0;
    break;

   default:
    motor_DW.RateTransition4_write_buf = (int8_T)
      ((motor_DW.RateTransition4_last_buf_wr == 0) ? 1 : 0);
    break;
  }

  if (motor_DW.RateTransition4_write_buf != 0) {
    motor_DW.RateTransition4_Buffer1 = motor_B.Gain1;
  } else {
    motor_DW.RateTransition4_Buffer0 = motor_B.Gain1;
  }

  motor_DW.RateTransition4_last_buf_wr = motor_DW.RateTransition4_write_buf;
  motor_DW.RateTransition4_write_buf = -1;

  {
    /* Compute frequency only. Duty is null because of Rising edge interrupt configuration */
    /* lock interrupt access during process */
    /*__HAL_TIM_DISABLE_IT(&htim3,TIM_IT_CC1);*/
    /*if (TIM3_Conf.ICC1CaptureNumber == 3) {*/
    /* Change acquisition order */
    /*  TIM3_Conf.ICC1ReadValue2 = TIM3_Conf.ICC1ReadValue3;*/
    /*  TIM3_Conf.ICC1ReadValue3 = TIM3_Conf.ICC1ReadValue1;*/
    /*  TIM3_Conf.ICC1ReadValue1 = TIM3_Conf.ICC1ReadValue2;*/
    /*}*/
    /*if (TIM3_Conf.ICC1ReadValue3 >= TIM3_Conf.ICC1ReadValue1){*/
    /*  TIM3_Conf.ICC1Capture = (TIM3_Conf.ICC1ReadValue3 - TIM3_Conf.ICC1ReadValue1);*/
    /*} else {*/
    /*  TIM3_Conf.ICC1Capture = ((0xFFFF - TIM3_Conf.ICC1ReadValue1) + TIM3_Conf.ICC1ReadValue3);*/
    /*}*/

    /* Compute Frequency */
    if (TIM3_Conf.ICC1Capture) {
      TIM3_Conf.ICC1Freq = (uint32_t) TIM3_Conf.TIM_Clock /
        TIM3_Conf.ICC1Capture ;
    } else {
      TIM3_Conf.ICC1Freq = 0;
    }

    /* Duty is Null use it to output Capture value*/
    /*TIM3_Conf.ICC1Duty = TIM3_Conf.ICC1Capture;*/
    /* unlock interrupt */
    /*__HAL_TIM_ENABLE_IT(&htim3,TIM_IT_CC1);*/
    motor_B.Timers1_o2 = TIM3_Conf.ICC1Freq;
    motor_B.Timers1_o3 = TIM3_Conf.ICC1Duty;
  }

  {
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.2, which is the step size
   * of the task. Size of "clockTick0" ensures timer will not overflow during the
   * application lifespan selected.
   */
  motor_M->Timing.clockTick0++;
}

/* Model initialize function */
void motor_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)motor_M, 0,
                sizeof(RT_MODEL_motor));

  /* block I/O */
  (void) memset(((void *) &motor_B), 0,
                sizeof(B_motor));

  /* states (dwork) */
  (void) memset((void *)&motor_DW, 0,
                sizeof(DW_motor));

  {
    /* user code (Start function Header) */
    {
      /* TIM4 initialization. */
      /* Store TIM4 informations and its handler. */
      G_TIM_Conf[G_TIM_Count] = &TIM4_Conf;
      G_TIM_Handler[G_TIM_Count] = &htim4;
      G_TIM_Count++;

      /* Store TIM information. */
      TIM4_Conf.TIM_Prescaler = 1679;
      TIM4_Conf.TIM_APBClock = 84000000;
      TIM4_Conf.TIM_ARR = 100 - 1;
      TIM4_Conf.TIM_Clock = 50000.0;
      TIM4_Conf.TIM_Freq = 500.0;
      TIM4_Conf.CH1_duty = 50.0;
      TIM4_Conf.CH2_duty = 0.0;
      TIM4_Conf.CH3_duty = 0.0;
      TIM4_Conf.CH4_duty = 0.0;
      TIM4_Conf.CH1_type = OUTPUT_PWM;
      TIM4_Conf.CH2_type = UNKNOWN;
      TIM4_Conf.CH3_type = UNKNOWN;
      TIM4_Conf.CH4_type = UNKNOWN;

      /* Interrupt handler default initialization. */
      TIM4_Conf.ItUpFcn = NULL;
      TIM4_Conf.ItTrgFcn = NULL;
      TIM4_Conf.ItComFcn = NULL;
      TIM4_Conf.ItBrkFcn = NULL;
      TIM4_Conf.ItCcFcn = NULL;

      /* Auto-reload preload enable */
      /*****Bugzilla 63376 *****/
      /*SET_BIT((&htim4)->Instance->CR1,TIM_CR1_ARPE);*/

      /* Update register value with blockset value. */
      /* Prescaler. */
      __HAL_TIM_SET_PRESCALER(&htim4,TIM4_Conf.TIM_Prescaler);

      /* Autoreload: ARR. */
      __HAL_TIM_SET_AUTORELOAD(&htim4,100 - 1);

      /* Set CH1 Pulse value. */
      __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,(uint32_t)(50));

      /* Update registers before start operation to come. */
      HAL_TIM_GenerateEvent(&htim4,TIM_EVENTSOURCE_UPDATE);
    }

    {
      /* TIM3 initialization. */
      /* Store TIM3 informations and its handler. */
      G_TIM_Conf[G_TIM_Count] = &TIM3_Conf;
      G_TIM_Handler[G_TIM_Count] = &htim3;
      G_TIM_Count++;

      /* Store TIM information. */
      TIM3_Conf.TIM_Prescaler = 839;
      TIM3_Conf.TIM_APBClock = 84000000;
      TIM3_Conf.TIM_ARR = 1600 - 1;
      TIM3_Conf.TIM_Clock = 100000.0;
      TIM3_Conf.TIM_Freq = 62.5;
      TIM3_Conf.CH1_duty = 0.0;
      TIM3_Conf.CH2_duty = 0.0;
      TIM3_Conf.CH3_duty = 0.0;
      TIM3_Conf.CH4_duty = 0.0;

      /* Input Capture data channel 1. */
      TIM3_Conf.ICC1ReadValue1 = 0;
      TIM3_Conf.ICC1ReadValue2 = 0;
      TIM3_Conf.ICC1ReadValue3 = 0;
      TIM3_Conf.ICC1ReadValue4 = 0;
      TIM3_Conf.ICC1CaptureNumber = 1;
      TIM3_Conf.ICC1Capture = 0;
      TIM3_Conf.ICC1Freq = 0;
      TIM3_Conf.ICC1Duty = 0;
      TIM3_Conf.CH1_type = INPUT_CAPTURE;
      TIM3_Conf.CH2_type = UNKNOWN;
      TIM3_Conf.CH3_type = UNKNOWN;
      TIM3_Conf.CH4_type = UNKNOWN;

      /* Interrupt handler default initialization. */
      TIM3_Conf.ItUpFcn = NULL;
      TIM3_Conf.ItTrgFcn = NULL;
      TIM3_Conf.ItComFcn = NULL;
      TIM3_Conf.ItBrkFcn = NULL;
      TIM3_Conf.ItCcFcn = NULL;

      /* Update interrupt function. */
      TIM3_Conf.ItUpFcn = TIM3_ItUpFcn;

      /* Auto-reload preload enable */
      /*****Bugzilla 63376 *****/
      /*SET_BIT((&htim3)->Instance->CR1,TIM_CR1_ARPE);*/

      /* Timer is used as input capture. */
      /* Prescaler.*/
      __HAL_TIM_SET_PRESCALER(&htim3,TIM3_Conf.TIM_Prescaler);

      /* Autoreload: ARR is max value.*/
      __HAL_TIM_SET_AUTORELOAD(&htim3,0xFFFF);

      /* ClockDivision is null. */
      __HAL_TIM_SET_CLOCKDIVISION(&htim3,0x00);

      /* Update registers before start operation to come. */
      HAL_TIM_GenerateEvent(&htim3,TIM_EVENTSOURCE_UPDATE);
    }

    {
      /* TIM7 initialization. */
      /* Store TIM7 informations and its handler. */
      G_TIM_Conf[G_TIM_Count] = &TIM7_Conf;
      G_TIM_Handler[G_TIM_Count] = &htim7;
      G_TIM_Count++;

      /* Store TIM information. */
      TIM7_Conf.TIM_Prescaler = 839;
      TIM7_Conf.TIM_APBClock = 84000000;
      TIM7_Conf.TIM_ARR = 1000 - 1;
      TIM7_Conf.TIM_Clock = 100000.0;
      TIM7_Conf.TIM_Freq = 100.0;
      TIM7_Conf.CH1_duty = 0.0;
      TIM7_Conf.CH2_duty = 0.0;
      TIM7_Conf.CH3_duty = 0.0;
      TIM7_Conf.CH4_duty = 0.0;
      TIM7_Conf.CH1_type = UNKNOWN;
      TIM7_Conf.CH2_type = UNKNOWN;
      TIM7_Conf.CH3_type = UNKNOWN;
      TIM7_Conf.CH4_type = UNKNOWN;

      /* Interrupt handler default initialization. */
      TIM7_Conf.ItUpFcn = NULL;
      TIM7_Conf.ItTrgFcn = NULL;
      TIM7_Conf.ItComFcn = NULL;
      TIM7_Conf.ItBrkFcn = NULL;
      TIM7_Conf.ItCcFcn = NULL;

      /* Update interrupt function. */
      TIM7_Conf.ItUpFcn = TIM7_ItUpFcn;

      /* Auto-reload preload enable */
      /*****Bugzilla 63376 *****/
      /*SET_BIT((&htim7)->Instance->CR1,TIM_CR1_ARPE);*/

      /* Update register value with blockset value. */
      /* Prescaler. */
      __HAL_TIM_SET_PRESCALER(&htim7,TIM7_Conf.TIM_Prescaler);

      /* Autoreload: ARR. */
      __HAL_TIM_SET_AUTORELOAD(&htim7,1000 - 1);

      /* Update registers before start operation to come. */
      HAL_TIM_GenerateEvent(&htim7,TIM_EVENTSOURCE_UPDATE);
    }

    /* user code (Start function Body) */
    {
      /* TIM4 Start. */

      /* Wait for htim4 State READY. */
      while ((&htim4)->State == HAL_TIM_STATE_BUSY) {
      }

      HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
    }

    /* USART3 initialization for send. */
    USART3_Tx_Initialization();

    {
      /* External interrupt function registering. */
      EXTI_Callback[0] = EXTI0_Callback;
    }

    {
      /* TIM3 Start. */

      /* Wait for htim3 State READY. */
      while ((&htim3)->State == HAL_TIM_STATE_BUSY) {
      }

      HAL_TIM_IC_Start_IT(&htim3,TIM_CHANNEL_1);

      /* Start interrupt for Update event*/
      HAL_TIM_Base_Start_IT(&htim3);
    }

    {
      /* TIM7 Start. */
      /* Starts the TIM Base generation in interrupt mode. */
      HAL_TIM_Base_Start_IT(&htim7);

      /* Start interrupt for Update event*/
      HAL_TIM_Base_Start_IT(&htim7);
    }
  }

  motor_DW.RateTransition5_write_buf = -1;
  motor_DW.RateTransition5_read_buf = -1;
  motor_DW.RateTransition_write_buf = -1;
  motor_DW.RateTransition_read_buf = -1;
  motor_DW.RateTransition2_write_buf = -1;
  motor_DW.RateTransition2_read_buf = -1;
  motor_DW.RateTransition3_write_buf = -1;
  motor_DW.RateTransition3_read_buf = -1;
  motor_DW.RateTransition4_write_buf = -1;
  motor_DW.RateTransition4_read_buf = -1;

  /* System initialize for function-call system: '<Root>/Change Setpoint' */
  motor_DW.is_active_c5_motor = 0U;
  motor_DW.is_c5_motor = motor_IN_NO_ACTIVE_CHILD;

  /* System initialize for function-call system: '<Root>/PID Loop' */
  motor_DW.PIDLoop_PREV_T = motor_M->Timing.clockTick0;
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] motor.c
 */
