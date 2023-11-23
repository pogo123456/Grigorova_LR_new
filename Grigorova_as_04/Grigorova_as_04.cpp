#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Pipe.h"
#include "Station.h"
#include "Header.h"
#include "logger.h"
#include "Graph.h"

using namespace std;

unordered_map <int, Pipe> pipes;
unordered_map <int, Station> stations;

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
			graph.SaveToFile();
			logger.log("Сохранение в файл (конец)");
			cout << "Данные успешно сохранены в файл.";
			break;
		}
		case 7:
		{
			cout << endl << "<  Загрузка  >" << endl << endl;
			logger.log("Загрузка из файла (начало)");
			graph.LoadToFile();
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
			cout << endl << "<  Удалить  >" << endl << endl;
			logger.log("Удалить (начало)");
			graph.DeleteObject();
			logger.log("Удалить (конец)");
			break;
		default:
			cout << "Ошибка! Введите снова" << endl;
			break;
		}
	}

	return 0;
}