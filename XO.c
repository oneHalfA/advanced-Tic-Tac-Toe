#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <stdbool.h>

// ==============================================VARIABLES/STRUCTURES
int board[9][9] = {
    {'O','O',' ',	' ',' ',' ',	'X','X','X'},
    {' ',' ',' ',	' ',' ',' ',	'X','X','X'},
    {' ',' ',' ',	' ',' ',' ',	'X','X',' '},

    {' ',' ',' ',	' ',' ',' ',	' ',' ',' '},
    {' ',' ',' ',	' ',' ',' ',	' ',' ',' '},
    {' ',' ',' ',	' ',' ',' ',	' ',' ',' '},

    {' ',' ',' ',	' ',' ',' ',	' ',' ',' '},
    {' ',' ',' ',	' ',' ',' ',	' ',' ',' '},
    {' ',' ',' ',	' ',' ',' ',	' ',' ',' '}
};

struct SubGridMap{
    int row;
    int col;
    int state; // -1(undefined) 0(tie) 1(O won) 2(X won)
} sub_grid[9] ={
    {0,0,-1}, // 1
    {0,3,-1}, // 2
    {0,6,-1}, // 3
    {3,0,-1}, // 4
    {3,3,-1}, // 5
    {3,6,-1}, // 6
    {6,0,-1}, // 7
    {6,3,-1}, // 8
    {6,6,-1}  // 9
};

int wPossibilities[8][3] =
{
    {0,1,2},
    {3,4,5},
    {6,7,8},
    {0,3,6},
    {1,4,7},
    {2,5,8},
    {0,4,8},
    {2,4,6}
};

// ==============================================FUNCTIONS

void clear_screen(void){
    printf("\033[2J\033[H");
}

void drawBoard(void){
    int sGrid = 2;
    for(int row=0;row<9;row++){
	if(row % 3 == 0 && row != 0)
	    sGrid++;
	else
	    sGrid-=2;
	for(int col=0;col<9;col++){
	    
	    if(col % 3==0 && col!=0)
		sGrid++;
	    
		if (sub_grid[sGrid].state==1)
		    printf("\033[36m %c  \033[0m",board[row][col]);
		else if (sub_grid[sGrid].state==2)
		    printf("\033[31m %c  \033[0m",board[row][col]);
		else
		    printf("[%c] ",board[row][col]);

	    fflush(stdout);
	    usleep(10000);
	    if((col+1) % 3 == 0 && col != 8)
		printf(" | ");
	}
	if((row+1)%3 ==0 && row != 8){
	    printf("\n-----------------------------------------");
	}
	printf("\n");
    }
}

void drawSubGrid(int num){
    clear_screen();
    printf("sub grid number: %d\n",num + 1);
    for(int i=sub_grid[num].row;i<sub_grid[num].row+3;i++){
	for(int j=sub_grid[num].col;j<sub_grid[num].col+3;j++){
	    printf("[%c] ",board[i][j]);
	    fflush(stdout);
	    usleep(1000);
	}
	printf("\n");
    }
}


struct SubGridMap *convertToRealSquare(int square,int gridNum){
    struct SubGridMap *real = malloc(1*sizeof(struct SubGridMap));
    int counter = 0;
    for(int i=sub_grid[gridNum].row;i<sub_grid[gridNum].row+3;i++){
	for(int j=sub_grid[gridNum].col;j<sub_grid[gridNum].col+3;j++){
	    if(counter == square){
		real->row = i;
		real->col = j;
		return real;
	    }
	    else
		counter++;
	}
    }
}

void computerMove(int *gridNum){
    int square = rand() % 9;
    struct SubGridMap *real = convertToRealSquare(square,*gridNum);
    while(board[real->row][real->col] != ' '){
	free(real);
	square = rand() % 9;
	real = convertToRealSquare(square,*gridNum);
    }
    board[real->row][real->col] = 'X';
    *gridNum = square;
    free(real);
}

bool playerMove(int square,int *gridNum){
    struct SubGridMap *real = convertToRealSquare(square-1,*gridNum);
    if(board[real->row][real->col] == ' '){
	board[real->row][real->col] = 'O';
	*gridNum = square - 1;
	free(real);
	return true;
    }else{
	printf("\nNot proper square!!\nTry Again =)\n");
	free(real);
	return false;
    }
}

bool isEmpty(int gridNum){
    for(int i=sub_grid[gridNum].row;i<sub_grid[gridNum].row+3;i++) {
	for(int j=sub_grid[gridNum].col;j<sub_grid[gridNum].col+3;j++) {
	    if(board[i][j] == ' ')
		return true;
	}
    }
    return false;
}

int winCheck(int gridNum){
    for(int win=0;win<8;win++){

	struct SubGridMap *real[3] ={
	    convertToRealSquare(wPossibilities[win][0],gridNum),
	    convertToRealSquare(wPossibilities[win][1],gridNum),
	    convertToRealSquare(wPossibilities[win][2],gridNum)
    
	};

	if( board[real[0]->row][real[0]->col] == 'X' && board[real[1]->row][real[1]->col] == 'X' && board[real[2]->row][real[2]->col] == 'X' ){
	    return 2; //computer has won this sub grid
	}else if( board[real[0]->row][real[0]->col] == 'O' && board[real[1]->row][real[1]->col] == 'O' && board[real[2]->row][real[2]->col] == 'O' ){
	    return 1; // Player has won this sub grid
	}else {
	    if(isEmpty(gridNum))
		return -1;
	    return 0; // that sub grid does not belong to any one (Tie) 
	}
    }
}

void changeState(int gridNum){
    int state = winCheck(gridNum);
    switch(state){
	case 1:
	    printf("[P] has won sub-grid number %d \n",1+gridNum);
	    sub_grid[gridNum].state = 1;
	    break;
	case 2:
	    printf("\n\n[C] has won sub-grid number %d \n",1+gridNum);
	    sub_grid[gridNum].state = 2;
	    break;
	case 0:
	    printf("sub-grid number %d does not belong to anyone\n",1+gridNum);
	    sub_grid[gridNum].state = 0;
	    break;
	case -1:
	    sub_grid[gridNum].state = -1;
	    break;
    }
}

void fillTheSubGrid(int gridNum){
    char winner;

    if(sub_grid[gridNum].state == 1)
	winner = 'O';
    else
	winner = 'X';

    for(int i=sub_grid[gridNum].row;i<sub_grid[gridNum].row+3;i++)
	for(int j=sub_grid[gridNum].col;j<sub_grid[gridNum].col+3;j++)	    
	    board[i][j] = winner;
}
// ==============================================MAIN

int main(void){

    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO,TCSANOW, &tty);

    srand(time(NULL));
    int currentSubGrid = 0,previousSubGrid;
    while(true){
	
	clear_screen();
	drawBoard();
	printf("Press any key to start (e.g. Enter)\n");
	
	getchar();
	drawSubGrid(currentSubGrid);
	printf("which square? ");

	while(true){
	    previousSubGrid = currentSubGrid;
	    if(sub_grid[previousSubGrid].state != -1){
		printf("\n[P] Selected sub grid is filled.So..\n");
		usleep(2500000);
		clear_screen();
		drawBoard();
		printf("sub-grid: \n");
		currentSubGrid = (int)getchar() - 49;
		break;
	    }
	    bool success = playerMove( (int)getchar() - 48 ,&currentSubGrid);
	    printf("\n\n\n\n");
	    if(success){
		
		changeState(previousSubGrid);
		if(sub_grid[previousSubGrid].state == 1)
		    fillTheSubGrid(previousSubGrid);

		previousSubGrid = currentSubGrid;
		if(sub_grid[previousSubGrid].state != -1){
		    printf("[C] Selected sub grid is filled.\n");
		    while(sub_grid[previousSubGrid].state != -1)
			currentSubGrid = previousSubGrid = rand() % 9;
		}
		computerMove(&currentSubGrid);
		printf("\n\n\nCOMPUTER CHOOSING A MOVE....\n\n");
		usleep(1500000);
		drawSubGrid(previousSubGrid);
		
		
		changeState(previousSubGrid);
		if(sub_grid[previousSubGrid].state == 2)
		    fillTheSubGrid(previousSubGrid);
		fflush(stdout);
		usleep(2000000);
		break;
	    }

	}
    }
    return 0;
}
