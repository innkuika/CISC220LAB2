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
int checkBombNum(int n);
int** makeVisibleBoard(int);
void printVisible(int **newBoard, int n);
int placeBombs(int **newBoard, int n);
void placeCounts(int **newBoard, int n);

int main() {
	srand(time(NULL));
	int size = 0;
	int bombsfound = 0;
	getSize(size);
	cout << "Size is " << size << endl;
	int **mat = makeBoard(size);
	printBoard(mat, size); //- for testing purposes
//	placeBombs(mat,size);
//	//printBoard(mat, size); - for testing purposes
//	placeCounts(mat, size);
//	//printBoard(mat, size); - for testing purposes
//	char **visible = makeVisibleBoard(size);

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
			}else{
				 cout << newBoard[i][j] << "\t";
			}

		}
		cout << endl;
	}
}

int placeBombs(int **newBoard, int n) {
	int a, b, numOfBombs = 0;
	for (int numOfBombs = 0; numOfBombs < n; numOfBombs++) {
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

void placeCounts(int **newBoard, int n) {
	int countBombs = 0, i, j;
	int a = i - 1, b = j - 1;
	for (int i = 1; i < n; i++) {
		for (int j = 1; i < n; j++) {
			if (a > i - 1 || b > j - 1) {
				continue;
			}
			if (a + 2 > n || b + 2 > n) {
				b = b + 1;
				a++;
			}
			if (newBoard[i][j] == 9) {
				countBombs++;
			}
		}
	}
	newBoard[i][j] = countBombs;
}

int** makeVisibleBoard(int **newBoard, int n) {
	newBoard = new int*[n];
	for (int i = 0; i < n; i++) {
		newBoard[i] = new int[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			newBoard[i][j] = '-';
		}
	}

	return newBoard;
}
void printVisible(int **newBoard, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (newBoard[i][j] == 0) {
				cout << '-';
			}
		}
		cout << endl;
	}
}

