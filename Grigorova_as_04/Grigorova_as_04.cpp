#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include "Pipe.h"
#include "Station.h"
#include "Header.h"
#include <unordered_map>
#include <unordered_set>

using namespace std;

template <typename T>
T& SelectElements(unordered_map<int>, T>& elements)
{
	return 0;
}

int main()
{
	unordered_map <int, Pipe> pipes = {};
	unordered_map <int, Station> stations = {};

	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	while (true)
	{
		cout  << endl << "------------------------------------" << endl;
		cout << "Меню" << endl;
		cout << "1. Добавить трубу" << endl;
		cout << "2. Добавить станцию" << endl;
		cout << "3. Вывести все объекты" << endl;
		cout << "4. Редактировать трубу" << endl;
		cout << "5. Редактировать станцию" << endl;
		cout << "6. Сохранить" << endl;
		cout << "7. Загрузить" << endl;
		cout << "8. Выйти" << endl;
		cout << "------------------------------------" << endl << endl;

		cout << "Ваш выбор: ";
		int choice = 0;
		GetCorrectNumber(choice);

		switch (choice)
		{
		case 1:
		{
			cout << endl << "<  Добавление трубы  >" << endl << endl;
			Pipe pipe;
			cin >> pipe;
			pipes.insert(make_pair(pipe.GetId(), pipe));
			break;
		}
		case 2:
		{
			cout << endl << "<  Добавление станции  >" << endl << endl;
			Station station;
			cin >> station;
			stations.insert(make_pair(station.GetId(), station));
			break;
		}
		case 3:
		{
			cout << endl <<  "<  Все объекты  >" << endl << endl;
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
			break;
		}
		case 4:
		{
			cout << endl << "<  Редактирование трубы  >" << endl << endl;
			Pipe pipe = SelectElements(pipes);
			EditPipe(pipe);
			break;
		}
		case 5:
		{
			cout << endl << "<  Редактирование станции  >" << endl << endl;
			Station station = SelectElements(stations);
			EditStation(station);
			break;
		}
		case 6:
		{
			cout << endl << "<  Сохрание  >" << endl << endl;
			ofstream fout;
			string fname;
			cout << "Введите имя файла:  ";
			cin.ignore();
			getline(cin, fname);
			fout.open(fname+".txt");

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
			break;
		}
		case 7:
		{
			cout << endl << "<  Загрузка  >" << endl << endl;
			ifstream fin;
			string fname;
			cout << "Введите имя файла:  ";
			cin.ignore();
			getline(cin, fname);
			fin.open(fname+".txt");
			int number;

			if (!fin.is_open())
				cout << "Ошибка открытия файла!" << endl;
				
			else
			{
				int sizePipe = 0;
				if (sizePipe == 0)
					cout << "Трубы нет." << endl;
				while (sizePipe-- > 0)
				{
					Pipe pipe;
					cin >> pipe;
					pipes.insert(make_pair(pipe.GetId(), pipe));
				}

				int sizeStation = 0;
				if (sizeStation == 0)
					cout << "" << endl;
				while (sizeStation-- > 0)
				{
					Station station;
					cin >> station;
					stations.insert(make_pair(station.GetId(), station));
				}

				fin.close();
			}
			break;
		}
		case 8:
			cout << endl << "<  Выход  >" << endl << endl;
			return 0;
			break;
		default:
			cout << "Ошибка! Введите снова" << endl;
			break;
		}
	}

	return 0;
}