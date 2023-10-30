#include "Pipe.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Header.h"

int Pipe::max_id = 1;

istream& operator >> (istream& in, Pipe& new_pipe)
{
	cout << "Введите километровую отметку:  ";
	in.ignore();
	getline(in, new_pipe.km_mark);
	cout << "Введите длину трубы (км):  ";
	GetCorrectNumber(new_pipe.len);
	cout << "Введите диаметр трубы (мм):  ";
	GetCorrectNumber(new_pipe.diam);
	cout << "Состояние трубы (1 - в ремонте; 0 - работает):  ";
	new_pipe.inrepair = GetCorrectNumber(new_pipe.inrepair);
	cout << new_pipe.OutputStatus();
	cout << "Введите ID трубы:  ";
	GetCorrectNumber(new_pipe.ID);

	return in;
}

ostream& operator<<(ostream& out, Pipe& new_pipe)
{
	if (new_pipe.len == 0)
		out << "Нет трубы." << endl;
	else
	{
		out << "Километровая отметка:  " << new_pipe.km_mark << endl;
		out << "Длина трубы:  " << new_pipe.len << "км" << endl;
		out << "Диаметр трубы:  " << new_pipe.diam << "мм" << endl;
		out << "ID трубы:  " << new_pipe.ID << endl;
		out << "Статус трубы:  " << new_pipe.OutputStatus();
	}
	return out;
}

string Pipe::OutputStatus()
{
	return (inrepair ? "Труба в ремонте." : "Труба работает.");
}

void Pipe::EditPipe()
{

}

void Pipe::Savepipe(ofstream& file)
{
}

void Pipe::DownloadPipe(ifstream& file)
{
}
