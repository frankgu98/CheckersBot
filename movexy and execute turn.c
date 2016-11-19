

rotatetocoord

rotate2tocoord
void moveXY(point p,actuator motorX,actuator motorY1,actuator motorY2)
{
	rotateToCoord(p.x, motorX);
	rotateToCoord(p.y motorY1, motorY2);
	
}


//take in array of points, read in two at a time, increment by one
//;et cupdown be the distance for the cup to lower
//firat element of pickedmove is the the desired piece
	
void executeTurn(turn pickedMove[], actuator motorX, actuator motorY1,actuator motorY2,
				actuator motorZ)
{
	//moves arm to piece using moveXY
	
	moveXY(pickedMove[0], motorX, motorY1, motorY2);
	
	//lowers the arm
	rotateToCoord(cupdown, motorZ)

	//checks the size of the array
	int SIZE = 0;
	int n = 0;
	
	while (pickedMove[n] != sentinel)
		{
			SIZE++;
			n++;
		}	
	//moves piece by iterating through picked move
	
	for (n=1; n < SIZE, n++)
			moveXY(pickedMove[n], motorX, motorY1, motorY2);

	//check for crowning
	

	//indicate to player that piece has been crowned?

	//stop move

	//raises arm


}



task main()
{



}
