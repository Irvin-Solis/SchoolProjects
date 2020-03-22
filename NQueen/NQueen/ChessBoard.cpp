#include "ChessBoard.h"
#include<iostream>

ChessBoard::ChessBoard() : boardSize(8), boardPtr(nullptr) {
	boardPtr = new char* [boardSize];
	for (int i = 0; i < boardSize; i++) {
		boardPtr[i] = new char[boardSize];
		for (int j = 0; j < boardSize; j++)
		{
			boardPtr[i][j] = '*'; // * for openSpace
		}
	}
}

ChessBoard::ChessBoard(int size) {
	int newSize = size;
	if (size < 4) {
		newSize = 4;
	}
	if (size > 12) {
		newSize = 12;
	}
	boardSize = newSize;
	boardPtr = new char* [newSize];
	for (int i = 0; i < newSize; i++) {
		boardPtr[i] = new char[newSize];
		for (int j = 0; j < newSize; j++)
		{
			boardPtr[i][j] = '*'; // * for openSpace
		}
	}
}

ChessBoard::~ChessBoard() {
	for (int i = 0; i != boardSize; ++i) {
		delete[] boardPtr[i];
	}
	delete[] boardPtr;
}

void ChessBoard::setSize(int size) {
	//delete existing array
	for (int i = 0; i != boardSize; ++i) {
		delete[] boardPtr[i];
	}
	delete[] boardPtr;
	int newSize = size;
	if (size < 4) {
		newSize = 4;
	}
	if (size > 12) {
		newSize = 12;
	}
	boardSize = newSize;
	boardPtr = new char* [newSize];
	for (int i = 0; i != newSize; i++) {
		boardPtr[i] = new char[newSize];
		for (int j = 0; j != newSize; j++)
		{
			boardPtr[i][j] = '*'; // * for openSpace
		}
	}
}

int ChessBoard::getSize() {
	return boardSize;
}
void ChessBoard::displayBoard() {
	for (int i = 0; i != boardSize; i++) {

		for (int j = 0; j != boardSize; j++)
		{
			if (boardPtr[i][j] == 'N') {
				std::cout << '*';
			}
			else {
				std::cout << boardPtr[i][j];
			}
		}
		std::cout << "\n";
	}
}

bool ChessBoard::solve() {
	return placeQueens(0, 0);
}

bool ChessBoard::isQueenAmbushed(int row, int col) {
	 
	//look for a queen to your left
	for (int i = 0; i < col; i++) {
		if (boardPtr[row][i] == 'Q') {
			return true;
		}
	}

	//look for queens to your upper diagonal
	for (int i = row, j = col; (i >= 0) && (j >= 0); i--, j--) {
		if (boardPtr[i][j] == 'Q') {
			return true;
		}
	}

	// look for queens to your lower diagonal
	for (int i = row, j = col; (j >= 0) && (i < boardSize); i++, j--) {
		if (boardPtr[i][j] == 'Q') {
			return true;
		}
	}

	return false;
	
}

int ChessBoard::findOpenSpace(int col) {
	for (int i = 0; i < boardSize; i++)
	{
		if (!isQueenAmbushed(i, col) && boardPtr[i][col] != 'N') {
			return i;
		}
	}
	return -1;
}

void ChessBoard::clearRowofN(int col) {
	for (int i = 0; i < boardSize; i++)
	{
		if (boardPtr[i][col] == 'N') {
			boardPtr[i][col] = '*';
		}
	}
}

bool ChessBoard::placeQueens(int row, int column) {
	if (column >= boardSize)
	{
		return true;
	} // end if
	else
	{
		
		int unconsideredRow = boardSize - row;
		while (unconsideredRow != 0)
		{
			int openRow = findOpenSpace(column);
			clearRowofN(column + 1);
			if (openRow != -1) { //if that spot is not under fire
				boardPtr[openRow][column] = 'Q';

				if (!placeQueens(row, column + 1)) {
					boardPtr[openRow][column] = 'N'; // removed last placed queen and put N in its place, to look for next available open spot
					row++;

				}
				else {
					return true; // queens were succesfully placed
				}
			}
			else {
				clearRowofN(column + 1);
				return false; //backtrack
			}

		} // end while
		clearRowofN(column + 1);
		return false; //backtrack
	} // end else
} // end placeQueens()