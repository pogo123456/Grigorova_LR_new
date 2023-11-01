#include "Station.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Header.h"

int Station::max_id_cs = 1;

int Station::GetId()
{
	return ID;
}

istream& operator >> (istream& in, Station& new_station)
{
	new_station.ID = ++new_station.max_id_cs;
	cout << "Станции присвоен ID:  " << new_station.ID << endl;
	cout << "Введите название станции:  ";
	cin.ignore();
	getline(cin, new_station.title);
	cout << "Введите кол-во цехов:  ";
	GetCorrectNumber(new_station.workshop);
	cout << "Введите кол-во работающих цехов:  ";
	GetCorrectNumber(new_station.active_workshop);
	while (new_station.workshop < new_station.active_workshop)
	{
		cout << "Ошибка! Превышено кол-во работающих цехов!" << endl << "Введите корректные данные:  ";
		GetCorrectNumber(new_station.active_workshop);
	}
	cout << "Введите эффективность станции от A до G:  ";
	cin >> new_station.efficiency;
	while (!(new_station.efficiency >= "A" && new_station.efficiency <= "G" && new_station.efficiency.length() == 1))
	{
		cout << "Ошибка! Введите корректные данные:  ";
		cin >> new_station.efficiency;
	}
	return in;
}

ostream& operator << (ostream& out, const Station& new_station)
{
	if (new_station.workshop == 0)
		out << "Нет станции." << endl;
	else
	{
		out << "Название станции:  " << new_station.title << endl;
		out << "Кол-во цехов:  " << new_station.workshop << endl;
		out << "Кол-во работающих цехов:  " << new_station.active_workshop << endl;
		out << "Эффективность:  " << new_station.efficiency << endl;
		out << "ID станции:  " << new_station.ID << endl;
	}
	return out;
}

void EditStation(Station& edit_station)
{
	int choice = 0;
	if (edit_station.workshop == 0)
		cout << "Нет станции." << endl;
	else
	{
		cout << "Хотите изменить кол-во работающих цехов?" << endl;
		cout << "1. Да" << endl << "2. Нет" << endl << "Ваш выбор: ";
		GetCorrectNumber(choice);
		switch (choice)
		{
		case 1:
			cout << "Введите новое кол-во работающих цехов:  ";
			GetCorrectNumber(edit_station.active_workshop);
			while (edit_station.active_workshop > edit_station.workshop)
			{
				cout << "Ошибка! Превышено кол-во работающих цехов!" << endl << "Кол-во всех цехов:  " << edit_station.workshop << endl;
				cout << "Введите корректные данные:  ";
				GetCorrectNumber(edit_station.active_workshop);
			}
			break;
		case 2:
			return;
			break;
		default:
			cout << "Ошибка! Введите корректные данные:  ";
			break;
		}
	}
}

ofstream& operator << (ofstream& fout, const Station& station)
{
	fout << station.title << endl
		<< station.workshop << endl
		<< station.active_workshop << endl
		<< station.efficiency << endl
		<< station.ID << endl;
	cout << "Данные станции сохранены в файл." << endl;
	return fout;
}


ifstream& operator >> (ifstream& fin, Station& station)
{
	fin.ignore();
	getline(fin, station.title);
	fin >> station.workshop;
	fin >> station.active_workshop;
	fin >> station.efficiency;
	fin >> station.ID;
	cout << "Данные станции загружены из файла." << endl;
	return fin;
}