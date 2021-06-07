#include "MoveStack.h"

MoveStack::MoveStack() {
	//_top = NULL;
}

MoveStack::~MoveStack() {
	while (!isEmpty())
		pop();
}

void MoveStack::push(Move move)
{
	MoveStack *temp = new MoveStack();
	temp->_move = move;

	if (!isEmpty()) {
		for (int i = 0; i < 6; i++)
			temp->castlingBools[i] = _top->castlingBools[i];
		temp->_turn = _top->_turn;
	}
		

	temp->_next = _top;
	_top = temp;
}

void MoveStack::pop()
{
	if (!isEmpty())
	{
		MoveStack * oldtop = _top;
		_top = _top->_next;
		delete oldtop;
	}
}

MoveStack * MoveStack::peak() 
{
	return _top;
}

bool MoveStack::isEmpty()
{
	return (_top == NULL);
}

bool MoveStack::getCastlingBools(int index)
{
	if (isEmpty()) 
		return false;

	return _top->castlingBools[index];
}

void MoveStack::setCastlingBools(int index, bool state)
{
	if (isEmpty() == false)
		_top->castlingBools[index] = state;
}

int MoveStack::getTurn()
{
	if (isEmpty())
		return 0;

	return _top->_turn;
}

void MoveStack::changeTurn()
{
	if (isEmpty() == false)
		_top->_turn = !_top->_turn;
}

Move MoveStack::getMove()
{
	return _top->_move;
}

ChessPiece * MoveStack::getCapturedPiece()
{
	if (isEmpty())
		return NULL;

	return _top->_capturedPiece;
}

ChessPiece * MoveStack::getEnPassant()
{
	if (isEmpty())
		return NULL;

	return _top->_enPassant;
}

ChessPiece * MoveStack::getPromotedFrom()
{
	if (isEmpty())
		return NULL;

	return _top->_promotedFrom;
}

void MoveStack::setCapturedPiece(ChessPiece * capturedPiece)
{
	_top->_capturedPiece = capturedPiece;
}

void MoveStack::setEnPassant(ChessPiece * enPassant)
{
	_top->_enPassant = enPassant;
}
