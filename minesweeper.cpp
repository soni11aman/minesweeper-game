#include<bits/stdc++.h> 
using namespace std; 
#define ll long long
#define vi vector<ll> 
#define vii vector<vi> 
#define BEGINNER 0 
#define INTERMEDIATE 1 
#define ADVANCED 2 
#define MAXSIDE 25 
#define MAXMINES 99 
#define MOVESIZE 526
const ll mod=1e9+7;
const ll nmod=998244353;
int SIDE ;
int MINES ;

bool isValid(int row, int col) 
{ 
	// Returns true if row number and column number 
	// is in range 
	return (row >= 0) && (row < SIDE) && 
		(col >= 0) && (col < SIDE); 
} 

// A Function to print the current gameplay board 
void printBoard(char myBoard[][MAXSIDE]) 
{ 
	int i, j; 

	cout<<"  ";

	for (i=0; i<SIDE; i++) 
		cout<<i<<" ";

	cout<<"\n";

	for (i=0; i<SIDE; i++) 
	{ 
		cout<<i<<" ";

		for (j=0; j<SIDE; j++) 
			cout<<myBoard[i][j]<<" "; 
		cout<<'\n';
	} 
	return; 
} 

// this Function  count the number of 
// mines in the adjacent cells 
int countAdjacentMines(int row, int col, int mines[][2], 
					char realBoard[][MAXSIDE]) 
{ 
	// isvalid function checks only
	// those places which are valid
	int count = 0; 

		// North neighbour 
		if (isValid (row-1, col) == true) 
		{ 
			if (realBoard[row-1][col] == '*') 
			count++; 
		} 


		//South neighbour 
		if (isValid (row+1, col) == true) 
		{ 
			if (realBoard[row+1][col] == '*') 
			count++; 
		} 
 

		//East neighbour 
		if (isValid (row, col+1) == true) 
		{ 
			if (realBoard[row][col+1] == '*') 
			count++; 
		} 
 

		//West neighbour 
		if (isValid (row, col-1) == true) 
		{ 
			if (realBoard[row][col-1] == '*') 
			count++; 
		} 
 

		//N.E neighbour 
		if (isValid (row-1, col+1) == true) 
		{ 
			if (realBoard[row-1][col+1] == '*') 
			count++; 
		} 
 

		//N.W neighbour 
		if (isValid (row-1, col-1) == true) 
		{ 
			if (realBoard[row-1][col-1] == '*') 
			count++; 
		} 


		//S.E neighbour 
		if (isValid (row+1, col+1) == true) 
		{ 
			if (realBoard[row+1][col+1] == '*') 
			count++; 
		} 
 

		//S.W neighbour 
		if (isValid (row+1, col-1) == true) 
		{ 
			if (realBoard[row+1][col-1] == '*') 
			count++; 
		} 

	return (count); 
} 

bool playMinesweeperUtil(char myBoard[][MAXSIDE], char realBoard[][MAXSIDE], 
			int mines[][2], int row, int col, int *movesLeft) 
{ 
	if (myBoard[row][col] != '-') 
		return (false); 

	int i, j; 

	// You opened a mine 
	// You are going to lose 
	if (realBoard[row][col] == '*') 
	{ 
		myBoard[row][col]='*'; 

		for (i=0; i<MINES; i++) 
			myBoard[mines[i][0]][mines[i][1]]='*'; 

		printBoard (myBoard); 
		cout<<"\n You Lost\n";
		return (true) ; 
	} 

	else
	{ 
		// Calculate the number of adjacent mines and put it 
		// on the board 
		int count = countAdjacentMines(row, col, mines, realBoard); 
		(*movesLeft)--; 

		myBoard[row][col] = count + '0'; 
		// if count is 0 then check all neighbour elements
		if (!count) 
		{
 
			if (isValid (row-1, col) == true) 
			{ 
				if (realBoard[row-1][col] != '*') 
				playMinesweeperUtil(myBoard, realBoard, mines, row-1, col, movesLeft); 
			} 

			if (isValid (row+1, col) == true) 
			{ 
				if (realBoard[row+1][col] != '*') 
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col, movesLeft); 
			} 
 
			if (isValid (row, col+1) == true) 
			{ 
				if (realBoard[row][col+1] != '*') 
					playMinesweeperUtil(myBoard, realBoard, mines, row, col+1, movesLeft); 
			} 
 
			if (isValid (row, col-1) == true) 
			{ 
				if (realBoard[row][col-1] != '*') 
					playMinesweeperUtil(myBoard, realBoard, mines, row, col-1, movesLeft); 
			} 

			if (isValid (row-1, col+1) == true) 
			{ 
				if (realBoard[row-1][col+1] != '*') 
					playMinesweeperUtil(myBoard, realBoard, mines, row-1, col+1, movesLeft); 
			} 

			if (isValid (row-1, col-1) == true) 
			{ 
				if (realBoard[row-1][col-1] != '*') 
					playMinesweeperUtil(myBoard, realBoard, mines, row-1, col-1, movesLeft); 
			} 

			if (isValid (row+1, col+1) == true) 
			{ 
				if (realBoard[row+1][col+1] != '*') 
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col+1, movesLeft); 
			} 

			if (isValid (row+1, col-1) == true) 
			{ 
				if (realBoard[row+1][col-1] != '*') 
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col-1, movesLeft); 
			} 
		} 

		return (false); 
	} 
} 

// A Function to place the mines randomly 
// on the board 
void placeMines(int mines[][2], char realBoard[][MAXSIDE]) 
{ 
	bool mark[MAXSIDE*MAXSIDE]; 

	memset (mark, false, sizeof (mark)); 

	// Continue until all random mines have been created. 
	for (int i=0; i<MINES; ) 
	{ 
		int random = rand() % (SIDE*SIDE); 
		int x = random / SIDE; 
		int y = random % SIDE; 

		// Add the mine if no mine is placed at this 
		// position on the board 
		if (mark[random] == false) 
		{ 
			// Row Index of the Mine 
			mines[i][0]= x; 
			// Column Index of the Mine 
			mines[i][1] = y; 

			// Place the mine 
			realBoard[mines[i][0]][mines[i][1]] = '*'; 
			mark[random] = true; 
			i++; 
		} 
	} 

	return; 
} 

// A Function to initialise the game 
void initialise(char realBoard[][MAXSIDE], char myBoard[][MAXSIDE]) 
{ 
	// Initiate the random number generator so that 
	// the same configuration doesn't arises 
	srand(time (NULL)); 

	// Assign all the cells as mine-free 
	for (int i=0; i<SIDE; i++) 
	{ 
		for (int j=0; j<SIDE; j++) 
		{ 
			myBoard[i][j] = realBoard[i][j] = '-'; 
		} 
	} 
	return; 
} 

// A function to replace the mine from (row, col) and put 
// it to a vacant space 
void replaceMine (int row, int col, char board[][MAXSIDE]) 
{ 
	for (int i=0; i<SIDE; i++) 
	{ 
		for (int j=0; j<SIDE; j++) 
			{ 
				// Find the first location in the board 
				// which is not having a mine and put a mine 
				// there. 
				if (board[i][j] != '*') 
				{ 
					board[i][j] = '*'; 
					board[row][col] = '-'; 
					return; 
				} 
			} 
	} 
	return; 
} 

// A Function to play Minesweeper game 
void playMinesweeper () 
{ 
	// Initially the game is not over 
	bool gameOver = false; 

	char realBoard[MAXSIDE][MAXSIDE], myBoard[MAXSIDE][MAXSIDE]; 

	int movesLeft = SIDE * SIDE - MINES, x, y; 
	int mines[MAXMINES][2]; // stores (x,y) coordinates of all mines. 

	initialise (realBoard, myBoard); 

	// Place the Mines randomly 
	placeMines (mines, realBoard); 


	// You are in the game until you have not opened a mine 

	int currentMoveIndex = 0; 
	while (gameOver == false) 
	{ 
		cout<<"Current Status of Board : \n"; 
		printBoard (myBoard); 
		cout<<"Enter your move, (row, column) -> "; 
		cin>>x>>y; 
		// This is to guarantee that the first move is 
		// always safe 
		// If it is the first move of the game 
		if (currentMoveIndex == 0) 
		{ 
			// If the first move itself is a mine 
			// then we remove the mine from that location 
			if (realBoard[x][y] == '*') 
				replaceMine (x, y, realBoard); 
		} 

		currentMoveIndex = 1; 

		gameOver = playMinesweeperUtil (myBoard, realBoard, mines, x, y, &movesLeft); 

		if ((gameOver == false) && (movesLeft == 0)) 
		{ 
			printf ("\nYou won !\n"); 
			gameOver = true; 
		} 
	} 
	return; 
} 

bool chooseDifficultyLevel () 
{	
	int lvl; 
	cout<<"Enter the Difficulty Level\n"; 
	cout<<"Press 0 for BEGINNER (9 * 9 Cells and 10 Mines)\n"; 
	cout<<"Press 1 for INTERMEDIATE (16 * 16 Cells and 40 Mines)\n"; 
	cout<<"Press 2 for ADVANCED (24 * 24 Cells and 99 Mines)\n";
	cin>>lvl;
	
	if (lvl == BEGINNER) 
	{ 
		SIDE = 9; 
		MINES = 10; 
		return true;
	} 

	if (lvl == INTERMEDIATE) 
	{ 
		SIDE = 16; 
		MINES = 40; 
		return true;
	} 
	
	if (lvl == ADVANCED) 
	{ 
		SIDE = 24; 
		MINES = 99; 
		return true;
	}
	return false; 
}
int main() 
{ 
	// choose level of difficulty
	if(!chooseDifficultyLevel() )
	{
		cout<<"Please select a correct level..!!";
		return 0;
	}
	playMinesweeper ();
	return (0); 
}

