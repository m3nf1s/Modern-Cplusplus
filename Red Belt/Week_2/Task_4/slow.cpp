#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>

class ReadingManager
{
public:
	ReadingManager()
		: user_page_counts_(MAX_USER_COUNT_ + 1, 0)
		, sorted_users_()
		, user_positions_(MAX_USER_COUNT_ + 1, -1)
	{}

	void Read(int user_id, int page_count)
	{
		if (user_page_counts_[user_id] == 0)			// O(1)
		{
			AddUser(user_id);// O(1)
		}

		user_page_counts_[user_id] = page_count;		// O(1)
		int& position = user_positions_[user_id];		// O(1)

		while (position > 0 && page_count > user_page_counts_[sorted_users_[position - 1]])
		{
			SwapUsers(position, position - 1);
		}
	}

	double Cheer(int user_id) const
	{
		if (user_page_counts_[user_id] == 0)	// O(1)
		{
			return 0;
		}
		const int user_count = GetUserCount();	// O(1)
		if (user_count == 1)
		{
			return 1;
		}
		const int page_count = user_page_counts_[user_id]; // O(1)

		int position = user_positions_[user_id]; // O(1)

		while (position < user_count && user_page_counts_[sorted_users_[position]] == page_count)
		{
			++position;
		}

		if (position == user_count)
		{
			return 0;
		}
		// ѕо умолчанию деление целочисленное, поэтому
		// нужно привести числитель к типу double.
		// ѕростой способ сделать это Ч умножить его на 1.0.
		return (user_count - position) * 1.0 / (user_count - 1);
	}

private:
	// —татическое поле не принадлежит какому-то конкретному
	// объекту класса. ѕо сути это глобальна€ переменна€,
	// в данном случае константна€.
	// Ѕудь она публичной, к ней можно было бы обратитьс€ снаружи
	// следующим образом: ReadingManager::MAX_USER_COUNT.
	static const int MAX_USER_COUNT_ = 100'000;

	std::vector<int> user_page_counts_;
	std::vector<int> sorted_users_;   // отсортированы по убыванию количества страниц
	std::vector<int> user_positions_; // позиции в векторе sorted_users_
	// Total: O(1)
	int GetUserCount() const
	{
		return sorted_users_.size();
	}
	// Total: Arm O(1)
	void AddUser(int user_id)									
	{
		sorted_users_.push_back(user_id);						// Arm O(1)
		user_positions_[user_id] = sorted_users_.size() - 1;	// O(1)
	}
	// Total: O(1)
	void SwapUsers(int lhs_position, int rhs_position)
	{
		const int lhs_id = sorted_users_[lhs_position];// O(1)
		const int rhs_id = sorted_users_[rhs_position];// O(1)

		std::swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);	//O(1)
		std::swap(user_positions_[lhs_id], user_positions_[rhs_id]);			//O(1)
	}
};


int main()
{
	// ƒл€ ускорени€ чтени€ данных отключаетс€ синхронизаци€
	// cin и cout с stdio,
	// а также выполн€етс€ отв€зка cin от cout
	std::ios::sync_with_stdio(false);
	//std::cin.tie(nullptr);

	ReadingManager manager;

	int query_count;
	std::cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id)
	{
		std::string query_type;
		std::cin >> query_type;
		int user_id;
		std::cin >> user_id;

		if (query_type == "READ")
		{
			int page_count;
			std::cin >> page_count;
			manager.Read(user_id, page_count);
		}
		else if (query_type == "CHEER")
		{
			std::cout << std::setprecision(6) << manager.Cheer(user_id) << "\n";
		}
	}

	return 0;
}