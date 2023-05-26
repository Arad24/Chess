#include "Solider.h"

Solider::Solider(char type, char color, Position pos)
{
    this->_type = type;
    this->_color = color;
    this->_position = pos;
}

Solider::~Solider()
{
    this->_type = ' ';
    this->_color = ' ';
    this->_position.~Position();
}

Solider::Solider()
{
}

char Solider::getType() const
{
    return this->_type;
}

char Solider::getColor() const
{
    return this->_color;
}

Position Solider::getPos() const
{
    return this->_position;
}

void Solider::setType(char type)
{
    this->_type = type;
}

void Solider::setColor(char color)
{
    this->_color = color;
}

void Solider::setPos(std::string position)
{
    if (position.length() != 2)
    {
        // to do: exception
    }
    else
    {
        this->_position.setX(position[0]);
        this->_position.setY(int(position[1] - '0'));
    }
}

void Solider::move(Position* to, Board* gameBoard)
{
    int source_x = int(this->getPos().getX() - a_LOC);
    int source_y = this->getPos().getY();

    int to_x = int(to->getX() - 97);
    int to_y = to->getY();

    // call Dtor
    if (gameBoard->getByPlace(to_x, to_y) != nullptr) gameBoard->getByPlace(to_x, to_y)->~Solider();

    // Move
    gameBoard->setByPlace(gameBoard->getByPlace(source_x, source_y), to_x, to_y);
    gameBoard->setByPlace(nullptr, source_x, source_y);
}


