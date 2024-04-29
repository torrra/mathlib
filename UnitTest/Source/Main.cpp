#include <catch2/catch_session.hpp>

#include "TestCaller.h"

#include <iostream>



#if (WIN32)

int main(void)
{
	std::vector<const char*>	arguments;

	AddTests(arguments);

	return Catch::Session().run((int)arguments.size(), &arguments[0]);
}

#else

int main(int argc, char* argv[])
{
	return Catch::Session().run(argc, argv);
}

#endif