#pragma once

#include "ChessPiece.h"

class Bishop : virtual public ChessPiece
{
public:

	Bishop(std::wstring unicode, int color, int code, double value) : ChessPiece(unicode, color, code, value) {}

	virtual void getMoves(std::list<Move>& list, Tile* tile, Position* position, int color, int pieceValue = 2)
	{
		int row = tile->getRow();
		int column = tile->getColumn();

		Tile origin = Tile(row, column);

		// Up Right
		for (int i = 1; i < 8; i++)
		{
			int new_row = row + i;
			int new_column = column + i;

			if (new_row > 7 || new_column > 7)
				break;

			ChessPiece* n = position->board[new_column][new_row];

			//Is new location empty?
			if (n == nullptr)
			{
				list.push_back(Move(origin, Tile(new_row, new_column), pieceValue));
				continue;
			}

			// Is location occupied by opponent?
			else if (n->getColor() != color)
			{
				list.push_back(Move(origin, Tile(new_row, new_column), pieceValue));
			}

			break;
		}

		// Up Left
		for (int i = 1; i < 8; i++)
		{
			int new_row = row + i;
			int new_column = column - i;

			if (new_row > 7 || new_column < 0)
				break;

			ChessPiece* n = position->board[new_column][new_row];

			//Is new location empty?
			if (n == nullptr)
			{
				list.push_back(Move(origin, Tile(new_row, new_column), pieceValue));
				continue;
			}

			// Is location occupied by opponent?
			if (n->getColor() != color)
			{
				list.push_back(Move(origin, Tile(new_row, new_column), pieceValue));
			}

			break;
		}

		// Down Right
		for (int i = 1; i < 8; i++)
		{
			int new_row = row - i;
			int new_column = column + i;

			if (new_row < 0 || new_column > 7)
				break;

			ChessPiece* n = position->board[new_column][new_row];

			//Is new location empty?
			if (n == nullptr)
			{
				list.push_back(Move(origin, Tile(new_row, new_column), pieceValue));
				continue;
			}

			// Is location occupied by opponent?
			if (n->getColor() != color)
			{
				list.push_back(Move(origin, Tile(new_row, new_column), pieceValue));
			}

			break;
		}

		// Down Left
		for (int i = 1; i < 8; i++)
		{
			int new_row = row - i;
			int new_column = column - i;

			if (new_row < 0 || new_column < 0)
				break;

			ChessPiece* n = position->board[new_column][new_row];

			//Is new location empty?
			if (n == nullptr)
			{
				list.push_back(Move(origin, Tile(new_row, new_column), pieceValue));
				continue;
			}

			// Is location occupied by opponent?
			if (n->getColor() != color)
			{
				list.push_back(Move(origin, Tile(new_row, new_column), pieceValue));
			}

			break;
		}
	}
};