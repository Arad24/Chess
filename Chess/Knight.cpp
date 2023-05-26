#include "Knight.h"

Knight::Knight(char type, char color, Position pos) : Solider(type, color, pos)
{
}

Knight::~Knight()
{
    Solider::~Solider();
}

int Knight::checkMove(Position* to, Board* gameBoard, char turn)
{
    int dest_x = int(to->getX() - 97);
    int dest_y = to->getY();

    int source_x = int(this->getPos().getX() - 97);
    int source_y = this->getPos().getY();

    // Same index
    if (this->getPos().getX() == to->getX() - 97 && this->getPos().getY() == to->getY()) return UV_SAME_INDEX;

    // Empty place
    if (gameBoard->getByPlace(source_x, source_y) == nullptr) return UV_UNEXIST_SOURCE_SOLIDER;

    // Other side solider
    else if (gameBoard->getByPlace(source_x, source_y)->getColor() != turn) return UV_UNEXIST_SOURCE_SOLIDER;

    // other side solider in destination
    if (gameBoard->getByPlace(to->getX() - 97, to->getY())) // If in to exist solider
    {
        if (gameBoard->getByPlace(to->getX() - 97, to->getY())->getColor() == turn)
        {
            return UV_FRIENDLY_FIRE;
        }
    }

    //if out of bounds
    if (source_x < 0 || source_y > 8 || to->getX() - 97 < 0 || to->getY() > 8) return UV_INDEX;

    // if valid move
    if ((abs(dest_x - source_x) == 2) && (abs(dest_y - source_y) == 1) || 
        (abs(dest_x - source_x) == 1) && (abs(dest_y - source_y) == 2))
    {
        return V_MOVE;
    }

    //not valid
    return UV_MOVE;
}
