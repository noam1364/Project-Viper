#include "stdafx.h"
#include <unordered_map>
#include <List>
#include <array>
using namespace std;



void test()
{

}

int main()
{
	test();
	string input;
	Type* output = nullptr;
	cout << "Viper - Version 0.4\n\n";
	while (true)
	{
		cout << ">>>";
		getline(cin, input);
		if (input == "quit")break;

		try 
		{
			output = Parser::executeCommand(input);
		}
		catch (InterpreterException e)
		{
			cout << e.what()+"\n";
		}

		if (output != nullptr)
		{
			if (output->isPrintable())cout << output->toString()+"\n";
			if (output->_isTemp)delete output;
		}
		output = nullptr;
	}
    return 0;
}


