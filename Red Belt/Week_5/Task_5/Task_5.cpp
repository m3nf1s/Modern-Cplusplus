﻿#include "simple_vector_2.h"
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>


void TestConstruction() 
{
    SimpleVector<int> empty;
    ASSERT_EQUAL(empty.Size(), 0u);
    ASSERT_EQUAL(empty.Capacity(), 0u);
    ASSERT(empty.begin() == empty.end());

    SimpleVector<std::string> five_strings(5);
    ASSERT_EQUAL(five_strings.Size(), 5u);
    ASSERT(five_strings.Size() <= five_strings.Capacity());
    for (auto& item : five_strings)
    {
        ASSERT(item.empty());
    }
    five_strings[2] = "Hello";
    ASSERT_EQUAL(five_strings[2], "Hello");
}

void TestPushBack() 
{
    SimpleVector<int> v;
    for (int i = 10; i >= 1; --i)
    {
        v.PushBack(i);
        ASSERT(v.Size() <= v.Capacity());
    }
    std::sort(std::begin(v), std::end(v));

    const std::vector<int> expected = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    ASSERT(std::equal(std::begin(v), std::end(v), std::begin(expected)));
}

class StringNonCopyable : public std::string
{
public:
    using std::string::string;
    StringNonCopyable(std::string&& other) : std::string(move(other)) {}
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() 
{
    SimpleVector<StringNonCopyable> strings;
    static const int SIZE = 10;
    for (int i = 0; i < SIZE; ++i) 
    {
        strings.PushBack(StringNonCopyable(std::to_string(i)));
    }
    for (int i = 0; i < SIZE; ++i) 
    {
        ASSERT_EQUAL(strings[i], std::to_string(i));
    }
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestConstruction);
    RUN_TEST(tr, TestPushBack);
    RUN_TEST(tr, TestNoCopy);
    return 0;
}