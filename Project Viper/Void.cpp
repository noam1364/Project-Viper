#include "stdafx.h"
#include "Void.h"


Void::Void(bool temp)
{
	_isTemp = temp;
}


Void::~Void()
{
}

string Void::toString()
{
	return "null";
}

bool Void::isPrintable()
{
	return false;
}

string Void::getType()
{
	return "<type 'void'";
}
