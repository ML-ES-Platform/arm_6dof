/**
 * @file arm_6dof_demo_config.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-06-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "arm_6dof_demo_config.h"

Std_ChannelIdType ADC_PIN_Group[MCAL_ADC_CHANNEL_NR_OF] = {A3, A4, A5};

Std_ChannelIdType ADC_Group[MCAL_ADC_CHANNEL_NR_OF] = {ADC_1, ADC_2, ADC_3};

Std_ChannelIdType POT_Group[DD_POT_CHANNEL_NR_OF] = {POT_1, POT_2, POT_3};

Std_ChannelIdType ANGSNS_Group[VD_ANGLE_SENS_CHANNEL_NR_OF] = {ANGSNS_1, ANGSNS_2, ANGSNS_3};

Std_ChannelIdType PCA9685_PIN_Group[PCA9685_PIN_NR_OF] = {PCA9685_PIN_1, PCA9685_PIN_2, PCA9685_PIN_2};

Std_ChannelIdType PCA9685_Group[DD_PCA9685_CHANNEL_NR_OF] = {PCA9685_PWM_1, PCA9685_PWM_2, PCA9685_PWM_3};

Std_ChannelIdType DDSERVO_Group[DD_SERVO_CHANNEL_NR_OF] = {DD_SERVO_1, DD_SERVO_2, DD_SERVO_3};

Std_ChannelIdType VDSERVO_Group[VD_SERVO_CHANNEL_NR_OF] = {VD_SERVO_1, VD_SERVO_2, VD_SERVO_3};

OSTT_TaskDescriptor_t VD_ServoRun_TaskDescriptor_1 = OSTT_TaskDescriptorDefault();

//Std_ChannelIdType ARM_ServoGroup[ARM_6DOF_SERVO_CHANNEL_NR_OF] = {ACT_BASE = 0, ACT_L1, ACT_L2, ACT_ROLL, ACT_PITCH, ACT_CLAW};
Std_ChannelIdType ARM_ServoGroup[ARM_6DOF_SERVO_CHANNEL_NR_OF] = {ACT_BASE, ACT_L1, ACT_L2};
Std_ChannelIdType ARM_SegmentGroup[ARM_6DOF_SEGMENT_CHANNEL_NR_OF] = {SEG_BASE, SEG_L1, SEG_L2};




Std_ReturnType arm_6dof_demo_config(void)
{

    Serial.begin(115200);
    Serial.println("Application Demo for 3-DOF Robotic arm  control");

    Std_ReturnType error = E_OK;

    error += ADC_GroupSetup(ADC_Group, ADC_PIN_Group, MCAL_ADC_CHANNEL_NR_OF);
    error += MCAL_ADC_ChannelSetup(ADC_1, A3);
    error += MCAL_ADC_ChannelSetup(ADC_2, A4);
    error += MCAL_ADC_ChannelSetup(ADC_3, A5);

    Serial.print("MCAL ADC configured - Error : ");
    Serial.println(error);

    error += POT_GroupSetup(POT_Group, ADC_Group, DD_POT_CHANNEL_NR_OF);
    error += DD_POT_ChannelSetup(POT_1, ADC_1);
    error += DD_POT_ChannelSetup(POT_2, ADC_2);
    error += DD_POT_ChannelSetup(POT_3, ADC_3);

    error += POT_SetGroupRawGetter(POT_Group, ADC_ReadChannel, DD_POT_CHANNEL_NR_OF);
    error += DD_POT_SetPullMethod(POT_1, ADC_ReadChannel);
    error += DD_POT_SetPullMethod(POT_2, ADC_ReadChannel);
    error += DD_POT_SetPullMethod(POT_3, ADC_ReadChannel);

    Serial.print("DD POT configured - Error : ");
    Serial.println(error);

    error += ANGSNS_GroupSetup(ANGSNS_Group, POT_Group, VD_ANGLE_SENS_CHANNEL_NR_OF);
    error += VD_ANGLE_SENS_ChannelSetup(ANGSNS_1, POT_1);
    error += VD_ANGLE_SENS_ChannelSetup(ANGSNS_2, POT_2);
    error += VD_ANGLE_SENS_ChannelSetup(ANGSNS_3, POT_3);

    error += ANGSNS_SetGroupSourceGetter(ANGSNS_Group, POT_GetPosition, VD_ANGLE_SENS_CHANNEL_NR_OF);
    error += VD_ANGLE_SENS_SetPullMethod(ANGSNS_1, POT_GetPosition);
    error += VD_ANGLE_SENS_SetPullMethod(ANGSNS_2, POT_GetPosition);
    error += VD_ANGLE_SENS_SetPullMethod(ANGSNS_3, POT_GetPosition);

    Serial.print("VD ANG Sensor configured - Error : ");
    Serial.println(error);

    error += PCA9685_DeviceInit(PCA9685_PWM_FREQ);

    error += PCA9685_GroupSetup(PCA9685_Group, PCA9685_PIN_Group, PCA9685_PIN_NR_OF);
    error += DD_PCA9685_ChannelSetup(PCA9685_PWM_1, 0);
    error += DD_PCA9685_ChannelSetup(PCA9685_PWM_2, 1);
    error += DD_PCA9685_ChannelSetup(PCA9685_PWM_3, 2);
 
    Serial.print("DD_PCA9685 configured - Error : ");
    Serial.println(error);

    error += DDSERVO_GroupSetup(DDSERVO_Group, PCA9685_Group, DD_SERVO_CHANNEL_NR_OF);
    error += DD_SERVO_ChannelSetup(DD_SERVO_1, PCA9685_PWM_1);
    error += DD_SERVO_ChannelSetup(DD_SERVO_2, PCA9685_PWM_2);
    error += DD_SERVO_ChannelSetup(DD_SERVO_3, PCA9685_PWM_3);

    error += DDSERVO_SetGroupDevSetter(DDSERVO_Group, PCA9685_WriteChannel, DD_SERVO_CHANNEL_NR_OF);
    error += DD_SERVO_SetPushMethod(DD_SERVO_1, PCA9685_WriteChannel);
    error += DD_SERVO_SetPushMethod(DD_SERVO_2, PCA9685_WriteChannel);
    error += DD_SERVO_SetPushMethod(DD_SERVO_3, PCA9685_WriteChannel);

    Serial.print("DD_SERVO configured - Error : ");
    Serial.println(error);

    error += VDSERVO_GroupSetup(VDSERVO_Group, DDSERVO_Group, DD_SERVO_CHANNEL_NR_OF);
	
    error += VD_SERVO_ChannelSetup(VD_SERVO_1, DD_SERVO_1);
    error += VD_SERVO_ChannelSetup(VD_SERVO_2, DD_SERVO_2);
    error += VD_SERVO_ChannelSetup(VD_SERVO_3, DD_SERVO_3);

    error += VDSERVO_SetGroupDevSetter(VDSERVO_Group, DDSERVO_SetAngle, DD_SERVO_CHANNEL_NR_OF);
    error += VD_SERVO_SetPushMethod(VD_SERVO_1, DDSERVO_SetAngle);
    error += VD_SERVO_SetPushMethod(VD_SERVO_2, DDSERVO_SetAngle);
    error += VD_SERVO_SetPushMethod(VD_SERVO_3, DDSERVO_SetAngle);

    VD_ServoRun_TaskDescriptor_1.recurrence = SERVO_TASK_REC;
    VD_ServoRun_TaskDescriptor_1.startupTimeout = SERVO_TASK_OFFSET;
    error += OSTT_TaskInit(VDSERVO_ChannelRunnable, &VD_ServoRun_TaskDescriptor_1);

    VDSERVO_GroupSetRecurency(VDSERVO_Group, SERVO_TASK_REC, DD_SERVO_CHANNEL_NR_OF);
    VDSERVO_SetRecurency(VD_SERVO_1, SERVO_TASK_REC);
    VDSERVO_SetRecurency(VD_SERVO_2, SERVO_TASK_REC);
    VDSERVO_SetRecurency(VD_SERVO_3, SERVO_TASK_REC);

    Serial.print("VD_SERVO configured - Error : ");
    Serial.println(error);
    // Setup Arm

    error += ARM_GroupServoSetup(ARM_9DOF_1, ARM_ServoGroup, VDSERVO_Group, ARM_6DOF_SERVO_CHANNEL_NR_OF);
    error += ARM_6DOF_ChannelSetup(ARM_9DOF_1, ACT_BASE, VD_SERVO_1);
    error += ARM_6DOF_ChannelSetup(ARM_9DOF_1, ACT_L1, VD_SERVO_2);
    error += ARM_6DOF_ChannelSetup(ARM_9DOF_1, ACT_L2, VD_SERVO_3);

    error += ARM_6DOF_SetPushMethod(ARM_9DOF_1, VDSERVO_AngleSet);

    Serial.print("ARM configured - Error : ");
    Serial.println(error);

    return error;
}
