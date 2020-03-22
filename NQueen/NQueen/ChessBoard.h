#ifndef ChessBoard_H
#define ChessBoard_H

class ChessBoard {
private:
	char** boardPtr;

	int boardSize;

	bool placeQueens(int, int);

	bool isQueenAmbushed(int row, int col);
	
	int findOpenSpace(int col);

	void clearRowofN(int col);

public:
	ChessBoard();

	ChessBoard(int);

	~ChessBoard();

	void setSize(int size);

	int getSize();

	bool solve();

	void displayBoard();
};
#endif // !ChessBoard_H

