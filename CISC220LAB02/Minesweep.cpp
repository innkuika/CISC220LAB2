/*
 * Minesweeper.cpp
 *
 *  Created on: Feb 21, 2020
 *      Author: jessicawu, JinhengZhang
 *      TA's name: Lauren Olson
 */
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

void getSize(int&);
int** makeBoard(int n);
void printBoard(int **newBoard, int n);
int checkBombNum(int n);
void printVisible(int **newBoard, int n);

int main() {
	srand (time(NULL));int size = 0;
	int bombsfound = 0;
	getSize(size);
	cout << size;
	//Part2
	int n;
	int x= **makeBoard(n);
	//Bug need to be fixed: cannot convert ‘int*’ to ‘int**’
	printBoard(&makeBoard(n),n);
}

void getSize(int &size) {
	size = rand() % 13 + 7;
}

int** makeBoard(int n) {
	int **newBoard = NULL;
	newBoard = new int*[n];
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
				cout << " ";
			}
		}
		cout << endl;
	}
}

int placeBomb(int **newBoard, int n) {
	int a, b, numOfBombs = 0;
	for (int numOfBombs = 0; numOfBombs < n; numOfBombs++) {
		a = rand % n;
		b = rand % n;
		if (newBoard[a][b] != 9) {
			newBoard[a][b] = 9;
		} else {
			numOfBombs--;
		}
	}
	return 0;
}

void placeCounts(int **newBoard, int n) {
	int countBombs = 0;
	int a = i - 1, b = j - 1;
	for (int i = 1; i < n; i++) {
		for (int j = 1; i < n; j++) {
			if (a > size - 1 || b > size - 1) {
				continue;
			}
			if (a + 2 > n || b + 2 > n) {
				b = b + 1;
				a++;
			}
			if (**newBoard[i][j] == 9) {
				countBombs++;
			}
		}
	}
	**newBoard[i][j] = countBombs;
}

int** makeVisibleBoard(int n) {
	int **newBoard = NULL;
	newBoard = new int*[n];
	for (int i = 0; i < n; i++) {
		newBoard[i] = new int[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			newBoard[i][j] = "-";
		}
	}

	return newBoard;
}

void printVisible(int **newBoard, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (newBoard[i][j] == 0) {
			cout <<;
		}
	}
	cout << endl;
}

}
int chooseSquare(,,int n) {

}
