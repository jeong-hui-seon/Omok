#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

#define KEY_SPACE ' ' // not defined in ncurses.h
#define KEY_Enter 10
#define START_ROW 5
#define START_COL 5


int HEIGHT, WIDTH;

int** initBoard(int **board, int *row, int *col, int *turn){
	board = (int**)malloc(sizeof(int*)*HEIGHT);
	for(int i=0; i<HEIGHT; i++){
		board[i] = (int*)malloc(sizeof(int)*WIDTH);
	}

	//printf("%d %d\n", HEIGHT, WIDTH);
	board[0][0] = ACS_ULCORNER;//'┌'
	for (int i=1; i < WIDTH-1; i++)
		board[0][i] = ACS_TTEE;//'┬'
	board[0][WIDTH-1] = ACS_URCORNER; //'┐'

	for (int i=1; i<HEIGHT-1; i++){
		board[i][0] = ACS_LTEE; // '├'
		for (int j=1; j < WIDTH-1; j++)
			board[i][j] = ACS_PLUS; //'┼'
		board[i][WIDTH-1] = ACS_RTEE; //'┤'
	}

	board[HEIGHT-1][0] = ACS_LLCORNER; //'└'
	for (int i=1; i < WIDTH-1; i++)
		board[HEIGHT-1][i] = ACS_BTEE; //'┴'
	board[HEIGHT-1][WIDTH-1] = ACS_LRCORNER; // '┘'

	return board;
}

void paintBoard(int **board, WINDOW *win, int row, int col){
	/*
		Print the board to the given WINDOW 
		using functions of the ncurses library.
	*/

	// TODO
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			mvwaddch(win, i, j, board[i][j]);
		}
	}
}

int checkWin(int ** board){ // parameters and return type can be modified with any form. 
	/*
		Check if the game is over. 
	*/
	// TODO
	int i,j;		

	for(j=0;j<WIDTH;j++){
		for(i=2;i<HEIGHT-2;i++){
				
			if(
			board[i-2][j]=='X'&& board[i-1][j]=='X'&& board[i][j]=='X'&& board[i+1][j]=='X'&& board[i+2][j]=='X'
			){
				mvprintw(HEIGHT+5,7,"PLAYER 2 WIN !! Press 9 to terminate the program");
				return 1;
			}

			else if(
			board[i-2][j]=='O'&& board[i-1][j]=='O'&& board[i][j]=='O'&& board[i+1][j]=='O'&& board[i+2][j]=='O'
			){
				mvprintw(HEIGHT+5,7,"PLAYER 1 WIN !! Press 9 to terminate the program");
				return 1;
			}
		}
	}

	for(i=0;i<HEIGHT;i++){
		for(j=2;j<WIDTH-2;j++){
			if(
			board[i][j-2]=='X'&& board[i][j-1]=='X'&& board[i][j]=='X'&& board[i][j+1]=='X'&& board[i][j+2]=='X'
			){
				mvprintw(HEIGHT+5,7,"PLAYER 2 WIN !! Press 9 to terminate the program");
				return 1;
			}

			else if(
			board[i][j-2]=='O'&& board[i][j-1]=='O'&& board[i][j]=='O'&& board[i][j+1]=='O'&& board[i][j+2]=='O'
			){
				mvprintw(HEIGHT+5,7,"PLAYER 1 WIN !! Press 9 to terminate the program");
				return 1;
			}
		}
	}

	for(i=2;i<HEIGHT-2;i++){
		for(j=2;j<WIDTH-2;j++){
			if(
			board[i-2][j-2]=='X'&& board[i-1][j-1]=='X'&& board[i][j]=='X'&& board[i+1][j+1]=='X'&& board[i+2][j+2]=='X'
			){
				mvprintw(HEIGHT+5,7,"PLAYER 2 WIN !! Press 9 to terminate the program");
				return 1;
			}
			else if(
			board[i-2][j-2]=='O'&& board[i-1][j-1]=='O'&& board[i][j]=='O'&& board[i+1][j+1]=='O'&& board[i+2][j+2]=='O'
			){
				mvprintw(HEIGHT+5,7,"PLAYER 1 WIN !! Press 9 to terminate the program");
				return 1;
			}

			else if(
			board[i-2][j+2]=='X'&& board[i-1][j+1]=='X'&& board[i][j]=='X'&& board[i+1][j-1]=='X'&& board[i+2][j-2]=='X'
			){
				mvprintw(HEIGHT+5,7,"PLAYER 2 WIN !! Press 9 to terminate the program");
				return 1;
			}

			else if(
			board[i-2][j+2]=='O'&& board[i-1][j+1]=='O'&& board[i][j]=='O'&& board[i+1][j-1]=='O'&& board[i+2][j-2]=='O'
			){
				mvprintw(HEIGHT+5,7,"PLAYER 1 WIN !! Press 9 to terminate the program");
				return 1;
			}

		}
	}

	return 0;
}

int Action(WINDOW *win, int **board, int keyin, int *row, int *col, int *turn){
	/*
		following right after the keyboard input,
		perform a corresponding action. 
	*/
	// TODO 
	switch(keyin){
		case '9':
			return 9;

		case KEY_SPACE:
		case KEY_Enter:
			if(board[*row][*col]!='O' && board[*row][*col]!='X'){
				if (*turn==1){
			    	board[*row][*col]='O';
			    	*turn=2;
				}
				else if(*turn==2){
					board[*row][*col]='X';
					*turn=1;
				}
			}
			break;

		case KEY_DOWN:
			*row += 1;
			if(*row>=HEIGHT) *row-=1;
			break;

		case KEY_LEFT:
			*col -= 1;
			if(*col<0) *col+=1;
			break;

		case KEY_RIGHT:
			*col += 1;
			if(*col>=WIDTH) *col-=1;
			break;

		case KEY_UP:
			*row -= 1;
			if(*row<0) *row+=1;
			break;
	}
	
	wmove(win, *row, *col);
	refresh();
	wrefresh(win);

	if(checkWin(board)) return 1;
	return 0;	       
	
}

void gameStart(WINDOW *win){
	int **board;
	int row = 0;
	int col = 0;
	int keyin;
	int turn = 1;
	char stone;
	int action;
	int check=0;

	wmove(win, row, col); //커서 이동
	board = initBoard(board, &row, &col, &turn); // Initiating the board

	while(1){
		/* 
			This While loop constantly loops in order to 
			draw every frame of the WINDOW.
		*/

		// TODO LIST
		  // PAINT THE BOARD
		paintBoard(board, win, row, col);
		wmove(win, row, col);
		//refresh();
		wrefresh(win);
		
		  // PAINT MENU
		if(turn == 1){
			stone='O';
		}
		else if(turn == 2){
			stone='X';
		}
		noecho();
		mvprintw(HEIGHT+6, 7,"Current Trun : %c", stone);
		mvprintw(HEIGHT+7, 7,"Press 9 to exit");
		wmove(win, row, col);
		refresh();
		wrefresh(win);
		  // MOVE CURSOR TO THE LAST POINT 
		  // GET KEYBOARD INPUT
		
		keyin = wgetch(win);
		  // DO ACTION ACCORDING TO THAT INPUT
		action = Action(win, board, keyin, &row, &col, &turn);

		if(action == 9) break;
		  // update WINDOW 

				
		
	}

	return;
}

int main(){
	// TODO 
	/*
		Prompts to ask options of the game
	*/
	printf("Enter the HEIGHT of the board : ");
	scanf("%d", &HEIGHT);
	printf("Enter the WIDTH of the board : ");
	scanf("%d", &WIDTH);

	// TODO LIST
	// define a window
	// terminate the window safely so that the terminal settings can be restored safely as well. 
	initscr();
	refresh();
	WINDOW * win = newwin(HEIGHT, WIDTH, START_ROW, START_COL);

	keypad(stdscr,TRUE);
	keypad(win,TRUE);
	gameStart(win); 
	endwin();
	return 0;
}
