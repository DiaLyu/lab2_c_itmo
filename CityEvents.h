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

	// ��������� ������
	std::string getName();
	std::string getDescription();
	std::vector<std::string> getTopics();
	std::vector<Person> getVisitors();

	// ���������� ������
	void updateName(std::string newName);
	void updateDescription(std::string newDescr);
	void updateTopics(std::vector<std::string> newTopics);

	// ������ � ������������
	void registrNewVisitor(std::string nameVisitor, std::string surnameVisitor, std::string phoneVisitor);															// ����������� ����������	
	void updateDataVisitor(std::string phone, std::string newData, std::string whatUpdate = "name");	// ���������� ������ ���������� �� ������ ��������
	void deleteVisitor(std::string phone);																// �������� ������������ �� ������ ��������
	bool isThereOnRegistry(std::string phone);															// �������� �������� � ������ ������������������

private:
	std::string name;									// �������� �����������
	std::string description;							// �������� �����������
	std::vector<std::string> topics;					// ���� �����������
	std::vector<Person> visitors;						// ������ ������������������ ����� �� �����������
};

