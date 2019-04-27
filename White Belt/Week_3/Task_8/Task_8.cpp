/*
	Определите тип Incognizable, для которого следующий код будет корректен:
*/

#include <iostream>

class Incognizable
{	
public:
	Incognizable() 
	{
		x = 0;
		y = 0;
	};
	
	Incognizable(int a)
	{
		x = a;
		y = 0;
	};
	
	Incognizable(int a, int b) 
	{
		x = a;
		y = b;
	};
	
private:
	int x;
	int y;
};
int main()
{
	Incognizable a;
	Incognizable b = {};
	Incognizable c = { 0 };
	Incognizable d = { 0, 1 };
}