/*
 * arm_9dof.cpp
 *
 *  Created on: Apr 23, 2020
 *      Author: Andrei Bragarenco
 */

#include "arm_6dof.h"
#include "math.h"

ARM_ChannelType ARM_Channels[ARM_6DOF_CHANNEL_NR_OF];


Std_ReturnType ARM_6DOF_ChannelSetup(Std_ChannelIdType armChannelId, Std_ChannelIdType actChannelId, Std_ChannelIdType servoChannelId){
	Std_ReturnType error;
	if (armChannelId < ARM_6DOF_CHANNEL_NR_OF) {
		ARM_ChannelType *channelRef = ARM_GetChannelRef(armChannelId);
		channelRef->servos[actChannelId] = servoChannelId;
		error = E_OK;
	} else {
		error = E_NOT_OK;
	}
	return error;
}



Std_ReturnType ARM_GroupServoSetup(Std_ChannelIdType armChannelId, Std_ChannelIdType *srcIds, Std_ChannelIdType *targhetIds, uint8_t nr_of_channels)
{
	Std_ReturnType error = E_OK;

	for (size_t i = 0; i < nr_of_channels; i++)
	{
		Std_ChannelIdType srcId = srcIds[i];
		Std_ChannelIdType targhetId = targhetIds[i];
		error += ARM_6DOF_ChannelSetup(armChannelId, srcId, targhetId);
	}
	return error;
}

ARM_ChannelType* ARM_GetChannelRef(Std_ChannelIdType channelId) {
	ARM_ChannelType *channelRef;
	if (channelId < ARM_6DOF_CHANNEL_NR_OF) {
		channelRef = &ARM_Channels[channelId];
	} else {
		channelRef = NULL;
	}
	return channelRef;

}

Std_ReturnType ARM_6DOF_SetPushMethod( Std_ChannelIdType channelId,  Std_PhySetterType SetAngle){
	Std_ReturnType error;
	if (channelId < ARM_6DOF_CHANNEL_NR_OF) {
		ARM_ChannelType *channelRef = ARM_GetChannelRef(channelId);
		channelRef->DeviceSetAngle = SetAngle;
		error = E_OK;
	} else {
		error = E_NOT_OK;
	}
	return error;
}

Std_ReturnType ARM_SetAngles(Std_ChannelIdType channelId, float baseAngle, float seg1Angle, float seg2Angle) {
	Std_ReturnType error;

	ARM_ChannelType *channelRef = ARM_GetChannelRef(channelId);
	if (channelRef != NULL) {
		error = E_OK;
		error +=channelRef->DeviceSetAngle(channelRef->servos[ACT_BASE],baseAngle + channelRef->angleOfset[ACT_BASE]);
		error +=channelRef->DeviceSetAngle(channelRef->servos[ACT_L1],seg1Angle + channelRef->angleOfset[ACT_BASE]);
		error +=channelRef->DeviceSetAngle(channelRef->servos[ACT_L2],seg2Angle + channelRef->angleOfset[ACT_BASE]);
		channelRef->dcAngle[ACT_BASE] = baseAngle;
		channelRef->dcAngle[ACT_L1] = seg1Angle;
		channelRef->dcAngle[ACT_L2] = seg2Angle;
		ARM_DirectCinematics(channelRef->dcAngle, channelRef->segLen, channelRef->dcCoord);


	} else {
		error = E_NOT_OK;
	}
	return error;
}

Std_ReturnType ARM_SetSegLengths(Std_ChannelIdType channelId,float base, float seg1, float seg2){
	Std_ReturnType error;

	ARM_ChannelType *channelRef = ARM_GetChannelRef(channelId);
	if (channelRef != NULL) {
		error = E_OK;
		channelRef->segLen[ACT_BASE] = base;
		channelRef->segLen[ACT_L1] = seg1;
		channelRef->segLen[ACT_L2] = seg2;
	} else {
		error = E_NOT_OK;
	}
	return error;
}


Std_ReturnType ARM_UpdateFbAngles(Std_ChannelIdType channelId) {

	for (int i = 0; i < ARM_6DOF_SERVO_CHANNEL_NR_OF; ++i) {
		//float angle = ServoFBList[i].angleVal;
		//ServoList[i].SetAngle(angle);

	}
	return E_OK;
}

Std_ReturnType ARM_GoToAll(Std_ChannelIdType channelId, float target_x, float target_y, float target_z ){

	Std_ReturnType error;
	ARM_ChannelType *channelRef = ARM_GetChannelRef(channelId);
	if (channelRef != NULL) {
		error = E_OK;
		channelRef->icCoord[COORD_X] = target_x;
		channelRef->icCoord[COORD_Y] = target_y;
		channelRef->icCoord[COORD_Z] = target_z;

		ARM_InverseKinematics(channelRef->icCoord, channelRef->segLen, channelRef->icAngle);

		float baseAngle = channelRef->icAngle[ACT_BASE];
		float seg1Angle = channelRef->icAngle[ACT_L1]  ;
		float seg2Angle = channelRef->icAngle[ACT_L2]  ;

		error += ARM_SetAngles(channelId, baseAngle, seg1Angle, seg2Angle);

	} else {
		error = E_NOT_OK;
	}
	return error;

}

Std_ReturnType ARM_GoToAxis(Std_ChannelIdType channelId, eCoordId axis, float target){
	Std_ReturnType error;
	ARM_ChannelType *channelRef = ARM_GetChannelRef(channelId);
	if (channelRef != NULL) {
		error = E_OK;

		channelRef->icCoord[axis] = target;

		ARM_InverseKinematics(channelRef->icCoord, channelRef->segLen, channelRef->icAngle);

		float baseAngle = channelRef->icAngle[ACT_BASE];
		float seg1Angle = channelRef->icAngle[ACT_L1]  ;
		float seg2Angle = channelRef->icAngle[ACT_L2]  ;

		error += ARM_SetAngles(channelId, baseAngle, seg1Angle, seg2Angle);

	} else {
		error = E_NOT_OK;
	}
	return error;

}


Std_ReturnType ARM_MoveAll(Std_ChannelIdType channelId, float delta_x, float delta_y, float delta_z ){

	Std_ReturnType error;
	ARM_ChannelType *channelRef = ARM_GetChannelRef(channelId);
	if (channelRef != NULL) {
		error = E_OK;
		channelRef->icCoord[COORD_X] += delta_x;
		channelRef->icCoord[COORD_Y] += delta_y;
		channelRef->icCoord[COORD_Z] += delta_z;

		ARM_InverseKinematics(channelRef->icCoord, channelRef->segLen, channelRef->icAngle);

		float baseAngle = channelRef->icAngle[ACT_BASE];
		float seg1Angle = channelRef->icAngle[ACT_L1]  ;
		float seg2Angle = channelRef->icAngle[ACT_L2]  ;

		error += ARM_SetAngles(channelId, baseAngle, seg1Angle, seg2Angle);

	} else {
		error = E_NOT_OK;
	}
	return error;

}


Std_ReturnType ARM_MoveAxis(Std_ChannelIdType channelId, eCoordId axis, float delta){

	Std_ReturnType error;
	ARM_ChannelType *channelRef = ARM_GetChannelRef(channelId);
	if (channelRef != NULL) {
		error = E_OK;

		channelRef->icCoord[axis] += delta;

		ARM_InverseKinematics(channelRef->icCoord, channelRef->segLen, channelRef->icAngle);

		float baseAngle = channelRef->icAngle[ACT_BASE];
		float seg1Angle = channelRef->icAngle[ACT_L1]  ;
		float seg2Angle = channelRef->icAngle[ACT_L2]  ;

		error += ARM_SetAngles(channelId, baseAngle, seg1Angle, seg2Angle);

	} else {
		error = E_NOT_OK;
	}
	return error;



}




void ARM_DirectCinematics(float dcAngle[3], float segLen[3], float dcCoord[3])
{
	float segX[3];
	float segY[3];
	float segZ[3];

    //float segXYZ[3];
    float segXY[3];

    segZ[1] = segLen[1] * sin((float)dcAngle[1] * PI / (180 ));
    segXY[1] = segLen[1] * cos((float)dcAngle[1] * PI / (180 ));

    //segXYZ[1] = sqrt(pow(segZ[1], 2) + pow(segXY[1], 2));
    segX[1] = segXY[1] * cos((float)dcAngle[0] * PI / (180 ));
    segY[1] = segXY[1] * sin((float)dcAngle[0] * PI / (180 ));

    segZ[2]  = segZ[1]  + segLen[2] * sin((float)(dcAngle[1] + dcAngle[2] - (90 )) * PI / (180 ));
    segXY[2] = segXY[1] + segLen[2] * cos((float)(dcAngle[1] + dcAngle[2] - (90 )) * PI / (180 ));

   // segXYZ[2] = sqrt(pow(segZ[2], 2) + pow(segXY[2], 2));
    segX[2] = segXY[2] * cos((float)dcAngle[0] * PI / (180 ));
    segY[2] = segXY[2] * sin((float)dcAngle[0] * PI / (180 ));

    dcCoord[COORD_X] = segX[2];
    dcCoord[COORD_Y] = segY[2];
    dcCoord[COORD_Z] = segZ[2];


}

void ARM_InverseKinematics(float icCoord[3], float segLen[3],  float icAngle[3])
{
    float r_xy = sqrt(pow(icCoord[COORD_X], 2) + pow(icCoord[COORD_Y], 2));
    float r_xyz = sqrt(pow(icCoord[COORD_Z], 2) + pow(r_xy, 2));
    float beta1 = asin(icCoord[COORD_Z] / r_xyz);
    //float alpha = acos((pow(segLen[2], 2) + pow(icXYZ, 2) - pow(segLen[1], 2)));
    float beta2 = acos((pow(segLen[1], 2) + pow(r_xyz, 2) - pow(segLen[2], 2)) / (2 * segLen[1] * abs(r_xyz)));
    float gama = acos((pow(segLen[2], 2) + pow(segLen[1], 2) - pow(r_xyz, 2)) / (2 * segLen[2] * segLen[1]));
    float delta = asin(icCoord[COORD_Y] / r_xy);
    delta = ((icCoord[COORD_X]>0)?delta: (PI -delta));
    icAngle[0] = delta * ((float)180 / PI);
    icAngle[1] = (beta1 + beta2) * ((float)180 / PI);
    icAngle[2] = (gama * ((float)180 / PI) - 90) ;
}


