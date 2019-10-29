#include "stdafx.h"
#include "Type.h"

Type::Type()
{
	_isTemp = false;
}


Type::~Type()
{
}

int Type::len()
{
	string str = this->getType();
	throw InterpreterException(str+" has no len method");
}

void Type::add(Type* t)
{
	string str = this->getType();
	throw InterpreterException(str + " has no add method");
}

void Type::subtract(Type* t)
{
	string str = this->getType();
	throw InterpreterException(str + " has no add method");
}

void Type::divide(Type* t)
{
	string str = this->getType();
	throw InterpreterException(str + " has no add method");
}

void Type::mulltiply(Type* t)
{
	string str = this->getType();
	throw InterpreterException(str + " has no add method");
}
