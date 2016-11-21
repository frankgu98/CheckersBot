
#include "actuator.c"

struct point{
	int x,y;
};

#ifndef TURN
#define TURN
struct turn{
	point tiles[3];
	int nCaps;
};
#endif

void initPoint(point & p, float x, float  y)
{
	p.x = x;
	p.y = y;
}


//constant to convert coordinates to cm for rotate to dist
const float tileDim = 3.5;

void moveXY(float x, float y,actuator actX,actuator actY1,actuator actY2)
{
	rotateToCoord(actX, x*SQUARESIZE);
	rotateToCoord(actY1, actY2, y*SQUARESIZE);

}
void executeTurn(turn pickedTurn ,actuator actX, actuator actY1,actuator actY2,
				actuator actZ, point sentinel, point idle)
{

	//moves arm to piece using moveXY
	moveXY(pickedTurn.tiles[0].x, pickedTurn.tiles[0].y, actX, actY1, actY2);

	//i hate robotc
	//point pTemp;
	//pTemp.x = pickedTurn[0].x;
	//pTemp.y = pickedTurn[0].y;
	//moveXY(pTemp.x, pTemp.y, motorX, motorY1, motorY2);

	//lowers the arm
	rotateToCoord(actZ, 1);

	////checks the size of the array
	int size = 0;
	int n = 0;

	//change this when getmove returns an int indicating the size of the array
	while (pickedTurn.tiles[n] != sentinel)
		{
			size++;
			n++;
		}
	//moves piece by iterating through picked move
	//starts at the first DESTINATION (b/c pickedTurn[0] is the desired piece)

	for (int n=1; n < 5; n++)
	{
			//robotC is gaaaarbaage
			//tempP.x = pickedTurn[n].x ;
			//tempP.y = pickedTurn[n].y ;
			moveXY(pickedTurn.tiles[n].x ,pickedTurn.tiles[n].y,actX, actY1, actY2); 
	}
	//check for crowning
	//if (tempP.y == 8)
	//	//set the last position to a "kinged" state
	//	BOARD[tempP.x][tempP.y] = 3;

	//indicate to player that piece has been crowned?

	//raises arm
	rotateToCoord(actZ, 0);

	//back to idle
	moveXY(idle.x, idle.y,actX, actY1, actY2);

}
#ifndef MAIN
#define MAIN
task main()
{
	actuator actX, actY1, actY2, actZ;
	initActuator(actY1, motorA, 50, 1.7, 1000);
	initActuator(actY2, motorB, 50, 1.7, 1000);
	initActuator(actX, motorC, 30, 2.1, 1000);
	initActuator(actZ, motorD, 30, 2.1, 10);
	
	point pickedTurn[5];

	point sentinel, idle;
	sentinel.x=100;
	sentinel.y=100;
	idle.x = 0;
	idle.y = 0;
	
	initPoint(pickedTurn[0],3.5,3.5);
	initPoint(pickedTurn[1],7,7);
	initPoint(pickedTurn[2],14,14);
	initPoint(pickedTurn[3],28.5,28.5);
	initPoint(pickedTurn[4],100,100);

	//for (int n = 0; n < 5; n++)
	//{
	//		point tempP;`
	//		//robotC is gaaaarbaage
	//		tempP.x = pickedTurn[n].x ;
	//		tempP.y = pickedTurn[n].y ;
	//		moveXY(tempP.x , tempP.y, motorX, motorY1, motorY2);
	//}
	
	for (int i = 0; i <4; i++)
		moveXY(pickedTurn[i].x,pickedTurn[i].y, actX, actY1, actY2); 

	executeTurn(pickedTurn, actX, actY1, actY2, actZ, sentinel, idle);
}
#endif
