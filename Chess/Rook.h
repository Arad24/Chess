#pragma once
# include "Solider.h"
# include "Position.h"
# include "Board.h"
# include <iostream>
# include <string>

# define MAX_UP		8
# define MAX_DOWN	0
# define MAX_RIGHT  8
# define MAX_LEFT	0

class Rook : public Solider
{
public:
	// Ctor & Dtor
	Rook(char type, char color, Position pos);
	~Rook();

	// Override functions
	//bool isValidMove() override;
	virtual int checkMove(Position* to, Board* gameBoard, char turn) override;
};
