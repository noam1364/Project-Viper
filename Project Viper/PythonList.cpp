#include "stdafx.h"
#include "PythonList.h"



PythonList::PythonList()
{
	lst = new list<Type*>();
}


PythonList::~PythonList()
{
}

bool PythonList::isPrintable()
{
	return true;
}

string PythonList::getType()
{
	return "<type 'List'>";
}

string PythonList::toString()	//TODO:implement
{
	string str = "[";
	for each(Type* t in *lst)
		str.append(t->toString()+",");
	str[str.length() - 1] = ']';
	return str;
}

int PythonList::len()		//TODO:implement
{
	return lst->size();
}

void PythonList::append(Type* t)	//TODO:implement
{
	this->lst->push_back(t);
}

Type* PythonList::get(int i)
{
	return nullptr;
}
