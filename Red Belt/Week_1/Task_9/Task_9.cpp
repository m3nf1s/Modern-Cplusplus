#include "test_runner.h"
#include "paginator.h"
#include "tests.h"

#include <numeric>

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestPageCounts);
	RUN_TEST(tr, TestLooping);
	RUN_TEST(tr, TestModification);
	RUN_TEST(tr, TestPageSizes);
	RUN_TEST(tr, TestConstContainer);
	RUN_TEST(tr, TestPagePagination);
}