#pragma once

#include "date.h"
#include <string>
#include <memory>

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
	bool Evaluate(const Date& date, const string& event) override;
};

class DateComparisonNode : public Node
{
public: 
	DateComparisonNode(Comparison cmp, const Date& date) : cmp_(cmp), date_(date) {}
	bool Evaluate(const Date& date, const string& event) override;
private:
	const Comparison cmp_;
	const Date date_;
};

class EventComparisonNode : public Node
{
public:
	EventComparisonNode(Comparison cmp, const string& event) : cmp_(cmp), event_(event) {}
	bool Evaluate(const Date& date, const string& event) override;
private:
	const Comparison cmp_;
	const string event_;
};

class LogicalOperationNode : public Node
{
public:
	LogicalOperationNode(LogicalOperation lop, const shared_ptr<Node>& lhs, const shared_ptr<Node>& rhs) : logop_(lop), lhs_(lhs), rhs_(rhs) {}
	bool Evaluate(const Date& date, const string& event) override;
private:
	const LogicalOperation logop_;
	const shared_ptr<Node> lhs_;
	const shared_ptr<Node> rhs_;
};