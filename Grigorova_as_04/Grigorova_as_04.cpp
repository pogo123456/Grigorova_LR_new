#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include "Pipe.h"
#include "Header.h"

using namespace std 

struct station
{
	string title = "";
	int workshop = 0;
	int active_workshop = 0;
	string efficiency = "A";
	int ID = 0;
};

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

//void InputDouble(double& var)
//{
//	cin >> var;
//	while (cin.fail() || cin.peek() != '\n' || var <= 0)
//	{
//		cin.clear();
//		cin.ignore(1000, '\n');
//		cout << "Некорректно введенные данные! Попробуйте снова:  ";
//		cin >> var;
//	}
//}
//
//void InputBool(bool& var)
//{
//	cin >> var;
//	while (cin.fail() || cin.peek() != '\n')
//	{
//		cin.clear();
//		cin.ignore(1000, '\n');
//		cout << "Некорректно введенные данные! Попробуйте снова:  ";
//		cin >> var;
//	}
//}

//pipe AddPipe()
//{
//	pipe new_pipe;
//	cout << "Введите километровую отметку:  ";
//	cin.ignore();
//	getline(cin, new_pipe.km_mark);
//	cout << "Введите длину трубы (км):  ";
//	InputDouble(new_pipe.len);
//	cout << "Введите диаметр трубы (мм):  ";
//	InputInt(new_pipe.diam);
//	cout << "Состояние трубы (1 - в ремонте; 0 - работает):  ";
//	InputBool(new_pipe.inrepair);
//	cout << "Введите ID трубы:  ";
//	InputInt(new_pipe.ID);
//
//	return new_pipe;
//}
//
//station AddStation()
//{
//	station new_station;
//	cout << "Введите название станции:  ";
//	cin.ignore();
//	getline(cin, new_station.title);
//	cout << "Введите кол-во цехов:  ";
//	InputInt(new_station.workshop);
//	cout << "Введите кол-во работающих цехов:  ";
//	InputInt(new_station.active_workshop);
//	while (new_station.workshop < new_station.active_workshop)
//	{
//		cout << "Ошибка! Превышено кол-во работающих цехов!" << endl << "Введите корректные данные:  ";
//		InputInt(new_station.active_workshop);
//	}
//	cout << "Введите эффективность станции от A до G:  ";
//	cin >> new_station.efficiency;
//	while (!(new_station.efficiency >= "A" && new_station.efficiency <= "G" && new_station.efficiency.length() == 1))
//	{
//		cout << "Ошибка! Введите корректные данные:  ";
//		cin >> new_station.efficiency;
//	}
//	cout << "Введите ID станции:  ";
//	InputInt(new_station.ID);
//
//	return new_station;
//}
//
//void ShowPipe(const pipe& new_pipe)
//{
//	if (new_pipe.len == 0)
//		cout << "Нет трубы." << endl;
//	else
//	{
//		cout << "Километровая отметка:  " << new_pipe.km_mark << endl;
//		cout << "Длина трубы:  " << new_pipe.len << "км" << endl;
//		cout << "Диаметр трубы:  " << new_pipe.diam << "мм" << endl;
//		(new_pipe.inrepair) ? cout << "Труба в ремонте." << endl : cout << "Труба работает." << endl;
//		cout << "ID трубы:  " << new_pipe.ID << endl;
//	}
//}
//
//void ShowStation(const station& new_station)
//{
//	if (new_station.workshop == 0)
//		cout << "Нет станции." << endl;
//	else
//	{
//		cout << "Название станции:  " << new_station.title << endl;
//		cout << "Кол-во цехов:  " << new_station.workshop << endl;
//		cout << "Кол-во работающих цехов:  " << new_station.active_workshop << endl;
//		cout << "Эффективность:  " << new_station.efficiency << endl;
//		cout << "ID станции:  " << new_station.ID << endl;
//	}
//}

void EditPipe(pipe& edit_pipe)
{
	int choice = 0;
	if (edit_pipe.len == 0)
		cout << "Нет трубы." << endl;
	else
	{
		cout << "Хотите изменить статус трубы?" << endl;
		cout << "1. Да" << endl << "2. Нет" << endl << "Ваш выбор: ";
		GetCorrectNumber(choice);
		switch (choice)
		{
		case 1:
			edit_pipe.inrepair = !edit_pipe.inrepair;
			cout << "Статус трубы изменен." << endl;
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

void EditStation(station& edit_station)
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

//сохранение трубы
ofstream& operator >> (ofstream& fout, const pipe& pipe)
{
	fout << pipe.km_mark << endl
		<< pipe.len << endl
		<< pipe.diam << endl
		<< pipe.inrepair << endl
		<< pipe.ID << endl;
	cout << "Данные трубы сохранены в файл." << endl;
	return fout;
}
//сохранение станции
ofstream& operator >> (ofstream& fout, const station& station)
{
	fout << station.title << endl
		<< station.workshop << endl
		<< station.active_workshop << endl
		<< station.efficiency << endl
		<< station.ID << endl;
	cout << "Данные станции сохранены в файл." << endl;
	return fout;
}

//загрузка трубы
ifstream& operator << (ifstream& fin, pipe& pipe)
{
	fin.ignore();
	getline(fin, pipe.km_mark);
	fin >> pipe.len;
	fin >> pipe.diam;
	fin >> pipe.inrepair;
	fin >> pipe.ID;
	cout << "Данные трубы загружены из файла." << endl;
	return fin;
}
//загрузка станции
ifstream& operator << (ifstream& fin, station& station)
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

//добавление трубы
istream& operator >> (istream& in, pipe& new_pipe)
{
	cout << "Введите километровую отметку:  ";
	in.ignore();
	getline(in, new_pipe.km_mark);
	cout << "Введите длину трубы (км):  ";
	GetCorrectNumber(new_pipe.len);
	cout << "Введите диаметр трубы (мм):  ";
	GetCorrectNumber(new_pipe.diam);
	cout << "Состояние трубы (1 - в ремонте; 0 - работает):  ";
	GetCorrectNumber(new_pipe.inrepair);
	cout << "Введите ID трубы:  ";
	GetCorrectNumber(new_pipe.ID);
	
	return in;
}
//показать трубу
ostream& operator << (ostream& out, const pipe& new_pipe)
{
	if (new_pipe.len == 0)
		out << "Нет трубы." << endl;
	else
	{
		out << "Километровая отметка:  " << new_pipe.km_mark << endl;
		out << "Длина трубы:  " << new_pipe.len << "км" << endl;
		out << "Диаметр трубы:  " << new_pipe.diam << "мм" << endl;
		(new_pipe.inrepair) ? out << "Труба в ремонте." << endl : out << "Труба работает." << endl;
		out << "ID трубы:  " << new_pipe.ID << endl;
	}
	return out;
}

//добавление станции
istream& operator >> (istream& in, station& new_station)
{
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
	cout << "Введите ID станции:  ";
	GetCorrectNumber(new_station.ID);

	return in;
}
//показать станцию
ostream& operator << (ostream& out, const station& new_station)
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
		GetCorrectNumber(choice);

		switch (choice)
		{
		case 1:
		{
			cout << endl << "<  Добавление трубы  >" << endl << endl;
			//pipe = AddPipe();
			cin >> pipe;
			break;
		}
		case 2:
		{
			cout << endl << "<  Добавление станции  >" << endl << endl;
			//station = AddStation();
			cin >> station;
			break;
		}
		case 3:
		{
			cout << endl <<  "<  Все объекты  >" << endl << endl;
			//ShowPipe(pipe);
			//ShowStation(station);
			cout << pipe << endl;
			cout << station << endl;
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
			fout.open(fname+".txt");

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
			fin.open(fname+".txt");
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