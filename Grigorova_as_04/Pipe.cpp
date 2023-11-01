#include "Pipe.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Header.h"

int Pipe::max_id_p = 1;

int Pipe::GetId()
{
	return ID;
}

istream& operator >> (istream& in, Pipe& new_pipe)
{
	new_pipe.ID = ++new_pipe.max_id_p;
	cout << "����� �������� ID:  " << new_pipe.ID << endl;
	cout << "������� ������������ �������:  ";
	in.ignore();
	getline(in, new_pipe.km_mark);
	cout << "������� ����� ����� (��):  ";
	GetCorrectNumber(new_pipe.len);
	cout << "������� ������� ����� (��):  ";
	GetCorrectNumber(new_pipe.diam);
	cout << "��������� ����� (1 - � �������; 0 - ��������):  ";
	GetCorrectNumber(new_pipe.inrepair);
	cout << new_pipe.OutputStatus();
	cout << "������� ID �����:  ";
	GetCorrectNumber(new_pipe.ID);

	return in;
}

ostream& operator << (ostream& out, Pipe& new_pipe)
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

void EditPipe(Pipe& edit_pipe)
{
	int choice = 0;
	if (edit_pipe.len == 0)
		cout << "��� �����." << endl;
	else
	{
		cout << "������ �������� ������ �����?" << endl;
		cout << "1. ��" << endl << "2. ���" << endl << "��� �����: ";
		GetCorrectNumber(choice);
		switch (choice)
		{
		case 1:
			edit_pipe.inrepair = !edit_pipe.inrepair;
			cout << "������ ����� �������." << endl;
			break;
		case 2:
			return;
			break;
		default:
			cout << "������! ������� ���������� ������:  ";
			break;
		}
	}
}

string Pipe::OutputStatus()
{
	return (inrepair ? "����� � �������." : "����� ��������.");
}

ofstream& operator << (ofstream& fout, const Pipe& pipe)
{
	fout << pipe.km_mark << endl
		<< pipe.len << endl
		<< pipe.diam << endl
		<< pipe.inrepair << endl
		<< pipe.ID << endl;
	cout << "������ ����� ��������� � ����." << endl;
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
	cout << "������ ����� ��������� �� �����." << endl;
	return fin;
}