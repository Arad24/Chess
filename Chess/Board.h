#pragma once
# include <iostream>
# include <string>
# include "Solider.h"

# define BOARD_LEN 8
# define a_LOC  97
# define PAWN	'p'
# define ROOK	'r'
# define KNIGHT 'n'
# define BISHOP 'b'
# define QUEEN  'q'
# define KING	'k'
# define NULL_SIGN "#"

class Solider;

class Board
{
public:
	// Ctor & Dtor
	Board(Board& board);
	Board(std::string boardStr);
	~Board();

	

	// Getters
	Solider* getByPlace(int i, int j) const;
	void clone(Board& board);
	std::string getBoardString();

	// Setters
	void setByPlace(Solider* s, int i, int j);
	void setBoard(Solider* board[BOARD_LEN][BOARD_LEN]);

	/*
		Checks if the king is in check.
		color: The color of the king.
	*/
	bool isCheck(char color);
	bool isClearVertical(Position* from, Position* to);
	bool isClearHorizontal(Position* from, Position* to);
	bool isClearDiagonal(Position* from, Position* to);
	

	Solider* _wKing;
	Solider* _bKing;
private:
	Solider* _gameBoard[BOARD_LEN][BOARD_LEN];
};
