#pragma once
#include <iostream>
#include "Solider.h"
#include "Position.h"
# include <string>
#include "Board.h"


class Pawn : public Solider
{
public:
	// Ctor & Dtor
	Pawn(char type, char color, Position pos);
	~Pawn();

	// virtual functions
	virtual int checkMove(Position* to, Board* gameBoard, char turn) override;

};