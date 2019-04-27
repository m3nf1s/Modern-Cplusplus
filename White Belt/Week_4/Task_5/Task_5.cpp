/*
 * В этом задании вам предстоит написать две небольшие программы.
 * Каждый пункт - отдельная задача, решение отправляйте в поле с соответствующим номером.
 * 
 * Часть 2
 * Снова считайте все содержимое файла input.txt, но на этот раз выведите его в файл output.txt.
 * Точно так же гарантируется, что содержимое файла input.txt заканчивается переводом строки.
 */
 
#include <fstream>
#include <string>

int main()
{
	std::fstream input("input.txt");
	std::ofstream output("output.txt");

	if(input)
	{
		std::string line;
		while (std::getline(input, line))
		{
			output << line << std::endl;			
		}
	}
}