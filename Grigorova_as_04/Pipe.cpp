#include "Pipe.h"
#include "Header.h"

int Pipe::max_id_p = 0;

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
	new_pipe.diam = GetCorrectDiam(500, 1400);
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

void Pipe::OutputPipeStatus()
{
	cout << (inrepair ? "����� � �������." : "����� ��������.") << endl;
}

bool Pipe::GetStatus()
{
	return inrepair;
}

int Pipe::GetDia()
{
	return diam;
}

int Pipe::GetLen()
{
	return len;
}

string Pipe::GetName() const
{
	return km_mark;
}

int Pipe::GetId()
{
	return ID;
}

bool Pipe::ConnectionNotBusy() const
{
	return CSid1 < 1 || CSid2 < 1;
}

void Pipe::Connect(const int& id1, const int& id2)
{
	CSid1 = id1;
	CSid2 = id2;
}

void Pipe::DeleteConnection()
{
	CSid1 = 0;
	CSid2 = 0;
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