#pragma once
#include "Type.h"
class Sequence :
	public Type
{
public:
	Sequence();
	~Sequence();
	int len() = 0;
};

