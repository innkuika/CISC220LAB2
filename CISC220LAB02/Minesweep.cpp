/*
 * Minesweeper.cpp
 *
 *  Created on: Feb 21, 2020
 *      Author: jessicawu, JinhengZhang
 *      TA's name: Lauren Olson
 */

//change k's back to 0
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

void getSize(int&);
/* Parameter: int. This int will take the input from the players.
 *
 * Return: None.
 *
 * This function uses call by reference to modify the integer input parameter to a random
 * number between 7 and 20 (not including 20). This will be the size of your board.
 */

int** makeBoard(int n);
/* Parameter: int n. It decides the length and width of the board (it's a square board).
 *
 * Return: a pointer to the matrix.
 *
 * The function is used to create an integer matrix (a 2-d array) on the heap, fill
 * matrix with 0s (that's the number, not the letter 'O').
 */

void printBoard(int **newBoard, int n);
/* Parameter: a pointer to a matrix (a 2-D function) of integers and an
 *			integer for the size (the length and the width - it's a square).
 *
 * Return: None.
 *
 * It should print out the matrix, it will print a square matrix which consists of space
 * instead of 0s as the players' view.
 */

int placeBombs(int **newBoard, int n);
/* Parameter: a pointer to the 2-D matrix of integers (the board) and an integer(the size).
 *
 * Return: 0.
 *
 * This function uses to place size + 1 "bombs" randomly on the 2-D matrix.
 * The "bomb" will be shown as number 9.
 */
void placeCounts(int **newBoard, int n);
/* Parameter: a pointer to a matrix (a 2-D function) of integers and an
 *			integer for the size (the length and the width - it's a square).
 *
 * Return: None.
 *
 * This function calculates the number of adjacent bombs for each square on the matrix and places those
 * counts on the matrix.
 */

char** makeVisibleBoard(int);
/* Parameter: an integer for the size (the length and the width - it's a square).
 *
 * Return: char.  A pointer to a matrix (a 2-D function) (player's view)
 *
 * This function will produce a 2-D matrix which is initialized to all '-'. It will used to make the view of
 * players. (Information of bombs will be hidden.)
 */

void printVisible(char **visibleBoard, int n);
/* Parameter: an integer for the size (the length and the width - it's a square).
 *
 * Return: None.
 *
 * This function will display a 2-D matrix which consists of '-'. (Information of bombs will be hidden.)
 * (player's view)
 */

bool chooseSquare(int **newBoard, char **visibleBoard, int size);

bool addBomb(char **visibleBoard, int size, int *bombsfound);
/* Parameter: a pointer to the board matrix(int), a pointer to the visible matrix (char), and the size(int).
 *
 * Return: boolean. It will show true if it the number of "bombs" equal to (size+1)
 *
 * This function allows the user to choose a square, using cout and cin to get the x and y values, respectively, and then
 * modifies that square in the visible matrix (marked as 9). Then it will increase the third
 * parameter by 1 (the pointer to the number of bombs found so far). It checks if the number of bombs
 * found is equal to the total number of bombs.
 */

void removeBomb(char **visibleBoard, int size, int *bombsfound);

bool checkForWin(int **newBoard,char **visibleBoard, int size);
void removeVisible(char **visibleBoard, int size);
void removeBoard(int **visibleBoard, int size);


int main() {
	srand(time(NULL));
	int size = 0;
	int bombsfound = 0;
	getSize(size);
	cout << "Size is " << size << endl;
	int **mat = makeBoard(size);
	//printBoard(mat, size);  - for testing purposes
	placeBombs(mat,size);
	//printBoard(mat, size);  - for testing purposes
	placeCounts(mat, size);
	//printBoard(mat, size);  - for testing purposes
	char **visible = makeVisibleBoard(size);

	/*  For testing purposes:  */
//	printVisible(visible,size);
//	chooseSquare(mat,visible,size);
//	printVisible(visible,size);
//	addBomb(visible, size, &bombsfound);
//	printVisible(visible,size);
//	removeBomb(visible, size, &bombsfound);
//	printVisible(visible,size);
//	checkForWin(mat, visible, size);
	/*  End of testing */


	char c;
	bool flag = true;
	char again = 'n';
	while (flag) {
		printVisible(visible,size);
		cout << "Choose: A for choose square, B for add Bomb, C for remove bomb: " << endl;
		cin >> c;
		if (c == 'A' || c == 'a') {
			flag = chooseSquare(mat, visible, size);
			if (!flag) {
				cout << "YOU LOSE!  YOU HIT  A BOMB!!" << endl;
				printBoard(mat, size);
				cout << "\n\nDo you want to play again?" <<endl;
				cin >> again;
			}
		}
		if (c == 'B' || c == 'b') {

			if (addBomb(visible, size, &bombsfound)) {
				cout << "Bombs found: " << bombsfound << endl;
				cout << "You appear to think you've found all the bombs" << endl;
				cout << "Choose: D for check for Win, or C for remove bomb:" << endl;
				cin >> c;
				if (c == 'D' || c == 'd') {
					if (checkForWin(mat, visible, size)) {
						cout <<"YOU WON!!!  WOO WOO!!!" << endl;
						printBoard(mat, size);
					}
					else {
						cout <<"Sorry, you were wrong.  Boo hoo." << endl;
						printBoard(mat, size);
					}
					removeBoard(mat, size);
					removeVisible(visible, size);
					bombsfound = 0;
					flag = false;
				}

				cout << "\n\nDo you want to play again? (y or n)" <<endl;
				cin >> again;

			}
		}
		if (c == 'C' || c == 'c') {
			removeBomb(visible, size, &bombsfound);
		}
		if (!flag && (again == 'y' || again == 'Y')) {
			flag = true;
			bombsfound = 0;
			getSize(size);
			cout << "Size is " << size << endl;
			mat = makeBoard(size);
			//printBoard(mat, size);  - for testing purposes
			placeBombs(mat,size);
			//printBoard(mat, size);  - for testing purposes
			placeCounts(mat, size);
			//printBoard(mat, size);  - for testing purposes
			visible = makeVisibleBoard(size);

		}
	}
	return 0;
}


void getSize(int &size) {
	size = rand() % 13 + 7;
}

int** makeBoard(int n) {
	int **newBoard = new int*[n];
	for (int i = 0; i < n; i++) {
		newBoard[i] = new int[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			newBoard[i][j] = 0;
		}
	}
	return newBoard;
}

void printBoard(int **newBoard, int n) {

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (newBoard[i][j] == 0) {
				cout << " " << "\t";
			} else {
				cout << newBoard[i][j] << "\t";
			}

		}
		cout << endl;
	}
}

int placeBombs(int **newBoard, int n) {
	int a, b;
	for (int numOfBombs = 0; numOfBombs < n + 1; numOfBombs++) {
		a = rand() % n;
		b = rand() % n;
		if (newBoard[a][b] != 9) {
			newBoard[a][b] = 9;
		} else {
			numOfBombs--;
		}
	}
	return 0;
}

int countBombs(int **newBoard, int n, int i, int j) {
	int countBombs = 0;
	int a = i - 1, b = j - 1;
	for (int k = 0; k < n + 1; k++) {
		if (a > n - 1 or b > n - 1 or a < 0 or b < 0) {
			b++;
			if (b > j + 1) {
				a++;
				b = j - 1;
			}
			continue;
		}

		if (newBoard[a][b] == 9) {
			countBombs++;
		}

		b++;
		if (b > j + 1) {
			a++;
			b = j - 1;
		}

	}

	return countBombs;
}
void placeCounts(int **newBoard, int n) {

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {

			if (newBoard[i][j] != 9) {
				newBoard[i][j] = countBombs(newBoard, n, i, j);
			}

		}
	}
}

char** makeVisibleBoard(int n) {
	char **visibleBoard = new char*[n];
	for (int i = 0; i < n; i++) {
		visibleBoard[i] = new char[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visibleBoard[i][j] = '-';
		}
	}

	return visibleBoard;
}
void printVisible(char **newBoard, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << newBoard[i][j] << "\t";
		}
		cout << endl;
	}
}

bool chooseSquare(int **newBoard, char **visibleBoard, int size) {
	bool isNotBoom = true;
	int x = -1, y = -1;

	while (x < 0 or x >= size or y < 0 or y >= size) {
		cout << "Choose square x (between 0 and " << size << ")" << endl;
		cin >> x;
		cout << "Choose square y (between 0 and " << size << ")" << endl;
		cin >> y;

		if (x >= 0 and x < size and y >= 0 and y < size) {
			break;
		}
		cout << "Invalid square, try again:" << endl;
	}
	//*******************************************************
	visibleBoard[x][y] = newBoard[x][y] + '0';
	if (newBoard[x][y] == 9) {
		isNotBoom = false;
	}
	return isNotBoom;
}

bool addBomb(char **visibleBoard, int size, int *bombsfound) {
	bool allBombsFound = false;

	int x = -1, y = -1;

	while (x < 0 or x >= size or y < 0 or y >= size) {
		cout << "Choose square x (between 0 and " << size << ")" << endl;
		cin >> x;
		cout << "Choose square y (between 0 and " << size << ")" << endl;
		cin >> y;

		if (x >= 0 and x < size and y >= 0 and y < size) {
			break;
		}
		cout << "Invalid square, try again:" << endl;
	}
	visibleBoard[x][y] = 'X';

	*bombsfound += 1;

	if (size + 1 == *bombsfound)
		allBombsFound = true;
	return allBombsFound;
}

void removeBomb(char **visibleBoard, int size, int *bombsfound) {
	int x = -1, y = -1;

	while (x < 0 or x >= size or y < 0 or y >= size) {
		cout << "Choose square x (between 0 and " << size << ")" << endl;
		cin >> x;
		cout << "Choose square y (between 0 and " << size << ")" << endl;
		cin >> y;

		if (x >= 0 and x < size and y >= 0 and y < size) {
			break;
		}
		cout << "Invalid square, try again:" << endl;
	}
	if (visibleBoard[x][y] == 'X') {
		visibleBoard[x][y] = '-';
		*bombsfound -= 1;
	}
}
bool checkForWin(int **newBoard,char **visibleBoard, int size){

	bool winGame = true;
	for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if(newBoard[i][j]== 9 && visibleBoard[i][j]== 'X'){
					continue;
			}else{
				winGame = false;
				break;
			}
			cout << endl;
		}
	}
	return winGame;
}

void removeBoard(int **visibleBoard, int size){
	for(int i = 0; i < size; i++){
		delete []visibleBoard[i];

	}
}
void removeVisible(char **visibleBoard, int size){
	for(int i = 0; i < size; i++){
		delete []visibleBoard[i];

	}
}





