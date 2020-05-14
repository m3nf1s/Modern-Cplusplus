/*
* У каждого из нас есть ежемесячные дела, каждое из которых нужно выполнять в конкретный день каждого месяца: оплата счетов за электричество, абонентская плата за связь и пр.
* Вам нужно реализовать работу со списком таких дел, а именно, обработку следующих операций:
* 
* ADD i s
* Добавить дело с названием s в день i.
* 
* NEXT
* Закончить текущий месяц и начать новый.
* Если новый месяц имеет больше дней, чем текущий, добавленные дни изначально не будут содержать дел.
* Если же в новом месяце меньше дней, дела со всех удаляемых дней необходимо будет переместить на последний день нового месяца.
* 
* Обратите внимание, что количество команд этого типа может превышать 11.
* 
* DUMP i
* Вывести все дела в день i.
* 
* Изначально текущим месяцем считается январь.
* Количества дней в месяцах соответствуют Григорианскому календарю с той лишь разницей, что в феврале всегда 28 дней.
* 
* Формат ввода
* Сначала число операций Q, затем описания операций.
* 
* Названия дел s уникальны и состоят только из латинских букв, цифр и символов подчёркивания.
* Номера дней i являются целыми числами и нумеруются от 1 до размера текущего месяца.
* 
* Формат вывода
* Для каждой операции типа DUMP в отдельной строке выведите количество дел в соответствующий день, а затем их названия, разделяя их пробелом.
* Порядок вывода дел в рамках каждой операции значения не имеет.
*/

#include <iostream>
#include <vector>

int main()
{
    size_t count_command, month { 0 };
    std::cin >> count_command;
    
    const std::vector<size_t> days_months = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    std::vector<std::vector<std::string>> list_tasks(days_months[month]);
    
    for(size_t i = 0; i < count_command; ++i)
    {
        std::string command;
        std::cin >> command;

        if(command == "NEXT")
        {
            if(++month > 11)
            {
                month = 0;
            }

            if(list_tasks.size() > days_months[month])
            {
                for(size_t j = days_months[month]; j < list_tasks.size(); ++j)
                {
                    std::move(list_tasks[j].begin(), list_tasks[j].end(), std::back_inserter(list_tasks[days_months[month] - 1]));
                }                
            }
            list_tasks.resize(days_months[month]);
        }
        else
        {
            size_t day;
            std::cin >> day;
            
            if(command == "ADD")
            {                
                std::string task;
                std::cin >> task;

                list_tasks[day - 1].push_back(std::move(task));
            }
            else if(command == "DUMP")
            {
                std::cout << list_tasks[day - 1].size() << ' ';
                for(const auto& task : list_tasks[day - 1])
                {
                    std::cout << task << ' ';
                }
                std::cout << std::endl;
            }
        }
    }
}