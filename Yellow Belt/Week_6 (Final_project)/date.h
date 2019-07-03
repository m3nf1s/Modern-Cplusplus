#pragma once

//хранит в себе дату год-мес€ц-день
class Date
{
public:
	explicit Date(int year, int month, int day) : year_(year), month_(month), day_(day) {}
private:
	const int year_;
	const int month_;
	const int day_;
};