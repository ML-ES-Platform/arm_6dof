/*
 * arm_9dof_cfg.h
 *
 *  Created on: Apr 23, 2020
 *      Author: Andrei Bragarenco
 */

#ifndef _ARM_6DOF_CFG_H_
#define _ARM_6DOF_CFG_H_


#include "platform_config.h"

#ifndef ARM_6DOF_CONFIG
#define ARM_6DOF_CONFIG
//for demo application purpose
//shall be defined in the platform
enum ARM_6DOF_IdType {ARM_9DOF_1, ARM_6DOF_CHANNEL_NR_OF};
enum ARM_6DOF_SERVO_IdType{ACT_BASE = 0, ACT_L1, ACT_L2, ACT_ROLL, ACT_PITCH, ACT_CLAW, ARM_6DOF_SERVO_CHANNEL_NR_OF };
enum ARM_6DOF_SEGMENT_IdType{SEG_BASE = 0, SEG_L1, SEG_L2, ARM_6DOF_SEGMENT_CHANNEL_NR_OF};
#endif


#endif /* _ARM_6DOF_CFG_H_ */
