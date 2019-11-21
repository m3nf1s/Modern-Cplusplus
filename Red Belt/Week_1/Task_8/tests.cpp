#include "tests.h"
#include "Deque.h"
#include "test_runner.h"

void TestEmpty()
{
	Deque<int> deq;
	ASSERT_EQUAL(deq.Empty(), true);

	deq.PushBack(1);
	ASSERT_EQUAL(deq.Empty(), false);

	Deque<double> d;
	ASSERT_EQUAL(d.Empty(), true);

	d.PushFront(2.0);
	ASSERT_EQUAL(d.Empty(), false);
}

void TestSize()
{
	Deque<int> deq;
	ASSERT_EQUAL(deq.Size(), 0);

	deq.PushBack(10);
	ASSERT_EQUAL(deq.Size(), 1);

	deq.PushFront(-10);
	ASSERT_EQUAL(deq.Size(), 2);

	for (int i = 5; i < 7; ++i)
	{
		deq.PushBack(i);
		deq.PushFront(i);
	}

	ASSERT_EQUAL(deq.Size(), 6);
}

void TestOperator()
{
	Deque<int> deq;

	deq.PushFront(1);
	ASSERT_EQUAL(deq[0], 1);

	deq.PushBack(2);
	ASSERT_EQUAL(deq[1], 2);

	deq.PushFront(-10);
	ASSERT_EQUAL(deq[1], 1);
}

void TestAt()
{
	Deque<int> deq;

	deq.PushFront(10);
	ASSERT_EQUAL(deq.At(0), 10);

	deq.PushFront(20);
	ASSERT_EQUAL(deq.At(1), 10);

	deq.PushBack(-10);
	ASSERT_EQUAL(deq.At(2), -10);

	for (int i = -20; i > -50; i -= 10)
	{
		deq.PushBack(i);
	}

	ASSERT_EQUAL(deq.At(5), -40);
}

void TestFront()
{
	Deque<int> deq;

	deq.PushBack(-100);
	ASSERT_EQUAL(deq.Front(), -100);

	deq.PushFront(100);
	ASSERT_EQUAL(deq.Front(), 100);
}

void TestBack()
{
	Deque<int> deq;

	deq.PushFront(std::numeric_limits<int>::max());
	ASSERT_EQUAL(deq.Back(), std::numeric_limits<int>::max());

	deq.PushBack(std::numeric_limits<int>::min());
	ASSERT_EQUAL(deq.Back(), std::numeric_limits<int>::min());
}