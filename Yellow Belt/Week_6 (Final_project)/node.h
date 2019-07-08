#pragma once

#include "date.h"
#include <string>

using namespace std;

enum class Comparison
{
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual,
};

enum class LogicalOperation
{
	Or,
	And,
};

class Node
{
public:
	bool virtual Evaluate(const Date& date, const string& event) = 0;
};

class EmptyNode : public Node
{
public:

};

class DateComparisonNode : public Node
{
public: 
	DateComparisonNode(const Comparison& cmp, const Date& date) : cmp_(cmp), date_(date) {}

private:
	const Comparison cmp_;
	const Date date_;
};

class EventComparisonNode : public Node
{
public:
	EventComparisonNode(const Comparison& cmp, const string& event) : cmp_(cmp), event_(event) {}
private:
	const Comparison cmp_;
	const string event_;
};

class LogicalOperationNode : public Node
{
public:
	LogicalOperationNode(const LogicalOperation& lop, const shared_ptr<Node>& lhs, const shared_ptr<Node>& rhs) : logop_(lop), lhs_(lhs), rhs_(rhs) {}
private:
	const LogicalOperation logop_;
	const shared_ptr<Node> lhs_;
	const shared_ptr<Node> rhs_;
};