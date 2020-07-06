/*
 * arm_6dof.h
 *
 *  Created on: Apr 23, 2020
 *      Author: Andrei Bragarenco
 */

#ifndef _ARM_6DOF_H_
#define _ARM_6DOF_H_

#include "arm_6dof_cfg.h"




enum eCoordId{COORD_X, COORD_Y, COORD_Z};

typedef struct ARM_ChannelType_t{

// Actuator Group
	Std_ChannelIdType servos[ARM_6DOF_SERVO_CHANNEL_NR_OF];
	Std_PhySetterType DeviceSetAngle = NULL;

	float segLen[ARM_6DOF_SEGMENT_CHANNEL_NR_OF];

	float angleOfset[3]={0,0,0};
	float icAngle[3];

	float dcAngle[3];

	float icCoord[3];
	float dcCoord[3];

}ARM_ChannelType;

ARM_ChannelType* ARM_GetChannelRef(Std_ChannelIdType channelId);
Std_ReturnType ARM_6DOF_ChannelSetup(Std_ChannelIdType armChannelId, Std_ChannelIdType actChannelId, Std_ChannelIdType servoChannelId);
Std_ReturnType ARM_6DOF_SetPushMethod( Std_ChannelIdType channelId,  Std_PhySetterType SetAngle);
Std_ReturnType ARM_GroupServoSetup(Std_ChannelIdType armChannelId, Std_ChannelIdType *srcIds, Std_ChannelIdType *targhetIds, uint8_t nr_of_channels);

Std_ReturnType ARM_SetAngles(Std_ChannelIdType channelId, float angleBase, float seg1Angle, float seg2Angle);
Std_ReturnType ARM_SetSegLengths(Std_ChannelIdType channelId,float base, float seg1, float seg2);
Std_ReturnType ARM_UpdateFbAngles(Std_ChannelIdType channelId);

Std_ReturnType ARM_MoveAxis(Std_ChannelIdType channelId, eCoordId axis, float delta);
Std_ReturnType ARM_GoToAxis(Std_ChannelIdType channelId, eCoordId axis, float target);
Std_ReturnType ARM_MoveAll(Std_ChannelIdType channelId, float delta_x, float delta_y, float delta_z );
Std_ReturnType ARM_GoToAll(Std_ChannelIdType channelId, float target_x, float target_y, float target_z );


void ARM_DirectCinematics(float dcAngle[3], float segLen[3], float dcCoord[3]);
void ARM_InverseKinematics(float icCoord[3], float segLen[3], float icAngle[3]);
void ARM_SetCoordinates(Std_ChannelIdType channelId, float coordX, float coordY, float coordZ);


#endif /* ARM_6DOF_H_ */
