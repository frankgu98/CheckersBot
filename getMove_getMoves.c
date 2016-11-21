#ifndef TURN
#define TURN
struct turn{
	point tiles[12];
	int nCaps;
};
#endif

int EMPTY = 1;
int RMAN = 2;
int RKING = 3;
int EMAN = 4;
int EKING = 5;

turn turnPoss[12], allTurnPoss[20];
turn tempTurn;
//BEN READ
/*
turn tempTurn;
int tempX = x;
int tempY = y;
while(doJump(tempX, tempY, tempTurn))
    	tempTurn.nCaps++;

*/
//This will give you a turn that has the jumps possible in one direction in essence
//Just add this to your array of possible turns somehow
//Sincerely,
//Chris and Frank


//proudly brought to you by
//					||~~ Chris & Frank ~~||
bool doJump(int &x, int &y, turn & tempTurn){
	if(x-2 > 0||y+2 < 7){
		int endx = x -2;
		int endy = y +2;
		int enex = x -1;
		int eney = y + 1;
		if(BOARD[endx][endy] == EMPTY && (BOARD[enex][eney] == EKING || BOARD[enex][eney] == EMAN)){
			tempTurn.tiles[tempTurn.nCaps].x -= 2;
			tempTurn.tiles[tempTurn.nCaps].y += 2;
			x-=2;
			y+=2;
			return true;
		}
	}
	else if(x+2 < 7||y+2 < 7){
		int endx = x +2;
		int endy = y +2;
		int enex = x +1;
		int eney = y + 1;
		if(BOARD[endx][endy] == EMPTY && (BOARD[enex][eney] == EKING || BOARD[enex][eney] == EMAN)){
			tempTurn.tiles[tempTurn.nCaps].x += 2;
			tempTurn.tiles[tempTurn.nCaps].y += 2;
			x+=2;
			y+=2;
			return true;
		}
	}
	if(BOARD[x][y] == RKING){
		if(x-2 > 0||y-2 > 0){
			int endx = x -2;
			int endy = y -2;
			int enex = x -1;
			int eney = y - 1;
			if(BOARD[endx][endy] == EMPTY && (BOARD[enex][eney] == EKING || BOARD[enex][eney] == EMAN)){
				tempTurn.tiles[tempTurn.nCaps].x -= 2;
				tempTurn.tiles[tempTurn.nCaps].y -= 2;
				x-=2;
				y-=2;
				return true;
			}
		}
		else if(x-2 > 0||y+2 < 7){
			int endx = x -2;
			int endy = y +2;
			int enex = x -1;
			int eney = y + 1;
			if(BOARD[endx][endy] == EMPTY && (BOARD[enex][eney] == EKING || BOARD[enex][eney] == EMAN)){
				tempTurn.tiles[tempTurn.nCaps].x += 2;
				tempTurn.tiles[tempTurn.nCaps].y -= 2;
				x+=2;
				y-=2;
				return true;
			}
		}
	}
	return false;
}


void getMove(int x, int y){ //takes a coordinate, checks the piece, determines all possible moves for that piece in the next two moves
    for (int i = 0; i < 12; i++){ //re-initializing turnPoss[]
        turnPoss[i].tiles[0].x = x;
        turnPoss[i].tiles[0].y = y; //the first tile is where the piece started
        for (int j = 1; j < 3; j++){
            turnPoss[i].tiles[j].x = 0;
            turnPoss[i].tiles[j].y = 0; //the other two tiles are 0,0
        }
        turnPoss[i].nCaps = -1; //-1 captures means an invalid turn or not a turn
    }

    int tCount = 0; //counting the possible turns

    //   INSERT HERE    //  INSERT HERE    //   INSERT HERE  //   INSERT HERE    //   INSERT HERE    //   INSERT HERE    //   INSERT HERE    //   INSERT HERE    //   INSERT HERE    //   INSERT HERE    //   INSERT HERE    //   INSERT HERE    //   INSERT HERE    //   INSERT HERE
    //probably insert doJumps here!!

    if (BOARD[x][y] == 2) { //checks if the piece belongs to robot

	    for (int i = 0; i < 2; i++){ //checks for regular move forward, no captures
	        if (x+1-2*i >= 0 && //checks if the next tile exists  (is on the BOARD)
	        		x+1-2*i <= 7 && y+1 <= 7 &&
	        		BOARD[x+1-2*i][y+1] == 1){ //checks if the tile is empty (BLACKCOLOR)
	           turnPoss[tCount].nCaps++; //capture increases to 0
	           turnPoss[tCount].tiles[1].x = x+1-2*i;
	           turnPoss[tCount].tiles[1].y = y+1; //saves this move as a point
	           tCount++; //turn over; next possible turn
	        }
	    }
    }
    if (BOARD[x][y] == 3){ //if the piece is a king

      for (int i = 0; i < 2; i++){
          if (x+1-2*i >= 0 && y-1 >= 0 &&
          x+1-2*i <= 7 && y-1 <= 7 &&
          BOARD[x+1-2*i][y-1] == 1){ //also check for backwards moves
              turnPoss[tCount].nCaps++; //capture increases to 0
              turnPoss[tCount].tiles[1].x = x+1-2*i;
              turnPoss[tCount].tiles[1].y = y-1; //saves this move
              tCount++; //next turn
        	}

      }
    }
}

int getMoves(){ //takes the whole BOARD
//for each piece, gets all moves and puts legal loves into allTurnPoss[]
    for (int i = 0; i < 20; i++){ //re-intialize allTurnPoss
        for (int j = 0; j < 3; j++){
            allTurnPoss[i].tiles[j].x = 0;
            allTurnPoss[i].tiles[j].y = 0;
        }

        allTurnPoss[i].nCaps = -1;
    }

    int allTurnIndex = 0; //how many possible moves total
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){ //checks every tile on the BOARD
            if (BOARD[i][j] == 2 || BOARD[i][j] == 3){ //checks if the piece belings to robot
                getMove(i, j); //fills turnPoss with all moves

                for (int k = 0; k < 12; k++){ //goes through turnPoss
                    if(turnPoss[k].nCaps != -1){ //if the move is legal (nCaps isn't -1)
                        allTurnPoss[allTurnIndex] = turnPoss[k]; //records the turn in allTurnPoss
                        allTurnIndex++; //increases the count
                    }
                }
            }
        }
    }
    return allTurnIndex; //returns the number of elements in the array (max index + 1)
}

/*
if (x+1-2*i >= 0 &&
            	x+1-2*i <= 7 && y+1 <= 7 &&
            	BOARD[x+1-2*i][y+1] > 3 &&
            	x+2-4*i >= 0 &&
            	x+2-4*i <= 7 && y+2 <= 7 &&
            	BOARD[x+2-4*i][y+2] == 1){ //checks if next tile exists, contains a piece, and the subsequent tile is empty
                int xNew = x+2-4*i, yNew = y+2; //new positions of piece
                turnPoss[tCount].tiles[1].x = xNew;
                turnPoss[tCount].tiles[1].y = yNew; //saves this move as a point
                turnPoss[tCount].nCaps += 2; //capture increases to 1

                bool nextMove = false; //boolean for if another capture is possible

                for (int j = 0; j < 4; j++){ //if there was a capture, check for another possible capture
                //pow(-1,j) and pow(-1,j/2) switch between (1,1),(-1,1),(1,-1),(-1,1), the four possible directions
                    if (!(xNew+2*pow(-1,j) == x && yNew+2*pow(-1,j/2) == y)){ //prevents going back in the same direction

                    	if(xNew+pow(-1,j) >= 0 && yNew+pow(-1,j/2) >= 0 && //checks remaining 3 directions
	                        xNew+pow(-1,j) <= 7 && yNew+pow(-1,j/2) <= 7 && //if they exist
	                        BOARD[xNew+(int)(pow(-1,j))][yNew+(int)(pow(-1,j/2))] > 3 && //if its an enemy piece
	                        xNew+2*pow(-1,j) >= 0 && yNew+2*pow(-1,j/2) >= 0 &&
	                        xNew+2*pow(-1,j) <= 7 && yNew+2*pow(-1,j/2) <= 7 && //if the subsequent tile exists
	                        BOARD[xNew+2*(int)(pow(-1,j))][yNew+2*(int)(pow(-1,j/2))] == 1){ //and if they're empty

	                        	if (j){ //if this loop already ran once
                                turnPoss[tCount].tiles[1].x = xNew;
                                turnPoss[tCount].tiles[1].y = yNew;
                                turnPoss[tCount].nCaps = 1; //then the first jump needs to be copied again

                                if (BOARD[x][y] == 2)
                                    j += 3; //if its a man, then only run the loop twice
                            }

                            turnPoss[tCount].tiles[2].x = xNew+2*pow(-1,j);
                            turnPoss[tCount].tiles[2].y = yNew+2*pow(-1,j/2); //saves this second move
                            turnPoss[tCount].nCaps++; //captures increases to 2

                            tCount++; //turn over; next turn
                            nextMove = true; //a second capture was possible
                        }
                    }
                }
                if (!nextMove) //if there was no second capture after 4 loops
                    tCount++; //turn over; next turn*/
