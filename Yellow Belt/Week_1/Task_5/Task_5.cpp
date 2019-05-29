// Task_5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <map>
#include <string>
#include <tuple>

// Перечислимый тип для статуса задачи
enum class TaskStatus {
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = std::map<TaskStatus, int>;

class TeamTasks {
public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const std::string& person) const
	{
		return workers.at(person);
	}

	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const std::string& person)
	{
		++workers[person][TaskStatus::NEW];
	}

	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(const std::string& person, int task_count)
	{

	}
private:
	std::map<std::string, TasksInfo> workers;
};

void PrintTasksInfo(TasksInfo tasks_info)
{
	std::cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
		", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
		", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
		", " << tasks_info[TaskStatus::DONE] << " tasks are done" << std::endl;
}

int main()
{
	TeamTasks tasks;

	tasks.AddNewTask("Ilia");

	for (int i = 0; i < 3; ++i)
	{
		tasks.AddNewTask("Ivan");
	}

	std::cout << "Ilia's tasks: ";

	PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));

	std::cout << "Ivan's tasks: ";

	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

	TasksInfo updated_tasks, untouched_tasks;

	std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);

	std::cout << "Updated Ivan's tasks: ";

	//PrintTasksInfo(updated_tasks);

	//std::cout << "Untouched Ivan's tasks: ";

	//PrintTasksInfo(untouched_tasks);

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);

	//std::cout << "Updated Ivan's tasks: ";

	//PrintTasksInfo(updated_tasks);

	//std::cout << "Untouched Ivan's tasks: ";

	//PrintTasksInfo(untouched_tasks);

	//return 0;
}