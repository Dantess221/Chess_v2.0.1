#pragma once

#include "ChessPiece.h"

class Rook : virtual public ChessPiece
{
public:

	Rook(std::wstring unicode, int color, int code, double value) : ChessPiece(unicode, color, code, value) {}

	virtual void getMoves(std::list<Move>& list, Tile* tile, Position* position, int color, int pieceValue = 0)
	{
		//Current location
		int row = tile->getRow();
		int column = tile->getColumn();

		Tile origin = Tile(row, column);

		// Right
		for (int i = column + 1; i < 8; i++)
		{
			ChessPiece* n = position->board[i][row];
			
			//Is new location empty?
			if (n == NULL)
			{
				//Add new location to move list
				list.push_back(Move(origin, Tile(row, i), pieceValue));
				continue;
			}

			// Is location occupied by opponent?
			else if (n->getColor() != color)
			{
				//Add new location to move list
				list.push_back(Move(origin, Tile(row, i), pieceValue));
			}

			break;
		}

		// Left
		for (int i = column - 1; i >= 0; i--)
		{
			ChessPiece* n = position->board[i][row];

			//Is new location empty?
			if (n == nullptr)
			{
				//Add new location to move list
				list.push_back(Move(origin, Tile(row, i), pieceValue));
				continue;
			}

			// Is location occupied by opponent?
			if (n->getColor() != color)
			{
				//Add new location to move list
				list.push_back(Move(origin, Tile(row, i), pieceValue));
			}

			break;
		}

		// Up
		for (int i = row + 1; i < 8; i++)
		{
			ChessPiece* n = position->board[column][i];

			//Is new location empty?
			if (n == nullptr)
			{
				//Add new location to move list
				list.push_back(Move(origin, Tile(i, column), pieceValue));
				continue;
			}

			// Is location occupied by opponent?
			if (n->getColor() != color)
			{
				//Add new location to move list
				list.push_back(Move(origin, Tile(i, column), pieceValue));
			}

			break;
		}

		// Down
		for (int i = row - 1; i >= 0; i--)
		{
			ChessPiece* n = position->board[column][i];

			//Is new location empty?
			if (n == nullptr)
			{
				//Add new location to move list
				list.push_back(Move(origin, Tile(i, column), pieceValue));
				continue;
			}

			// Is location occupied by opponent?
			if (n->getColor() != color)
			{
				//Add new location to move list	
				list.push_back(Move(origin, Tile(i, column), pieceValue));
			}

			break;
		}
	}
};