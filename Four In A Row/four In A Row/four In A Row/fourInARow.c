#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
const int FOUR = 4;
#define ROWS 6
#define COLS 7
char board[ROWS][COLS];

/// This function initializes the game board by assigning each cell
/// with ' ' (resulting with an empty game board).
void initBoard();

/// This function gets a row number and a column number (a cell),
/// and returns the character in that cell (could be 'X', 'O' or ' ').
/// For example:
/// char c = getCell(1, 1);
char getCell(int row, int col);

/// This function gets a row number, a column number and a sign,
/// and assigns the cell with the given sign.
/// For example:
/// setCell(1, 1, 'X');
void setCell(int row, int col, char sign);

/// This function clears the screen.
void clearScreen();

//מדפיסה את לוח המשחק כולו
void printGameBoard();

// פונקציה שבודקת אם יש 4 בטור וגם מעדכנת את המשתנים שמתייחסים לניצחון של השחקנים
bool checkForFourInACol(bool* victoriPlayer1, bool* victoriPlayer2);

//פונקציה שבודקת אש יש 4 בשורה וגם מעדכנת את המשתנים שמתייחסים לניצחון של השחקנים
bool checkForFourInARow(bool* victoriPlayer1, bool* victoriPlayer2);

//פונקציה שבודקת אם יש 4 באלכסון עולה חלק ראשון וגם מעדכנת את המשתנים שמתייחסים לניצחון של השחקנים
bool checkForFourInAUpwardDiagonalPartOne(bool* victoriPlayer1, bool* victoriPlayer2);

//פונקציה שבודקת אם יש 4 באלכסון עולה חלק שני וגם מעדכנת את המשתנים שמתייחסים לניצחון של השחקנים
bool checkForFourInAUpwardDiagonalPartTwo(bool* victoriPlayer1, bool* victoriPlayer2);

//פונקציה שבודקת אם יש 4 באלכסון יורד חלק ראשון וגם מעדכנת את המשתנים שמתייחסים לניצחון של השחקנים
bool checkForFourInADownwardDiagonalPartOne(bool* victoriPlayer1, bool* victoriPlayer2);

//פונקציה שבודקת אם יש 4 באלכסון יורד חלק שני וגם מעדכנת את המשתנים שמתייחסים לניצחון של השחקנים
bool checkForFourInADownwardDiagonalPartTwo(bool* victoriPlayer1, bool* victoriPlayer2);

int main()
{
	int count, cHelp, rHelp; //משתני עזר
	int gameStageNumber = 0, columnInput;
	bool  finish = false, fullcolumn, victoriPlayer1 = false, victoriPlayer2 = false;
	void initBoard();
	while (finish == false)
	{
		printGameBoard();
		printf("\n");
		if (gameStageNumber % 2 == 0)				//שחקן ראשון משחק כל איטראציה זוגית
			printf("Player number %d:\n", 1);
		else									//שחקן שני משחק כל איטראציה אי זוגית
			printf("Player number %d:\n", 2);
		printf("Please enter column input (a number between 1-7):");
		scanf("%d", &columnInput);

		if (getCell(1 + 1, columnInput + 1) == 'X' || getCell(1 + 1, columnInput + 1) == 'O')
			fullcolumn = true;
		else
			fullcolumn = false;

		while (columnInput > 7 || columnInput < 1 || fullcolumn)//דואג לטור מלא ולטור שלא בטווח המחשק
		{
			if (fullcolumn)
				printf("The col you entered is full.\n");
			printf("Please enter column input (a number between 1-7):");
			scanf("%d", &columnInput);
			if (getCell(2, columnInput + 1) == 'X' || getCell(2, columnInput + 1) == 'O')
				fullcolumn = true;
			else
				fullcolumn = false;
		}

		for (rHelp = ROWS; rHelp >= 1; rHelp--)//עדכון המטריצה והוספת הסימן
		{
			if (getCell(rHelp + 1, columnInput + 1) != 'X' && getCell(rHelp + 1, columnInput + 1) != 'O')
			{
				if (gameStageNumber % 2 == 0)
				{
					setCell(rHelp + 1, columnInput + 1, 'X');

				}
				else
				{
					setCell(rHelp + 1, columnInput + 1, 'O');

				}
				break;
			}
		}
		//בדיקות
		if (checkForFourInACol(&victoriPlayer1, &victoriPlayer2))
			break;

		if (checkForFourInARow(&victoriPlayer1, &victoriPlayer2))
			break;

		if (checkForFourInAUpwardDiagonalPartOne(&victoriPlayer1, &victoriPlayer2))
			break;

		if (checkForFourInAUpwardDiagonalPartTwo(&victoriPlayer1, &victoriPlayer2))
			break;

		if (checkForFourInADownwardDiagonalPartOne(&victoriPlayer1, &victoriPlayer2))
			break;

		if (checkForFourInADownwardDiagonalPartTwo(&victoriPlayer1, &victoriPlayer2))
			break;
		count = 0;		//עוזר לבדוק אם כל העמודות תפוסות
		for (cHelp = 1; cHelp <= COLS; cHelp++)//דואג ללוח מלא
		{
			if (getCell(1 + 1, cHelp + 1) == 'X' || getCell(1 + 1, cHelp + 1) == 'O')
				count++;
			if (count == COLS)
				finish = true;
		}

		gameStageNumber++;
		clearScreen();
	}

	clearScreen();
	printGameBoard();

	if (victoriPlayer1)
		printf("player 1 won!\nplayer 2 maybe next time.\n");
	else if (victoriPlayer2)
		printf("player 2 won!\nplayer 1 maybe next time.\n");
	else if (finish)
		printf("we have a tie score here!\n");
}
//--------------------------------------------------------------------פונקציות עזר-----------


void printGameBoard()
{
	int rHelp, cHelp;
	for (rHelp = 0; rHelp <= ROWS; rHelp++)
	{
		for (cHelp = 0; cHelp <= COLS; cHelp++)
		{
			if (cHelp == 0 && rHelp == 0)
			{
				printf(" ");
				printf(" ");
				cHelp++;

			}
			if (rHelp == 0)
				printf("%d ", cHelp);
			else
			{
				if (cHelp == 0)
					printf("%c ", 'A' + rHelp - 1);   //דואג לטווים בשורה של המשחק
				else
				{
					char cell = getCell(rHelp + 1, cHelp + 1);
					if(cell == 0)
						printf(" ");
					else
						printf("%c", cell);    //דואג למטריצה של המשחק board
					printf(" ");
				}
			}
		}
		printf("\n");
	}
}


bool checkForFourInACol(bool* victoriPlayer1, bool* victoriPlayer2)
{
	int cHelp, rHelp, i, j;

	for (cHelp = 1; cHelp <= COLS; cHelp++)
	{
		i = 0;
		j = 0;
		for (rHelp = ROWS; rHelp >= 1; rHelp--)
		{
			if (getCell(rHelp + 1, cHelp + 1) == 'X')
			{
				i++;
				j = 0;
			}
			if (getCell(rHelp + 1, cHelp + 1) == 'O')
			{
				j++;
				i = 0;
			}
			if (i == FOUR)
			{
				*victoriPlayer1 = true;
				break;
			}
			if (j == FOUR)
			{
				*victoriPlayer2 = true;
				break;
			}
		}
		if (*victoriPlayer1 || *victoriPlayer2)
			break;
	}
	if (*victoriPlayer1 || *victoriPlayer2)	// בדיקה של ניצחון	
		return true;
	return false;
}


bool checkForFourInARow(bool* victoriPlayer1, bool* victoriPlayer2)
{
	int i, j, cHelp, rHelp;

	for (rHelp = ROWS; rHelp >= 1; rHelp--)
	{
		i = 0;
		j = 0;
		for (cHelp = 1; cHelp <= COLS; cHelp++)
		{
			if (getCell(rHelp + 1, cHelp + 1) == 'X')
			{
				i++;
				j = 0;
			}
			else if (getCell(rHelp + 1, cHelp + 1) == 'O')
			{
				j++;
				i = 0;
			}
			else
			{
				j = 0;
				i = 0;
			}

			if (i == FOUR)
			{
				*victoriPlayer1 = true;
				break;
			}
			if (j == FOUR)
			{
				*victoriPlayer2 = true;
				break;
			}
		}
		if (*victoriPlayer1 || *victoriPlayer2)
			break;
	}
	if (*victoriPlayer1 || *victoriPlayer2) // בדיקה של ניצחון
		return true;
	return false;
}


bool checkForFourInAUpwardDiagonalPartOne(bool* victoriPlayer1, bool* victoriPlayer2)
{
	int i, j, h, rHelp, cHelp;

	for (rHelp = 4; rHelp <= 7; rHelp++)
	{
		i = 0;
		j = 0;
		h = 1;
		for (cHelp = 1; cHelp < rHelp; cHelp++)
		{
			if (getCell(rHelp + 1 - h, cHelp + 1) == 'X')
			{
				i++;
				j = 0;
			}
			else if (getCell(rHelp + 1 - h, cHelp + 1) == 'O')
			{
				j++;
				i = 0;

			}
			else
			{
				i = 0;
				j = 0;
			}
			h++;
			if (i == FOUR)
			{
				*victoriPlayer1 = true;
				break;
			}
			if (j == FOUR)
			{
				*victoriPlayer2 = true;
				break;
			}
		}
		if (*victoriPlayer1 || *victoriPlayer2)
			break;
	}
	if (*victoriPlayer1 || *victoriPlayer2) // בדיקה של ניצחון
		return true;
	return false;
}


bool checkForFourInAUpwardDiagonalPartTwo(bool* victoriPlayer1, bool* victoriPlayer2)
{
	int i, j, h, cHelp, rHelp;

	for (cHelp = 2; cHelp <= 4; cHelp++)
	{
		i = 0;
		j = 0;
		h = 0;
		for (rHelp = ROWS; rHelp >= cHelp - 1; rHelp--)
		{
			if (getCell(rHelp + 1, cHelp + 1 + h) == 'X')
			{
				i++;
				j = 0;
			}
			else if (getCell(rHelp + 1, cHelp + 1 + h) == 'O')
			{
				j++;
				i = 0;
			}
			else
			{
				i = 0;
				j = 0;
			}
			h++;
			if (i == FOUR)
			{
				*victoriPlayer1 = true;
				break;
			}
			if (j == FOUR)
			{
				*victoriPlayer2 = true;
				break;
			}
		}
		if (*victoriPlayer1 || *victoriPlayer2)
			break;
	}
	if (*victoriPlayer1 || *victoriPlayer2)// בדיקה של ניצחון
		return true;
	return false;
}


bool checkForFourInADownwardDiagonalPartOne(bool* victoriPlayer1, bool* victoriPlayer2)
{
	int i, j, h, cHelp, rHelp;

	for (rHelp = 1; rHelp <= 3; rHelp++)
	{
		i = 0;
		j = 0;
		h = 0;
		for (cHelp = 1; cHelp <= COLS - rHelp; cHelp++)
		{

			if (getCell(rHelp + 1 + h, cHelp + 1) == 'X')
			{
				i++;
				j = 0;
			}
			else if (getCell(rHelp + 1 + h, cHelp + 1) == 'O')
			{
				j++;
				i = 0;
			}
			else
			{
				i = 0;
				j = 0;
			}
			h++;
			if (i == FOUR)
			{
				*victoriPlayer1 = true;
				break;
			}
			if (j == FOUR)
			{
				*victoriPlayer2 = true;
				break;
			}
		}
		if (*victoriPlayer1 || *victoriPlayer2)
			break;
	}
	if (*victoriPlayer1 || *victoriPlayer2)//בדיקה של ניצחון
		return true;
	return false;
}


bool checkForFourInADownwardDiagonalPartTwo(bool* victoriPlayer1, bool* victoriPlayer2)
{
	int i, j, h, cHelp, rHelp;

	for (cHelp = 2; cHelp <= 4; cHelp++)
	{
		i = 0;
		j = 0;
		h = 0;
		for (rHelp = 1; rHelp <= COLS - cHelp + 1; rHelp++)
		{

			if (getCell(rHelp + 1, cHelp + 1 + h) == 'X')
			{
				i++;
				j = 0;
			}
			else if (getCell(rHelp + 1, cHelp + 1 + h) == 'O')
			{
				j++;
				i = 0;
			}
			else
			{
				i = 0;
				j = 0;
			}
			h++;
			if (i == FOUR)
			{
				*victoriPlayer1 = true;
				break;
			}
			if (j == FOUR)
			{
				*victoriPlayer2 = true;
				break;
			}
		}
		if (*victoriPlayer1 || *victoriPlayer2)
			break;
	}
	if (*victoriPlayer1 || *victoriPlayer2)// בדיקה של ניצחון
		return true;
	return false;
}


char getCell(int row, int col)
{
	return board[row - 1][col - 1];
}


void setCell(int row, int col, char sign)
{
	board[row - 1][col - 1] = sign;
}


void initBoard()
{
	int i, j;

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			setCell(i + 1, j + 1, ' ');
		}
	}
}


void clearScreen()
{
	system("cls");
}