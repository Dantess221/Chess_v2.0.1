#pragma once

#include <iostream>
#include "ChessPiece.h"

class MoveStack {
public:

	MoveStack();
	~MoveStack();

	void push(Move move);

	void pop();
	MoveStack * peak();

	bool isEmpty();

	bool getCastlingBools(int index);
	void setCastlingBools(int index, bool state);

	int getTurn();
	void changeTurn();

	Move getMove();
	ChessPiece * getCapturedPiece();
	ChessPiece * getEnPassant();
	ChessPiece * getPromotedFrom();

	void setCapturedPiece(ChessPiece * capturedPiece);
	void setEnPassant(ChessPiece * enPassant);

private:
	MoveStack* _top = NULL;
	MoveStack* _next = NULL;

	bool castlingBools[6] = { 0,0,0,0,0,0 };

	int _turn = 0;

	Move _move;
	ChessPiece * _capturedPiece = NULL;
	ChessPiece * _enPassant = NULL;
	ChessPiece * _promotedFrom = NULL;
};
