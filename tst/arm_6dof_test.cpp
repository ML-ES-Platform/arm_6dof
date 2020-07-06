/*
 * arm_9dof_test.cpp
 *
 *  Created on: Apr 23, 2020
 *      Author: Andrei Bragarenco
 */

#include "../arm_6dof.h"

/*
 * arm_6dof_test.cpp
 *
 *  Created on: Jun 4, 2020
 *      Author: Andrei Bragarenco
 */

#include "arm_6dof_test.h"

#include "../arm_6dof.h"

// Inverse set to direct check

void Test2_Inverse_set_direct_check()
{

	float segLen[3] = {
		50,	 // BASE
		110, // BRAT
		123	 // ANTEBRAT
	};

	float dcAngle[3] = {0, 0, 0};
	float icAngle[3] = {0, 0, 0};

	float dcCoord[3];

	float icCoord[3] = {-100, -100, -100};

	for (int i = 0; i < 10; i++)
	{
		icCoord[COORD_X] += 10;
		icCoord[COORD_Y] = -100;

		for (int j = 0; j < 10; j++)
		{
			icCoord[COORD_Y] += 10;
			icCoord[COORD_Z] = -100;
			for (int k = 0; k < 10; k++)
			{
				icCoord[COORD_Z] += 10;
				//Inverse cinematics

				ARM_InverseKinematics(icCoord, segLen, icAngle);

				dcAngle[0] = icAngle[0];
				dcAngle[1] = icAngle[1];
				dcAngle[2] = icAngle[2];

				// Direct cinematics

				ARM_DirectCinematics(dcAngle, segLen, dcCoord);

				Serial.print(" IC =");
				Serial.print(" icX =");
				Serial.print(icCoord[COORD_X]);
				Serial.print(" icY=");
				Serial.print(icCoord[COORD_Y]);
				Serial.print(" icZ=");
				Serial.print(icCoord[COORD_Z]);
				Serial.print(" L1A=");
				Serial.print(icAngle[1]);
				Serial.print(" L2A=");
				Serial.print(icAngle[2]);
				Serial.print(" BA=");
				Serial.print(icAngle[0]);
				Serial.println();

				Serial.print(" DC =");
				Serial.print(" dcX =");
				Serial.print(dcCoord[COORD_X]);
				Serial.print(" dcY=");
				Serial.print(dcCoord[COORD_Y]);
				Serial.print(" dcZ=");
				Serial.print(dcCoord[COORD_Z]);
				Serial.print(" L1A=");
				Serial.print(dcAngle[1]);
				Serial.print(" L2A=");
				Serial.print(dcAngle[2]);
				Serial.print(" BA=");
				Serial.print(dcAngle[0]);
				Serial.println();

				Serial.println();

				/* code */
			}

			/* code */
		}
		/* code */
	}
}

// Direct set Inverse check

void Test1_Direct_set_Inverse_check()
{
	float segLen[3] = {
		50,	 // BASE
		110, // BRAT
		123	 // ANTEBRAT
	};

	float dcAngle[3] = {-90, -90, -90};
	float icAngle[3] = {0, 0, 0};

	float dcCoord[3];

	float icCoord[3] = {10, 10, 10};

	for (int i = 0; i < 18; i++)
	{
		dcAngle[1] += 10;
		dcAngle[2] = -90;

		for (int j = 0; j < 18; j++)
		{
			dcAngle[2] += 10;
			dcAngle[0] = -90;

			for (int k = 0; k < 18; k++)
			{

				dcAngle[0] += 10;
				// Direct cinematics

				ARM_DirectCinematics(dcAngle, segLen, dcCoord);

				icCoord[COORD_X] = dcCoord[COORD_X];
				icCoord[COORD_Y] = dcCoord[COORD_Y];
				icCoord[COORD_Z] = dcCoord[COORD_Z];

				//Inverse cinematics

				ARM_InverseKinematics(icCoord, segLen, icAngle);

				//                cout << " DC =" << " dcX =" << segX[2] << " dcY=" << segY[2] << " dcZ=" << segZ[2]
				//                     // << " dcXY=" << segXY[2] << " dcXYZ=" << segXYZ[2]
				//                     << " L1A=" << dcAngle[1] << " L2A=" << dcAngle[2] << " BA=" << dcAngle[0]
				//                     << endl;
				//
				//                cout << " IC =" << " icX =" << icX << " icY=" << icY << " icZ=" << icZ
				//                     // << " icXY=" << icXY << " icXYZ=" << icXYZ
				//                     << " L1A=" << icAngle[1] << " L2A=" << icAngle[2] << " BA=" << icAngle[0]
				//                     << endl;
				//                cout << endl;

				Serial.print(" DC =");
				Serial.print(" dcX =");
				Serial.print(dcCoord[COORD_X]);
				Serial.print(" dcY=");
				Serial.print(dcCoord[COORD_Y]);
				Serial.print(" dcZ=");
				Serial.print(dcCoord[COORD_Z]);
				Serial.print(" L1A=");
				Serial.print(dcAngle[1]);
				Serial.print(" L2A=");
				Serial.print(dcAngle[2]);
				Serial.print(" BA=");
				Serial.print(dcAngle[0]);
				Serial.println();

				Serial.print(" IC =");
				Serial.print(" icX =");
				Serial.print(icCoord[COORD_X]);
				Serial.print(" icY=");
				Serial.print(icCoord[COORD_Y]);
				Serial.print(" icZ=");
				Serial.print(icCoord[COORD_Z]);
				Serial.print(" L1A=");
				Serial.print(icAngle[1]);
				Serial.print(" L2A=");
				Serial.print(icAngle[2]);
				Serial.print(" BA=");
				Serial.print(icAngle[0]);
				Serial.println();

				Serial.println();

				/* code */
			}
			/* code */
		}
		/* code */
	}
}

void arm_6dof_test_setup(void)
{
	Serial.begin(9600);
	Serial.println("ARM 6 DOF test !");
}

void arm_6dof_test_loop(void)
{

	Serial.println(" Hello World");

	Test2_Inverse_set_direct_check();

	delay(1000);
}
