# include "Board.h"
#include "King.h"
# include "Queen.h"
# include "Pawn.h"
# include "Bishop.h"
# include "Knight.h"
# include "Rook.h"

class Solider;

Board::Board(Board& board)
{
	for (int i = 0; i < BOARD_LEN; i++)
	{
		for (int j = 1; j <= BOARD_LEN; j++)
		{
			this->_gameBoard[j - 1][i] = board.getByPlace(i, j);
		}
	}

	this->_bKing = board._bKing;
	this->_wKing = board._wKing;
}

// Ctor & Dtor
Board::Board(std::string boardStr)
{
	char color = ' ';

	for (int i = 0; i < BOARD_LEN; i++)
	{


		for (int j = 0; j < BOARD_LEN; j++)
		{
			char type = boardStr[j + (BOARD_LEN * i)];

			if (type >= 65 && type <= 90) // Black lines
			{
				color = 'b';
			}
			else if (type == '#')
			{
				color = ' ';
			}
			else // White lines
			{
				color = 'w';
			}

			Position pos(char(a_LOC + j), i + 1); // create pos

			switch (tolower(type))
			{
			case PAWN:
				this->_gameBoard[i][j] = new Pawn(tolower(type), color, pos);
				break;

			case ROOK:
				this->_gameBoard[i][j] = new Rook(tolower(type), color, pos);
				break;

			case KNIGHT:
				this->_gameBoard[i][j] = new Knight(tolower(type), color, pos);
				break;

			case BISHOP:
				this->_gameBoard[i][j] = new Bishop(tolower(type), color, pos);
				break;

			case QUEEN:
				this->_gameBoard[i][j] = new Queen(tolower(type), color, pos);
				break;

			case KING:
				this->_gameBoard[i][j] = new King(tolower(type), color, pos);

				if (color == 'w')
				{
					this->_wKing = this->_gameBoard[i][j];
				}
				else
				{
					this->_bKing = this->_gameBoard[i][j];
				}
				break;
			defualt:
				this->_gameBoard[i][j] = nullptr;
				break;
			}
		}

	}
}

void Board::clone(Board& board)
{
	for (int i = 0; i < BOARD_LEN; i++)
	{
		for (int j = 1; j <= BOARD_LEN; j++)
		{
			this->_gameBoard[j - 1][i] = board.getByPlace(i, j);
		}
	}

	this->_bKing = board._bKing;
	this->_wKing = board._wKing;
}

Board::~Board()
{
	for (int i = 0; i < BOARD_LEN; i++)
	{
		for (int j = 0; j < BOARD_LEN; j++)
		{
			// Delete all the soliders
			if (this->_gameBoard[i][j]) delete _gameBoard[i][j];
		}
	}

}


// Getters
Solider* Board::getByPlace(int i, int j) const
{
	return this->_gameBoard[j-1][i];
}

std::string Board::getBoardString()
{
	std::string strBoard = "";

	for (int i = 0; i < BOARD_LEN; i++)
	{
		for (int j = 0; j < BOARD_LEN; j++)
		{
			if (this->_gameBoard[i][j])
			{
				strBoard += this->_gameBoard[i][j]->getType();
			}
			else
			{
				strBoard += NULL_SIGN;
			}
		}
	}

	return strBoard;
}



// Setters
void Board::setByPlace(Solider* s, int i, int j)
{
	this->_gameBoard[j-1][i] = s;

	if (s)
	{
		std::string pos = "";
		pos += char(i + a_LOC);
		pos += std::to_string(j);

		s->setPos(pos);
	}
}

void Board::setBoard(Solider* board[BOARD_LEN][BOARD_LEN])
{
	for (int i = 0; i < BOARD_LEN; i++)
	{
		for (int j = 0; j < BOARD_LEN; j++)
		{
			if (board[i][j])
			{
				this->_gameBoard[i][j] = board[i][j]; // Need create clone function(like copy ctor) -- this->_gameBoard[i][j] = board[i][j]->clone();
			}
		}
	}
}

bool Board::isCheck(char color)
{
	bool check = false;
	Position* kingPos = nullptr;

	for (int i = 0; i < BOARD_LEN; i++)
	{
		for (int j = 1; j <= BOARD_LEN; j++)
		{
			if (this->getByPlace(i, j) != nullptr)
			{
				if (color == 'w')
				{
					// Create king position
					kingPos = new Position(this->_wKing->getPos().getX(), this->_wKing->getPos().getY());

					// Check if the color is not the same color as the king && check if the solider in the position(i,j) can move to the king position(check).
					if (this->getByPlace(i, j)->getColor() != color)
					{
						if (this->getByPlace(i, j)->checkMove(kingPos, this, 'b') == V_MOVE)
						{
							check = true;
							return check;
						}
					}
				}
				else if (color == 'b')
				{
					// Create king position
					kingPos = new Position(this->_bKing->getPos().getX(), this->_bKing->getPos().getY());

					// Check if the color is not the same color as the king && check if the solider in the position(i,j) can move to the king position(check).
					if (this->getByPlace(i, j)->getColor() != color)
					{
						if (this->getByPlace(i, j)->checkMove(kingPos, this, 'w') == V_MOVE)
						{
							check = true;
							return check;
						}
					}
				}

			}
		}
	}

	return check;
}

bool Board::isClearVertical(Position* from, Position* to)
{
	Position* start = NULL;
	Position* end = NULL;
	bool valid = true;

	// determine which square has the smaller y-value, 
	// (this helps to determine which direction to travel in)
	if (from->getY() <= to->getY())
	{
		start = from;
		end = to;
	}
	else
	{
		start = to;
		end = from;
	}

	// check that there is no horizontal movement
	if (start->getX() != end->getX())
	{
		valid = false;
	}
	else
	{
		// iterate over vertical interval between squares
		for (int i = start->getY() + 1; i < end->getY() && valid; i++)
		{
			// if a square is occupied, the vertical is not clear
			if (getByPlace(start->getX() - a_LOC, i) != nullptr)
			{
				valid = false;
			}
		}
	}

	return valid;
}

bool Board::isClearHorizontal(Position* from, Position* to)
{
	Position* start = NULL;
	Position* end = NULL;
	bool valid = true;

	// determine which square has the smaller x-value, 
	// (this helps to determine which direction to travel in)
	if (int(from->getX() - a_LOC) <= to->getX() - a_LOC)
	{
		start = from;
		end = to;
	}
	else
	{
		start = to;
		end = from;
	}

	// check that there is no vertical movement
	if (start->getY() != end->getY())
	{
		valid = false;
	}
	else
	{
		// iterate over horizontal interval between squares
		for (int i = int(start->getX()-a_LOC) + 1; i < int(end->getX()-a_LOC) && valid; i++)
		{
			// if a square is occupied, the vertical is not clear
			if (getByPlace(i, start->getY()) != nullptr)
			{
				valid = false;
			}
		}
	}

	return valid;
}

bool Board::isClearDiagonal(Position* from, Position* to)
{
	bool valid = true;
	int translationX = int(to->getX() - from->getX());
	int translationY = to->getY() - from->getY();
	int xDir = 1;
	int yDir = 1;

	if (translationX < 0)
	{
		xDir = -1;
	}

	if (translationY < 0)
	{
		yDir = -1;
	}

	// not a diagonal if absolute value of x and y translations don't match
	if (abs(translationX) != abs(translationY))
	{
		valid = false;
	} 
	else
	{
		// iterate over diagonal interval between squares
		for (int i = 1; i < abs(translationX) && valid; i++)
		{
			// if a square is occupied, the diagonal is not clear
			if (getByPlace(int(from->getX()-a_LOC) + (i * xDir), from->getY() + (i * yDir)) != nullptr)
			{
				valid = false;
			}
		}
	}

	return valid;
}
