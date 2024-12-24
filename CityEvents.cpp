#include "CityEvents.h"
#include "Person.h"
#include <random>

CityEvent::CityEvent() {
	static const std::string names[] = { 
		"Концерт", "Фестиваль", "Выставка", "Мастер-класс", "Спортивное событие"
	};
	static const std::string descriptions[] = { 
		"Увлекательный концерт известной группы.",
		"Присоединяйтесь к празднику искусств.",
		"Выставка современных художников.",
		"Мастер-класс по рукоделию.",
		"Спортивные соревнования чемпионата."
	};
	static const std::vector<std::string> topicsList = { "Музыка", "Искусство", "Спорт", "Образование", "Культура" };

	std::default_random_engine engine(rd());
	std::uniform_int_distribution<int> nameDist(0, sizeof(names) / sizeof(names[0]) - 1);
	std::uniform_int_distribution<int> descrDist(0, sizeof(descriptions) / sizeof(descriptions[0]) - 1);
	std::uniform_int_distribution<int> topicDist(0, topicsList.size() - 1);

	name = names[nameDist(engine)];
	description = descriptions[descrDist(engine)];
	topics.push_back(topicsList[topicDist(engine)]);

	generateRandomVisitors(rand() % 50);
}

void CityEvent::generateRandomVisitors(int size) {
	std::vector<std::string> visitorNames = { "Алина", "Борис", "Скарлетт", "Давид", "Ева", "Анжелла" };
	std::vector<std::string> visitorSurname = { "Йохансон", "Сноу", "Поттер", "Грейнджер", "Уизли", "Дамблдор" };

	std::default_random_engine engine(rd());
	std::uniform_int_distribution<int> visitorNamesDist(0, visitorNames.size() - 1);
	std::uniform_int_distribution<int> visitorSurnameDist(0, visitorSurname.size() - 1);
	std::uniform_int_distribution<int> number(100000, 300000);

	for (int i = 0; i < size; i++) {
		visitors.push_back({ 
			visitorNames[visitorNamesDist(engine)],
			visitorSurname[visitorSurnameDist(engine)],
			std::to_string(number(engine))
			});
	}
}

CityEvent::CityEvent(std::string nameEvents, std::string descrEvents, std::vector<std::string> topicsEvents) :
	name(nameEvents), description(descrEvents), topics(topicsEvents){
}

CityEvent::CityEvent(const CityEvent& cityEvent) :
	name(cityEvent.name), description(cityEvent.description), topics(cityEvent.topics), visitors(cityEvent.visitors) {
}

CityEvent::CityEvent(CityEvent&& cityEvent) noexcept :
	name(cityEvent.name), description(cityEvent.description), topics(cityEvent.topics), visitors(cityEvent.visitors) {
}

CityEvent::~CityEvent() {
	name = "";
	description = "";
	topics.clear();
	visitors.clear();
}

CityEvent& CityEvent::operator=(const CityEvent& cityEvent) {
	if (this != &cityEvent) {
		name = cityEvent.name;
		description = cityEvent.description;
		topics = cityEvent.topics;
		visitors = cityEvent.visitors;
	}
	return *this;
}

CityEvent& CityEvent::operator=(CityEvent&& cityEvent) noexcept {
	if (this != &cityEvent) {
		name = std::move(cityEvent.name);
		description = std::move(cityEvent.description);
		topics = std::move(cityEvent.topics);
		visitors = std::move(cityEvent.visitors);
	}
	return *this;
}

bool CityEvent::operator<(const CityEvent& other) const {
	return visitors.size() < other.visitors.size();
}

bool CityEvent::operator==(const CityEvent& cityEvent) {
	if (visitors.size() == cityEvent.visitors.size()) {
		for (int i = 0; i < visitors.size(); i++) {
			if (visitors[i].name != cityEvent.visitors[i].name &&
				visitors[i].phone != cityEvent.visitors[i].phone &&
				visitors[i].surname != cityEvent.visitors[i].surname) {
				return false;
			}
		}
		if (topics.size() == cityEvent.topics.size()) {
			for (int i = 0; i < topics.size(); i++) {
				if (topics[i] != cityEvent.topics[i]) {
					return false;
				}
			}
			return name == cityEvent.name && description == cityEvent.description;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

std::string CityEvent::getName() {
	return this->name;
}

std::string CityEvent::getDescription() {
	return this->description;
}

std::vector<std::string> CityEvent::getTopics() {
	return this->topics;
}

std::vector<Person> CityEvent::getVisitors() {
	return this->visitors;
}

void CityEvent::updateName(std::string newName) {
	this->name = newName;
}

void CityEvent::updateDescription(std::string newDescr) {
	this->description = newDescr;
}

void CityEvent::updateTopics(std::vector<std::string> newTopics) {
	this->topics.clear();
	this->topics = newTopics;
}

void CityEvent::registrNewVisitor(std::string nameVisitor, std::string surnameVisitor, std::string phoneVisitor) {
	auto it = std::find_if(this->visitors.begin(), this->visitors.end(),
		[&phoneVisitor](const Person& p) {
			return p.phone == phoneVisitor;
		});

	if (it != this->visitors.end())
		std::cout << "Человек с телефоном " << it->phone << " уже есть в списке зарегистрированных на мероприятие\n";
	else {
		Person visitor;
		visitor.name = nameVisitor;
		visitor.surname = surnameVisitor;
		visitor.phone = phoneVisitor;

		this->visitors.push_back(visitor);
		std::cout << visitor.name << " " << visitor.surname << " зарегистрирован\n";
	}
}

void CityEvent::updateDataVisitor(std::string phone, std::string newData, std::string whatUpdate) {
	auto it = std::find_if(this->visitors.begin(), this->visitors.end(),
		[&phone](const Person& p) {
			return p.phone == phone;
		});

	if (it != this->visitors.end()) {
		std::cout << "Найден: " << it->name << " " << it->surname << ", Телефон: " << it->phone << std::endl;

		if (whatUpdate == "surname") {
			it->surname = newData;
		} 
		else if (whatUpdate == "phone") {
			it->phone = newData;
		}
		else {
			it->name = newData;
		}

		std::cout << "Изменено на: " << it->name << " " << it->surname << ", Телефон: " << it->phone << std::endl;
	}
	else {
		std::cout << "Человек с телефоном " << phone << " не найден." << std::endl;
	}
}

void CityEvent::deleteVisitor(std::string phone) {
	auto newEnd = std::remove_if(this->visitors.begin(), this->visitors.end(),
		[&phone](const Person& p) {
			return p.phone == phone;
		});

	if (newEnd != this->visitors.end()) {
		std::cout << "Удаляем: " << std::distance(newEnd, this->visitors.end())
			<< " экземпляров с телефоном " << phone << std::endl;
		this->visitors.erase(newEnd, this->visitors.end());
	}
	else {
		std::cout << "Экземпляр с телефоном " << phone << " не найден." << std::endl;
	}
}

bool CityEvent::isThereOnRegistry(std::string phone) {
	auto it = std::find_if(this->visitors.begin(), this->visitors.end(),
		[&phone](const Person& p) {
			return p.phone == phone;
		});

	if (it != this->visitors.end())
		return true;
	else
		return false;
}