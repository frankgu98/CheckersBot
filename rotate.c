//Frank Gu

struct actuator{
	int motorI, powerLevel; //which motor (A,B,C,D), power to run motor at with + being away from initial origin at bottom, left, robot-side
													//of board
	float gearRadius, curDist, maxDist; //standard units are cm but it'll work as long as all the units are the same
};

//can't return struct....
void initActuator(actuator & act, int motorI, int powerLevel, float gearRadius, float curDist, float maxDist){
	act.motorI = motorI;
	act.powerLevel = powerLevel;
	act.gearRadius = gearRadius;
	act.curDist = curDist;
	act.maxDist = maxDist;
}

void startActuator(actuator act){
	motor[act.motorI] = act.powerLevel;
}
void stopActuator(actuator act){
	motor[act.motorI] = 0;
}

void updateActuatorDist(actuator act){
	act.curDist = nMotorEncoder[act.motorI] * act.gearRadius * PI / 180;
}

void updateActuatorDist(actuator act, float dist){
	act.curDist = dist;
}

//if false, probably attempt to zero
bool rotateToDist(actuator act, float dist){
	if(0 < dist || dist <= act.maxDist){
		startActuator(act);
		while(act.curDist < dist)
			updateActuatorDist(act);
		stopActuator(act);
		return true;
	}
	else
		return false;
}

task main()
{
	actuator act;
	initActuator(act, motorA, 50, 2.1, 0, 1000);
	//select dist with arrow buttons
	rotateToDist(act, -40);
}
