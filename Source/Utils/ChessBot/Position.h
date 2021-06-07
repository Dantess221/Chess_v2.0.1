#pragma once
#include "ChessPiece.h"
#include "PositionStack.h"
#include "MinMaxReturn.h"
#include "PieceSquareValues.h"

using namespace std;

class Position {

public:
	//Constructor sets the starting position on the board
	Position();

	Position(const Position& pos)
	{
		if (this != &pos)
			*this = pos;
	}

	ChessPiece * board[8][8];

	static ChessPiece *wKing, *wQueen, *wRook, *wBishop, *wHorse, *wPawn;	// Valkeat nappulat.
	static ChessPiece *bKing, *bQueen, *bRook, *bBishop, *bHorse, *bPawn;	// Mustat nappulat.

	void updatePosition(Move* move, bool realMove = true, bool aiMove = false);
	void undoMove();

	int getTurn();
	void changeTurn();

	bool getKingMoved(int color);
	bool getShortRookMoved(int color);
	bool getLongRookMoved(int color);

	void setKingMoved();
	void setShortRookMoved();
	void setLongRookMoved();

	void getLegalMoves(std::list<Move>& moves, int turn);
	void getRawMoves(std::list<Move>& moves, int turn);

	void isCheck(std::list<Move>& moves, int turn);

	void addCastling(std::list<Move>& moves, int turn);
	void addEnPassant(std::list<Move>& moves, int turn);
	

	bool isTileThreatened(Tile tile, int color);

	PositionStack * _positionStack;

	double endResult(int turn);
	double evaluate(int turn, Move move);
	MinMaxReturn minimax(int depth, double alpha, double beta, int turn, Move currentMove, long startTime);
	pair<double, double> calculateMaterialValue();
	double calculatePieceTileValueAndCenterControl(/*Move currentMove, int turn*/bool materialValue);
	double calculateCastlingValue(Move move);
	double calculateKingSafetyValue(bool inEndChessEnginePhase);

	long _maxTime = 1000;

	bool _castlingBools[6] = { 0,0,0,0,0,0 };
	int _turn = 0;

	Move _previousMove;

	Tile _BlackKing, _WhiteKing;
	Tile _BlackQueen, _WhiteQueen;
};
