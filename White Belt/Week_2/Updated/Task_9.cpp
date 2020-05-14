/*
* Люди стоят в очереди, но никогда не уходят из её начала, зато могут приходить в конец и уходить оттуда.
* Более того, иногда некоторые люди могут прекращать и начинать беспокоиться из-за того, что очередь не продвигается.
* 
* Реализуйте обработку следующих операций над очередью:
* WORRY i: пометить i-го человека с начала очереди (в нумерации с 0) как беспокоящегося;
* QUIET i: пометить i-го человека как успокоившегося;
* COME k: добавить k спокойных человек в конец очереди;
* COME -k: убрать k человек из конца очереди;
* WORRY_COUNT: узнать количество беспокоящихся людей в очереди.
* Изначально очередь пуста.
* 
* Формат ввода
* Количество операций Q, затем описания операций.
*  
* Для каждой операции WORRY i и QUIET i гарантируется, что человек с номером i существует в очереди на момент операции.
* Для каждой операции COME -k гарантируется, что k не больше текущего размера очереди.
* 
* Формат вывода
* Для каждой операции WORRY_COUNT выведите одно целое число — количество беспокоящихся людей в очереди.
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    size_t command_count;
    std::cin >> command_count;
    std::vector<bool> queue;
    
    for(size_t i = 0; i < command_count; ++i)
    {
        std::string command;
        std::cin >> command;

        if(command == "COME")
        {
            int count;
            std::cin >> count;
            queue.resize(queue.size() + count);
        }
        else if(command == "WORRY" || command == "QUIET")
        {
            size_t index;
            std::cin >> index;
            queue[index] = (command == "WORRY");
        }
        else if(command == "WORRY_COUNT")
        {
            std::cout << std::count(queue.begin(), queue.end(), true) << std::endl;
        }        
    }
}