struct point{
	int x,y;
};
struct actuator{
	int motorI, powerLevel; //which motor (A,B,C,D), power to run motor at with + being away from initial origin at top, left, robot-side
													//of board
	float gearRadius, curCoord, maxCoord; //standard units are cm but it'll work as long as all the units are the same
};

//can't return struct....
//i wish we had classes
//no curDist since cannot assign to motor encoders
void initActuator(actuator & act, int motorI, int powerLevel, float gearRadius, float maxCoord){
	act.motorI = motorI;
	act.powerLevel = powerLevel;
	act.gearRadius = gearRadius;
	act.curCoord = 0;
	nMotorEncoder[motorI] = 0;
	act.maxCoord = maxCoord;
}

void stopActuator(actuator act){
	motor[act.motorI] = 0;
}

void updateActuatorCoord(actuator & act){
	act.curCoord = nMotorEncoder[act.motorI] * act.gearRadius * PI / 180;
}

void updateActuatorCoord(actuator & act, float coord){
	act.curCoord = coord;
}

//if false, won't move for safety/part preservation, probably attempt to zero
bool rotateToCoord(actuator & act, float coord){
	//if the coordinate you tried to go to is within the acceptable range
	if(0 <= coord || coord <= act.maxCoord){
		//if you're behind the coord go forward
		if(act.curCoord < coord){
			motor[act.motorI] = act.powerLevel;
			while(act.curCoord < coord)
				updateActuatorCoord(act);
		}
		//if you're past the coord go backwards
		else if (act.curCoord > coord){
			motor[act.motorI] = -act.powerLevel;
			while(act.curCoord > coord)
				updateActuatorCoord(act);
				displayString(0, "%f", act.curCoord);
		}
		stopActuator(act);
		return true;
	}
	else
		return false;
}

bool rotate2ToCoord(actuator & act1, actuator & act2, float coord){
	if(0 <= coord || coord <= act1.maxCoord){

		if(act1.curCoord < coord && act2.curCoord < coord){

			motor[act1.motorI] = act1.powerLevel;
			motor[act2.motorI] = act2.powerLevel;

			//stops at the earlier stop
			while(act1.curCoord < coord && act2.curCoord < coord){
				updateActuatorCoord(act1);
				updateActuatorCoord(act2);
			}
		}

		else if (act1.curCoord > coord && act2.curCoord > coord){

			motor[act1.motorI] = -act1.powerLevel;
			motor[act2.motorI] = -act2.powerLevel;

			while(act1.curCoord > coord && act2.curCoord > coord){
				updateActuatorCoord(act1);
				updateActuatorCoord(act2);
			}
		}

		else
			return false;

		stopActuator(act1);
		stopActuator(act2);
		return true;
	}
	else
		return false;
}


void moveXY(point p ,actuator motorX,actuator motorY1,actuator motorY2)
{
	rotateToCoord(motorX, p.x) ;
	rotate2ToCoord(motorY1, motorY2, p.y);

}
void executeTurn(point* pickedTurn, actuator motorX, actuator motorY1,actuator motorY2,
				actuator motorZ)
{
	point sentinel;
	sentinel.x=9;
	sentinel.y=9;
	//moves arm to piece using moveXY

	moveXY(pickedTurn[0], motorX, motorY1, motorY2);

	//lowers the arm
	rotateToCoord(motorZ, 3);

	//checks the size of the array
	int SIZE = 0;
	int n = 0;

	while (pickedTurn[n] != sentinel)
		{
			SIZE++;
			n++;
		}
	//moves piece by iterating through picked move
	//starts at the first DESTINATION (bc pickedTurn[0] is the desired piece)

	for (n=1; n < SIZE; n++)
			moveXY(pickedTurn[n], motorX, motorY1, motorY2);

	//check for crowning

	//indicate to player that piece has been crowned?

	//raises arm

	//back to idle


}
task main()
{
	actuator motorX, motorY1, motorY2;
	initActuator(motorY1, motorA, 50, 2.1, 1000);
	initActuator(motorY2, motorB, 50, 2.1, 1000);
	initActuator(motorX, motorC, 50, 2.1, 1000);
	point p0, p1,p2, p3;

	p0.x = 0;
	p0.y = 0;

	p1.x = 3.5;
	p1.y = 3.5;

	p2.x = 7;
	p2.y = 28;

	p3.x = 10.5;
	p3.y = 10.5;
	moveXY(p0, motorX, motorY1, motorY2);
	wait1Msec(1000);
	moveXY(p1, motorX, motorY1, motorY2);
	wait1Msec(1000);
	moveXY(p2, motorX, motorY1, motorY2);
	wait1Msec(1000);
	moveXY(p3, motorX, motorY1, motorY2);
}
