#pragma once

#include "Position.h"

using namespace std;

class UI {

public:
	UI(Position* position);
	Position* _position;
	void drawBoard(bool colorSelection);
	Move getOpponentMove(string inputOpponentMove, bool colorSelection);
	void printMoves(std::list<Move>& moves, int colorSelection);
	void printMove(Move move, int colorSelection);
};
