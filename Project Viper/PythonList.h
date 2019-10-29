#pragma once
#include "Sequence.h"
#include <List>
class PythonList :
	public Sequence
{
private:
	list<Type*>* lst;
public:
	PythonList();
	~PythonList();
	void append(Type* t);
	int len();
	bool isPrintable();
	string toString();
	string getType();
	Type* get(int i);
};

