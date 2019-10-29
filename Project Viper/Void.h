#pragma once
#include "Type.h"
class Void :
	public Type
{
public:
	Void(bool temp = false);
	~Void();
	string toString();
	bool isPrintable();
	string getType();
};

