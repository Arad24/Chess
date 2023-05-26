#include "Pawn.h"
#include "Queen.h"
Pawn::Pawn(char type, char color, Position pos) : Solider(type, color, pos)
{
}

Pawn::~Pawn()
{
    Solider::~Solider();
}

int Pawn::checkMove(Position* to, Board* gameBoard, char turn)
{
    int dest_x = int(to->getX() - a_LOC);
    int dest_y = to->getY();

    int source_x = int(this->getPos().getX() - 97);
    int source_y = this->getPos().getY();
    Position pos = this->getPos();
    // Same index
    if (this->getPos().getX() == to->getX() - a_LOC && this->getPos().getY() == to->getY()) return UV_SAME_INDEX;

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
    if (source_x < 0 || source_y > 8 || dest_x < 0 || dest_y > 8) return UV_INDEX;

    //if first move
    if ((source_y == 2 && this->getColor() == 'w') || (source_y == 7 && this->getColor() == 'b'))
    {
        if (source_x == dest_x && ((dest_y - source_y == 1 || dest_y - source_y == 2) && this->getColor() == 'w') ||
            (dest_y - source_y == -1 || dest_y - source_y == -2) && this->getColor() == 'b')
        {
            if(gameBoard->isClearVertical(&pos, to))
            {
                if (gameBoard->getByPlace(to->getX() - a_LOC, to->getY()) != nullptr) return UV_MOVE;
                return V_MOVE;
            }
        }
        else if ((((dest_x == source_x - 1) || (dest_x == source_x + 1)) && (source_x < 8 && source_x > 1)) && 
            ((dest_y - source_y == 1) && this->getColor() == 'w') || (dest_y - source_y == -1 && this->getColor() == 'b'))
        {
                if (gameBoard->getByPlace(to->getX() - a_LOC, to->getY()) == nullptr) return UV_MOVE;
                return V_MOVE;
        }
    }
    //if not first move
    else if (source_y > 2 && this->getColor() == 'w' || source_y < 7 && this->getColor() == 'b')
    {
        if (source_x == dest_x && (((dest_y - source_y == 1) && this->getColor() == 'w') || (dest_y - source_y == -1 && this->getColor() == 'b')))
        {
            if (gameBoard->isClearVertical(&pos, to))
            {
                if (gameBoard->getByPlace(to->getX() - a_LOC, to->getY()) != nullptr) return UV_MOVE;

                //bonus - when in last row replace to Queen
                if (dest_y == 8 && this->getColor() == 'w')
                {
                    Queen* q1 = new Queen('q', 'w', pos);
                    gameBoard->setByPlace(q1, source_x, source_y);
                }
                else if (dest_y == 1 && this->getColor() == 'b')
                {
                    Queen* q = new Queen('q', 'b', pos);
                    gameBoard->setByPlace(q, source_x, source_y);
                }

                return V_MOVE;
            }
        }
        
        //if eating
        else if ((((dest_x == source_x - 1) || (dest_x == source_x + 1)) && (source_x < 8 && source_x > 1)) &&
            (((dest_y - source_y == 1) && this->getColor() == 'w') || (dest_y - source_y == -1 && this->getColor() == 'b')))
        {
            if (gameBoard->getByPlace(to->getX() - a_LOC, to->getY()) == nullptr) return UV_MOVE;

            //bonus - when in last row replace to Queen
            if (dest_y == 8 && this->getColor() == 'w')
            {
                Queen* q1 = new Queen('q', 'w', pos);
                gameBoard->setByPlace(q1, source_x, source_y);
            }
            else if (dest_y == 1 && this->getColor() == 'b')
            {
                Queen* q = new Queen('q', 'b', pos);
                gameBoard->setByPlace(q, source_x, source_y);
            }

            return V_MOVE;
        }
    }
    //not valid
    return UV_MOVE;
}
