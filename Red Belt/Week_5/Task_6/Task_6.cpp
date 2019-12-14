/*
    Условие
    Напишите шаблонную функцию MergeSort,
    принимающую два итератора шаблонного типа RandomIt и сортирующую заданный ими диапазон с помощью сортировки слиянием.
    Гарантируется, что:    
    *   итераторы типа RandomIt аналогичны по функциональности итераторам вектора и строки,
        то есть их можно сравнивать с помощью операторов <, <=, > и >=, а также вычитать и складывать с числами;
    *   сортируемые объекты можно сравнивать с помощью оператора <.

    Алгоритм
    В этой задаче вы должны реализовать точь-в-точь алгоритм, представленный ниже;
    тестирующая система будет проверять, что вы выполняете с элементами именно эти действия:    
    1.  Если диапазон содержит меньше 2 элементов, выйти из функции.
    2.  Создать вектор, содержащий все элементы текущего диапазона.
    3.  Разбить вектор на три равные части.
        (В этой задаче гарантируется, что длина передаваемого диапазона является степенью тройки,
        так что вектор всегда можно разбить на три равные части.)
    4.  Вызвать функцию MergeSort от каждой части вектора.
    5.  Слить первые две трети вектора с помощью алгоритма merge,
        сохранив результат во временный вектор с помощью back_inserter.
    6.  Слить временный вектор из предыдущего пункта с последней третью вектора из п. 2,
        записав полученный отсортированный диапазон вместо исходного.

    В процессе работы вашего алгоритма не должно происходить копирования сортируемых элементов.
    Если вы используете копирование, при отправке не проверку решение не скомпилируется.
*/
#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    using Value = typename RandomIt::value_type;
    
    // 1.  Если диапазон содержит меньше 2 элементов, выйти из функции.
    const int range_length = range_end - range_begin;
    if (range_length < 2)
    {
        return;
    }

    // 2.  Создать вектор, содержащий все элементы текущего диапазона.
    std::vector<Value> elements(std::make_move_iterator(range_begin), std::make_move_iterator(range_end));

    // 3.  Разбить вектор на три равные части.
    auto first_middle_it = elements.begin() + (range_length / 3);
    auto second_middle_it = elements.begin() + (range_length / 3 * 2);

    // 4.  Вызвать функцию MergeSort от каждой части вектора.
    MergeSort(elements.begin(), first_middle_it);
    MergeSort(first_middle_it, second_middle_it);
    MergeSort(second_middle_it, elements.end());

    // 5.  Слить первые две трети вектора с помощью алгоритма merge,
    // сохранив результат во временный вектор с помощью back_inserter.
    std::vector<Value> temp;
    std::merge
    (
        std::make_move_iterator(elements.begin()), std::make_move_iterator(first_middle_it),
        std::make_move_iterator(first_middle_it), std::make_move_iterator(second_middle_it),
        std::back_inserter(temp)
    );

    // 6.  Слить временный вектор из предыдущего пункта с последней третью вектора из п. 2,
    // записав полученный отсортированный диапазон вместо исходного.
    std::merge
    (
        std::make_move_iterator(temp.begin()), std::make_move_iterator(temp.end()),
        std::make_move_iterator(second_middle_it), std::make_move_iterator(elements.end()),
        range_begin
    );

}

void TestIntVector()
{
    std::vector<int> numbers = { 6, 1, 3, 9, 1, 9, 8, 12, 1 };
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}
