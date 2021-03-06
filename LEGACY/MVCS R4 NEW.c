#pragma config(Sensor, in1,    ejctPot,        sensorPotentiometer)
#pragma config(Sensor, in2,    potScissor,     sensorPotentiometer)
#pragma config(Sensor, dgtl1,  ledR,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl2,  ledG,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl3,  legB,           sensorLEDtoVCC)
#pragma config(Motor,  port1,           mEject,        tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           mL1,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           mL2,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           mR1,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           mScissorR,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           sClaw,         tmotorServoStandard, openLoop)
#pragma config(Motor,  port7,           mClawExtend,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           mScissorL,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           mTray,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          mR2,           tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define potScissorErrorAllowance 100

/*
Eject Pot Rest: 2200
Eject Pot Ejected: 1400
Eject Motor Eject: (-)
*/
int ejectRest = 2200;
int ejectOut = 1000;
int activationDelay = 1000;

int stackedCount = 0;
int potPositions[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int mScissorValues[2] = {127, -127};

task trayCtrl {
	while(true){
		if(vexRT[Btn7U ]){
			motor[mEject] = -100;
			while(SensorValue(ejctPot) >= ejectOut){
				wait1Msec(1);
			}
			motor[mEject] = 100;
			while(SensorValue(ejctPot) <= ejectRest){
				wait1Msec(1);
			}
			motor[mEject] = 0;
		}

	}
}
task manualCtrl {
	while(true){
		if(vexRT[Btn8L]){
			motor[sClaw] = 127;
		}
		if(vexRT[Btn8R]){
			motor[sClaw] = -127;
		}
		if(vexRT[Btn6D]){
			motor[mTray] = 100;
		}else if(vexRT[Btn6U]){
			motor[mTray] = -100;
		} else{
			motor[mTray] = 0;
		}
		EndTimeSlice();
	}
}

bool autoStacking = false;
task autoStack {
	if (autoStacking) {
		return;
	}
	while (abs(SensorValue[potScissor] - potPositions[stackedCount]) > potScissorErrorAllowance) {
		motor[mScissorL] = mScissorValues[SensorValue[potScissor] < potPositions[stackedCount]];
	}
}

float theta = 90, power = 0, x = 0, y = 0, z = 0, vmL1, vmL2, vmR1, vmR2, vmax, direction = 1;

task main()
{
	//startTask(manualCtrl);
	//startTask(trayCtrl);
	while (true) {

		if (vexRT[Btn8D]) {
			startTask(autoStack);
		}

		if (vexRT[Btn5D]) {
			motor[mScissorL] = mScissorValues[0];
		} else if(vexRT[Btn5U]) {
			motor[mScissorL] = mScissorValues[1];
		} else {
			motor[mScissorL] = 0;
		}

		if (vexRT[Btn7D]) {
			motor[mTray] = 100;
		} else if(vexRT[Btn7U]) {
			motor[mTray] = -100;
		} else {
			motor[mTray] = 0;
		}
		x = vexRT[Ch4];
		y = vexRT[Ch3];
		z = vexRT[Ch1];
		power = sqrt(x * x + y * y);

		if (vexRT[Ch3] > 20 || vexRT[Ch3] < -20) {
			motor[mL1] = motor[mL2] = vexRT[Ch3];
		} else {
			motor[mL1] = motor[mL2] = 0;
		}
		if (vexRT[Ch2] > 20 || vexRT[Ch2] < -20) {
			motor[mR1] = motor[mR2] = vexRT[Ch2];
		} else {
			motor[mR1] = motor[mR2] = 0;
		}*/
		/*
		if (power > 20) {


			vmR1 = (x + y);
			vmL1 = (y - x);
			vmR2 = 2.828 * (y - x);
			vmL2 = 2.828 * (x + y);

	    vmax = fabs(vmL1);
	    if (fabs(vmL2) > fabs(vmax)) {
	        vmax = fabs(vmL2);
	    }
	    if (fabs(vmR1) > fabs(vmax)) {
	        vmax = fabs(vmR1);
	    }
	    if (fabs(vmR2) > fabs(vmax)) {
	        vmax = fabs(vmR2);
	    }
	    motor[mL1] = vmL1 / vmax * 127.0;
	    motor[mR1] = vmR1 / vmax * 127.0;
    	motor[mL2] = vmL2 / vmax * 127.0;
    	motor[mR2] = vmR2 / vmax * 127.0;
		} else {
			motor[mL1] = motor[mL2] = motor[mR1] = motor[mR2] = 0;
		}
		*/

		/*

		if (power > 10) {
			//if (y > 0) {
			if (power > 100) {
				power = 127;
			}
			direction = (y < 0 ? -1 : 1);
				motor[mL1] = motor[mL2] = (y - x) / 2;
				if (x > -20 && x < 20) {
					motor[mL1] = motor[mR1] = motor[mL2] = motor[mR2] = direction * power;
				} else {
					if (x < 0) {
						motor[mL2] = 0;
						motor[mR2] = direction * -x * (power / 127.0);
						motor[mL1] = motor[mR1] = (1.2 * y) / 2;
					} else {
						motor[mL2] = direction * x * (power / 127.0);
						motor[mR2] = 0;
						motor[mL1] = motor[mR1] = (1.2 * y) / 2;
					}
				}
		} else {
			motor[mL1] = motor[mL2] = motor[mR1] = motor[mR2] = 0;
		}
		x = vexRT[Ch1];
		y = vexRT[Ch2];
		power = sqrt(x * x + y * y);
		if (power > 50) {
			if (x > - 25 && x < 25) {
			} else if (y > -25 && y < 25) {
				if (x < 0) {
					motor[mL1] = motor[mL2] = -power;
					motor[mR1] = motor[mR2] = power;
				} else {
					motor[mL1] = motor[mL2] = power;
					motor[mR1] = motor[mR2] = -power;
				}
			}
		}
		if (vexRT[Btn6U]) {
			motor[mTray] = -127;
		} else if (vexRT[Btn6D]) {
			motor[mTray] = 127;
		} else {
			motor[mTray] = 0;
		}

 		EndTimeSlice();
	}

}
