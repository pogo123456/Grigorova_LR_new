#include "Pipe.h"
#include "Header.h"

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
	new_pipe.OutputPipeStatus();

	return in;
}

ostream& operator << (ostream& out, const Pipe& new_pipe)
{
	if (new_pipe.len == 0)
		out << "��� �����." << endl;
	else
	{
		out << "ID �����:  " << new_pipe.ID << endl;
		out << "������������ �������:  " << new_pipe.km_mark << endl;
		out << "����� �����:  " << new_pipe.len << "��" << endl;
		out << "������� �����:  " << new_pipe.diam << "��" << endl;
		if (new_pipe.inrepair)
			out << "����� � �������." << endl;
		else
			out << "����� ��������." << endl;
	}
	return out;
}

void EditPipe(Pipe& edit_pipe)
{
	cout << "������ �������� ������ �����?" << endl;
	cout << "1. ��" << endl << "2. ���" << endl << "��� �����:  ";
	int choice = 0;
	GetCorrectNumber(choice);
	switch (choice)
	{
	case 1:
		bool inrepair;
		cout << "����� ������: (1 - � �������, 0 - ��������):  ";
		GetCorrectNumber(inrepair);

		edit_pipe.inrepair = inrepair;
		cout << endl << "ID: " << edit_pipe.ID << " - ";
		edit_pipe.OutputPipeStatus();
		break;
	case 2:
		return;
		break;
	default:
		cout << "������! ������� ���������� ������:  ";
		break;
	}
	
}

void EditPipes(vector <Pipe*>& edit_pipes)
{
	cout << endl << "������ �������� ������ �����?" << endl;
	cout << "1. ��" << endl << "2. ���" << endl << "��� �����:  ";
	int choice = 0;
	GetCorrectNumber(choice);
	switch (choice)
	{
	case 1:
		bool inrepaire;
		cout << "����� ������ (1 - � �������, 0 - ��������):  ";
		GetCorrectNumber(inrepaire);

		for (auto& pipe : edit_pipes)
		{
			pipe->inrepair = inrepaire;
			cout << endl << "ID: " << pipe->ID << " - ";
			pipe->OutputPipeStatus();
		}
		break;
	case 2:
		return;
	default:
		cout << "������! ������� ���������� ������:  " << endl;
		break;
	}
}

void Pipe::OutputPipeStatus()
{
	cout << (inrepair ? "����� � �������." : "����� ��������.") << endl;
}

bool Pipe::GetStatus()
{
	return inrepair;
}

ofstream& operator << (ofstream& fout, const Pipe& pipe)
{
	fout << pipe.ID << endl
		<< pipe.km_mark << endl
		<< pipe.len << endl
		<< pipe.diam << endl
		<< pipe.inrepair << endl;
	/*cout << "������ ����� ��������� � ����." << endl;*/
	return fout;
}

ifstream& operator >> (ifstream& fin, Pipe& pipe)
{
	fin >> pipe.ID;
	fin.ignore();
	getline(fin, pipe.km_mark);
	fin >> pipe.len;
	fin >> pipe.diam;
	fin >> pipe.inrepair;
	pipe.max_id_p = pipe.ID;
	/*cout << "������ ����� ��������� �� �����." << endl;*/
	return fin;
}