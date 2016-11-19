//Frank Gu

//keeps each motor organized and prevents them from going off the board
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


task main()
{
	actuator act1, act2;
	initActuator(act1, motorA, 50, 2.1, 1000);
	initActuator(act2, motorB, 50, 2.1, 1000);
	//select dist with arrow buttons
	rotateToCoord(act1, 40);

	wait1Msec(10000);
}
