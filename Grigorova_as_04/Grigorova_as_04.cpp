#include <iostream>
#include <fstream>
#include <Windows.h>
#include <chrono>
#include <format>
#include "Pipe.h"
#include "Station.h"
#include "Header.h"
#include "logger.h"
#include "Graph.h"

using namespace std;
using namespace chrono;

unordered_map <int, Pipe> pipes = {};
unordered_map <int, Station> stations = {};

void AddPipe()
{
	Pipe pipe;
	cin >> pipe;
	pipes.insert(make_pair(pipe.GetId(), pipe));
}

void AddStation()
{
	Station station;
	cin >> station;
	stations.insert(make_pair(station.GetId(), station));
}

void AllObject()
{
	Pipe pipe;
	Station station;

	if (pipes.size() == 0)
		cout << "Труб нет." << endl;
	for (auto& pair : pipes)
		cout << pair.second;

	if (stations.size() == 0)
		cout << "Станций нет." << endl;
	for (const auto& pair : stations)
		cout << pair.second;
}

void EditPipe()
{
	if (pipes.size() == 0)
		cout << "Труб для редактирования нет." << endl;
	else
	{
		Pipe pipe = SelectElement(pipes);
		EditPipe(pipe);
	}
}

void EditStation()
{
	if (stations.size() == 0)
		cout << "Станций для редактирования нет." << endl;
	else
	{
		Station station = SelectElement(stations);
		EditStation(station);
	}
}

void SaveToFile()
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

void LoadToFile()
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

void DeleteObject()
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

int main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Logger logger;
	logger.log("Старт");

	wokrWithGraph graph;

	while (true)
	{
		cout  << endl << "------------------------------------" << endl;
		cout << " Меню" << endl;
		cout << " 0. Выход" << endl;
		cout << " 1. Добавить трубу" << endl;
		cout << " 2. Добавить станцию" << endl;
		cout << " 3. Вывести все объекты" << endl;
		cout << " 4. Редактировать трубу" << endl;
		cout << " 5. Редактировать станцию" << endl;
		cout << " 6. Сохранить" << endl;
		cout << " 7. Загрузить" << endl;
		cout << " 8. Найти трубу" << endl;
		cout << " 9. Найти станцию" << endl;
		cout << " 10. Удалить" << endl;
		cout << " 11. Создать систему" << endl;
		cout << " 12. Показать соединение" << endl;
		cout << " 13. Удалить соединения" << endl;
		cout << " 14. Топологическая сортировка графа" << endl;
		cout << "------------------------------------" << endl << endl;
		cout << "Ваш выбор: ";

		int choice = 0;
		GetCorrectNumber(choice);
		switch (choice)
		{
		case 0:
			cout << endl << "<  Выход  >" << endl << endl;
			logger.log("Выход");
			return 0;
			break;
		case 1:
		{
			cout << endl << "<  Добавление трубы  >" << endl << endl;
			logger.log("Добавление трубы (начало)");
			AddPipe();
			logger.log("Добавление трубы (конец)");
			break;
		}
		case 2:
		{
			cout << endl << "<  Добавление станции  >" << endl << endl;
			logger.log("Добавление станции (начало)");
			AddStation();
			logger.log("Добавление станции (конец)");
			break;
		}
		case 3:
		{
			cout << endl <<  "<  Все объекты  >" << endl << endl;
			logger.log("Показать все объекты (начало)");
			AllObject();
			logger.log("Показать все объекты (конец)");
			break;
		}
		case 4:
		{
			cout << endl << "<  Редактирование трубы  >" << endl << endl;
			logger.log("Редактирование трубы (начало)");
			EditPipe();
			logger.log("Редактирование трубы (конец)");
			break;
		}
		case 5:
		{
			cout << endl << "<  Редактирование станции  >" << endl << endl;
			logger.log("Редактирование станции (начало)");
			EditStation();
			logger.log("Редактирование станции (конец)");
			break;
		}
		case 6:
		{
			cout << endl << "<  Сохрание  >" << endl << endl;
			logger.log("Сохранение в файл (начало)");
			SaveToFile();
			logger.log("Сохранение в файл (конец)");
			cout << "Данные успешно сохранены в файл.";
			break;
		}
		case 7:
		{
			cout << endl << "<  Загрузка  >" << endl << endl;
			logger.log("Загрузка из файла (начало)");
			LoadToFile();
			logger.log("Загрузка из файла (конец)");
			cout << "Данные успешно загружены из файла.";
			break;
		}
		case 8:
		{
			cout << endl << "<  Найти трубу  >" << endl << endl;
			logger.log("Найти трубу (начало)");
			graph.SearchPipes(pipes);
			logger.log("Найти трубу (конец)");
			break;
		}
		case 9:
		{
			cout << endl << "<  Найти станцию  >" << endl << endl;
			logger.log("Найти станцию (начало)");
			graph.SearchStations(stations);
			logger.log("Найти станцию (конец)");
			break;
		}
		case 10:
		{
			cout << endl << "<  Удалить  >" << endl << endl;
			logger.log("Удалить (начало)");
			DeleteObject();
			logger.log("Удалить (конец)");
			break;
		}
		case 11:
		{
			cout << endl << "<  Создать систему  >" << endl << endl;
			logger.log("Создать систему (начало)");
			graph.ConnectInGraph(pipes, stations);
			logger.log("Создать систему (конец)");
			break;
		}
		case 12:
		{
			cout << endl << "<  Показать соединение  >" << endl << endl;
			logger.log("Показать соединение (начало)");
			if (pipes.size() == 0)
				cout << "Трубы не входят в граф!" << endl;
			if (stations.size() == 0)
				cout << "Станции не входят в граф!" << endl;
			int connectCount = 0;
			for (const auto& elem : pipes)
				if (!elem.second.ConnectionNotBusy())
				{
					cout << "Станция 1 [" << elem.second.CSid1 << "] - Труба [" << elem.first << "] - Станция 2 [" << elem.second.CSid2 << "]" << endl;
					connectCount++;
				}
			cout << "Соединение: " << connectCount << endl;
			logger.log("Показать соединение (конец)");
			break;
		}
		case 13:
		{
			cout << endl << "<  Удаление соединения  >" << endl << endl;
			logger.log("Удаление соединения (начало)");
			if (pipes.size() == 0)
				cout << "В графе труб нет!" << endl;
			else
			{
				cout << "Введите ID трубы, которую нужно удалить: ";
				int delPipe;
				GetCorrectNumber(delPipe);
				while (pipes.find(delPipe) == pipes.end())
				{
					cout << "\nPipe with this ID not exist! Please, try again: ";
					GetCorrectNumber(delPipe);
				}
				if (pipes[delPipe].ConnectionNotBusy())
				{
					cout << "Труба не содержится в графе." << endl;
				}
				else
				{
					pipes[delPipe].DeleteConnection();
					cout << "Соединение успешно удалено." << endl;
				}
			}
			logger.log("Удаление соединения (конец)");
			break;
		}
		case 14:
		{
			cout << endl << "<  Топологическая сортировка графа  >" << endl << endl;
			logger.log("Сортировка графа (начало)");
			vector <int> sortStations = graph.topologSort(pipes, stations);
			for (int id : sortStations)
			{
				cout << id << " ";
			}
			cout << endl;
			logger.log("Сортировка графа (конец)");
			break;
		}
		default:
			cout << "Ошибка! Введите снова" << endl;
			break;
		}
	}

	return 0;
}