#pragma once

#include "ChessPiece.h"
#include "Bishop.h"
#include "Rook.h"

class Queen : public Bishop, public Rook
{
public:

	Queen(std::wstring unicode, int color, int code, double value) :
		ChessPiece(unicode, color, code, value),
		Bishop(unicode, color, code, value),
		Rook(unicode, color, code, value) {}

	virtual void getMoves(std::list<Move>& list, Tile* tile, Position* position, int color, int pieceValue)
	{
		Rook::getMoves(list, tile, position, color, 3);
		Bishop::getMoves(list, tile, position, color, 3);
	}
};