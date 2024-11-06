#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <Windows.h>

#include "CityEvents.h"
#include "Person.h"

using namespace std;

void processCityEvents(std::vector<CityEvent> events) {
    // Выводим названия всех мероприятий
    cout << "Начало функции processCityEvents\n";
    for (int i = 0; i < events.size(); i++) {
        cout << to_string(i) << " " << events[i].getName() << endl;
    }
    cout << "Конец функции\n";
}

CityEvent* createDynamicCityEvent() {
    CityEvent* event = new CityEvent("Festival", "A summer festival", { "Music", "Food", "Art" });
    return event;
}

CityEvent& returnEventByReference(CityEvent& event) {
    return event; // Возвращаем ссылку на переданный объект
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // создание экземпляра класса с помощью стандартного конструктора
    // часть кода демонстрации работы всех методов класса
    CityEvent event1("Conference", "Tech conference", { "AI", "Security", "Networking" });
    event1.registrNewVisitor("Ivan", "Ivanov", "12345");
    event1.registrNewVisitor("Petr", "Petrov", "67890");
    event1.registrNewVisitor("Alina", "Bushmakina", "95763");

    event1.updateDataVisitor("12345", "Ilya");

    event1.deleteVisitor("67890");

    cout << "Есть человек с номером 67890? " << to_string(event1.isThereOnRegistry("67890")) << endl;

    event1.updateName("Highload development conference");
    event1.updateDescription("conference for developers in the field of highly loaded systems");
    event1.updateTopics({"Highly loaded systems", "Cloud technologies", "Networking"});

    cout << "Итоговая информация в экземпляре\n";
    cout << "Event name: " << event1.getName() << endl;
    cout << "Event description: " << event1.getDescription() << endl;

    string str_topics = "";
    vector<string> topics = event1.getTopics();
    for (int i = 0; i < topics.size(); i++) {
        str_topics += topics[i] + " ";
    }

    cout << "Event topics: " << str_topics << endl;

    vector<Person> registrFaces = event1.getVisitors();

    cout << "Registrants:\n";
    for (int i = 0; i < registrFaces.size(); i++) {
        cout << to_string(i) << " " << registrFaces[i].name << " " << registrFaces[i].surname << " " << registrFaces[1].phone << endl;
    }

    cout << "Операции присванивания" << endl;
    CityEvent event2 = event1;
    CityEvent event3 = move(event2);
    event1 = event2;
    event2 = move(event3);

    cout << "\n\n";

    cout << "Вектор из событий" << endl;
    vector<CityEvent> listEvents;
    cout << "Создание экземпляра класса..." << endl;
    CityEvent event4("Workshop", "Coding workshop", { "C++", "Python", "JavaScript" });
    cout << "Добавление в вектор экземпляра класса с помощью push_back..." << endl;
    listEvents.push_back(event3);
    cout << "Добавление в вектор экземпляра класса с помощью emplace_back..." << endl;
    listEvents.emplace_back(event4);

    cout << "\nПередача список из событий в функцию" << endl;
    processCityEvents(listEvents);

    cout << "\nСоздание динамического экземпляра, присвоив ей результат из функции" << endl;
    CityEvent* dynamicEvent = createDynamicCityEvent();
    dynamicEvent->registrNewVisitor("Anna", "Smith", "54321");

    delete dynamicEvent;

    cout << "\nСоздание динамического экземпляра" << endl;
    CityEvent* dynamicEvent1 = new CityEvent("Festival_2", "A summer festival 2", { "Music", "Food", "Art" });
    dynamicEvent1->registrNewVisitor("Elena", "Smith", "75424");

    delete dynamicEvent1;

    cout << "\nПередача экземпляра в функцию по ссылке и вывод данных" << endl;
    CityEvent& referenceEvent = returnEventByReference(event1);
    std::cout << "Событие по ссылке: " << referenceEvent.getName() << std::endl;

    dynamicEvent = nullptr;
    dynamicEvent1 = nullptr;

    cout << "\nКонтейнер list" << endl;
    list<CityEvent> cityEventList;
    cout << "Добавление в вектор экземпляра класса с помощью push_back..." << endl;
    cityEventList.push_back(event3);
    cout << "Добавление в вектор экземпляра класса с помощью emplace_back..." << endl;
    cityEventList.emplace_back(event4);

    cout << "Добавление новых элементов (больше 5 по заданию)...\n";
    CityEvent event5("name5", "descrition5", {"topic 1", "topic2"});
    CityEvent event6("name6", "descrition6", { "topic 1", "topic2" });
    CityEvent event7("name7", "descrition7", { "topic 1", "topic2" });
    CityEvent event8("name8", "descrition8", { "topic 1", "topic2" });
    CityEvent event9("name9", "descrition9", { "topic 1", "topic2" });
    cityEventList.push_back(event5);
    cityEventList.push_back(event6);
    cityEventList.push_back(event7);
    cityEventList.push_back(event8);
    cityEventList.push_back(event9);

    cout << "\nНачало цикла...\n";
    // Вывод всех мероприятий из списка
    for (CityEvent evnt : cityEventList) {
        cout << evnt.getName() << endl;
    }
    cout << "Конец цикла...";

    cout << "\n\n\n";
}