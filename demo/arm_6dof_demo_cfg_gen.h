/**
 * @file arm_6dof_demo_cfg_gen.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-06-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef _ARM_6DOF_DEMO_CONFIG_H_
#define _ARM_6DOF_DEMO_CONFIG_H_

#include "platform_config.h"

#define MCAL_ADC_CONFIG
enum MCAL_ADC_IdType {ADC_1, ADC_2, ADC_3, MCAL_ADC_CHANNEL_NR_OF};
enum NULL_IdType {A3, A4, A5, NULL_CHANNEL_NR_OF};
#include "MCAL/mcal_adc/mcal_adc.h"

#define DD_POTENTIOMETER_CONFIG
enum DD_POT_IdType {POT_1, POT_2, POT_3, DD_POT_CHANNEL_NR_OF};
#include "ESW/dd_pot/dd_potentiometer.h"

#define VD_ANGLE_SENS_CONFIG
enum VD_ANGLE_SENS_IdType {ANGSNS_1, ANGSNS_2, ANGSNS_3, VD_ANGLE_SENS_CHANNEL_NR_OF};
#include "ESW/vd_angle_sens/vd_angle_sens.h"

#define DD_PCA9685_CONFIG
enum DD_PCA9685_IdType {PCA9685_PWM_1, PCA9685_PWM_2, PCA9685_PWM_3, DD_PCA9685_CHANNEL_NR_OF};
#define PCA9685_PWM_FREQ 50
#include "ESW/dd_pca9685/dd_pca9685.h"

#define DD_SERVO_CONFIG
enum DD_SERVO_IdType {DD_SERVO_1, DD_SERVO_2, DD_SERVO_3, DD_SERVO_CHANNEL_NR_OF};
#include "ESW/dd_servo/dd_servo.h"

#define VD_SERVO_CONFIG
enum VD_SERVO_IdType {VD_SERVO_1, VD_SERVO_2, VD_SERVO_3, VD_SERVO_CHANNEL_NR_OF};
#define SECOND_MS 1000.0
#define SERVO_TASK_REC 10
#define SERVO_TASK_OFFSET 100
#include "ESW/vd_servo/vd_servo.h"

#define OS_TIME_TRIG_CONFIG
#include "BSW/os_time_trig/os_time_trig.h"

#define ARM_6DOF_CONFIG
enum ARM_6DOF_IdType {ARM_9DOF_1, ARM_6DOF_CHANNEL_NR_OF};
enum ARM_6DOF_SERVO_IdType {ACT_BASE, ACT_L1, ACT_L2, ACT_ROLL, ACT_PITCH, ACT_CLAW, ARM_6DOF_SERVO_CHANNEL_NR_OF};
enum ARM_6DOF_SEGMENT_IdType {SEG_BASE, SEG_L1, SEG_L2, ARM_6DOF_SEGMENT_CHANNEL_NR_OF};
#include "ASW/arm_6dof/arm_6dof.h"

Std_ReturnType arm_6dof_demo_config(void);

#endif // _ARM_6DOF_DEMO_CONFIG_H_
