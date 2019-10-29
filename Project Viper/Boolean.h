#pragma once
#include "Type.h"
class Boolean :
	public Type
{
public:
	Boolean(bool param, bool temp=false);
	~Boolean();
	bool val;
	bool isPrintable();
	string toString();
	string getType();
};

