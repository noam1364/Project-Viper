#include "stdafx.h"
#include "Parser.h"
#include <array>
using namespace std;

static unordered_map<string, Type*> _variables; 

Type* Parser::executeCommand(string str)
{
	if (str == "")return new Void(true);
	if (str[0] == ' ')throw IndentationException();
	else
	{
		str = trimStr(str);
		Type* t = getSingleExpressionValue(str);
		if (t!= nullptr)return t;
		else
		{
			if (makeAssignment(str)||voidFunctions(str))return new Void(true);
			else	///if str is not a legal a variable assignment,check if its a variables name
			{
				t = valueRetFunctions(str);
				if (t != nullptr)return t;
				else throw UnknownSymbolException(str);
			}
		}
	}
	return nullptr;
}

Type* Parser::getSingleExpressionValue(string str)
{							///returns the value of a non operations exspression (not like '1+2')
	Type* t = getType(str);
	if (t == nullptr)
		return getVariableValue(str);
	return t;
}

Type* Parser::getType(string str,bool isTemp)	///recives only trimmed strings	| isTemp = false
{			///if str has a legal type,return it,else return a nullptr
	if (str[0] == '['&&str[str.length() - 1] == ']')return getList(str);
	if (str.empty())return new Void();
	if (isInteger(str))return new Integer(stoi(str),isTemp);
	else
	{
		if (str == "True")return new Boolean(true,isTemp);
		else if (str == "False") return new Boolean(false,isTemp);
		else if (isString(str)) return new String(str,isTemp);
		else return nullptr;	///string contains no accepted value
	}
}

bool Parser::makeAssignment(string str)
{
	int len = str.length(), equalIdx = str.find('=');
	if (equalIdx == -1) return false;///if str doesnt conatins a '=' 
	if (!(equalIdx > 0 && equalIdx < len - 1))
	{
		throw SyntaxException();///if str doesnt conatins a '=' IN THE MIDDLE
		return false;
	}

	string name = str.substr(0, equalIdx), value = str.substr(equalIdx + 1, len);	///split str in where the '=' is
	name = trimStr(name);
	value = trimStr(value);

	if (!isLegalVarName(name))
	{
		throw NameErrorException(name);
		return false;
	}

	Type* t = getSingleExpressionValue(value);
	if (t == nullptr)	///if 'value' is not a legal value
	{
		t = valueRetFunctions(value);
		if (t != nullptr)goto setValue;
		else
		{
			throw SyntaxException();
		}
	}
	else
	{
		setValue:
		_variables[name] = t;
		return true;
	}
	return false;
}

bool Parser::voidFunctions(string str)
{
	string exp;
	exp = getExp(str, "del", "");
	if (exp != "")
	{
		delFunction(exp);
		return true;
	}
	return false;
}

Type* Parser::valueRetFunctions(string str)///return 'nullptr' if no function was actually called in 'str'
{
	string exp;
	if (isLegalIntOperation(str))return integerOperations(str);
	if (islegalStringOperation(str))return stringOperations(str);
	
	exp = getExp(str, "len", "");
	if (exp != "")
	{
		return lenFunction(exp);
	}
	exp = getExp(str, "type(", ")");
	if (exp != "")
	{
		return typeOfFunction(exp);
	}
	return nullptr;
}

///interpreter functions
Type* Parser::typeOfFunction(string str)
{
	Type* t = getSingleExpressionValue(str);
	if (t == nullptr)
	{
		throw NameErrorException(str);
		return new Void();	///Void instead of 'nullptr',so that 'parseString' will return a value to main
	}
	return new String(t->getType());
}

void Parser::delFunction(string var)
{
	if (_variables[var] == nullptr)throw NameErrorException(var);
	_variables.erase(var);
}

Integer* Parser::lenFunction(string str)
{
	Type* value = getSingleExpressionValue(str);
	if (value == nullptr)
	{
		throw NameErrorException(str);
		return nullptr;
	}
	return new Integer(value->len());
}

Type* Parser::integerOperations(string str)
{
	int idx = 0, len = str.length();
	string exp, temp, chars = "+-";
	Type* result = nullptr;
	Type* t;
	char c = ' ';
	if (isdigit(str[0]))
	{
		temp = str;
		str = "+";
		str.append(temp);
	}
	do
	{
		idx = find_second_of(str, chars);
		if (idx != 0)
		{
			c = str[idx];
			exp = str.substr(0, idx);
			str.erase(0, idx);
		}
		else
			exp = str;

		if (result == nullptr)
		{
			result = Parser::getSingleExpressionValue(exp);
		}
		else
		{
			t = Parser::getSingleExpressionValue(exp);
			try
			{
				if (c == '+' || c == '-')
					result->add(t);
			}
			catch (exception e)
			{
				throw SyntaxException();
			}
		}
	} while (idx != 0);
	return result;
}

Type* Parser::stringOperations(string str)
{
	int idx = 0;
	char c;
	string exp;
	Type* result = new String("");
	Type* temp = nullptr;
	
	while (idx != -1)
	{
		idx = str.find_first_of('+');
		exp = str.substr(0, idx);
		str.erase(0, idx + 1);
		temp = getSingleExpressionValue(exp);
		if (temp == nullptr)
		{///if it's not a String, maybe there is a '+' in the middle, and exp is the first half of a legal String
			if (exp[0] == '\'' || exp[0] == '\"')
			{
				c = exp[0];
				exp.append(str.substr(0, str.find_first_of(c)));
				temp = getSingleExpressionValue(exp);
			}
		}
		result->add(temp);
	}
	return result;
}

Type* Parser::getVariableValue(string str)
{
	if (_variables.count(str) >= 1)
		return _variables[str];
	return nullptr;
}

#pragma region helper methods
///string helper methods
string Parser::trimStr(string str)
{
	int start = str.find_first_not_of(" \t"), end = str.find_last_not_of(" \t");
	string ret = str.substr(start, end - start + 1);
	return ret;
}
string Parser::getExp(string fullExp, string str1, string str2)
{																///str2 default value ' "" '
	bool endCondition;
	if (str2 == "")
		endCondition = false;
	else
		endCondition = fullExp.substr(fullExp.length() - str2.length(), str2.length()) != str2;

	if (fullExp.substr(0, str1.length()) != str1 || endCondition) return "";
	string exp = fullExp.substr(str1.length());
	exp = exp.substr(0, exp.length() - str2.length());
	exp = trimStr(exp);
	return exp;
}
int Parser::find_second_of(string str, string chars)
{
	int idx = str.find_first_of(chars);
	str.erase(0, idx + 1);
	return str.find_first_of(chars) + idx + 1;
}
///syntax helper methods
bool Parser::isLegalVarName(string str)
{
	if (isdigit(str[0]))return false;
	for each(char c in str)
		if (c != '_' && !isalpha(c) && !isdigit(c)) return false;
}
bool Parser::isLegalIntOperation(string str)
{
	if ((!isdigit(str[0])&&str[0]!='+'&&str[0]!='-')||!isdigit(str[str.length()-1]))return false;
	string next,both = "both",digit = "digit",temp;
	char c = ' ';
	if (isdigit(str[0]))	///put a '+' at the beginning of str if there is none
	{
		temp = str;
		str = "+";
		str.append(temp);
	}
	next = both;
	for (int i = 0; i < str.length(); i++)
	{
		c = str[i];
		if (!isdigit(c))
		{
			if (next != both)return false;
			if (c == '+' || c == '-' || c == '/')
				next = digit;
			else
			{
				if (c == '*')
				{
					next = digit;
					if (str.length() > i + 1)
					{
						if (str[i + 1] == '*')///the '**' operator
							i++;
					}
				}
				else return false;
			}
		}
		else next = both;
	}
	return true;
}
bool Parser::islegalStringOperation(string str)
{
	bool isStr = true;
	int idx=0;
	char c;
	string typeSt = String("").getType(),exp,typeOfExp;
	Type* temp;
	while (idx != -1)
	{
		idx = str.find_first_of('+');
		exp = str.substr(0, idx);		///exp-->the part of str until the first '+'
		str.erase(0, idx + 1);
		temp = getVariableValue(exp);			///check if exp is an existing variable
		if (temp == nullptr)typeOfExp = "null";
		
		if (isString(exp)||temp!=nullptr)isStr = true; ///if exp is a string or a string variable
		else	///if it's not a String, maybe there is a '+' in the middle, and exp is the first half of a legal String
		{
			if (exp[0] == '\'' || exp[0] == '\"')
			{
				c = exp[0];
				exp.append(str.substr(0, str.find_first_of(c)));
			}
			else isStr = false;
		}
		
		if (!isStr&&typeOfExp!=typeSt)return false;
	}
	return true;
}
bool Parser::isInteger(string str)
{
	if (str[0] == '+' || str[0] == '-')str = str.erase(0, 1);
	for each(char c in str)
		if (!isdigit(c))return false;
	return true;
}
bool Parser::isString(string str)
{
	char startChar;
	if (str[0] == '"'&&str.back() == '"')startChar = '"';
	else if (str[0] == '\''&&str.back() == '\'') startChar = '\'';
	else return false;
	///if str starts and ends with a " or a '
	for (int i = 0; i < str.length(); i++)	///for some reason,doesn't work with a 'for each' loop
	{
		if (str[i] == startChar&&i != 0 && i != str.length() - 1)return false;
	}
	return true;
}
PythonList* Parser::getList(string str)
{
	if (str[0] != '[' || str[str.length() - 1] != ']' || str[1] == ',' || str[str.length() - 2] == ',')return nullptr;
	PythonList* lst = new PythonList();
	int idx = 1;
	string exp;
	Type* t;
	for (int i = 1; i < str.length(); i++)
	{
		if (str[i] == ',' || i == str.length() - 1)
		{
			exp = str.substr(idx, i - idx);
			exp = trimStr(exp);
			if (getVariableValue(exp) != nullptr)
				lst->append(_variables[exp]);
			else
			{
				t = getType(exp);
				if (t != nullptr)
					lst->append(getType(exp));
				else
					throw UnknownSymbolException(exp);
			}
			idx = i + 1;
		}
	}
	return lst;
}
#pragma endregion

