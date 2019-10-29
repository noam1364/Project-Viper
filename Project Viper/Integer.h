#pragma once
#include "Type.h"
class Integer :
	public Type
{
public:
	Integer(int param, bool temp=false);
	~Integer();
	bool isPrintable();
	string toString();
	int val;
	string getType();
	void add(Type* t);
	void subtract(Type * t);
};

