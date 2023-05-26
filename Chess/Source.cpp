/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project, 
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include <iostream>
#include <thread>
#include "Board.h"
#include "Position.h"

using std::endl;
using std::string;

# define START_BOARD "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR"


char changeTurn(char turn);

void main()
{
	srand(time_t(NULL));
	Solider* sToMove = nullptr;
	
	int code = 0;
	char turn = 'w';
	
	Pipe p;
	bool isConnect = p.connect();
	
	string ans;
	while (!isConnect)
	{
		std::cout << "cant connect to graphics" << endl;
		std::cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			std::cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else 
		{
			p.close();
			return;
		}
	}
	
	char msgToGraphics[1024];

	Board* gameBoard = new Board(START_BOARD);
	strcpy_s(msgToGraphics, "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0"); // Set start board
	
	p.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4           (move e2 to e4)

		/******* JUST FOR EREZ DEBUGGING ******/
		int r = rand() % 10; // just for debugging


		// Initialize "to" position
		Position pos(msgFromGraphics[2], int(msgFromGraphics[3] - '0'));

		sToMove = gameBoard->getByPlace(int(msgFromGraphics[0] - 97), int(msgFromGraphics[1] - '0'));

		if (sToMove != nullptr)
		{
			Position oldPos(msgFromGraphics[0], int(msgFromGraphics[1] - '0'));
			Board* tempBoard = new Board(*gameBoard);

			code = sToMove->checkMove(&pos, tempBoard, turn); 
			

			if(code == V_MOVE)
			{
				sToMove->move(&pos, tempBoard);

				if (tempBoard->isCheck(turn))
				{
					code = UV_SELF_CHECK;
					sToMove->move(&oldPos, tempBoard);
				}
				else if (tempBoard->isCheck(changeTurn(turn)))
				{
					code = V_CHECK_MOVE;

					turn = changeTurn(turn);
					gameBoard->clone(*tempBoard); // Change board to the board after solider move
				}
				else
				{
					turn = changeTurn(turn);
					
					gameBoard->clone(*tempBoard); // Change board to the board after solider move
				}

			}

			msgToGraphics[0] = (char)(code + '0');
		}
		else
		{
			msgToGraphics[0] = (char)(UV_UNEXIST_SOURCE_SOLIDER + '0');
		}
		msgToGraphics[1] = 0;



	
		p.sendMessageToGraphics(msgToGraphics);   

		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
}



char changeTurn(char turn)
{
	if (turn == 'w') return 'b';
	else if (turn == 'b') return 'w';
}