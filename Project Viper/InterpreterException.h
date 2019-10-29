#pragma once
#include "stdafx.h"
using namespace std;

class InterpreterException : public std::exception
{
public:
	InterpreterException(string param = "Unknown error");
	~InterpreterException();
	string what();
	string msg;
};

