#include "Queen.h"

Queen::Queen(char type, char color, Position pos) : Solider(type, color, pos)
{
}

Queen::~Queen()
{
    Solider::~Solider();
}

int Queen::checkMove(Position* to, Board* gameBoard, char turn)
{
    int dest_x = int(to->getX() - 97);
    int dest_y = to->getY();

    int source_x = int(this->getPos().getX() - 97);
    int source_y = this->getPos().getY();
    Position pos = this->getPos();

    // Same index
    if (this->getPos().getX() == to->getX()-97 && this->getPos().getY() == to->getY()) return UV_SAME_INDEX;

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
    if ((source_x == dest_x) ||
        (source_y == dest_y) ||
        (abs(source_x - dest_x) == abs(source_y - dest_y)))
    {
        if (gameBoard->isClearVertical(&pos, to) ||
            gameBoard->isClearHorizontal(&pos, to) ||
            gameBoard->isClearDiagonal(&pos, to))
        {
            return V_MOVE;
        }
    }

    //not valid
    return UV_MOVE;
}
