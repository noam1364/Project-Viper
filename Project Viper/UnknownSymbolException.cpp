#include "stdafx.h"
#include "UnknownSymbolException.h"


UnknownSymbolException::UnknownSymbolException(string param)
{
	msg = "Unknown Symbol [" + param + "]";
}


UnknownSymbolException::~UnknownSymbolException()
{
}
