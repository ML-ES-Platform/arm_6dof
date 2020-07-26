/**
* @file arm_6dof_demo_cfg_gen.cpp
* @author your name (you@domain.com)
* @brief 
* @version 0.1
* @date 2020-06-12
* 
* @copyright Copyright (c) 2020
* 
*/

#include "arm_6dof_demo_cfg_gen.h"

Std_ReturnType arm_6dof_demo_config(void)
{
    Serial.begin(115200);
    Serial.println("Application Demo for 3-DOF Robotic arm  control");
    Std_ReturnType error = E_OK;

    error += MCAL_ADC_ChannelSetup(ADC_1, A3);
    error += MCAL_ADC_ChannelSetup(ADC_2, A4);
    error += MCAL_ADC_ChannelSetup(ADC_3, A5);
    Serial.print("MCAL_ADC configured - Error : ");
    Serial.println(error);

    Serial.print("NULL configured - Error : ");
    Serial.println(error);


    error += DD_POTENTIOMETER_ChannelSetup(POT_1, ADC_1);
    error += DD_POTENTIOMETER_ChannelSetup(POT_2, ADC_2);
    error += DD_POTENTIOMETER_ChannelSetup(POT_3, ADC_3);

    error += DD_POTENTIOMETER_SetPullMethod(POT_1, ADC_ReadChannel);
    error += DD_POTENTIOMETER_SetPullMethod(POT_2, ADC_ReadChannel);
    error += DD_POTENTIOMETER_SetPullMethod(POT_3, ADC_ReadChannel);
    Serial.print("DD_POT configured - Error : ");
    Serial.println(error);


    error += VD_ANGLE_SENS_ChannelSetup(ANGSNS_1, POT_1);
    error += VD_ANGLE_SENS_ChannelSetup(ANGSNS_2, POT_2);
    error += VD_ANGLE_SENS_ChannelSetup(ANGSNS_3, POT_3);

    error += VD_ANGLE_SENS_SetPullMethod(ANGSNS_1, POT_GetPosition);
    error += VD_ANGLE_SENS_SetPullMethod(ANGSNS_2, POT_GetPosition);
    error += VD_ANGLE_SENS_SetPullMethod(ANGSNS_3, POT_GetPosition);
    Serial.print("VD_ANGLE_SENS configured - Error : ");
    Serial.println(error);


    error += DD_PCA9685_ChannelSetup(PCA9685_PWM_1, PCA9685_PIN_1);
    error += DD_PCA9685_ChannelSetup(PCA9685_PWM_2, PCA9685_PIN_2);
    error += DD_PCA9685_ChannelSetup(PCA9685_PWM_3, PCA9685_PIN_3);
    Serial.print("DD_PCA9685 configured - Error : ");
    Serial.println(error);


    error += DD_SERVO_ChannelSetup(DD_SERVO_1, PCA9685_PWM_1);
    error += DD_SERVO_ChannelSetup(DD_SERVO_2, PCA9685_PWM_2);
    error += DD_SERVO_ChannelSetup(DD_SERVO_3, PCA9685_PWM_3);

    error += DD_SERVO_SetPushMethod(DD_SERVO_1, PCA9685_WriteChannel);
    error += DD_SERVO_SetPushMethod(DD_SERVO_2, PCA9685_WriteChannel);
    error += DD_SERVO_SetPushMethod(DD_SERVO_3, PCA9685_WriteChannel);
    Serial.print("DD_SERVO configured - Error : ");
    Serial.println(error);


    error += VD_SERVO_ChannelSetup(VD_SERVO_1, DD_SERVO_1);
    error += VD_SERVO_ChannelSetup(VD_SERVO_2, DD_SERVO_2);
    error += VD_SERVO_ChannelSetup(VD_SERVO_3, DD_SERVO_3);

    error += VD_SERVO_SetPushMethod(VD_SERVO_1, DDSERVO_SetAngle);
    error += VD_SERVO_SetPushMethod(VD_SERVO_2, DDSERVO_SetAngle);
    error += VD_SERVO_SetPushMethod(VD_SERVO_3, DDSERVO_SetAngle);
    Serial.print("VD_SERVO configured - Error : ");
    Serial.println(error);



    Serial.print("ARM_6DOF configured - Error : ");
    Serial.println(error);

    error += ARM_6DOF_ChannelSetup(ARM_9DOF_1, ACT_BASE, VD_SERVO_1);
    error += ARM_6DOF_ChannelSetup(ARM_9DOF_1, ACT_L1, VD_SERVO_2);
    error += ARM_6DOF_ChannelSetup(ARM_9DOF_1, ACT_L2, VD_SERVO_3);

    error += ARM_6DOF_SetPushMethod(ARM_9DOF_1, ACT_BASE, VDSERVO_AngleSet);
    error += ARM_6DOF_SetPushMethod(ARM_9DOF_1, ACT_L1, VDSERVO_AngleSet);
    error += ARM_6DOF_SetPushMethod(ARM_9DOF_1, ACT_L2, VDSERVO_AngleSet);
    Serial.print("ARM_6DOF_SERVO configured - Error : ");
    Serial.println(error);

    Serial.print("ARM_6DOF_SEGMENT configured - Error : ");
    Serial.println(error);

    return error;
}
