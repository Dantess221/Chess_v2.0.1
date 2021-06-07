#include "ChessPiece.h"

ChessPiece::ChessPiece(std::wstring unicode, int color, int code, double value) {
	_unicode = unicode;
	_code = code;
	_color = color;
	_value = value;
}

int ChessPiece::getCode() {
	return _code;
}

std::wstring ChessPiece::getUnicode() {
	return _unicode;
}

int ChessPiece::getColor() {

	return _color;
}

double ChessPiece::getValue()
{
	return _value;
}
