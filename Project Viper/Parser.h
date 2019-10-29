#pragma once
#include "Type.h"
#include "PythonList.h"
#include "Integer.h"
#include <unordered_map>
#include <List>
using namespace std;
class Parser
{
public:
	///base methods
	static Type* executeCommand(string str);
	static bool makeAssignment(string str);
	static Type* getType(string str, bool isTemp = false);
	static PythonList* getList(string str);
	///func implementation methods
	static Type* getSingleExpressionValue(string str);
	static Type* valueRetFunctions(string str);
	static bool voidFunctions(string str);
	static Type* typeOfFunction(string str);
	static void delFunction(string var);
	static Integer* lenFunction(string str);
	static Type* integerOperations(string str);
	static Type* stringOperations(string str);
	///helper methods
	static bool isLegalVarName(string str);
	static bool isLegalIntOperation(string str);
	static bool islegalStringOperation(string str);
	static Type * getVariableValue(string str);
	static string trimStr(string str);
	static string getExp(string str1, string str2, string fullExp = "");
	static bool isString(string str);
	static bool isInteger(string str);
	static int find_second_of(string str, string chars);
};

