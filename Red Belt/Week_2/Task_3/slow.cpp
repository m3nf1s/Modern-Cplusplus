#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class RouteManager
{
public:
  void AddRoute(int start, int finish)                                                      // Total: O(log(Q))
  {
    reachable_lists_[start].push_back(finish);                                              // O(log(Q) + Arm O(1))
    reachable_lists_[finish].push_back(start);                                              // O(log(Q) + Arm O(1))
  }

  int FindNearestFinish(int start, int finish) const                                        // Total: O(Q)
  {
    int result = abs(start - finish);                                                       // O(1)
    if (reachable_lists_.count(start) < 1)                                                  // O(log(Q)
	  {
        return result;
    }

    const vector<int>& reachable_stations = reachable_lists_.at(start);                     // O(1)

    if (!reachable_stations.empty())                                                        // O(1)
	  {
      result = min(                                                                         // O(1)
          result,
          abs(finish - *min_element(                                                        // O(1)
              begin(reachable_stations), end(reachable_stations),
              [finish](int lhs, int rhs) { return abs(lhs - finish) < abs(rhs - finish); }  // O(Q)
          ))
      );
    }
    return result;
  }
private:
  map<int, vector<int>> reachable_lists_;
};


int main()                                                                                  // Total: O(Q^2)
{
  RouteManager routes;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id)
  {
    string query_type;
    cin >> query_type;
    int start, finish;
    cin >> start >> finish;
    if (query_type == "ADD")
	{
      routes.AddRoute(start, finish);
    } else if (query_type == "GO")
	{
      cout << routes.FindNearestFinish(start, finish) << "\n";
    }
  }

  return 0;
}
