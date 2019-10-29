#pragma once
#include "InterpreterException.h"
class IndentationException :
	public InterpreterException
{
public:
	IndentationException();
	~IndentationException();
};

