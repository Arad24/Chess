#include "King.h"

King::King(char type, char color, Position pos) : Solider(type, color, pos)
{
}

King::~King()
{
	Solider::~Solider();
}

int King::checkMove(Position* to, Board* gameBoard, char turn)
{
    int translationX = int(to->getX() - this->getPos().getX());
    int translationY = (to->getY()) - (this->getPos().getY());

    int source_x = int(this->getPos().getX() - 97);
    int source_y = this->getPos().getY();

    // Same index
    if (this->getPos().getX() == to->getX() && this->getPos().getY() == to->getY()) return UV_SAME_INDEX;

    // Empty place
    if (gameBoard->getByPlace(source_x, source_y) == nullptr) return UV_UNEXIST_SOURCE_SOLIDER;
    
    // Other side solider
    else if (gameBoard->getByPlace(source_x, source_y)->getColor() != turn) return UV_UNEXIST_SOURCE_SOLIDER;
    
    // other side solider in destination
    if (gameBoard->getByPlace(to->getX() - a_LOC, to->getY())) // If in to exist solider
    {
        if (gameBoard->getByPlace(to->getX() - a_LOC, to->getY())->getColor() == turn)
        {
            return UV_FRIENDLY_FIRE;
        }
    }
    

    //if out of bounds
    if (source_x < 0 || source_y > 8 || to->getX() - 97 < 0 || to->getY() > 8) return UV_INDEX;

    // valid move if moving 1 square forward/backwards/sideways/diagonally
    if ((abs(translationY) == 1 && translationX == 0) ||
        (abs(translationX) == 1 && abs(translationY) == 1) ||
        (abs(translationX) == 1 && translationY == 0))
    {
        return V_MOVE;
    }

    
    //not valid
    return UV_MOVE;
}
