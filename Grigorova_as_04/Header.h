#pragma once
#include <iostream>
using namespace std;
#include <unordered_map>
#include <unordered_set>
#include "Pipe.h"
#include "Station.h"

template <typename T>
void GetCorrectNumber(T& var)
{
	cin >> var;
	while (cin.fail() || cin.peek() != '\n' || var <= 0)
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
	int Id = 0;
	cout << "Enter number: ";
	InputCorrectNumber(Id);
	while (elements.find(Id) == elements.end())
	{
		cout << "Error!\nThe number exceeds the number of elements." << endl
			<< "Number of elements: " << elements.size() << endl
			<< "Please enter correct data: ";
		InputCorrectNumber(Id);
	}
	return elements[Id];
}

template <typename T>
ostream& operator<< (ostream& out, unordered_map <int, T>& p) {
	out << "ID: ";
	for (auto& [i, obj] : p) {
		cout << i << " ";
	}
	out << endl;
	return out;
}

template <typename T>
ostream& operator<< (ostream& out, unordered_set<int, T>& p) {
	out << "ID: ";
	for (auto& i : p) {
		cout << i << " ";
	}
	out << endl;
	return out;
}

template <typename T>
using filter_p = bool (*) (Pipe& p, T par);

template <typename T>
using filter_s = bool(*) (Station& s, T par);

template <typename T>
unordered_set <int> search_p_by_parametr(unordered_map <int, Pipe>& pipes, filter_p<T> f, T par) {
	unordered_set <int> id;
	for (auto& pipe : pipes) {
		if (f(pipe.second, par))
			id.insert(pipe.second.get_id());
	}
	return id;
}


template <typename T>
unordered_set <int> search_s_by_parametr(unordered_map <int, Station>& stations, filter_s<T> f, T par) {
	unordered_set <int> id;
	for (auto& s : stations) {
		if (f(s.second, par))
			id.insert(s.second.get_idc());
	}
	return id;
}