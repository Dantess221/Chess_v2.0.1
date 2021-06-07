#pragma once

#include <iostream>
//#include "ChessPiece.h"

class Position; 
class Move;

class PositionStack {
public:

	PositionStack();
	~PositionStack();

	void push(Position * position);

	void pop();
	PositionStack * peak();

	bool isEmpty();

	Position *getPosition();

private:
	PositionStack* _top = NULL;
	PositionStack* _next = NULL;
	Position * _position = NULL;
};
