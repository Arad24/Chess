#pragma once
#include <iostream>
#include "Solider.h"
#include "Position.h"
# include <string>
#include "Board.h"


class Bishop : public Solider
{
public:
	// Ctor & Dtor
	Bishop(char type, char color, Position pos);
	~Bishop();

	// virtual functions
	virtual int checkMove(Position* to, Board* gameBoard, char turn) override;

};