#include "PositionStack.h"

PositionStack::PositionStack() {
	_top = NULL;
}

PositionStack::~PositionStack() {
	while (!isEmpty())
		pop();
}

void PositionStack::push(Position *position)
{
	PositionStack *temp = new PositionStack();

	temp->_position = position;
	temp->_next = _top;
		
	_top = temp;
}

void PositionStack::pop()
{
	if (!isEmpty())
	{
		PositionStack * oldtop = _top;
		_top = _top->_next;
		delete oldtop;
	}
}

PositionStack * PositionStack::peak()
{
	return _top;
}

bool PositionStack::isEmpty()
{
	return (_top == NULL);
}

Position * PositionStack::getPosition()
{
	if (!isEmpty())
		return _top->_position;
	return NULL;
}
