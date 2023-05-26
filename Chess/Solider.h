#pragma once
#include <string>
#include <iostream>
#include "Position.h"
#include "Board.h"

# define V_MOVE 0
# define V_CHECK_MOVE 1
# define UV_UNEXIST_SOURCE_SOLIDER 2
# define UV_FRIENDLY_FIRE 3
# define UV_SELF_CHECK 4
# define UV_INDEX 5
# define UV_MOVE 6
# define UV_SAME_INDEX 7
# define V_CHECKMATE 8 // bonus

class Board;

class Solider
{
private:

	char _type;
	char _color;
	Position _position;

public:

	// Getters
	char getType() const;
	char getColor() const;
	Position getPos() const;
	
	// Setters
	void setType(char type);
	void setColor(char color);
	void setPos(std::string position);
	
	//virtual
	virtual int checkMove(Position* to, Board* gameBoard, char turn) = 0;
	
	void move(Position* to, Board* gameBoard);

	// Ctor & Dtor
	Solider(char type, char color, Position pos) ;
	virtual ~Solider() = 0;
	Solider();
};
