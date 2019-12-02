/*
	Вам дан класс Logger и макрос LOG

	Параметры макроса LOG — объект класса Logger и строковое сообщение, которое должно быть передано в метод Log.
	В зависимости от настроек объекта класса Logger логируемое сообщение должно предваряться именем файла или номером строки.
	Смотрите юнит-тесты в заготовке решения для более подробного описания поведения.

	Реализуйте макрос LOG так, чтобы он добавлял в логируемое сообщение имя файла
		и номер строки в зависимости от настроек объекта logger. Пришлите на проверку cpp-файл, содержащий
	* реализацию макроса LOG
	* объявление класса Logger, при этом вы можете при необходимости добавлять в него дополнительные поля и методы
	* определения всех методов класса Logger

	Замечание

	Если вы используете Visual Studio, у вас могут не проходить юнит-тесты из заготовки,
		потому что в этой среде макрос __FILE__ раскрывается в абсолютный путь до файла.
	Учитывайте это при отладке своего решения.
*/

#include "test_runner.h"
#include <sstream>
#include <string>
using namespace std;

class Logger
{
public:
	explicit Logger(ostream& output_stream)
		: os(output_stream)
	{
	}

	void SetLogLine(bool value) { log_line = value; }
	void SetLogFile(bool value) { log_file = value; }

	void SetFile(const string& filename) { file = filename; }
	void SetLine(const int& line_number) { line = line_number; }

	void Log(const string& message)
	{
		if (log_file && log_line)
		{
			os << file << ":" << line << ' ';
		}
		else if (log_file)
		{
			os << file << ' ';
		}
		else if (log_line)
		{
			os << "Line " << line << ' ';
		}

		os << message << '\n';
	}
private:
	ostream& os;
	bool log_line = false;
	bool log_file = false;
	string file;
	int line;
};

#define LOG(logger, message)		\
{					\
	logger.SetFile(__FILE__);	\
	logger.SetLine(__LINE__);	\
	logger.Log(message);		\
}


void TestLog()
{
#line 1 "logger.cpp"

	ostringstream logs;
	Logger l(logs);
	LOG(l, "hello");

	l.SetLogFile(true);
	LOG(l, "hello");

	l.SetLogLine(true);
	LOG(l, "hello");

	l.SetLogFile(false);
	LOG(l, "hello");

	string expected = "hello\n";
	expected += "logger.cpp hello\n";
	expected += "logger.cpp:10 hello\n";
	expected += "Line 13 hello\n";
	ASSERT_EQUAL(logs.str(), expected);
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestLog);
}