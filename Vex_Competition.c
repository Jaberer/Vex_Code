#pragma config(Motor,  port1,           Cubeholder,    tmotorVex393, openLoop)
#pragma config(Motor,  port2,           FrontLeftDrive, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           FrontRightDrive, tmotorVex393, openLoop)
#pragma config(Motor,  port4,           RearLeftDrive, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port5,           RearRightDrive, tmotorVex393, openLoop)
#pragma config(Motor,  port6,           LeftArmBottom, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7,           LeftArmTop,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port8,           RightArmBottom, tmotorVex393, openLoop)
#pragma config(Motor,  port9,           RightArmTop,   tmotorVex393, openLoop)

#pragma platform(VEX)
#pragma competitionControl(Competition)
//get hacked by rohit u scrub #420noscoped

#include "Vex_Competition_Includes.c"   //Main competition background code... you can modify if you want :)

#define vexMotorOff = 0
// #define vexMotorMax = 127
// #define vexMotorMin = -127

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

}

//Autonomous Functions
void move_forward(int power, int time)
{

		motor[FrontLeftDrive] = power;
		motor[RearLeftDrive] = power;
		motor[FrontRightDrive] = power;
		motor[RearRightDrive] = power;
		wait1Msec(time);
		motor[FrontLeftDrive] = 0;
		motor[RearLeftDrive] = 0;
		motor[FrontRightDrive] = 0;
		motor[RearRightDrive] = 0;

}

void turn(int power, int time, int direction) //-1 for left, 1 for right
{
		//not great code, but a example
		//*compiles, but untested
		int directionNUMB;
		if(direction == "Left") { directionNUMB = -1; }
		if(direction == "Right") { directionNUMB = 1; }

		motor[FrontLeftDrive] = power*directionNUMB;
		motor[RearLeftDrive] = power*directionNUMB;
		motor[FrontRightDrive] = power*directionNUMB*-1;
		motor[RearRightDrive] = power*directionNUMB*-1;

		wait1Msec(time);
		motor[FrontLeftDrive] = vexMotorOff;		//just good practice instead of 0
		motor[RearLeftDrive] = vexMotorOff;
		motor[FrontRightDrive] = vexMotorOff;
		motor[RearRightDrive] = vexMotorOff;

}

void liftarm(int power,int time){
	motor[LeftArmBottom] = power;
		motor[LeftArmTop] = power;
		motor[RightArmBottom] = power;
		motor[RightArmTop] = power;
	wait1Msec(time);

	motor[LeftArmBottom] = vexMotorOff;
		motor[LeftArmTop] = vexMotorOff;
		motor[RightArmBottom] = vexMotorOff;
		motor[RightArmTop] = vexMotorOff;

}

task autonomous()
{

	move_forward(80,500);
	// quickscopeDemNoob(300 /* Amount */, 1000000 /* AimbotHaxSpeed */);

}

task usercontrol()
{


	while (true)
	{
	 
	int RightDrive, LeftDrive = 0;
	// int Slowdriving = 0;
	//guessing this is going to be a 0 or 1 to determine a slowdrive mode, if this is true:
	bool Slowdriving = false; //could also use 0

	int Channel3 = vexRT(Ch3);
	int Channel1 = vexRT(Ch1);

	RightDrive = Channel3 + Channel1;
	LeftDrive = Channel3 - Channel1;

	if (vexRT[Btn5U] == 1)
	{
		motor[LeftArmBottom] = 40;
		motor[LeftArmTop] = 40;
		motor[RightArmBottom] = 40;
		motor[RightArmTop] = 40;
	}
	else if (vexRT[Btn5D] == 1)
	{
		motor[LeftArmBottom] = -40;
		motor[LeftArmTop] = -40;
		motor[RightArmBottom] = -40;
		motor[RightArmTop] = -40;
	}
	else
	{
		motor[LeftArmBottom] = 0;
		motor[LeftArmTop] = 0;
		motor[RightArmBottom] = 0;
		motor[RightArmTop] = 0;
	}

	if (vexRT[Btn6U] == 1)
	{
		motor[Cubeholder] = 120;
	}
	else if (vexRT[Btn6D] == 1)
	{
		motor[Cubeholder] = -120;
	}
	else
	{
		motor[Cubeholder] = 0;
	}


	motor[FrontLeftDrive] = LeftDrive;
	motor[RearLeftDrive] = LeftDrive;
	motor[FrontRightDrive] = RightDrive;
	motor[RearRightDrive] = RightDrive;
	}
	//testing for autonmous
	if(vexRT[Btn8D]==1)
		{

    liftarm(80,400);
		move_forward(80,500);
		turn(80,600, -1);
	}

}
