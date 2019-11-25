#include "learner.h"

int Learner::Learn(const vector<string>& words)
{
	int newWords = 0;
	for (const auto& word : words)
	{
		if (dict.insert(word).second)
		{
			++newWords;
		}
	}
	return newWords;
}

vector<string> Learner::KnownWords()
{
	return { dict.begin(), dict.end() };
}