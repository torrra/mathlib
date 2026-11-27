#include <iostream>

#include <catch2/catch_session.hpp>


#if (WIN32)

#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW

#endif  // DBG_NEW

#endif  // _DEBUG

#include "TestCaller.h"

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

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

#endif // WIN32