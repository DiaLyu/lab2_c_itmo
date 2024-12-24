#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <Windows.h>
#include <random>
#include <algorithm>
#include <numeric>

#include "CityEvents.h"
#include "Person.h"

using namespace std;

template <typename T>
void quick_remove_at(std::vector<T>& v, typename std::vector<T>::iterator it)
{
    if (it != std::end(v)) {
        *it = std::move(v.back());
        v.pop_back();
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // 1
    cout << "1. Создать вектор v1 размером от 500 до 1000 элементов, число элементов не известно до запуска программы\n";

    random_device rd;
    default_random_engine engine(rd());
    uniform_int_distribution<size_t> sizeDist(500, 1000);
    size_t vectorSize = sizeDist(engine);

    vector<CityEvent> v1(vectorSize);
    
    cout << "Размер вектора v1: " << v1.size() << "\n\n";
    // 2
    cout << "2. Создать вектор v2, поместив в него последние 200 элементов вектора v1. Рассмотрите решение для произвольных b и e, которые задают позиции первого и последнего копируемых элементов.\n";
    cout << "---- создание вектора с последними 200 значениями из вектора v1 ----\n";
    vector<CityEvent> v2_1(v1.end() - 200, v1.end());
    cout << "Размер вектора v2_1: " << v2_1.size() << "\n";

    cout << "---- создание вектора со случайными позициями b и e ----\n";
    uniform_int_distribution<size_t> sizeDist_b(0, 400);
    uniform_int_distribution<size_t> sizeDist_e(401, v1.size());
    size_t b = sizeDist_b(engine);
    size_t e = sizeDist_e(engine);
    cout << "Диапазон значений:\n";
    cout << "b = " << b << '\n';
    cout << "e = " << e << '\n';

    vector<CityEvent> v2_2(v1.begin() + b, v1.begin() + e);
    cout << "Размер вектора v2: " << v2_2.size() << "\n\n";

    // 3
    cout << "3. Сформировать список list1, поместив в него первые n (от 20 до 50) наибольших элементов вектора v1\n";

    size_t n = rand() % 31 + 20;
    // сортируем по количеству зарегистрированных на мероприятие по убыванию
    sort(v1.begin(), v1.end(), [](CityEvent& a, CityEvent& b) {
        return a.getVisitors().size() > b.getVisitors().size();
    });

    list<CityEvent> list1(v1.begin(), v1.begin() + n);
    for (auto& event : list1) {
        cout << event.getName() << ". Количество гостей: " << to_string(event.getVisitors().size()) << endl;
    }
    cout << "Размер списка list1: " << list1.size() << "\n\n";

    // 4
    cout << "4. Сформировать список list2, поместив в него последние n (от 20 до 50) наименьших элементов вектора v2, порядок элементов не важен.\n";
    list<CityEvent> list2(v2_1.begin(), v2_1.end());
    list2.sort([](CityEvent& a, CityEvent& b) {
        return a.getVisitors().size() < b.getVisitors().size();
    });
    list2.erase(next(list2.begin(), n), list2.end());
    for (auto& event : list2) {
        cout << event.getName() << ". Количество гостей: " << to_string(event.getVisitors().size()) << endl;
    }
    cout << "Размер списка list2: " << list2.size() << "\n\n";


    // 5
    cout << "5. Удалить из векторов v1 и v2 перемещенные элементы.\n";
    cout << "List1 > " << list1.size() << "\n";
    cout << "Before Size v1 > " << v1.size() << "\n";
    v1.erase(remove_if(v1.begin(), v1.end(), [&list1](const CityEvent& e) {
        return find(list1.begin(), list1.end(), e) != list1.end();
        }), v1.end());
    cout << "After Size v1 > " << v1.size() << "\n";
    cout << "   -----   \n";
    cout << "List2 > " << list2.size() << "\n";
    cout << "Before Size v2_1 > " << v2_1.size() << "\n";
    v2_1.erase(remove_if(v2_1.begin(), v2_1.end(), [&list2](const CityEvent& e) {
        return find(list2.begin(), list2.end(), e) != list2.end();
        }), v2_1.end());
    cout << "After Size v2_1 > " << v2_1.size() << "\n\n";

    // 6
    cout << "6. Для списка list1 найти элемент со средним значением. Перегруппировать элементы списка так, чтобы в начале оказались все элементы, большие среднего значения\n";
    double average = accumulate(list1.begin(), list1.end(), 0.0,
        [](double sum, CityEvent& event) {
            return sum + event.getVisitors().size();
        }) / list1.size();

    auto it = partition(list1.begin(), list1.end(),
        [average](CityEvent& a) {
            return a.getVisitors().size() > average; // Условие для элементов в первой половине
        });
    for (auto& event : list1) {
        cout << event.getName() << ". Количество гостей: " << to_string(event.getVisitors().size()) << endl;
    }
    cout << "\n";

    // 7
    cout << "7. Удалите из списка list2 все нечётные элементы\n";
    cout << "До - Размер списка list2: " << list2.size() << "\n\n";
    list2.remove_if([](CityEvent& event) { return event.getName() == "Концерт"; });
    cout << "После - Размер списка list2: " << list2.size() << "\n\n";

    // 8
    cout << "8. Создайте вектор v3 из элементов, которые присутствуют и в векторе v1 и в векторе v2.\n";
    sort(v1.begin(), v1.end(), [](CityEvent& a, CityEvent& b) {
        return a.getVisitors().size() < b.getVisitors().size();
        });
    sort(v2_1.begin(), v2_1.end(), [](CityEvent& a, CityEvent& b) {
        return a.getVisitors().size() < b.getVisitors().size();
        });
    vector<CityEvent> v3; // Копируем v1 в v3
    set_intersection(v1.begin(), v1.end(), v2_1.begin(), v2_1.end(), back_inserter(v3));
    cout << "Размер списка v1: " << v1.size() << "\n";
    cout << "Размер списка v3: " << v3.size() << "\n\n";

    // 9
    cout << "9. Для списков list1 и list2 из списка с большим числом элементов удалите первые n так, чтобы оба списка имели бы одинаковый размер.\n";
    if (list1.size() > list2.size()) {
        auto it_l = list1.begin();
        advance(it_l, list1.size() - list2.size());
        list1.erase(list1.begin(), it_l);
    }
    else {
        auto it_l = list2.begin();
        advance(it_l, list2.size() - list1.size());
        list2.erase(list2.begin(), it_l);
    }

    list<pair<CityEvent, CityEvent>> list3;
    transform(list1.begin(), list1.end(), list2.begin(), std::back_inserter(list3), [](auto o1, auto o2)
        { return std::make_pair(o1, o2); });

    cout << "Размер списка list3: " << list3.size() << "\n\n";

    // 10
    cout << "10. Решите предыдущую задачу для векторов v1 и v2 без предварительного приведения векторов к одному размеру. Пар с пустыми значениями быть не должно.\n";
    list<pair<CityEvent, CityEvent>> list4;
    transform(v1.begin(), v1.begin() + min(v1.size(), v2_1.size()), v2_1.begin(), back_inserter(list4), [](auto o1, auto o2)
        { return make_pair(o1, o2); });
    cout << "Размер списка list4: " << list4.size() << endl;

    return 0;
}