#include "learner.h"
#include "profiler.h"

#include <iostream>
#include <sstream>

using namespace std;
int main()
{
	Learner learner;
	string line;
	while (getline(cin, line))
	{
		vector<string> words;
		stringstream ss(line);
		string word;
		while (ss >> word)
		{
			words.push_back(word);
		}
		{
			LOG_DURATION("Learn");
			cout << learner.Learn(words) << "\n";
		}
		
	}

	cout << "=== known words ===\n";
	{
		LOG_DURATION("KnowWords");
		for (auto word : learner.KnownWords())
		{
			cout << word << "\n";
		}
	}
}