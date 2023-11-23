#pragma once
#include <iostream>
using namespace std;
#include <unordered_map>


template <typename T>
void GetCorrectNumber(T& var)
{
	cin >> var;
	while (cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Некорректно введенные данные! Попробуйте снова:  ";
		cin >> var;
	}
}

template <typename T>
T& SelectElement(unordered_map <int, T>& elements)
{
	int ID = 0;
	cout << "Введите ID редактируемого объекта: ";
	GetCorrectNumber(ID);
	while (elements.find(ID) == elements.end())
	{
		cout << "Ошибка! Введенное ID превышает общее кол-во элементов." << endl
			<< "Кол-во всех элементов: " << elements.size() << endl
			<< "Введите корректные данные: ";
		GetCorrectNumber(ID);
	}
	return elements[ID];
}