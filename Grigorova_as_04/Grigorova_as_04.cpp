#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Pipe.h"
#include "Station.h"
#include "Header.h"


using namespace std;

unordered_map <int, Pipe> pipes;
unordered_map <int, Station> stations;

void SearchPipes(unordered_map <int, Pipe>& pipes) 
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

void SearchStations(unordered_map <int, Station>& stations) 
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
			return 0;
			break;
		case 1:
		{
			cout << endl << "<  Добавление трубы  >" << endl << endl;
			AddPipe();
			break;
		}
		case 2:
		{
			cout << endl << "<  Добавление станции  >" << endl << endl;
			AddStation();
			break;
		}
		case 3:
		{
			cout << endl <<  "<  Все объекты  >" << endl << endl;
			AllObject();
			break;
		}
		case 4:
		{
			cout << endl << "<  Редактирование трубы  >" << endl << endl;
			EditPipe();
			break;
		}
		case 5:
		{
			cout << endl << "<  Редактирование станции  >" << endl << endl;
			EditStation();
			break;
		}
		case 6:
		{
			cout << endl << "<  Сохрание  >" << endl << endl;
			SaveToFile();
			cout << "Данные успешно сохранены в файл.";
			break;
		}
		case 7:
		{
			cout << endl << "<  Загрузка  >" << endl << endl;
			LoadToFile();
			cout << "Данные успешно загружены из файла.";
			break;
		}
		case 8:
		{
			cout << endl << "<  Найти трубу  >" << endl << endl;
			SearchPipes(pipes);
			break;
		}
		case 9:
		{
			cout << endl << "<  Найти станцию  >" << endl << endl;
			SearchStations(stations);
			break;
		}
		case 10:
			cout << endl << "<  Удалить  >" << endl << endl;
			DeleteObject();
			break;
		default:
			cout << "Ошибка! Введите снова" << endl;
			break;
		}
	}

	return 0;
}