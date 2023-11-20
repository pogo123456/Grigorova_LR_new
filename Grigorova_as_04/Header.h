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
		cout << "����������� ��������� ������! ���������� �����:  ";
		cin >> var;
	}
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

template <typename K>
unordered_map<int, K> removeKey(std::unordered_map<int, K>& notes, int key) {
	if (notes.find(key) != notes.end()) {
		notes.erase(key);
		cout << "Removal was succesful!" << endl;
		return notes;
	}
	else {
		cout << "Key " << key << " does not exist!\nPlease enter a valid key: ";
		int newKey;
		cin >> newKey;
		return removeKeyIfExists(notes, newKey);
	}
}