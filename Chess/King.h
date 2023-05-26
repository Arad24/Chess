#pragma once
#include <iostream>
#include "Solider.h"
#include "Position.h"
# include <string>
#include "Board.h"


class King : public Solider
{
public:
	// Ctor & Dtor
	King(char type, char color, Position pos);
	~King();

	// virtual functions
	virtual int checkMove(Position* to, Board* gameBoard, char turn) override;

};