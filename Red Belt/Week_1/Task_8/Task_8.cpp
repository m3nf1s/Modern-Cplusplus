#include "Deque.h"
#include "test_runner.h"
#include "tests.h"

#include <iostream>



int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestEmpty);
	RUN_TEST(tr, TestSize);
	RUN_TEST(tr, TestOperator);
	RUN_TEST(tr, TestAt);
	RUN_TEST(tr, TestFront);
	RUN_TEST(tr, TestBack);

	return 0;
}
