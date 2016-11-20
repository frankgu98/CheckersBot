struct point{
	int x,y;
};

void initPoint(point & p, int x, int y)
{
	p.x = x;
	p.y = y;
}

struct actuator{
	int motorI, powerLevel; //which motor (A,B,C,D), power to run motor at with + being away from initial origin at top, left, robot-side
													//of board
	float gearRadius, curCoord, maxCoord; //standard units are cm but it'll work as long as all the units are the same
};

//constant to convert coordinates to cm for rotate to dist
const double tileDim = 3.5;


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


void moveXY(point p0,actuator motorX,actuator motorY1,actuator motorY2)
{
	rotateToCoord(motorX, p0.x*tileDim) ;
	rotate2ToCoord(motorY1, motorY2, p0.y*tileDim);

}
void executeTurn(point *pickedTurn,actuator motorX, actuator motorY1,actuator motorY2,
				actuator motorZ, point sentinel, point idle)
{

	//moves arm to piece using moveXY

	//i hate robotc
	point pTemp;
	pTemp.x = pickedTurn[0].x;
	pTemp.y = pickedTurn[0].y;
	moveXY(pTemp, motorX, motorY1, motorY2);

	//lowers the arm
	rotateToCoord(motorZ, 5);

	//checks the size of the array
	int SIZE = 0;
	int n = 0;

	//change this when getmove returns an int indicating the size of the array
	while (pickedTurn[n] != sentinel)
		{
			SIZE++;
			n++;
		}
	//moves piece by iterating through picked move
	//starts at the first DESTINATION (b/c pickedTurn[0] is the desired piece)

	for (n=1; n < SIZE; n++)
	{
			point tempP;
			//robotC is gaaaarbaage
			tempP.x = pickedTurn[n].x ;
			tempP.y = pickedTurn[n].y ;
			moveXY(tempP, motorX, motorY1, motorY2);
	}
	//check for crowning

	//indicate to player that piece has been crowned?

	//raises arm
	rotateToCoord(motorZ, -5);

	//back to idle
	moveXY(idle, motorX, motorY1, motorY2);

}
task main()
{
	actuator motorX, motorY1, motorY2, motorZ;
	initActuator(motorY1, motorA, 50, 2.1, 1000);
	initActuator(motorY2, motorB, 50, 2.1, 1000);
	initActuator(motorX, motorC, 50, 2.1, 1000);
	initActuator(motorZ, motorD, 50, 2.1, 1000);
	point idle, p0,p1,p2, p3;
	point pickedTurn[5];

	initPoint(idle, 0,0);
	initPoint(p0,4,4);
	initPoint(p1,1,1);
	initPoint(p2,2,8);
	initPoint(p3,3,3);

	point sentinel;
	sentinel.x=100;
	sentinel.y=100;

	pickedTurn[0] = p0;
	pickedTurn[1] = p1;
	pickedTurn[2] = p2;
	pickedTurn[3] = p3;
	pickedTurn[4] = sentinel;

	executeTurn(pickedTurn, motorX, motorY1, motorY2, motorZ, sentinel, idle);
}
