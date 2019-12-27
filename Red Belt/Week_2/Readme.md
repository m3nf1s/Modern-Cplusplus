# Принципы оптимизации кода, сложность алгоритмов и эффективное использование ввода/вывода

## [Задание по программированию: Сортировка студентов по рейтингу](https://github.com/m3nf1s/Modern-Cplusplus/tree/master/Red%20Belt/Week_2/Task_1)

В данной задаче необходимо оптимизировать код, использующийся для сортировки студентов по рейтингу. Данные каждого студента находятся в структуре Student, объявленной в файле student.h. Рейтинг студента записан в поле rating:
```cpp
struct Student {
  string first_name;
  string last_name;
  map<string, double> marks;
  double rating;

  bool operator < (const Student& other) const {
    return GetName() < other.GetName();
  }

  bool Less(const Student& other) const {
    return rating > other.rating;
  }

  string GetName() const {
    return first_name + " " + last_name;
  }
};
```

Для сортировки студентов по рейтингу используется функция сравнения, возвращающая true, если рейтинг студента first выше рейтинга студента second.
```cpp
bool Compare(Student first, Student second) {
  return first.Less(second);
}
```

Было выявлено, что эта функция является узким местом процесса сортировки, и именно её нужно оптимизировать.

Пришлите на проверку файл, содержащий оптимизированную версию функции Compare. Если ваша реализация будет недостаточно эффективной, то решение не уложится в ограничение по времени.

## [Задание по программированию: Изучение нового языка](https://github.com/m3nf1s/Modern-Cplusplus/tree/master/Red%20Belt/Week_2/Task_2)

Студента попросили написать класс Learner, помогающий изучать иностранный язык. В публичном интерфейсе класса должны быть две функции:
```cpp
int Learn(const vector<string>& words);
vector<string> KnownWords();
```

Функция Learn должна получать порцию слов, "запоминать" их и возвращать количество различных новых слов. Функция KnownWords должна возвращать отсортированный по алфавиту список всех выученных слов. В списке не должно быть повторов.

Студент написал следующее решение этой задачи, однако оно почему-то работает очень медленно. Вам надо его ускорить.

Вам дан файл learner.cpp с медленным решением задачи. **Не меняя публичный интерфейс класса Learner**, найдите в нём узкие места, исправьте их и сдайте переделанный класс в тестирующую систему.

## [Тренировочное задание по программированию: Экспрессы](https://github.com/m3nf1s/Modern-Cplusplus/tree/master/Red%20Belt/Week_2/Task_3)

Вам даны задача и её решение — верное, но не удовлетворяющее заданным ограничениям на время работы. Переработайте это решение и сдайте в систему.

### Условие
Разработайте простейшую систему маршрутизации экспрессов, курсирующих по одному железнодорожному направлению, представляющему собой прямую. Ваша программа должна уметь обрабатывать запросы двух типов:

* **ADD start finish** — добавить в систему маршрутов экспресс, следующий со станции start до станции finish и обратно. Экспресс не делает промежуточных остановок. Станции задаются целыми числами, равными их расстоянию от вокзала (он имеет номер 0).
* **GO start finish** — попытаться проложить беспересадочный маршрут от станции start до станции finish. Если существует экспресс между этими двумя станциями, в ответ на данный запрос выведите 0. В противном случае выведите положительное число — минимальное расстояние, на которое можно приблизиться к станции finish, стартовав строго на станции start и использовав не более одного экспресса.

### Формат входных данных
В первой строке вводится количество запросов Q — натуральное число, не превосходящее 10^5. В следующих Q строках в соответствии с описанным выше форматом вводятся запросы. Гарантируется, что номера станций являются целыми числами, по модулю не превосходящими 10^9.

### Формат выходных данных
Для каждого запроса GO выведите единственное целое неотрицательное число — минимальное расстояние до конечной станции маршрута, вычисляемое в соответствии с описанными выше правилами.

### Ограничения
1 секунда на выполнение всех запросов. Все описанные в условии гарантии действительно справедливы для всех тестов, на которых будет запускаться ваша программа. Проверять корректность тестов не нужно.

## [Тренировочное задание по программированию: Электронная книга](https://github.com/m3nf1s/Modern-Cplusplus/tree/master/Red%20Belt/Week_2/Task_4)

Вам даны задача и её решение — верное, но не удовлетворяющее заданным ограничениям на время работы. Переработайте это решение и сдайте в систему.

### Условие
Разработайте систему стимулирования чтения электронных книг. Для простоты будем считать, что книга всего одна, но её одновременно читают много людей. Необходимо следить за прогрессом чтения у всех пользователей и выводить мотивирующие уведомления. А именно, ваша программа должна обрабатывать следующие события:

* **READ user page** — сохранить факт того, что пользователь под номером user дочитал книгу до страницы page. Если ранее такой пользователь не встречался, необходимо его добавить. Гарантируется, что в рамках одного пользователя номера страниц в соответствующих ему событиях возрастают.
* **CHEER user** — сообщить пользователю user, какая доля существующих пользователей (не считая его самого) прочитала меньшую часть книги, чем он. Если этот пользователь на данный момент единственный, доля считается равной 1. Если для данного пользователя пока не было ни одного события READ, доля считается равной 0, а сам пользователь не учитывается при вычислении долей для других пользователей до тех пор, пока для него не случится событие READ.

### Формат входных данных
В первой строке вводится количество запросов Q — натуральное число, не превосходящее 10^6. В следующих Q строках в соответствии с описанным выше форматом вводятся запросы. Гарантируется, что все вводимые числа целые и положительные, при этом номера пользователей не превосходят 10^5, а номера страниц не превосходят 1000.

### Формат выходных данных
Для каждого запроса CHEER user выведите единственное вещественное число от 0 до 1 — долю пользователей, прочитавших меньше страниц, чем user. Формат вывода этого числа должен быть в точности таким же, как в опубликованном ниже медленном решении.

### Ограничения
4 секунды на выполнение всех запросов. Все описанные в условии гарантии действительно справедливы для всех тестов, на которых будет запускаться ваша программа. Проверять корректность тестов не нужно.

## [Тренировочное задание по программированию: Система бронирования отелей](https://github.com/m3nf1s/Modern-Cplusplus/tree/master/Red%20Belt/Week_2/Task_5)

### Условие
Разработайте систему бронирования отелей, позволяющую бронировать номера клиентами и контролировать спрос владельцами отелей. Ваша программа должна обрабатывать следующие события:

* **BOOK time hotel_name client_id room_count** — забронировать клиентом client_id room_count номеров в отеле hotel_name в момент времени time. Время измеряется в секундах, отсчитываемых от некоторого момента.
* **CLIENTS hotel_name** — вывести количество различных клиентов, бронировавших номера в отеле hotel_name за последние сутки. Более формально интересующий диапазон времени описывается следующим образом: пусть current_time — время последнего события BOOK, тогда в данном запросе нужно учесть все события с current_time − 86400 < time ⩽ current_time, где 86400 — количество секунд в сутках. Обратите внимание, что последнее бронирование должно учитываться, а бронирование, случившееся ровно за сутки до него, учитываться не должно.
* **ROOMS hotel_name** — вывести количество номеров, забронированных за последние сутки в отеле hotel_name.

### Формат входных данных
В первой строке вводится количество запросов Q — натуральное число, не превосходящее 10^5. В следующих Q строках в соответствии с описанным выше форматом вводятся запросы. Гарантируется, что:

* **time** — целое число в диапазоне от −10^18 до 10^18 и не убывает от события к событию.
* **hotel_name** — строка из латинских букв и цифр, имеющая длину не более 12 символов.
* **client_id** — натуральное число, не превосходящее 10^9.
* **room_count** — целое положительное число, не превосходящее 1000.

### Формат выходных данных
Для каждого запроса CLIENTS и ROOMS выведите единственное целое число — ответ на запрос. Если указанный в запросе отель пока не имеет ни одного бронирования, выведите 0.

### Ограничения
1 секунда на выполнение всех запросов. Все описанные в условии гарантии действительно справедливы для всех тестов, на которых будет запускаться ваша программа. Проверять корректность тестов не нужно.