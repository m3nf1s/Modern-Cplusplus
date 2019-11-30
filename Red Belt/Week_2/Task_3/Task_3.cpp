#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

class RouteManager
{
public:
	void AddRoute(int start, int finish)						// Total: O(log(Q))					
	{
		reachable_lists_[start].insert(finish);					// O(log(Q) + log(Q))	
		reachable_lists_[finish].insert(start);					// O(log(Q) + log(Q))	
	}

	int FindNearestFinish(int start, int finish) const				// Total : O(log(Q))	
	{
		int result = abs(start - finish);					// O(1)
		if (reachable_lists_.count(start) < 1)					// O(log(Q))	
		{  
			return result;
		}

		const std::set<int>& reachable_stations = reachable_lists_.at(start);	// O(1)

		const auto finish_pos = reachable_stations.lower_bound(finish);		// O(logQ)

		if (finish_pos != reachable_stations.end())				// O(1)
		{
			result = std::min(result, abs(finish - *finish_pos));		// O(1)
		}
		if (finish_pos != reachable_stations.begin())				// O(1)
		{
			result = std::min(result, abs(finish - *prev(finish_pos)));	// O(1)
		} 

		return result;
	}

private:
	std::map<int, std::set<int>> reachable_lists_;
};


int main()										// Total: O(Q log(Q))
{

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	RouteManager routes;

	int query_count;
	std::cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id)			// O(Q)
	{
		std::string query_type;
		std::cin >> query_type;
		int start, finish;
		std::cin >> start >> finish;
		if (query_type == "ADD")
		{
			routes.AddRoute(start, finish);
		}
		else if (query_type == "GO")
		{
			std::cout << routes.FindNearestFinish(start, finish) << "\n";
		}
	}

	return 0;
}