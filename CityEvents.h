#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Person.h"

class CityEvent
{
public: 
	CityEvent(std::string nameEvents, std::string descrEvents, std::vector<std::string> topicsEvents);
	CityEvent(const CityEvent& cityEvent);
	CityEvent(CityEvent&& cityEvent) noexcept;
	~CityEvent();

	CityEvent& operator=(const CityEvent& cityEvent);
	CityEvent& operator=(CityEvent&& cityEvent) noexcept;

	// получение данных
	std::string getName();
	std::string getDescription();
	std::vector<std::string> getTopics();
	std::vector<Person> getVisitors();

	// обновление данных
	void updateName(std::string newName);
	void updateDescription(std::string newDescr);
	void updateTopics(std::vector<std::string> newTopics);

	// работа с посетителями
	void registrNewVisitor(std::string nameVisitor, std::string surnameVisitor, std::string phoneVisitor);															// регистрация посетителя	
	void updateDataVisitor(std::string phone, std::string newData, std::string whatUpdate = "name");	// обновление данных посетителя по номеру телефону
	void deleteVisitor(std::string phone);																// удаление пользователя по номеру телефона
	bool isThereOnRegistry(std::string phone);															// проверка человека в списке зарегистрированных

private:
	std::string name;									// название мероприятия
	std::string description;							// описание мероприятия
	std::vector<std::string> topics;					// темы мероприятия
	std::vector<Person> visitors;						// список зарегистрированных людей на мероприятие
};

