#pragma once
#include <iostream>
#include "Solider.h"
#include "Position.h"
# include <string>
#include "Board.h"


class Queen : public Solider
{
public:
	// Ctor & Dtor
	Queen(char type, char color, Position pos);
	~Queen();

	// virtual functions
	virtual int checkMove(Position* to, Board* gameBoard, char turn) override;

};