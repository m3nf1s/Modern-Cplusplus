#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Learner
{
private:
	set<string> dict;

public:
	int Learn(const vector<string>& words);

	vector<string> KnownWords();
};
