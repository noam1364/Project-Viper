#include "stdafx.h"
#include "String.h"
using namespace std;

String::String(string param,bool temp)
{
	val = param;
	_isTemp = temp;
	if (val[0] == '"')	///if str starts with a '"',check if it contains a '\'' in it and if not replace '"' with a '\''
	{
		int counter = 0;
		for each(char c in val)
		{
			if (c == '\'')
				counter++;
		}
		if (counter == 0)	///if str doesn't contain '\'' in the middle
		{
			val[0] = '\'';
			val[val.length()-1] = '\'';
		}
	}
	
}

String::~String()
{
}

bool String::isPrintable()
{
	return true;
}

string String::toString()
{
	return val;
}

string String::getType()
{
	return "<type 'String'>";
}

int String::len()
{
	return val.length()-2;	///val includes 2 '\''s
}

void String::add(Type* t)
{
	if (this->getType() != t->getType())
		throw InterpreterException("Can only add " + this->getType() + "to " + this->getType());
	else
	{
		char c = '\'';
		string str1 = this->val, str2 = t->toString();
		if (str1.length() != 0 && str2.length() != 0)
		{
			if (str1[0] == '\"' || str2[0] == '\"')
				c = '\"';
			str1[0] = c;
			str2[str2.length() - 1] = c;
			str1.erase(str1.length() - 1, 1);
			str2.erase(0, 1);
		}
		this->val = str1.append(str2);
	}
}


