#pragma once
#include "Sequence.h"
class String :
	public Sequence
{
public:
	String(string param, bool temp=false);
	~String();
	string val;
	bool isPrintable();
	string toString();
	string getType();
	int len();
	void add(Type* t);
};

