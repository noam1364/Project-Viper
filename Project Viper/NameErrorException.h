#pragma once
#include "InterpreterException.h"
class NameErrorException :
	public InterpreterException
{
public:
	NameErrorException(string param);
	~NameErrorException();
};

