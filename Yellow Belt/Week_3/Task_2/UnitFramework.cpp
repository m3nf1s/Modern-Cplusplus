#include "UnitFramework.h"

void Assert(bool b, const std::string& hint)
{
	AssertEqual(b, true, hint);
}

UnitFramework::~UnitFramework()
{
	if (fail_count > 0)
	{
		std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
		exit(1);
	}
}