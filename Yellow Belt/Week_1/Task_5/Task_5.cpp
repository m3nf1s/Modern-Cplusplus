// Task_5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

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
		//Количество невыполненных заданий
		int untouched_tasks_count{ 0 };

		//подсчет количества невыполненных задач
		for (const auto& [status, task_ct] : workers[person])
		{
			if (status != TaskStatus::DONE)
			{
				untouched_tasks_count += task_ct;
			}
		}

		//Проверка больше ли задач, которые необходимо обновить, чем всего не выполненых
		if (task_count > untouched_tasks_count)
		{
			task_count = untouched_tasks_count;
		}
		
		//std::cout << untouched_tasks_count;

		//Обновленные задания
		TasksInfo updated_task;
		//Невыполненные задания
		TasksInfo untouched_tasks;

		TasksInfo worker_tasks = workers.at(person); //std::map<TaskStatus, int>
		//список статусов задач
		std::vector<TaskStatus> task_status = { TaskStatus::NEW, TaskStatus::IN_PROGRESS, TaskStatus::TESTING, TaskStatus::DONE };
		//
		for (size_t i = 0; i < task_status.size(); i++)
		{
			//Если количество задач, которые надо обновить, больше задач на текущем статусе
			if (task_count > worker_tasks[task_status.at(i)])
			{
				
				if (task_status.at(i) != TaskStatus::DONE)
				{
					//перекидывает текущие задачи на следующий статус
					updated_task[task_status.at(i + 1)] = worker_tasks.at(task_status.at(i));
					//уменьшаем количество, которые необходимо обновить
					task_count -= worker_tasks.at(task_status.at(i));
				}
				else
				{
					
					updated_task[task_status.at(i)] = worker_tasks.at(task_status.at(i));
				}				
			}
			else //если менше
			{
				if (task_status.at(i) != TaskStatus::DONE)
				{
					//переносим обновленные задачи в следующий статус
					updated_task[task_status.at(i + 1)] = task_count;
					//оставшиеся задачи переносим в нетронутые
					untouched_tasks[task_status.at(i)] = worker_tasks.at(task_status.at(i)) - task_count;
					//обнуляем счетчик задач, которые необходимо обновить
					task_count = 0;
				}
			}

			//чистим список работника, чтобы записать новые задачи (кроме выполненых)
			if (task_status.at(i) != TaskStatus::DONE)
				workers.at(person).erase(task_status.at(i));
		}		

		//обновляем список задач у работника
		for (const auto& status : task_status)
		{
			if (updated_task[status] != 0 || untouched_tasks[status] != 0)
			{
				workers.at(person)[status] += updated_task[status] + untouched_tasks[status];
			}
		}

		//удаляем нулевые статусы в обновленных и нетронутых задачах
		for (const auto& status : task_status)
		{
			if (updated_task.at(status) == 0)
				updated_task.erase(status);

			if (untouched_tasks.at(status) == 0)
				untouched_tasks.erase(status);
		}

		return std::tie(updated_task, untouched_tasks);
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

void PrintTasksInfo(const TasksInfo& updated_tasks, const TasksInfo& untouched_tasks) {
	std::cout << "Updated: [";
	PrintTasksInfo(updated_tasks);
	std::cout << "] ";

	std::cout << "Untouched: [";
	PrintTasksInfo(untouched_tasks);
	std::cout << "] ";

	std::cout << std::endl;
}

int main()
{
	TeamTasks tasks;

	//tasks.AddNewTask("Ilia");

	//for (int i = 0; i < 3; ++i)
	//{
	//	tasks.AddNewTask("Ivan");
	//}

	//std::cout << "Ilia's tasks: ";

	//PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));

	//std::cout << "Ivan's tasks: ";

	//PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

	TasksInfo updated_tasks, untouched_tasks;

	//std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);

	//std::cout << "Updated Ivan's tasks: ";

	//PrintTasksInfo(updated_tasks);

	//std::cout << "Untouched Ivan's tasks: ";

	//PrintTasksInfo(untouched_tasks);

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);

	//std::cout << "Updated Ivan's tasks: ";

	//PrintTasksInfo(updated_tasks);

	//std::cout << "Untouched Ivan's tasks: ";

	//PrintTasksInfo(untouched_tasks);

/* TEST 1 */
	//std::cout << "Alice" << std::endl;

	//for (auto i = 0; i < 5; ++i) {
	//	tasks.AddNewTask("Alice");
	//}

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
	//PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
	//PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
	//PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]

	//for (auto i = 0; i < 5; ++i) {
	//	tasks.AddNewTask("Alice");
	//}
	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice",
	//	2);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
	//PrintTasksInfo(updated_tasks, untouched_tasks);

	//PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
	//std::cout << std::endl;

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
	//PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

	//PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
	//std::cout << std::endl;

	//std::cout << "\nJack" << std::endl;

	//tasks.AddNewTask("Jack");

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 1);
	//PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]

	//tasks.AddNewTask("Jack");

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 2);
	//PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1}, {}]

	//tasks.AddNewTask("Jack");

	//PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"NEW": 1, "IN_PROGRESS": 1, "TESTING": 1, "DONE": 0}
	//std::cout << std::endl;

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 3);
	//PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}, {}]

	//PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}
	//std::cout << std::endl;

	std::cout << "\nLisa" << std::endl;

	for (auto i = 0; i < 5; ++i) {
		tasks.AddNewTask("Lisa");
	}

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 1);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]

	for (auto i = 0; i < 5; ++i) {
		tasks.AddNewTask("Lisa");
	}

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 4);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 4, "DONE": 1}, {"TESTING": 4}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"TESTING": 8, "DONE": 2}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 8}, {}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
	std::cout << std::endl;

	tasks.AddNewTask("Lisa");

	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 1, "DONE": 10}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 1, "DONE": 10}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Bob", 3);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]

	return 0;
}