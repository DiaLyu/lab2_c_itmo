#include "CityEvents.h"
#include "Person.h"

CityEvent::CityEvent(std::string nameEvents, std::string descrEvents, std::vector<std::string> topicsEvents) :
	name(nameEvents), description(descrEvents), topics(topicsEvents){
	std::cout << "Стандартный конструктор\n";
}

CityEvent::CityEvent(const CityEvent& cityEvent) :
	name(cityEvent.name), description(cityEvent.description), topics(cityEvent.topics), visitors(cityEvent.visitors) {
	std::cout << "Конструктор копирования\n";
}

CityEvent::CityEvent(CityEvent&& cityEvent) noexcept :
	name(cityEvent.name), description(cityEvent.description), topics(cityEvent.topics), visitors(cityEvent.visitors) {
	std::cout << "Конструктор перемещения\n";
}

CityEvent::~CityEvent() {
	std::cout << "Деструктор\n";
	name = "";
	description = "";
	topics.clear();
	visitors.clear();
}

CityEvent& CityEvent::operator=(const CityEvent& cityEvent) {
	std::cout << "Перегрузка оператора присваивания без перемещения\n";
	if (this != &cityEvent) {
		name = cityEvent.name;
		description = cityEvent.description;
		topics = cityEvent.topics;
		visitors = cityEvent.visitors;
	}
	return *this;
}

CityEvent& CityEvent::operator=(CityEvent&& cityEvent) noexcept {
	std::cout << "Перегрузка оператора присваивания с перемещением\n";
	if (this != &cityEvent) {
		name = std::move(cityEvent.name);
		description = std::move(cityEvent.description);
		topics = std::move(cityEvent.topics);
		visitors = std::move(cityEvent.visitors);
	}
	return *this;
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