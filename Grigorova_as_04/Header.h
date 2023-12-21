#pragma once
#include <iostream>
#include <unordered_map>

using namespace std;

template <typename T>
void GetCorrectNumber(T& var)
{
	cin >> var;
	while (cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "����������� ��������� ������! ���������� �����:  ";
		cin >> var;
	}
}

template <typename T>
int GetCorrectDiam(T min, T max)
{
	T var;
	cin >> var;
	while (var != 500 && var != 700 && var != 1000 && var != 1400)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "����������� ��������� ������! ���������� �����:  ";
		cin >> var;
	}
	return var;
}

template <typename T>
T& SelectElement(unordered_map <int, T>& elements)
{
	int ID = 0;
	cout << "������� ID �������������� �������: ";
	GetCorrectNumber(ID);
	while (elements.find(ID) == elements.end())
	{
		cout << "������! ��������� ID ��������� ����� ���-�� ���������." << endl
			<< "���-�� ���� ���������: " << elements.size() << endl
			<< "������� ���������� ������: ";
		GetCorrectNumber(ID);
	}
	return elements[ID];
}
