#pragma once

//������ � ���� ���� ���-�����-����
class Date
{
public:
	explicit Date(int year, int month, int day) : year_(year), month_(month), day_(day) {}
	const int year_;
	const int month_;
	const int day_;
};