/*
	Вы подключились к команде, которая разрабатывает web-сервер комментариев.
	Этот сервер позволяет создавать новых пользователей, публиковать новые объявления,
	а также читать все объявления выбранного пользователя.
	Кроме того команда недавно озаботилась борьбой со спамерами.
	Если какой-то пользователь признаётся спамером, он блокируется, после чего ему выдаётся страница капчи,
	на которой он должен подтвердить, что он человек.
	В случае успешного ввода капчи пользователь разблокируется и получает возможность снова оставлять комментарии.

	Для выявления спамеров используется довольно простой алгоритм — спамером признаётся пользователь,
	отправивший три комментария подряд (см. реализацию сервера в заготовке решения).

	Сервер работает по протоколу HTTP и обрабатывает следующие запросы:
	*	POST /add_user — добавляет нового пользователя и возвращает ответ 200 OK,
		в теле которого содержится идентификатор вновь добавленного пользователя (см. реализацию в заготовке решения)
	*	POST /add_comment — извлекает из тела запроса идентификатор пользователя и новый комментарий;
		если пользователь признаётся спамером, возвращает 302 Found c заголовком Location: /captcha,
		переводя пользователя на страницу капчи, в противном случае сохраняет комментарий и возвращает 200 OK
	*	GET /user_comments?user_id=[id] — возвращает ответ 200 OK,
		в теле которого содержатся все комментарии пользователя id, разделённые переводом строки
	*	GET /captcha — возвращает ответ 200 OK,
		в теле которого содержится страница капчи
		(для простоты в этой задаче мы просто возвращаем вопрос, на который надо ответить пользователю,
		на практике это может быть полноценная HTML-страница)
	*	POST /checkcaptcha — извлекает из тела запроса ответ на вопрос капчи;
		если он верен, разблокирует пользователя и возвращает 200 OK,
		если нет — возвращает 302 Found c заголовком Location: /captcha
	*	если метод запроса не POST и не GET или путь запроса не совпадает ни с одним из вышеперечисленных,
		сервер отвечает 404 Not found.

	Web-сервер в коде реализован с помощью класса CommentServer:
		struct HttpRequest
		{
			string method, path, body;
			map<string, string> get_params;
		};

		class CommentServer
		{
		public:
			void ServeRequest(const HttpRequest& req, ostream& response_output);
		private:
		  ...
		};

	Его метод ServeRequest принимает HTTP-запрос,
	обрабатывает его и записывает HTTP-ответ в выходной поток response_output
	(этот поток может быть привязан к сетевому соединению).
	При записи HTTP-ответа в выходной поток используется следующий формат:
		HTTP/1.1 [код ответа] [комментарий]
		[Заголовок 1]: [Значение заголовка 1]
		[Заголовок 2]: [Значение заголовка 2]
		...
		[Заголовок N]: [Значение заголовка N]
		<пустая строка>
		[Тело ответа]

	*	код ответа — это 200, 302, 404 и т.д.
	*	комментарий — "Found", "OK", "Not found" и т.д.
	*	Заголовок X — имя заголовка, например, "Location"
	*	тело ответа — например, это содержимое страницы капчи или идентификатор вновь добавленного пользователя;
		при этом, если тело ответа непустое, в ответе обязательно должен присутствовать заголовок Content-Length,
		значение которого равно длине ответа в байтах.

	Пример ответа на запрос /add_user, в котором возвращается идентификатор нового пользователя, равный 12.
	Content-Length равен 2, потому что "12" — это два символа:
		HTTP/1.1 200 OK
		Content-Length: 2

		12

	С нашим сервером есть проблема — иногда он ничего не отвечает на запросы,
	а иногда возвращает некорректно сформированные ответы.
	Источник этих проблем в том, что ответы формируются вручную каждый раз (см. заготовку решения).
	Из-за этого мы то перевод строки забыли, то добавили лишний, то в коде ответа опечатались.

	Вы решили избавиться от всех проблем разом и провести следующий рефакторинг:
	*	разработать класс HttpResponse, который будет представлять собой HTTP-ответ;
		в operator << вы решили инкапсулировать формат вывода HTTP-ответа в поток
	*	сделать новую сигнатуру метода ServeRequest — HttpResponse ServeRequest(const HttpRequest& req),
		— которая на этапе компиляции будет гарантировать,
		что наш сервер всегда возвращает хоть какой-то ответ
		(если мы забудем это сделать, компилятор выдаст предупреждение "control reaches end of non-void function")
	*	записывать ответ сервера в выходной поток в одном единственном месте, в котором вызывается метод ServeRequest

	Интерфейс класса HttpResponse вы решили сделать таким:
		enum class HttpCode {
			Ok = 200,
			NotFound = 404,
			Found = 302,
		};

		class HttpResponse {
		public:
		  explicit HttpResponse(HttpCode code);

		  HttpResponse& AddHeader(string name, string value);
		  HttpResponse& SetContent(string a_content);
		  HttpResponse& SetCode(HttpCode a_code);

		  friend ostream& operator << (ostream& output, const HttpResponse& resp);
		};

	Методы AddHeader, SetContent и SetCode должны возвращать ссылку на себя,
	чтобы иметь возможность сформировать ответ в одной строке с помощью chaining'а:
	return HttpResponse(HttpCode::Found).AddHeader("Location", "/captcha");.
	Перечисление HttpCode, передаваемое в конструктор класса HttpResponse,
	гарантирует, что мы не ошибёмся в коде ответа.

	Этот рефакторинг вам и предстоит выполнить в этой задаче.
	Пришлите на проверку cpp-файл, который:
	*	содержит реализацию класса HttpResponse,
	*	содержит реализацию класса CommentServer с публичным методом HttpResponse ServeRequest(const HttpRequest& req).

	Сервер должен реализовывать описанный выше протокол.

	Уточнения к реализации класса HttpResponse:
	*	Методы AddHeader, SetContent, SetCode должны возвращать ссылку на объект, для которого они вызваны
	*	Метод AddHeader всегда добавляет к ответу новый заголовок, даже если заголовок с таким именем уже есть
	*	operator<< для класса HttpResponse должен выводить HTTP-ответ в формате,
		описанном выше в описании метода ServerRequest;
		при этом заголовки можно выводить в произвольном порядке.
		Если у HTTP-ответа есть непустое содержимое, то необходимо вывести ровно один заголовок "Content-Length",
		значение которого равно размеру содержимого в байтах.

*/
#include "test_runner.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <map>
#include <optional>
#include <unordered_set>

enum class HttpCode
{
	Ok = 200,
	NotFound = 404,
	Found = 302,
};

std::ostream& operator << (std::ostream& os, const HttpCode& code)
{
	switch (code)
	{
	case HttpCode::Ok:
		os << "200 OK";
		break;
	case HttpCode::Found:
		os << "302 Found";
		break;
	case HttpCode::NotFound:
		os << "404 Not found";
		break;
	default:
		os << "Wrong http code";
		break;
	}
	return os;
}

struct HttpHeader
{
	std::string name, value;
};

std::ostream& operator<<(std::ostream& output, const HttpHeader& h)
{
	return output << h.name << ": " << h.value;
}

class HttpResponse
{
public:
	explicit HttpResponse(HttpCode code);

	HttpResponse& AddHeader(std::string name, std::string value);
	HttpResponse& SetContent(std::string a_content);
	HttpResponse& SetCode(HttpCode a_code);

	friend std::ostream& operator << (std::ostream& output, const HttpResponse& resp);

private:
	HttpCode code_;
	std::vector<HttpHeader> header_;
	std::string content_;
};

HttpResponse::HttpResponse(HttpCode code)
	:code_(code)
{
}

HttpResponse& HttpResponse::AddHeader(std::string name, std::string value)
{
	header_.push_back(HttpHeader{ std::move(name), std::move(value) });
	return *this;
}

HttpResponse& HttpResponse::SetContent(std::string a_content)
{
	content_ = std::move(a_content);
	return *this;
}

HttpResponse& HttpResponse::SetCode(HttpCode a_code)
{
	code_ = a_code;
	return *this;
}

std::ostream& operator << (std::ostream& output, const HttpResponse& resp)
{
	output << "HTTP/1.1 " << resp.code_ << '\n';

	for (const auto& h : resp.header_)
	{
		output << h << '\n';
	}

	if (!resp.content_.empty())
	{
		output << "Content-Length: " << resp.content_.size() << '\n';
	}

	return output << '\n' << resp.content_;
}

struct HttpRequest
{
	std::string method, path, body;
	std::map<std::string, std::string> get_params;
};

std::pair<std::string, std::string> SplitBy(const std::string& what, const std::string& by)
{
	size_t pos = what.find(by);
	if (by.size() < what.size() && pos < what.size() - by.size())
	{
		return { what.substr(0, pos), what.substr(pos + by.size()) };
	}
	else
	{
		return { what, {} };
	}
}

template<typename T>
T FromString(const std::string& s)
{
	T x;
	std::istringstream is(s);
	is >> x;
	return x;
}

std::pair<size_t, std::string> ParseIdAndContent(const std::string& body)
{
	auto [id_string, content] = SplitBy(body, " ");
	return { FromString<size_t>(id_string), content };
}

struct LastCommentInfo
{
	size_t user_id, consecutive_count;
};

class CommentServer
{
private:
	std::vector<std::vector<std::string>> comments_;
	std::optional<LastCommentInfo> last_comment;
	std::unordered_set<size_t> banned_users;

public:
	HttpResponse ServeRequest(const HttpRequest& req)
	{
		if (req.method == "POST")
		{
			if (req.path == "/add_user")
			{
				return ServerAddUser(req);
			}
			else if (req.path == "/add_comment")
			{
				return ServerAddComment(req);
			}
			else if (req.path == "/checkcaptcha")
			{
				return ServerCheckCaptcha(req);
			}
			else
			{
				return HttpResponse(HttpCode::NotFound);
			}
		}
		else if (req.method == "GET")
		{
			if (req.path == "/user_comments")
			{
				return ServerUserComments(req);
			}
			else if (req.path == "/captcha")
			{
				return ServerCaptcha(req);
			}
		}
		return HttpResponse(HttpCode::NotFound);
	}

private:
	HttpResponse ServerAddUser(const HttpRequest& req)
	{
		comments_.emplace_back();
		auto response = std::to_string(comments_.size() - 1);
		return HttpResponse(HttpCode::Ok).SetContent(std::move(response));
	}

	HttpResponse ServerAddComment(const HttpRequest& req)
	{
		auto [user_id, comment] = ParseIdAndContent(req.body);

		if (!last_comment || last_comment->user_id != user_id)
		{
			last_comment = LastCommentInfo{ user_id, 1 };
		}
		else if (++last_comment->consecutive_count > 3)
		{
			banned_users.insert(user_id);
		}

		if (banned_users.count(user_id) == 0)
		{
			comments_[user_id].push_back(std::string(comment));
			return HttpResponse(HttpCode::Ok);
		}
		else
		{
			return HttpResponse(HttpCode::Found).AddHeader("Location", "/captcha");
		}
	}

	HttpResponse ServerCheckCaptcha(const HttpRequest& req)
	{
		if (auto [id, response] = ParseIdAndContent(req.body); response == "42")
		{
			banned_users.erase(id);
			if (last_comment && last_comment->user_id == id)

			{
				last_comment.reset();
			}
			return HttpResponse(HttpCode::Ok);
		}
		else
		{
			return HttpResponse(HttpCode::Found).AddHeader("Location", "/captcha");
		}
	}

	HttpResponse ServerUserComments(const HttpRequest& req)
	{
		auto user_id = FromString<size_t>(req.get_params.at("user_id"));
		std::string response;
		for (const std::string& c : comments_[user_id])
		{
			response += c + '\n';
		}
		return HttpResponse(HttpCode::Ok).SetContent(std::move(response));
	}

	HttpResponse ServerCaptcha(const HttpRequest& req)
	{
		return HttpResponse(HttpCode::Ok).SetContent("What's the answer for The Ultimate Question of Life, the Universe, and Everything?");
	}
};

bool operator==(const HttpHeader& lhs, const HttpHeader& rhs)
{
	return lhs.name == rhs.name && lhs.value == rhs.value;
}

struct ParsedResponse
{
	int code;
	std::vector<HttpHeader> headers;
	std::string content;
};

std::istream& operator >>(std::istream& input, ParsedResponse& r)
{
	std::string line;
	std::getline(input, line);

	{
		std::istringstream code_input(line);
		std::string dummy;
		code_input >> dummy >> r.code;
	}

	size_t content_length = 0;

	r.headers.clear();
	while (getline(input, line) && !line.empty())
	{
		if (auto [name, value] = SplitBy(line, ": "); name == "Content-Length")
		{
			std::istringstream length_input(value);
			length_input >> content_length;
		}
		else
		{
			r.headers.push_back({ std::move(name), std::move(value) });
		}
	}

	r.content.resize(content_length);
	input.read(r.content.data(), r.content.size());
	return input;
}

void Test(CommentServer& srv, const HttpRequest& request, const ParsedResponse& expected)
{
	std::stringstream ss;
	HttpResponse http_resp = srv.ServeRequest(request);
	ss << http_resp;

	ParsedResponse resp;
	ss >> resp;
  	ASSERT_EQUAL(resp.code, expected.code);
	ASSERT_EQUAL(resp.headers, expected.headers);
	ASSERT_EQUAL(resp.content, expected.content);
}

template <typename CommentServer>
void TestServer()
{
	CommentServer cs;

	const ParsedResponse ok{ 200 };
	const ParsedResponse redirect_to_captcha{ 302, {{"Location", "/captcha"}}, {} };
	const ParsedResponse not_found{ 404 };

	Test(cs, { "POST", "/add_user" }, { 200, {}, "0" });
	Test(cs, { "POST", "/add_user" }, { 200, {}, "1" });
	Test(cs, { "POST", "/add_comment", "0 Hello" }, ok);
	Test(cs, { "POST", "/add_comment", "1 Hi" }, ok);
	Test(cs, { "POST", "/add_comment", "1 Buy my goods" }, ok);
	Test(cs, { "POST", "/add_comment", "1 Enlarge" }, ok);
	Test(cs, { "POST", "/add_comment", "1 Buy my goods" }, redirect_to_captcha);
	Test(cs, { "POST", "/add_comment", "0 What are you selling?" }, ok);
	Test(cs, { "POST", "/add_comment", "1 Buy my goods" }, redirect_to_captcha);
	Test(
		cs,
		{ "GET", "/user_comments", "", {{"user_id", "0"}} },
		{ 200, {}, "Hello\nWhat are you selling?\n" }
	);
	Test(
		cs,
		{ "GET", "/user_comments", "", {{"user_id", "1"}} },
		{ 200, {}, "Hi\nBuy my goods\nEnlarge\n" }
	);
	Test(
		cs,
		{ "GET", "/captcha" },
		{ 200, {}, {"What's the answer for The Ultimate Question of Life, the Universe, and Everything?"} }
	);
	Test(cs, { "POST", "/checkcaptcha", "1 24" }, redirect_to_captcha);
	Test(cs, { "POST", "/checkcaptcha", "1 42" }, ok);
	Test(cs, { "POST", "/add_comment", "1 Sorry! No spam any more" }, ok);
	Test(
		cs,
		{ "GET", "/user_comments", "", {{"user_id", "1"}} },
		{ 200, {}, "Hi\nBuy my goods\nEnlarge\nSorry! No spam any more\n" }
	);

	Test(cs, { "GET", "/user_commntes" }, not_found);
	Test(cs, { "POST", "/add_uesr" }, not_found);
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestServer<CommentServer>);
}
