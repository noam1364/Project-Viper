#pragma once
#include "InterpreterException.h"
class SyntaxException :
	public InterpreterException
{
public:
	SyntaxException();
	~SyntaxException();
};

