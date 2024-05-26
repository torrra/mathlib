#include <iostream>

#include <catch2/catch_session.hpp>

#if (WIN32)

#include "TestCaller.h"

int main(void)
{
	std::vector<const char*>	arguments;

	// Avoid using Visual Studio's command line tool,
	// manually add relevant tests
	AddTests(arguments);

	// Get address of first char array to use as char* argv[]
	return Catch::Session().run((int)arguments.size(), &arguments[0]);
}

#else

int main(int argc, char* argv[])
{
	// Get arguments from the command line if not
	// running on Windows
	return Catch::Session().run(argc, argv);
}

#endif