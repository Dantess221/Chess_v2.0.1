#pragma once
#include <string>
#include <list>
#include "Move.h"

class Position;

// constants for chess pieces
enum
{
	WR, WH, WB, WQ, WK, WP,
	BR, BH, BB, BQ, BK, BP
};

class ChessPiece {

private:
	std::wstring _unicode;
	int _color = 0; // white = 0, black = 1
	int _code; // enum
	double _value;
public:
	ChessPiece(std::wstring, int, int, double);
	int getCode();
	std::wstring getUnicode();
	int getColor();
	double getValue();


	virtual void getMoves(
		std::list<Move>& list,
		Tile* tile,
		Position* position,
		int color,
		int pieceValue = NULL
	) = 0;
};



