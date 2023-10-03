#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

struct pipe
{
	string km_mark = "";
	double len = 0;
	int diam = 0;
	bool inrepair = true;
}; 

struct station
{
	string title = "";
	int workshop = 0;
	int active_workshop = 0;
	string efficiency = "A";
};

void InputInt(int& var)
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

void InputDouble(double& var)
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

void InputBool(bool& var)
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

pipe AddPipe()
{
	pipe new_pipe;
	cout << "Введите километровую отметку:  ";
	cin.ignore();
	getline(cin, new_pipe.km_mark);
	cout << "Введите длину трубы (км):  ";
	InputDouble(new_pipe.len);
	cout << "Введите диаметр трубы (мм):  ";
	InputInt(new_pipe.diam);
	cout << "Состояние трубы (1 - в ремонте; 0 - работает):  ";
	InputBool(new_pipe.inrepair);

	return new_pipe;
}

station AddStation()
{
	station new_station;
	cout << "Введите название станции:  ";
	cin.ignore();
	getline(cin, new_station.title);
	cout << "Введите кол-во цехов:  ";
	InputInt(new_station.workshop);
	cout << "Введите кол-во работающих цехов:  ";
	InputInt(new_station.active_workshop);
	while (new_station.workshop < new_station.active_workshop)
	{
		cout << "Ошибка! Превышено кол-во работающих цехов!" << endl << "Введите корректные данные:  ";
		InputInt(new_station.active_workshop);
	}
	cout << "Введите эффективность станции от A до G:  ";
	cin >> new_station.efficiency;
	while (!(new_station.efficiency >= "A" && new_station.efficiency <= "G" && new_station.efficiency.length() == 1))
	{
		cout << "Ошибка! Введите корректные данные:  ";
		cin >> new_station.efficiency;
	}

	return new_station;
}

void ShowPipe(const pipe& new_pipe)
{
	if (new_pipe.len == 0)
		cout << "Нет трубы." << endl;
	else
	{
		cout << "Километровая отметка:  " << new_pipe.km_mark << endl;
		cout << "Длина трубы:  " << new_pipe.len << "км" << endl;
		cout << "Диаметр трубы:  " << new_pipe.diam << "мм" << endl;
		(new_pipe.inrepair) ? cout << "Труба в ремонте." << endl : cout << "Труба работает." << endl;
	}
}

void ShowStation(const station& new_station)
{
	if (new_station.workshop == 0)
		cout << "Нет станции." << endl;
	else
	{
		cout << "Название станции:  " << new_station.title << endl;
		cout << "Кол-во цехов:  " << new_station.workshop << endl;
		cout << "Кол-во работающих цехов:  " << new_station.active_workshop << endl;
		cout << "Эффективность:  " << new_station.efficiency << endl;
	}
}

void EditPipe(pipe& edit_pipe)
{
	if (edit_pipe.len == 0)
		cout << "Нет трубы." << endl;
	else
	{
		edit_pipe.inrepair = !edit_pipe.inrepair;
		cout << "Статус трубы изменен." << endl;
	}
}

void EditStation(station& edit_station)
{
	int choice = 0;
	if (edit_station.workshop == 0)
		cout << "Нет станции." << endl;
	else
	{
		cout << "Хотите изменить кол-во работающих цехов?" << endl;
		cout << "1. Да" << endl << "2. Нет" << endl << "Ваш выбор: ";
		InputInt(choice);
		switch (choice)
		{
		case 1:
			cout << "Введите новое кол-во работающих цехов:  ";
			InputInt(edit_station.active_workshop);
			while (edit_station.active_workshop > edit_station.workshop)
			{
				cout << "Ошибка! Превышено кол-во работающих цехов!" << endl << "Кол-во всех цехов:  " << edit_station.workshop << endl;
				cout << "Введите корректные данные:  ";
				InputInt(edit_station.active_workshop);
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

void SavePipe(pipe& new_pipe, ofstream& fout)
{
	fout << new_pipe.km_mark << endl
		<< new_pipe.len << endl
		<< new_pipe.diam << endl
		<< new_pipe.inrepair << endl;
	cout << "Данные трубы сохранены в файл." << endl;
	fout.close();
}

void SaveStation(station& new_station, ofstream& fout)
{
	fout << new_station.title << endl
		<< new_station.workshop << endl
		<< new_station.active_workshop << endl
		<< new_station.efficiency << endl;
	cout << "Данные станции сохранены в файл." << endl;
	fout.close();
}

void DownloadPipe(pipe& pipe, ifstream& fin)
{
	fin.ignore();
	getline(fin, pipe.km_mark);
	fin >> pipe.len;
	fin >> pipe.diam;
	fin >> pipe.inrepair;
	cout << "Данные трубы загружены из файла." << endl;
}

void DownloadStation(station& station, ifstream& fin)
{
	fin.ignore();
	getline(fin, station.title);
	fin >> station.workshop;
	fin >> station.active_workshop;
	fin >> station.efficiency;
	cout << "Данные станции загружены из файла." << endl;
}

int main()
{
	pipe pipe;
	station station;

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
		int choice;
		InputInt(choice);

		switch (choice)
		{
		case 1:
		{
			cout << endl << "<  Добавление трубы  >" << endl << endl;
			pipe = AddPipe();
			break;
		}
		case 2:
		{
			cout << endl << "<  Добавление станции  >" << endl << endl;
			station = AddStation();
			break;
		}
		case 3:
		{
			cout << endl <<  "<  Все объекты  >" << endl << endl;
			ShowPipe(pipe);
			ShowStation(station);
			break;
		}
		case 4:
		{
			cout << endl << "<  Редактирование трубы  >" << endl << endl;
			EditPipe(pipe);
			break;
		}
		case 5:
		{
			cout << endl << "<  Редактирование станции  >" << endl << endl;
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
			fout.open(fname);

			if (!fout.is_open())
				cout << "Ошибка открытия файла!" << endl;
			else
			{
				if (pipe.len == 0)
					fout << 0 << endl;
				else
				{
					fout << 1 << endl;
					SavePipe(pipe, fout);
				}
				if (station.workshop == 0)
					fout << 0 << endl;
				else
				{
					fout << 1 << endl;
					SaveStation(station, fout);
				}
				
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
			fin.open(fname);
			int number;

			if (!fin.is_open())
				cout << "Ошибка открытия файла!" << endl;
				
			else
			{
				fin >> number;
				if (number == 1)
					DownloadPipe(pipe, fin);
				else
					cout << "Нет трубы." << endl;
				fin >> number;
				if (number == 1)
					DownloadStation(station, fin);
				else
					cout << "Нет станции." << endl;
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