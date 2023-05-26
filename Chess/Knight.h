#pragma once
#include <iostream>
#include "Solider.h"
#include "Position.h"
# include <string>
#include "Board.h"


class Knight : public Solider
{
public:
	// Ctor & Dtor
	Knight(char type, char color, Position pos);
	~Knight();

	// virtual functions
	virtual int checkMove(Position* to, Board* gameBoard, char turn) override;

};