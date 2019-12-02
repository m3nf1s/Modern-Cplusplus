/*
	Вам даны задача и её решение — верное, но не удовлетворяющее заданным ограничениям на время работы.
	Переработайте это решение и сдайте в систему.

	Условие
	Разработайте систему стимулирования чтения электронных книг.
	Для простоты будем считать, что книга всего одна, но её одновременно читают много людей.
	Необходимо следить за прогрессом чтения у всех пользователей и выводить мотивирующие уведомления.
	А именно, ваша программа должна обрабатывать следующие события:
	*	READ user page — сохранить факт того, что пользователь под номером user дочитал книгу до страницы page.
		Если ранее такой пользователь не встречался, необходимо его добавить.
		Гарантируется, что в рамках одного пользователя номера страниц в соответствующих ему событиях возрастают.
	*	CHEER user — сообщить пользователю user, какая доля существующих пользователей (не считая его самого) прочитала меньшую часть книги, чем он.
		Если этот пользователь на данный момент единственный, доля считается равной 1.
		Если для данного пользователя пока не было ни одного события READ, доля считается равной 0,
			а сам пользователь не учитывается при вычислении долей для других пользователей до тех пор, пока для него не случится событие READ.

	Формат входных данных
	В первой строке вводится количество запросов Q — натуральное число, не превосходящее 10^6.
	В следующих Q строках в соответствии с описанным выше форматом вводятся запросы.
	Гарантируется, что все вводимые числа целые и положительные, при этом номера пользователей не превосходят 10^5,
		а номера страниц не превосходят 1000.

	Формат выходных данных
	Для каждого запроса CHEER user выведите единственное вещественное число от 0 до 1 — долю пользователей, прочитавших меньше страниц, чем user.
	Формат вывода этого числа должен быть в точности таким же, как в опубликованном ниже медленном решении.

	Ограничения
	4 секунды на выполнение всех запросов.
	Все описанные в условии гарантии действительно справедливы для всех тестов, на которых будет запускаться ваша программа.
	Проверять корректность тестов не нужно.
*/

#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>

class ReadingManager
{
public:
	ReadingManager()
		: user_page_counts_(MAX_USER_COUNT_ + 1, 0)
		, page_user_counts_(MAX_PAGES_COUNT_ + 1, 0)
		, pages_rating_(MAX_PAGES_COUNT_ + 1, 0.0)
		, total_users_(0)
	{
	}

	void Read(int user_id, int page_count)
	{
		if (user_page_counts_[user_id] == 0)
		{
			++total_users_;
		}
		else
		{
			--page_user_counts_[user_page_counts_[user_id]];
		}

		user_page_counts_[user_id] = page_count;
		++page_user_counts_[page_count];
	}

	double Cheer(int user_id)
	{
		if (user_page_counts_[user_id] == 0)
		{
			return 0;
		}
		if (total_users_ == 1)
		{
			return 1;
		}

		UpdateRating(user_page_counts_[user_id]);

		return pages_rating_[user_page_counts_[user_id]];
	}

private:
	static const int MAX_USER_COUNT_ = 100'000;
	static const int MAX_PAGES_COUNT_ = 1'000;

	std::vector<int> user_page_counts_;
	std::vector<int> page_user_counts_;
	std::vector<double> pages_rating_;

	int total_users_;

	void UpdateRating(int page_count)
	{
		int user_count = 0;
		for (int i = 0; i < page_count; ++i)
		{
			user_count += page_user_counts_[i];
		}
		pages_rating_[page_count] = static_cast<double>(user_count) / (total_users_ - 1);
	}
};


int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

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