#include "Move.h"

Move::Move(Tile origin, Tile destination, int piece, bool enPassant, int promoted) {
	_origin = origin;
	_destination = destination;
	_enPassant = enPassant;
	_promoted = promoted;
	_piece = piece;
}

Move::Move(bool shortRook, bool longRook, int piece) {
	_shortRook = shortRook;
	_longRook = longRook;
	_piece = piece;
}

bool Move::operator==(const Move & rhs) const
{
	if (_shortRook != rhs._shortRook)
		return false;

	if (_longRook != rhs._longRook)
		return false;

	if (_origin != rhs._origin)
		return false;

	if (_destination != rhs._destination)
		return false;

	if (_promoted != rhs._promoted)
		return false;

	return true;
}

Tile Move::getOrigin() {
	return _origin;
}

Tile Move::getDestination() {
	return _destination;
}

bool Move::isShortRook() {
	return _shortRook;
}

bool Move::isLongRook() {
	return _longRook;
}

bool Move::isEnPassant()
{
	return _enPassant;
}

int Move::isPromoted()
{
	return _promoted;
}

