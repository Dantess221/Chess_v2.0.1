#pragma once
#include "Tile.h"

class Move {
public:
	Move(Tile, Tile, int piece, bool enPassant = false, int promoted = -1);
	Move() {}
	Move(bool shortRook, bool longRook, int piece); // Castling
	bool operator ==(const Move& rhs) const;

	Tile getOrigin();
	Tile getDestination();
	bool isShortRook();
	bool isLongRook();
	bool isEnPassant();
	int isPromoted();

	int _piece = -1;

private:
	Tile _origin;
	Tile _destination;
	bool _shortRook = false;
	bool _longRook = false;
	bool _enPassant = false;
	int _promoted = -1;
};
