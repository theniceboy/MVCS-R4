#pragma config(Sensor, in1,    potTray,        sensorPotentiometer)
#pragma config(Sensor, in2,    ejctPot,        sensorPotentiometer)
#pragma config(Sensor, in3,    potScissorL,    sensorPotentiometer)
#pragma config(Sensor, in4,    potScissorR,    sensorPotentiometer)
#pragma config(Sensor, in5,    lfClaw,         sensorLineFollower)
#pragma config(Sensor, dgtl1,  ledR,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl2,  ledG,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl3,  legB,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl4,  ,               sensorTouch)
#pragma config(Sensor, dgtl5,  ,               sensorTouch)
#pragma config(Sensor, dgtl6,  armSwitch2,     sensorTouch)
#pragma config(Sensor, dgtl7,  startAuto,      sensorTouch)
#pragma config(Sensor, dgtl8,  rEncoder,       sensorQuadEncoder)
#pragma config(Sensor, dgtl10, lEncoder,       sensorQuadEncoder)
#pragma config(Sensor, dgtl12, dgt112,         sensorTouch)
#pragma config(Motor,  port1,           mL2,           tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           mL1,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           mR1,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           mEject,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           mScissorL,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           mClaw,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           mClawExtend,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           mScissorR,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           mTray,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          mR2,           tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define potScissorErrorAllowance 50
#define TURNING_COEFFICIENT 0.7
#define __POS_UP__ 2000
#define __POS_DOWN__ 570

tMotor BackRightMotor = mR2;
tMotor BackLeftMotor = mL2;
tMotor FrontRightMotor = mR1;
tMotor FrontLeftMotor = mL1;
tSensors quadLeft = lEncoder;
tSensors quadRight = rEncoder;

int max (int a, int b) {
	return (a > b ?  a : b);
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

//----------------Auton Movement Functions-------------
void moveStraightForRotationsCust(float rotations = 1.0)
{
	SensorValue[rEncoder] = 0;
	SensorValue[lEncoder] = 0;

	while(SensorValue[rEncoder] < (abs(rotations) * 360))
	{
		if(SensorValue[rEncoder] == SensorValue[lEncoder]) // If rightEncoder has counted the same amount as leftEncoder:
		{
			// Move Forward
			motor[mR1] = motor[mR2] = 127;		// Right Motor is run at power level 85
			motor[mL1] = motor[mL2]  = 127;		// Left Motor is run at power level 85
		}
		else if(SensorValue[rEncoder] > SensorValue[lEncoder])	// If rightEncoder has counted more encoder counts
		{
			// Turn slightly right
			motor[mR1] = motor[mR2] = 107;		// Right Motor is run at power level 65
			motor[mL1] = motor[mL2]  = 127;		// Left Motor is run at power level 85
		}
		else	// Only runs if leftEncoder has counted more encoder counts
		{
			// Turn slightly left
			motor[mR1] = motor[mR2] = 127;		// Right Motor is run at power level 85
			motor[mL1] = motor[mL2] = 107;		// Left Motor is run at power level 65
		}
		wait1Msec(1);
	}
	motor[mR1] = motor[mR2] = 0;
	motor[mL1] = motor[mL2] = 0;
}
void WideTurn(bool isRight = true, float rotations) {
	SensorValue[rEncoder] = 0;
	SensorValue[lEncoder] = 0;
	if(isRight){
		while(abs(SensorValue[lEncoder]) < abs(rotations)*360) {
			motor[mL1] = motor[mL2] = 127;
			wait1Msec(1);
		}
	} else {
		while(abs(SensorValue[lEncoder]) < abs(rotations)*360) {
			motor[mR1] = motor[mR2] = 127;
			wait1Msec(1);
		}
	}
}

void Turn(bool isRight = true, float rotations){
	SensorValue[rEncoder] = 0;
	SensorValue[lEncoder] = 0;
	if(isRight){
		while(SensorValue[lEncoder] < (abs(rotations) * 360))
		{
			if(-1*SensorValue[rEncoder] == SensorValue[lEncoder]) // If rightEncoder has counted the same amount as leftEncoder:
			{
				// Move Forward
				motor[mR1] = motor[mR2] = -127;		// Right Motor is run at power level 85
				motor[mL1] = motor[mL2]  = 127;		// Left Motor is run at power level 85
			}
			else if(-1*SensorValue[rEncoder] > SensorValue[lEncoder])	// If rightEncoder has counted more encoder counts
			{
				// Turn slightly right
				motor[mR1] = motor[mR2] = -107;		// Right Motor is run at power level 65
				motor[mL1] = motor[mL2]  = 127;		// Left Motor is run at power level 85
			}
			else	// Only runs if leftEncoder has counted more encoder counts
			{
				// Turn slightly left
				motor[mR1] = motor[mR2] = -127;		// Right Motor is run at power level 85
				motor[mL1] = motor[mL2] = 107;		// Left Motor is run at power level 65
			}
			wait1Msec(1);
		}
	}
	else {
		while(SensorValue[rEncoder] < (abs(rotations) * 360))
		{
			if(SensorValue[rEncoder] == -1*SensorValue[lEncoder]) // If rightEncoder has counted the same amount as leftEncoder:
			{
				// Move Forward
				motor[mR1] = motor[mR2] = 127;		// Right Motor is run at power level 85
				motor[mL1] = motor[mL2]  = -127;		// Left Motor is run at power level 85
			}
			else if(SensorValue[rEncoder] > -1*SensorValue[lEncoder])	// If rightEncoder has counted more encoder counts
			{
				// Turn slightly right
				motor[mR1] = motor[mR2] = 107;		// Right Motor is run at power level 65
				motor[mL1] = motor[mL2]  = -127;		// Left Motor is run at power level 85
			}
			else	// Only runs if leftEncoder has counted more encoder counts
			{
				// Turn slightly left
				motor[mR1] = motor[mR2] = 127;		// Right Motor is run at power level 85
				motor[mL1] = motor[mL2] = -107;		// Left Motor is run at power level 65
			}
			wait1Msec(1);
		}
	}
}


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


task autonomous(){
}
/*-----------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/



/*
Eject Pot Rest: 2200
Eject Pot Ejected: 1400
Eject Motor Eject: (-)
*/
int ejectRest = 2200;
int ejectOut = 1000;
int activationDelay = 1000;

//int stackedCount = 0;
//int potPositions[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//int mScissorValues[2] = {127, -127};



int scissorLeftHeight = 0, scissorRightHeight = 0;

task trayCtrl {
	while (true) {
		if (vexRT[Btn7L]){
			motor[mEject] = -127;
			while (SensorValue(ejctPot) > ejectOut) {
				wait1Msec (10);
			}
			motor[mEject] = 127;
			while (SensorValue(ejctPot) < ejectRest) {
				wait1Msec (10);
			}
			motor[mEject] = 0;
		}

		if (vexRT[Btn8D]) {
			motor[mTray] = 127;
			} else if (vexRT[Btn8U]) {
			motor[mTray] = -127;
			} else {
			motor[mTray] = 0;
		}
	}

	wait1Msec (10);
	EndTimeSlice ();
}


task scissorLiftControl {
	while (true) {
		if (vexRT[Btn5U]) {
			motor[mScissorL]=motor[mScissorR]=-127;}
		/*if (scissorLeftHeight - potScissorErrorAllowance > scissorRightHeight) {
		motor[mScissorL] = 0;
		motor[mScissorR] = 127;
		} else if (scissorLeftHeight < scissorRightHeight - potScissorErrorAllowance) {
		motor[mScissorL] = 127;
		motor[mScissorR] = 0;
		} else {
		motor[mScissorL] = motor[mScissorR] = 127;
		}
		}*/
		else if (vexRT[Btn5D]) {
			motor[mScissorL]=motor[mScissorR]=127;}
		/*if (scissorLeftHeight + potScissorErrorAllowance < scissorRightHeight) {
		motor[mScissorL] = 0;
		motor[mScissorR] = -127;
		} else if (scissorLeftHeight > scissorRightHeight + potScissorErrorAllowance) {
		motor[mScissorL] = -127;
		motor[mScissorR] = 0;
		} else {
		motor[mScissorL] = motor[mScissorR] = -127;
		}
		} else {
		motor[mScissorL] = motor[mScissorR] = 0;
		}
		EndTimeSlice();
		}*/
		else{
			motor[mScissorL]=motor[mScissorR]=0;}
}}

bool clawOpen = true;
bool autoStacking = false;
task autoStack {
	if (autoStacking) {
		return;
	}

	autoStacking = true;

	motor[mClaw] = 127;
	wait1Msec (400);
	motor[mClaw] = 60;
	motor[mClawExtend] = 127;
	while (SensorValue[lfClaw] > 3000) {
		wait1Msec (10);
		if (vexRT[Btn8L]) {
			return;
		}
		//EndTimeSlice();
	}

	wait1Msec (10);
	//motor[mClaw] = -127;
	motor[mClawExtend] = -25;
	wait1Msec (1000);
	motor[mClaw] = -127;
	wait1Msec (300);
	motor[mClaw] = 0;
	clawOpen = true;
	wait1Msec (5000);
	motor[mClawExtend] = -127;
	wait1Msec (200);
	motor[mClawExtend] = 0;
	autoStacking = false;

	//while (abs(SensorValue[potScissor] - potPositions[stackedCount]) > potScissorErrorAllowance) {
	//motor[mScissorL] = mScissorValues[SensorValue[potScissor] < potPositions[stackedCount]];
	//}
}
task manualStack{
	while (true){
		if (vexRT[Btn6U]){
			motor[mClawExtend]=127;
		}

		else if (vexRT[Btn6D]){
			motor[mClawExtend]=-127;
		}
		else if (SensorValue[armSwitch2]){
			motor[mClawExtend]=-100;
		}
		else {
			motor[mClawExtend] = 0;
		}
	}
}

task toggleClaw {
	while (true) {
		if (vexRT[Btn8L]) {
			while (vexRT[Btn8L]) { }
			if (clawOpen) {
				motor[mClaw] = 127;
				wait1Msec (250);
				motor[mClaw] = 30;
				} else {
				motor[mClaw] = -127;
				wait1Msec (1000);
			}
			clawOpen = !clawOpen;
		}
		motor[mClaw] = (clawOpen ? 0 : 30);
		EndTimeSlice ();
	}
}


task usercontrol()
{
	//startTask(manualCtrl);

	startTask(trayCtrl);
	startTask (scissorLiftControl);


	//startTask (autoStack);
	startTask (toggleClaw);
	startTask (manualStack);
	float theta = 90, power = 0, x = 0, y = 0, z = 0, direction = 1;
	int motorL1, motorL2, motorR1, motorR2;

	int lmtrs, rmtrs;

	while (true) {

		motor[mL1] = motor[mL2] = vexRT[Ch3];
		motor[mR1] = motor[mR2] = vexRT[Ch2];
		endTimeSlice();
	}
}
