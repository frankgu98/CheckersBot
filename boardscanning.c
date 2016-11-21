//Board scanning algorithms
#include "actuator.c"

bool KING = false; //
float SQUARESIZE = 3.5; //in cm
int BOARD[8][8]={{1,1,1,1,1,1,1,1},
								 {1,1,1,1,1,1,1,1},
								 {1,1,1,1,1,1,1,1},
								 {1,1,1,1,1,1,1,1},
								 {1,1,1,1,1,1,1,1},
								 {1,1,1,1,1,1,1,1},
								 {1,1,1,1,1,1,1,1},
								 {1,1,1,1,1,1,1,1} };
// Assume these all initialized
//actX is gantry // actY is on treads // actZ is arm

//Scan and initialize the entire board
void scanFullBoard(actuator actX, actuator actY1, actuator actY2){
	//ensure colour sensor is at (0,0){Bottom left corner of CPU side of the board}
	rotateToCoord(actX,0); //TENATIVE BASED ON COLOUR SENSOR MECH POSITION
	rotateToCoord(actY1,actY2,0); //TENATIVE BASED ON COLOUR SENSOR MECH POSITION
	
	//Move through the board checking every square
	for(int y=0;y<7;y++){
		for(int x=0;x<7;x++){
			
			//Move towards next space
			rotateToCoord(actX,actX.curCoord+SQUARESIZE);
			//Set value of board array to what the piece is
			BOARD[x][y] = SensorValue[S1]; //Assume sensor 1 is colour sensor
		}
		rotateToCoord(actX,0);
		rotateToCoord(actY1,actY2,actY1.curCoord+SQUARESIZE);
	}
	//Reset back to original position
	rotateToCoord(actY1,actY2,0);
	rotateToCoord(actX,0);
}

//Scan the board after a move has been made and updates it
bool updateBoard(actuator actX, actuator actY1, actuator actY2){
	//ensure colour sensor is at (0,0){Bottom left corner of CPU side of the board}
	rotateToCoord(actX,0); //TENATIVE BASED ON COLOUR SENSOR MECH POSITION
	rotateToCoord(actY1,actY2,0); //TENATIVE BASED ON COLOUR SENSOR MECH POSITION

	//If no piece has been kinged, uses a faster algorithm to not check the entire board	
	if(!KING){
		int foundMove = 0; //The amount of differences the computer found in player pieces(1 for new position,1 for empty position)
		int x=0,y=0;
		while(foundMove < 2){
			//Makes sure the robot has not gone off the board
			if(actY1.curCoord > 7*SQUARESIZE||actX.curCoord > 7*SQUARESIZE){
				return false; 
			}

			//Checks for a black piece out of place
			if(BOARD[x][y] != SensorValue[S1] && ((SensorValue[S1]==6)||(BOARD[x][y]==6))){
				BOARD[x][y] = SensorValue[S1];
				foundMove += 1;
			}
			if(foundMove > 0){
				BOARD[x][y] = SensorValue[S1];
			}
			//If the sensor has reached the end of a row
			if(x > 6){
				rotateToCoord(actX,0);
				rotateToCoord(actY1,actY2,actY1.curCoord+SQUARESIZE);
				x = 0;
				y++;
			}
			else{
				rotateToCoord(actX,actX.curCoord+SQUARESIZE);
				x++;
			}
		}
	}
	//If there is a king any number of moves can be made
	else{
		scanFullBoard(actX,actY1,actY2);
	}
	rotateToCoord(actX,0); //TENATIVE BASED ON COLOUR SENSOR MECH POSITION
	rotateToCoord(actY1,actY2,0); //TENATIVE BASED ON COLOUR SENSOR MECH POSITION
	return true;
}
