#include <windows.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <stdlib.h>
#include "UI.h"

UI::UI(Position* position)
{
	_position = position;
}

void UI::drawBoard(bool colorSelection)
{
	// Enables wcout to print unicode
	_setmode(_fileno(stdout), _O_U16TEXT);

	// For switching background color on/off
	bool color = false;

	// Printing the board and the pieces
	for (int i = 7; i >= 0; i--)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		wcout << i + 1;

		for (int j = 0; j < 8; j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color ? 96 : 240);

			ChessPiece* temp = _position->board[j][colorSelection ? i : (7 - i)];

			if (temp)
			{
				wcout << " " << temp->getUnicode() << " ";
			}
			else
			{
				wcout << "   ";
			}

			if (j < 7)
				color = !color;
		}

		wcout << "\n";
	}

	wcout << "  a  b  c  d  e  f  g  h";
}

Move UI::getOpponentMove(string inputOpponentMove, bool colorSelection)
{
	Move opponentMove;

	if (inputOpponentMove == "0-0")
	{
		opponentMove = Move(true, false, 6);
	}
	else if (inputOpponentMove == "0-0-0")
	{
		opponentMove = Move(false, true, 7);
	}
	else
	{
		int i = 0;

		Tile tiles[2];

		for (int j = 0; j < 2; i += 3, j++)
		{
			int columnInt = inputOpponentMove[i] - 'a';
			int rowInt = inputOpponentMove[i + 1] - '1';

			rowInt = colorSelection ? rowInt : 7 - rowInt;

			if (rowInt < 0 || rowInt > 7 || columnInt < 0 || columnInt > 7)
				return opponentMove;

			tiles[j] = Tile(rowInt, columnInt);
		}

		int promotedTo = -1;

		if (inputOpponentMove.length() == 6)
		{
			// T/R/L/D
			char a = inputOpponentMove[5];
			switch (a)
			{
			case 'r':
				promotedTo = 0;
				break;
			case 'h':
				promotedTo = 1;
				break;
			case 'b':
				promotedTo = 2;
				break;
			case 'q':
				promotedTo = 3;
				break;
			}
		}

		opponentMove = Move(tiles[0], tiles[1], 5, 0, promotedTo);
	}

	return opponentMove;
}

void UI::printMoves(std::list<Move>& moves, int colorSelection)
{
	Tile currentOriginTile = Tile();
	for (Move s : moves)
	{
		if (s.isShortRook())
			wcout << "\n0-0";
		else if (s.isLongRook())
			wcout << "\n0-0-0";
		else
		{
			Tile newOriginTile = s.getOrigin();
			if (currentOriginTile != newOriginTile)
			{
				wcout << endl;

				currentOriginTile = newOriginTile;
				int y = currentOriginTile.getRow();
				wcout << (char)(currentOriginTile.getColumn() + 'a')
					<< (char)((colorSelection ? y : 7 - y) + '1')
					<< " -> ";
			}
			else
			{
				wcout << ", ";
			}

			Tile destinationTile = s.getDestination();
			int y = destinationTile.getRow();
			wcout << (char)(destinationTile.getColumn() + 'a')
				<< (char)((colorSelection ? y : 7 - y) + '1');

			if (s.isPromoted() > -1)
			{
				char promotedChar = 0;
				switch (s.isPromoted())
				{
				case 0:
					promotedChar = 'R';
					break;
				case 1:
					promotedChar = 'H';
					break;
				case 2:
					promotedChar = 'B';
					break;
				case 3:
					promotedChar = 'Q';
					break;
				}
				wcout << promotedChar;
			}
		}
	}

	wcout << endl;
}

void UI::printMove(Move move, int colorSelection)
{
	if (move.isShortRook())
		wcout << "0-0";
	else if (move.isLongRook())
		wcout << "0-0-0";
	else
	{
		Tile origin = move.getOrigin();
		Tile destination = move.getDestination();
		wcout << (char)(origin.getColumn() + 'a') << (char)((colorSelection ? origin.getRow() : 7 - origin.getRow()) + '1') << "-"
			<< (char)(destination.getColumn() + 'a') << (char)((colorSelection ? destination.getRow() : 7 - destination.getRow()) + '1');

		if (move.isPromoted() > -1)
		{
			char promotedChar = 0;
			switch (move.isPromoted())
			{
			case 0:
				promotedChar = 'R';
				break;
			case 1:
				promotedChar = 'H';
				break;
			case 2:
				promotedChar = 'B';
				break;
			case 3:
				promotedChar = 'Q';
				break;
			}
			wcout << promotedChar;
		}
	}
	wcout << endl;
}