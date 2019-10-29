#include "stdafx.h"
#include "Boolean.h"


Boolean::Boolean(bool param, bool temp)
{
	val = param;
	_isTemp = temp;
}


Boolean::~Boolean()
{
}

bool Boolean::isPrintable()
{
	return true;
}

string Boolean::toString() 
{
	return to_string(val);
}

string Boolean::getType()
{
	return "<type 'boolean'";
}
