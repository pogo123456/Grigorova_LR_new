#include "Pipe.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Header.h"

int Pipe::max_id = 1;

istream& operator >> (istream& in, Pipe& new_pipe)
{
	cout << "������� ������������ �������:  ";
	in.ignore();
	getline(in, new_pipe.km_mark);
	cout << "������� ����� ����� (��):  ";
	GetCorrectNumber(new_pipe.len);
	cout << "������� ������� ����� (��):  ";
	GetCorrectNumber(new_pipe.diam);
	cout << "��������� ����� (1 - � �������; 0 - ��������):  ";
	new_pipe.inrepair = GetCorrectNumber(new_pipe.inrepair);
	cout << new_pipe.OutputStatus();
	cout << "������� ID �����:  ";
	GetCorrectNumber(new_pipe.ID);

	return in;
}

ostream& operator<<(ostream& out, Pipe& new_pipe)
{
	if (new_pipe.len == 0)
		out << "��� �����." << endl;
	else
	{
		out << "������������ �������:  " << new_pipe.km_mark << endl;
		out << "����� �����:  " << new_pipe.len << "��" << endl;
		out << "������� �����:  " << new_pipe.diam << "��" << endl;
		out << "ID �����:  " << new_pipe.ID << endl;
		out << "������ �����:  " << new_pipe.OutputStatus();
	}
	return out;
}

string Pipe::OutputStatus()
{
	return (inrepair ? "����� � �������." : "����� ��������.");
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
