

rotatetocoord

rotate2tocoord
void moveXY(point p,actuator motorX,actuator motorY1,actuator motorY2)
{
	rotateToCoord(motorX, p.x) ;
	rotate2ToCoord(motorY1, motorY2, p.y);
	
}


//take in array of points, read in two at a time, increment by one
//;et cupdown be the distance for the cup to lower
//firat element of pickedmove is the the desired piece
	
void executeTurn(turn pickedTurn], actuator motorX, actuator motorY1,actuator motorY2,
				actuator motorZ)
{
	//moves arm to piece using moveXY
	
	moveXY(pickedTurn[0], motorX, motorY1, motorY2);
	
	//lowers the arm
	rotateToCoord(motorZ, cupdown)

	//checks the size of the array
	int SIZE = 0;
	int n = 0;
	
	while (pickedTurn] != sentinel)
		{
			SIZE++;
			n++;
		}	
	//moves piece by iterating through picked move
	//starts at the first DESTINATION (bc pickedTurn[0] is the desired piece)
	
	for (n=1; n < SIZE, n++)
			moveXY(pickedTurn[n], motorX, motorY1, motorY2);

	//check for crowning
	
	//indicate to player that piece has been crowned?

	//raises arm
	
	//back to idle


}



task main()
{



}
