/*
В этой задаче вам нужно разработать классы SmsNotifier и EmailNotifier,
	отправляющие уведомления в виде SMS и e-mail соответственно, а также абстрактный базовый класс для них.

Вам даны функции SendSms и SendEmail, которые моделируют отправку SMS и e-mail.
		void SendSms(const string& number, const string& message);
		void SendEmail(const string& email, const string& message);

Разработайте:
	1. Абстрактный базовый класс INotifier, у которого будет один чисто виртуальный метод void Notify(const string& message).
	2. Класс SmsNotifier, который:
		1) является потомком класса INotifier;
		2) в конструкторе принимает один параметр типа string — номер телефона;
		3) переопределяет метод Notify и вызывает из него функцию SendSms.
	3. Класс EmailNotifier, который;
		1) является потомком класса INotifier;
		2) в конструкторе принимает один параметр типа string — адрес электронной почты;
		3) переопределяет метод Notify и вызывает из него функцию SendEmail.
*/

#include <iostream>
#include <string>

void SendSms(const std::string& number, const std::string& message)
{
	std::cout << "Send '" << message << "' to number " << number << std::endl;
}

void SendEmail(const std::string& email, const std::string& message)
{
	std::cout << "Send '" << message << "' to number " << email << std::endl;
}

class INotifier
{
public:
	virtual void Notify(const std::string& message) const = 0;
};

class SmsNotifier : public INotifier
{
public:
	SmsNotifier(const std::string& phone_number) : phone_number_(phone_number){}
	void Notify(const std::string& message) const override
	{
		SendSms(phone_number_, message);
	}

private:
	const std::string phone_number_;
};

class EmailNotifier : public INotifier
{
public:
	EmailNotifier(const std::string& email_adress) : email_adress_(email_adress) {}
	void Notify(const std::string& message) const override
	{
		SendEmail(email_adress_, message);
	}
private:
	std::string email_adress_;
};

void Notify(INotifier& notifier, const std::string& message)
{
	notifier.Notify(message);
}

int main()
{
	SmsNotifier sms{ "+7-495-777-77-77" };
	EmailNotifier email{ "na-derevnyu@dedushke.ru" };

	Notify(sms, "I have White belt in C++");
	Notify(email, "And want a Yellow one");
	return 0;
}