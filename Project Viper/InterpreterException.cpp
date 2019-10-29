#include "stdafx.h"
#include "InterpreterException.h"
using namespace std;

InterpreterException::InterpreterException(string param)
{
	msg = param;
}


InterpreterException::~InterpreterException()
{

}

string InterpreterException::what()
{
	return "An exception has occurred:"+msg;
}
