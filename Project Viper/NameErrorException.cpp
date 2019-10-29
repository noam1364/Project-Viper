#include "stdafx.h"
#include "NameErrorException.h"


NameErrorException::NameErrorException(string param)
{
	msg = "NameError : name '["+param+"]' is not defined";
}


NameErrorException::~NameErrorException()
{
}
