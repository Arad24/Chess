# include "Position.h"
class Position;
// Ctor & Dtor
Position::Position(char x, int y)
{
    this->_x = x;
    this->_y = y;
}

Position::~Position()
{
    this->_x = ' ';
    this->_y = 0;
}

Position::Position()
{
}

// Getters
char Position::getX() const
{
    return this->_x;
}

int Position::getY() const
{
    return this->_y;
}

// Setters
void Position::setX(char x)
{
    this->_x = x;
}

void Position::setY(int y)
{
    this->_y = y;
}

