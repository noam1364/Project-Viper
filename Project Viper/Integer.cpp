#include "stdafx.h"
#include "Integer.h"


Integer::Integer(int param,bool temp)
{
	val = param;
	_isTemp = temp;
}


Integer::~Integer()
{
}

bool Integer::isPrintable()
{
	return true;
}
string Integer::toString()
{
	return to_string(val);
}

string Integer::getType()
{
	return "<type 'int'>";
}
void Integer::add(Type* t)
{
	int n = 0;
	if (t == nullptr)throw SyntaxException();

	try 
	{
		n = stoi(t->toString());
	}
	catch (exception e)
	{
		throw SyntaxException();//temp | replace with TypeError
	}
	this->val +=n;
}

void Integer::subtract(Type* t)
{
	int n = 0;
	if (t == nullptr)throw SyntaxException();

	try
	{
		n = stoi(t->toString());
	}
	catch (exception e)
	{
		throw SyntaxException();//temp | replace with TypeError
	}
	this->val -= n;
}


