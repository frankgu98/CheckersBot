#define MAIN
#include "boardscanning.c"
#include "actuator.c"
#include "execute turn.c"
#include "getMove_getMoves.c"



task main()
{
	SensorType[S1] = sensorEV3_Color;
	actuator actX, actY1, actY2, actZ;
	initActuator(actY1, motorA, 50, 1.7, 1000);
	initActuator(actY2, motorB, 50, 1.7, 1000);
	initActuator(actX, motorC, 30, 2.1, 1000);
	initActuator(actZ, motorD, 30, 2.1, 10);
	
	//point pickedTurn[5];

	//point sentinel, idle;
	//sentinel.x=100;
	//sentinel.y=100;
	//idle.x = 0;
	//idle.y = 0;
	
	//initPoint(pickedTurn[0],3.5,3.5);
	//initPoint(pickedTurn[1],7,7);
	//initPoint(pickedTurn[2],14,14);
	//initPoint(pickedTurn[3],28.5,28.5);
	//initPoint(pickedTurn[4],100,100);

	////for (int n = 0; n < 5; n++)
	////{
	////		point tempP;`
	////		//robotC is gaaaarbaage
	////		tempP.x = pickedTurn[n].x ;
	////		tempP.y = pickedTurn[n].y ;
	////		moveXY(tempP.x , tempP.y, motorX, motorY1, motorY2);
	////}
	
	//for (int i = 0; i <4; i++)
	//	moveXY(pickedTurn[i].x,pickedTurn[i].y, actX, actY1, actY2); 

	//executeTurn(pickedTurn, actX, actY1, actY2, actZ, sentinel, idle);
	
	//scanFullBoard(actX,actY1,actY2);
	updateBoard(actX,actY1,actY2);
}
