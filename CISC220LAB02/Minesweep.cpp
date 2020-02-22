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
int** makeBoard(int n);
void printBoard(int **newBoard, int n);

void printVisible(char **newBoard, int n);
int placeBombs(int **newBoard, int n);
void placeCounts(int **newBoard, int n);
char** makeVisibleBoard(int);
void printVisible(char **visibleBoard, int n);
bool chooseSquare(int **newBoard, char **visibleBoard, int size);
bool addBomb(char **visibleBoard, int size, int *bombsfound);
void removeBomb(char **visibleBoard, int size, int *bombsfound);

int main() {
	srand(time(NULL));
	int size = 0;
	int bombsfound = 0;
	getSize(size);
	cout << "Size is " << size << endl;
	int **mat = makeBoard(size);
	//printBoard(mat, size);
	//- for testing purposes
	placeBombs(mat, size);
	//printBoard(mat, size);
	//- for testing purposes
	placeCounts(mat, size);
	//printBoard(mat, size);
	//- for testing purposes
	char **visible = makeVisibleBoard(size);

	printVisible(visible, size);

	chooseSquare(mat, visible, size);
	cout << bombsfound << endl;
	printVisible(visible, size);

	addBomb(visible, size, &bombsfound);
	cout << bombsfound << endl;
	printVisible(visible, size);

	removeBomb(visible, size, &bombsfound);
	cout << bombsfound << endl;
	printVisible(visible, size);
//	checkForWin(mat, visible, size);

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
				cout << "k" << "\t";
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

