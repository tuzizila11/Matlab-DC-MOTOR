/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: motor.h
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

#ifndef RTW_HEADER_motor_h_
#define RTW_HEADER_motor_h_
#include <math.h>
#include <string.h>
#include "motor_TIM.h"
#include "motor_USART.h"
#include "STM32_Config.h"
#include "motor_External_Functions.h"
#include "motor_EXTI.h"
#ifndef motor_COMMON_INCLUDES_
# define motor_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "getBuffPtr.h"
#include "main.h"
#include "stdio.h"
#include "stm32f4xx_hal_rcc.h"
#endif                                 /* motor_COMMON_INCLUDES_ */

#include "motor_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T RateTransition5;              /* '<Root>/Rate Transition5' */
  real_T RateTransition4;              /* '<Root>/Rate Transition4' */
  real_T RateTransition3;              /* '<Root>/Rate Transition3' */
  real_T RateTransition2;              /* '<Root>/Rate Transition2' */
  real_T RateTransition;               /* '<Root>/Rate Transition' */
  real_T PRESCALER_TIM3;               /* '<S2>/PRESCALER_TIM3' */
  real_T PERIOD_TIM3;                  /* '<S2>/PERIOD_TIM3' */
  real_T Divide;                       /* '<S2>/Divide' */
  real_T Add1;                         /* '<S2>/Add1' */
  real_T Saturation;                   /* '<S46>/Saturation' */
  real_T Gain1;                        /* '<S2>/Gain1' */
  real_T y;                            /* '<S1>/Chart' */
  uint32_T Timers1_o2;                 /* '<Root>/Timers1' */
  uint32_T Timers1_o3;                 /* '<Root>/Timers1' */
  uint32_T RateTransition1;            /* '<Root>/Rate Transition1' */
  uint32_T buff;                       /* '<S3>/Telemetry' */
  uint32_T DataTypeConversion;         /* '<S2>/Data Type Conversion' */
  uint16_T USART_Send;                 /* '<S3>/USART_Send' */
  uint16_T nbChar;                     /* '<S3>/Telemetry' */
} B_motor;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S39>/Integrator' */
  real_T Filter_DSTATE;                /* '<S34>/Filter' */
  volatile real_T RateTransition5_Buffer0;/* '<Root>/Rate Transition5' */
  volatile real_T RateTransition5_Buffer1;/* '<Root>/Rate Transition5' */
  volatile real_T RateTransition_Buffer0;/* '<Root>/Rate Transition' */
  volatile real_T RateTransition_Buffer1;/* '<Root>/Rate Transition' */
  volatile real_T RateTransition2_Buffer0;/* '<Root>/Rate Transition2' */
  volatile real_T RateTransition2_Buffer1;/* '<Root>/Rate Transition2' */
  volatile real_T RateTransition3_Buffer0;/* '<Root>/Rate Transition3' */
  volatile real_T RateTransition3_Buffer1;/* '<Root>/Rate Transition3' */
  volatile real_T RateTransition4_Buffer0;/* '<Root>/Rate Transition4' */
  volatile real_T RateTransition4_Buffer1;/* '<Root>/Rate Transition4' */
  uint32_T PIDLoop_PREV_T;             /* '<Root>/PID Loop' */
  volatile int8_T RateTransition5_write_buf;/* '<Root>/Rate Transition5' */
  volatile int8_T RateTransition5_read_buf;/* '<Root>/Rate Transition5' */
  volatile int8_T RateTransition5_last_buf_wr;/* '<Root>/Rate Transition5' */
  volatile int8_T RateTransition_write_buf;/* '<Root>/Rate Transition' */
  volatile int8_T RateTransition_read_buf;/* '<Root>/Rate Transition' */
  volatile int8_T RateTransition_last_buf_wr;/* '<Root>/Rate Transition' */
  volatile int8_T RateTransition2_write_buf;/* '<Root>/Rate Transition2' */
  volatile int8_T RateTransition2_read_buf;/* '<Root>/Rate Transition2' */
  volatile int8_T RateTransition2_last_buf_wr;/* '<Root>/Rate Transition2' */
  volatile int8_T RateTransition3_write_buf;/* '<Root>/Rate Transition3' */
  volatile int8_T RateTransition3_read_buf;/* '<Root>/Rate Transition3' */
  volatile int8_T RateTransition3_last_buf_wr;/* '<Root>/Rate Transition3' */
  volatile int8_T RateTransition4_write_buf;/* '<Root>/Rate Transition4' */
  volatile int8_T RateTransition4_read_buf;/* '<Root>/Rate Transition4' */
  volatile int8_T RateTransition4_last_buf_wr;/* '<Root>/Rate Transition4' */
  uint8_T is_active_c5_motor;          /* '<S1>/Chart' */
  uint8_T is_c5_motor;                 /* '<S1>/Chart' */
} DW_motor;

/* Real-time Model Data Structure */
struct tag_RTM_motor {
  const char_T *errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
  } Timing;
};

/* Block signals (default storage) */
extern B_motor motor_B;

/* Block states (default storage) */
extern DW_motor motor_DW;

/* Model entry point functions */
extern void motor_initialize(void);
extern void motor_step(void);

/* Real-time Model object */
extern RT_MODEL_motor *const motor_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'motor'
 * '<S1>'   : 'motor/Change Setpoint'
 * '<S2>'   : 'motor/PID Loop'
 * '<S3>'   : 'motor/Send Data'
 * '<S4>'   : 'motor/Change Setpoint/Chart'
 * '<S5>'   : 'motor/PID Loop/Discrete PID Controller'
 * '<S6>'   : 'motor/PID Loop/Gains'
 * '<S7>'   : 'motor/PID Loop/Get APB1 Freq'
 * '<S8>'   : 'motor/PID Loop/Discrete PID Controller/Anti-windup'
 * '<S9>'   : 'motor/PID Loop/Discrete PID Controller/D Gain'
 * '<S10>'  : 'motor/PID Loop/Discrete PID Controller/Filter'
 * '<S11>'  : 'motor/PID Loop/Discrete PID Controller/Filter ICs'
 * '<S12>'  : 'motor/PID Loop/Discrete PID Controller/I Gain'
 * '<S13>'  : 'motor/PID Loop/Discrete PID Controller/Ideal P Gain'
 * '<S14>'  : 'motor/PID Loop/Discrete PID Controller/Ideal P Gain Fdbk'
 * '<S15>'  : 'motor/PID Loop/Discrete PID Controller/Integrator'
 * '<S16>'  : 'motor/PID Loop/Discrete PID Controller/Integrator ICs'
 * '<S17>'  : 'motor/PID Loop/Discrete PID Controller/N Copy'
 * '<S18>'  : 'motor/PID Loop/Discrete PID Controller/N Gain'
 * '<S19>'  : 'motor/PID Loop/Discrete PID Controller/P Copy'
 * '<S20>'  : 'motor/PID Loop/Discrete PID Controller/Parallel P Gain'
 * '<S21>'  : 'motor/PID Loop/Discrete PID Controller/Reset Signal'
 * '<S22>'  : 'motor/PID Loop/Discrete PID Controller/Saturation'
 * '<S23>'  : 'motor/PID Loop/Discrete PID Controller/Saturation Fdbk'
 * '<S24>'  : 'motor/PID Loop/Discrete PID Controller/Sum'
 * '<S25>'  : 'motor/PID Loop/Discrete PID Controller/Sum Fdbk'
 * '<S26>'  : 'motor/PID Loop/Discrete PID Controller/Tracking Mode'
 * '<S27>'  : 'motor/PID Loop/Discrete PID Controller/Tracking Mode Sum'
 * '<S28>'  : 'motor/PID Loop/Discrete PID Controller/Tsamp - Integral'
 * '<S29>'  : 'motor/PID Loop/Discrete PID Controller/Tsamp - Ngain'
 * '<S30>'  : 'motor/PID Loop/Discrete PID Controller/postSat Signal'
 * '<S31>'  : 'motor/PID Loop/Discrete PID Controller/preSat Signal'
 * '<S32>'  : 'motor/PID Loop/Discrete PID Controller/Anti-windup/Disc. Clamping Parallel'
 * '<S33>'  : 'motor/PID Loop/Discrete PID Controller/D Gain/External Parameters'
 * '<S34>'  : 'motor/PID Loop/Discrete PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S35>'  : 'motor/PID Loop/Discrete PID Controller/Filter ICs/Internal IC - Filter'
 * '<S36>'  : 'motor/PID Loop/Discrete PID Controller/I Gain/External Parameters'
 * '<S37>'  : 'motor/PID Loop/Discrete PID Controller/Ideal P Gain/Passthrough'
 * '<S38>'  : 'motor/PID Loop/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S39>'  : 'motor/PID Loop/Discrete PID Controller/Integrator/Discrete'
 * '<S40>'  : 'motor/PID Loop/Discrete PID Controller/Integrator ICs/Internal IC'
 * '<S41>'  : 'motor/PID Loop/Discrete PID Controller/N Copy/Disabled'
 * '<S42>'  : 'motor/PID Loop/Discrete PID Controller/N Gain/External Parameters'
 * '<S43>'  : 'motor/PID Loop/Discrete PID Controller/P Copy/Disabled'
 * '<S44>'  : 'motor/PID Loop/Discrete PID Controller/Parallel P Gain/External Parameters'
 * '<S45>'  : 'motor/PID Loop/Discrete PID Controller/Reset Signal/Disabled'
 * '<S46>'  : 'motor/PID Loop/Discrete PID Controller/Saturation/Enabled'
 * '<S47>'  : 'motor/PID Loop/Discrete PID Controller/Saturation Fdbk/Disabled'
 * '<S48>'  : 'motor/PID Loop/Discrete PID Controller/Sum/Sum_PID'
 * '<S49>'  : 'motor/PID Loop/Discrete PID Controller/Sum Fdbk/Disabled'
 * '<S50>'  : 'motor/PID Loop/Discrete PID Controller/Tracking Mode/Disabled'
 * '<S51>'  : 'motor/PID Loop/Discrete PID Controller/Tracking Mode Sum/Passthrough'
 * '<S52>'  : 'motor/PID Loop/Discrete PID Controller/Tsamp - Integral/Passthrough'
 * '<S53>'  : 'motor/PID Loop/Discrete PID Controller/Tsamp - Ngain/Passthrough'
 * '<S54>'  : 'motor/PID Loop/Discrete PID Controller/postSat Signal/Forward_Path'
 * '<S55>'  : 'motor/PID Loop/Discrete PID Controller/preSat Signal/Forward_Path'
 * '<S56>'  : 'motor/Send Data/Telemetry'
 */
#endif                                 /* RTW_HEADER_motor_h_ */

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] motor.h
 */
