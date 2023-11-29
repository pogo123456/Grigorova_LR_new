#include "Graph.h"
#include "Pipe.h"
#include "Station.h"
#include "Header.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int wokrWithGraph::Graph::max_idg = 0;

void wokrWithGraph::EditPipes(vector<Pipe*>& edit_pipes)
{
	cout << endl << "Хотите изменить статус трубы?" << endl;
	cout << "1. Да" << endl << "2. Нет" << endl << "Ваш выбор:  ";
	int choice = 0;
	GetCorrectNumber(choice);
	switch (choice)
	{
	case 1:
		bool inrepaire;
		cout << "Новый статус (1 - В ремонте, 0 - Работает):  ";
		GetCorrectNumber(inrepaire);

		for (auto& pipe : edit_pipes)
		{
			pipe->inrepair = inrepaire;
			cout << endl << "ID: " << pipe->ID << " - ";
			pipe->OutputPipeStatus();
		}
		break;
	case 2:
		return;
	default:
		cout << "Ошибка! Введите корректные данные:  " << endl;
		break;
	}
}

void wokrWithGraph::SearchPipes(unordered_map<int, Pipe>& pipes)
{
	while (true)
	{
		int choice = 0;
		cout << "По какому критерию найти трубу?" << endl;
		cout << "1. Киллометровая отметка" << endl << "2. Статус трубы" << endl << "3. Назад" << endl << "Ваш выбор:  ";
		GetCorrectNumber(choice);
		switch (choice)
		{
		case 1:
		{
			string name;
			cout << endl << "Киллометрая отметка: ";
			cin.ignore();
			getline(cin, name);

			vector <Pipe*> p;
			for (auto& pair : pipes)
			{
				if (pair.second.GetName().find(name) != string::npos)
				{
					cout << endl << pair.second << endl;
					p.push_back(&(pair.second));
				}
			}
			if (p.empty())
				cout << "Трубы с таким именем нет." << endl;
			else
				EditPipes(p);
		}
		break;
		case 2:
		{
			bool inrepair;
			cout << "Cтатус трубы: в ремонте? (1 - Да, 0 - Нет): ";
			GetCorrectNumber(inrepair);

			vector<Pipe*> p;
			for (auto& pair : pipes) {
				if (pair.second.GetStatus() == inrepair)
				{
					cout << endl << pair.second << endl;
					p.push_back(&(pair.second));
				}
			}
			if (p.empty())
				cout << "Трубы с таким статусом нет." << endl;
			else
				EditPipes(p);
		}
		break;
		case 3:
		{
			return;
			break;
		}
		default:
			cout << "Ошибка! Введите корректные данные";
			break;
		}
	}
}

void wokrWithGraph::EditStations(vector<Station*>& edit_stations)
{
	cout << endl << "Хотите изменить кол-во работающих цехов?" << endl;
	cout << "1. Да" << endl << "2. Нет" << endl << "Ваш выбор: ";
	int choice = 0;
	GetCorrectNumber(choice);
	switch (choice)
	{
	case 1:
		cout << "Введите новый процент активных цехов (0-100): ";
		float percent;
		GetCorrectNumber(percent);

		for (auto& cs : edit_stations)
		{
			cs->active_workshop = round(cs->workshop * percent / 100);
			cout << endl << "ID: " << cs->ID << " - ";
			cs->OutputWorkshopStatus();
		}
		break;
	case 2:
		return;
	default:
		cout << "Ошибка! Введите корректные данные:  " << endl;
		break;
	}
}

void wokrWithGraph::SearchStations(unordered_map<int, Station>& stations)
{
	while (true)
	{
		int choice = 0;
		cout << "По какому критерию найти станцию?" << endl;
		cout << "1. Название" << endl << "2. Процент активных цехов" << endl << "3. Назад" << endl << "Ваш выбор:  ";
		GetCorrectNumber(choice);
		switch (choice)
		{
		case 1:
		{
			string name;
			cout << "Название: ";
			cin.ignore();
			getline(cin, name);

			vector<Station*> cs;
			for (auto& pair : stations)
			{
				if (pair.second.GetName().find(name) != string::npos)
				{
					cout << endl << pair.second << endl;
					cs.push_back(&(pair.second));
				}
			}
			if (cs.empty())
				cout << "Станции с таким названием нет." << endl;
			else
				EditStations(cs);
		}
		break;
		case 2:
		{
			int percent = 0;
			cout << "Введите процент активных цехов (0-100 с погрешностью в 5%): ";
			GetCorrectNumber(percent);

			vector<Station*> cs;
			for (auto& pair : stations) {
				if (pair.second.GetPercentOfActiveWorkshops() > (percent - 5.0) && pair.second.GetPercentOfActiveWorkshops() < (percent + 5.0))
				{
					cout << endl << pair.second << endl;
					cs.push_back(&(pair.second));
				}
			}
			if (cs.empty())
				cout << "Станции с таким процентом нет." << endl;
			else
				EditStations(cs);
		}
		break;
		case 3:
		{
			return;
			break;
		}
		default:
			cout << "Ошибка! Введите корректные данные";
			break;
		}
	}
}

void wokrWithGraph::DeleteObject()
{
	cout << "1. Удалить трубу" << endl << "2. Удалить станцию" << endl << "Ваш выбор:  ";
	int choice = 0;
	GetCorrectNumber(choice);
	switch (choice)
	{
	case 1:
	{
		if (pipes.size() == 0)
			cout << "Нет доступных труб." << endl;
		else
		{
			cout << endl << "Введите ID трубы, которую нужно удалить:  ";
			int idToDelete = 0;
			GetCorrectNumber(idToDelete);

			if (pipes.find(idToDelete) == pipes.end())
				cout << "Трубы с таким ID не существует." << endl;
			else
			{
				pipes.erase(idToDelete);

				cout << endl << "Труба удалена." << endl;

				for (auto& pair : pipes)
					cout << pair.second << endl;
			}
		}
	}
	break;
	case 2:
	{
		if (stations.size() == 0)
			cout << "Нет доступных станций." << endl;
		else
		{
			cout << endl << "Введите ID станции, которую нужно удалить:  ";
			int idToDelete = 0;
			GetCorrectNumber(idToDelete);

			if (pipes.find(idToDelete) == pipes.end())
				cout << "Трубы с таким ID не существует." << endl;
			else
			{
				stations.erase(idToDelete);

				cout << endl << "Станция удалена." << endl;

				for (auto& pair : stations)
					cout << pair.second << endl;
			}
		}
	}
	break;
	case 3:
		return;
		break;
	default:
		cout << "Ошибка! Введите снова" << endl;
		break;
	}
}

void wokrWithGraph::SaveToFile()
{
	ofstream fout;
	string fname;
	cout << "Введите имя файла:  ";
	cin.ignore();
	getline(cin, fname);
	fout.open(fname + ".txt");

	if (!fout.is_open())
		cout << "Ошибка открытия файла!" << endl;
	else
	{
		fout << pipes.size() << endl;
		for (const auto& pair : pipes)
			fout << pair.second;

		fout << stations.size() << endl;
		for (const auto& pair : stations)
			fout << pair.second;

		fout.close();
	}
}

void wokrWithGraph::LoadToFile()
{
	ifstream fin;
	string fname;
	cout << "Введите имя файла:  ";
	cin.ignore();
	getline(cin, fname);
	fin.open(fname + ".txt");

	if (!fin.is_open())
		cout << "Ошибка открытия файла!" << endl;

	else
	{
		int sizePipe = 0;
		fin >> sizePipe;
		if (sizePipe == 0)
			cout << "Трубы нет." << endl;
		while (sizePipe-- > 0)
		{
			Pipe pipe;
			fin >> pipe;
			pipes.insert(make_pair(pipe.GetId(), pipe));
		}

		int sizeStation = 0;
		fin >> sizeStation;
		if (sizeStation == 0)
			cout << "Станции нет." << endl;
		while (sizeStation-- > 0)
		{
			Station station;
			fin >> station;
			stations.insert(make_pair(station.GetId(), station));
		}

		fin.close();
	}
}

