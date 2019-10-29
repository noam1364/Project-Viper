#pragma once
#include "InterpreterException.h"
class UnknownSymbolException :
	public InterpreterException
{
public:
	UnknownSymbolException(string param);
	~UnknownSymbolException();
};

