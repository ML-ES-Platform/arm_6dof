/*
 * arm_6dof_demo.cpp
 *
 *  Created on: Jun 4, 2020
 *      Author: Andrei Bragarenco
 */

#include "arm_6dof_demo.h"
#include "arm_6dof_demo_config.h"
#include "../arm_6dof.h"

void ANGSENS_Report()
{
	Serial.print(" VD AngSens :");
	for (int i = 0; i < 3; i++)
	{
		Std_ChannelIdType servoId = i;
		Std_PhyDataType sensorAngle = ANGSNS_GetAngle(servoId);
		Serial.print(" Id_");
		Serial.print(i);
		Serial.print("=");
		Serial.print(sensorAngle);
	}
	Serial.println();
}

void VDSERVO_Report()
{
	ARM_ChannelType *armRef = ARM_GetChannelRef(ARM_9DOF_1);

	Serial.print(" VD Servo :");
	for (int i = 0; i < 3; i++)
	{
		Std_ChannelIdType servoId = armRef->servos[i];
		Std_PhyDataType servoAngle = VDSERVO_AngleGet(servoId);
		Serial.print(" Id_");
		Serial.print(i);
		Serial.print("=");
		Serial.print(servoAngle);
	}
	Serial.println();

	Serial.print(" V* Servo :");
	for (int i = 0; i < 3; i++)
	{
		Std_ChannelIdType servoId = armRef->servos[i];
		Std_PhyDataType servoAngle = VDSERVO_AngleOutGet(servoId);
		Serial.print(" Id_");
		Serial.print(i);
		Serial.print("=");
		Serial.print(servoAngle);
	}
	Serial.println();
}

void DDSERVO_Report()
{
	ARM_ChannelType *armRef = ARM_GetChannelRef(ARM_9DOF_1);

	Serial.print(" DD Servo :");
	for (int i = 0; i < 3; i++)
	{
		Std_ChannelIdType vdServoId = armRef->servos[i];
		VDSERVO_ChannelType *servoRef = VDSERVO_GetChannelRef(vdServoId);
		Std_ChannelIdType ddServoId = servoRef->deviceChannelId;
		Std_PhyDataType servoAngle = DDSERVO_AngleGet(ddServoId);
		Serial.print(" Id_");
		Serial.print(i);
		Serial.print("=");
		Serial.print(servoAngle);
	}
	Serial.println();
	Serial.print(" DD Pulse :");
	for (int i = 0; i < 3; i++)
	{

		Std_ChannelIdType vdServoId = armRef->servos[i];

		VDSERVO_ChannelType *servoRef = VDSERVO_GetChannelRef(vdServoId);

		Std_ChannelIdType ddServoId = servoRef->deviceChannelId;
		Std_RawDataType servoPulse = DDSERVO_PulseGet(ddServoId);
		Serial.print(" Id_");
		Serial.print(i);
		Serial.print("=");
		Serial.print(servoPulse);
	}
	Serial.println();
}

void ARM_Report(void)
{
	ARM_ChannelType *channelRef = ARM_GetChannelRef(ARM_9DOF_1);

	Serial.print("   ARM IC :");
	Serial.print("   BA=");
	Serial.print(channelRef->icAngle[ACT_BASE]);
	Serial.print("  L1A=");
	Serial.print(channelRef->icAngle[ACT_L1]);
	Serial.print("  L2A=");
	Serial.print(channelRef->icAngle[ACT_L2]);
	Serial.print("  icX =");
	Serial.print(channelRef->icCoord[COORD_X]);
	Serial.print("  icY=");
	Serial.print(channelRef->icCoord[COORD_Y]);
	Serial.print("  icZ=");
	Serial.print(channelRef->icCoord[COORD_Z]);
	Serial.println();

	Serial.print("   ARM DC :");
	Serial.print("   BA=");
	Serial.print(channelRef->dcAngle[ACT_BASE]);
	Serial.print("  L1A=");
	Serial.print(channelRef->dcAngle[ACT_L1]);
	Serial.print("  L2A=");
	Serial.print(channelRef->dcAngle[ACT_L2]);
	Serial.print("  dcX =");
	Serial.print(channelRef->dcCoord[COORD_X]);
	Serial.print("  dcY=");
	Serial.print(channelRef->dcCoord[COORD_Y]);
	Serial.print("  dcZ=");
	Serial.print(channelRef->dcCoord[COORD_Z]);
	Serial.println();
}

void arm_6dof_demo_setup(void)
{

	arm_6dof_demo_config();

	ARM_UpdateFbAngles(ARM_9DOF_1);
	ARM_SetSegLengths(ARM_9DOF_1,
					  90,  // BASE
					  120, // BRAT
					  85   // ANTEBRAT

					  //   50,  // BASE
					  //   110, // BRAT
					  //   123  // ANTEBRAT
	);

	ARM_MoveAll(ARM_9DOF_1, 0, 110, 123);

	ARM_Report();
	//	VDSERVO_Report();
	//	DDSERVO_Report();
	//	ANGSENS_Report();

	// Start Time triggered OS
	OSTT_Init();
}

#define CMD_DELTA_MOVE 30
extern portMUX_TYPE timerMux;

#define TaskRec 100
volatile int taskCnt = TaskRec;
volatile int interruptCounter;
int CheckPoint_HERE = 0;
int totalInterruptCounter;

void arm_6dof_demo_loop(void)
{
	// put your main code here, to run repeatedly:

	if (Serial.available())
	{
		char cmd = Serial.read();

		// Command Interpreter
		switch (cmd)
		{
		case 'q':
			ARM_MoveAxis(ARM_9DOF_1, COORD_X, CMD_DELTA_MOVE); // increment X
			Serial.println("X - rise");
			break;
		case 'w':
			ARM_MoveAxis(VD_SERVO_1, COORD_X, -CMD_DELTA_MOVE); //decrement X
			Serial.println("X - fall");
			break;
		case 'a':
			ARM_MoveAxis(ARM_9DOF_1, COORD_Y, CMD_DELTA_MOVE); // increment Y
			Serial.println("Y - rise");
			break;
		case 's':
			ARM_MoveAxis(ARM_9DOF_1, COORD_Y, -CMD_DELTA_MOVE); // increment Y
			Serial.println("Y - fall");
			break;
		case 'z':
			ARM_MoveAxis(ARM_9DOF_1, COORD_Z, CMD_DELTA_MOVE); // increment Z
			Serial.println("Z - rise");
			break;
		case 'x':
			ARM_MoveAxis(ARM_9DOF_1, COORD_Z, -CMD_DELTA_MOVE); // increment Z
			Serial.println("Z - fall");
			break;
		}

		ARM_Report();
		VDSERVO_Report();
		DDSERVO_Report();
		ANGSENS_Report();
	}

	if (OSTT_GetSchedulerFlag() == 1)
	{
		OSTT_Scheduler();
		OSTT_ResetSchedulerFlag();
	}
	static int channelId = 0;

	if (++channelId >= VD_SERVO_CHANNEL_NR_OF)
	{
		channelId = 0;
	}

	VDSERVO_ChannelType *channelRef = VDSERVO_GetChannelRef(channelId);
	if (channelRef)
	{
		channelRef->DeviceSetAngle(channelId, channelRef->curentAngle);
	}

	if (interruptCounter > 0)
	{

		portENTER_CRITICAL(&timerMux);
		interruptCounter--;
		portEXIT_CRITICAL(&timerMux);

		totalInterruptCounter++;
		if (--taskCnt <= 0)
		{
			//Serial.print("An interrupt as occurred. Total number: ");
			//Serial.println(CheckPoint_HERE);

			taskCnt = TaskRec;
		}
	}
}
