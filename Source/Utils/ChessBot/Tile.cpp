#include "Tile.h"

Tile::Tile(int row, int column) {
	_row = row;
	_column = column;
}

bool Tile::operator!=(const Tile & rhs) const
{
	if (_column == rhs._column && _row == rhs._row)
		return false;

	return true;
}

bool Tile::operator==(const Tile & rhs) const
{
	if (_column != rhs._column)
		return false;

	if (_row != rhs._row)
		return false;

	return true;
}

int Tile::getRow() {
	return _row;
}

int Tile::getColumn() {
	return _column;
}