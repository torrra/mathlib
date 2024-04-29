#include <catch2/catch_session.hpp>

#include "TestCaller.h"

#include <iostream>

int main (int argc, char* argv[])
{
    std::vector<const char*> arguments;


#if (WIN32)
    AddTests(arguments);
#else
	
	for (int i = 0; i < argc; i++)
	{
		arguments.push_back(argv[i]);
	}

#endif


    return Catch::Session().run((int) arguments.size(), &arguments[0]);
}