#include "Pipe.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Header.h"
#include <unordered_map>

int Pipe::max_id_p = 0;

string Pipe::GetName() const
{
	return km_mark;
}

int Pipe::GetId()
{
	return ID;
}

istream& operator >> (istream& in, Pipe& new_pipe)
{
	new_pipe.ID = ++new_pipe.max_id_p;
	cout << "Трубе присвоен ID:  " << new_pipe.ID << endl;
	cout << "Введите километровую отметку:  ";
	in.ignore();
	getline(in, new_pipe.km_mark);
	cout << "Введите длину трубы (км):  ";
	GetCorrectNumber(new_pipe.len);
	cout << "Введите диаметр трубы (мм):  ";
	GetCorrectNumber(new_pipe.diam);
	cout << "Состояние трубы (1 - в ремонте; 0 - работает):  ";
	GetCorrectNumber(new_pipe.inrepair);
	new_pipe.OutputPipeStatus();

	return in;
}

ostream& operator << (ostream& out, Pipe& new_pipe)
{
	if (new_pipe.len == 0)
		out << "Нет трубы." << endl;
	else
	{
		out << "Километровая отметка:  " << new_pipe.km_mark << endl;
		out << "Длина трубы:  " << new_pipe.len << "км" << endl;
		out << "Диаметр трубы:  " << new_pipe.diam << "мм" << endl;
		out << "ID трубы:  " << new_pipe.ID << endl;
		out << "Статус трубы:  ";
		new_pipe.OutputPipeStatus();
	}
	return out;
}

void EditPipe(Pipe& edit_pipe)
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

void EditPipes(vector <Pipe*>& edit_pipes)
{
	cout << endl << "Хотите изменить статус трубы?" << endl;
	cout << "1. Да" << endl << "2. Нет" << endl << "Ваш выбор: ";
	int choice = 0;
	GetCorrectNumber(choice);
	switch (choice)
	{
	case 1:
		bool inrepaire = 0;
		cout << "Труба в ремонте? (1 - Да, 0 - Нет) ";
		GetCorrectNumber(inrepaire);

		for (auto& pipe : edit_pipes)
		{
			pipe->inrepair = inrepaire;
			cout << "ID: " << pipe->ID << " - ";
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


void Pipe::OutputPipeStatus()
{
	cout << (inrepair ? "Труба в ремонте." : "Труба работает.") << endl;
}

bool Pipe::GetStatus()
{
	return inrepair;
}

ofstream& operator << (ofstream& fout, const Pipe& pipe)
{
	fout << pipe.km_mark << endl
		<< pipe.len << endl
		<< pipe.diam << endl
		<< pipe.inrepair << endl
		<< pipe.ID << endl;
	cout << "Данные трубы сохранены в файл." << endl;
	return fout;
}

ifstream& operator >> (ifstream& fin, Pipe& pipe)
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