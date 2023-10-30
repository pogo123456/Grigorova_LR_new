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
		cout << "����������� ��������� ������! ���������� �����:  ";
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
//		cout << "����������� ��������� ������! ���������� �����:  ";
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
//		cout << "����������� ��������� ������! ���������� �����:  ";
//		cin >> var;
//	}
//}

//pipe AddPipe()
//{
//	pipe new_pipe;
//	cout << "������� ������������ �������:  ";
//	cin.ignore();
//	getline(cin, new_pipe.km_mark);
//	cout << "������� ����� ����� (��):  ";
//	InputDouble(new_pipe.len);
//	cout << "������� ������� ����� (��):  ";
//	InputInt(new_pipe.diam);
//	cout << "��������� ����� (1 - � �������; 0 - ��������):  ";
//	InputBool(new_pipe.inrepair);
//	cout << "������� ID �����:  ";
//	InputInt(new_pipe.ID);
//
//	return new_pipe;
//}
//
//station AddStation()
//{
//	station new_station;
//	cout << "������� �������� �������:  ";
//	cin.ignore();
//	getline(cin, new_station.title);
//	cout << "������� ���-�� �����:  ";
//	InputInt(new_station.workshop);
//	cout << "������� ���-�� ���������� �����:  ";
//	InputInt(new_station.active_workshop);
//	while (new_station.workshop < new_station.active_workshop)
//	{
//		cout << "������! ��������� ���-�� ���������� �����!" << endl << "������� ���������� ������:  ";
//		InputInt(new_station.active_workshop);
//	}
//	cout << "������� ������������� ������� �� A �� G:  ";
//	cin >> new_station.efficiency;
//	while (!(new_station.efficiency >= "A" && new_station.efficiency <= "G" && new_station.efficiency.length() == 1))
//	{
//		cout << "������! ������� ���������� ������:  ";
//		cin >> new_station.efficiency;
//	}
//	cout << "������� ID �������:  ";
//	InputInt(new_station.ID);
//
//	return new_station;
//}
//
//void ShowPipe(const pipe& new_pipe)
//{
//	if (new_pipe.len == 0)
//		cout << "��� �����." << endl;
//	else
//	{
//		cout << "������������ �������:  " << new_pipe.km_mark << endl;
//		cout << "����� �����:  " << new_pipe.len << "��" << endl;
//		cout << "������� �����:  " << new_pipe.diam << "��" << endl;
//		(new_pipe.inrepair) ? cout << "����� � �������." << endl : cout << "����� ��������." << endl;
//		cout << "ID �����:  " << new_pipe.ID << endl;
//	}
//}
//
//void ShowStation(const station& new_station)
//{
//	if (new_station.workshop == 0)
//		cout << "��� �������." << endl;
//	else
//	{
//		cout << "�������� �������:  " << new_station.title << endl;
//		cout << "���-�� �����:  " << new_station.workshop << endl;
//		cout << "���-�� ���������� �����:  " << new_station.active_workshop << endl;
//		cout << "�������������:  " << new_station.efficiency << endl;
//		cout << "ID �������:  " << new_station.ID << endl;
//	}
//}

void EditPipe(pipe& edit_pipe)
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

void EditStation(station& edit_station)
{
	int choice = 0;
	if (edit_station.workshop == 0)
		cout << "��� �������." << endl;
	else
	{
		cout << "������ �������� ���-�� ���������� �����?" << endl;
		cout << "1. ��" << endl << "2. ���" << endl << "��� �����: ";
		GetCorrectNumber(choice);
		switch (choice)
		{
		case 1:
			cout << "������� ����� ���-�� ���������� �����:  ";
			GetCorrectNumber(edit_station.active_workshop);
			while (edit_station.active_workshop > edit_station.workshop)
			{
				cout << "������! ��������� ���-�� ���������� �����!" << endl << "���-�� ���� �����:  " << edit_station.workshop << endl;
				cout << "������� ���������� ������:  ";
				GetCorrectNumber(edit_station.active_workshop);
			}
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

//���������� �����
ofstream& operator >> (ofstream& fout, const pipe& pipe)
{
	fout << pipe.km_mark << endl
		<< pipe.len << endl
		<< pipe.diam << endl
		<< pipe.inrepair << endl
		<< pipe.ID << endl;
	cout << "������ ����� ��������� � ����." << endl;
	return fout;
}
//���������� �������
ofstream& operator >> (ofstream& fout, const station& station)
{
	fout << station.title << endl
		<< station.workshop << endl
		<< station.active_workshop << endl
		<< station.efficiency << endl
		<< station.ID << endl;
	cout << "������ ������� ��������� � ����." << endl;
	return fout;
}

//�������� �����
ifstream& operator << (ifstream& fin, pipe& pipe)
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
//�������� �������
ifstream& operator << (ifstream& fin, station& station)
{
	fin.ignore();
	getline(fin, station.title);
	fin >> station.workshop;
	fin >> station.active_workshop;
	fin >> station.efficiency;
	fin >> station.ID;
	cout << "������ ������� ��������� �� �����." << endl;
	return fin;
}

//���������� �����
istream& operator >> (istream& in, pipe& new_pipe)
{
	cout << "������� ������������ �������:  ";
	in.ignore();
	getline(in, new_pipe.km_mark);
	cout << "������� ����� ����� (��):  ";
	GetCorrectNumber(new_pipe.len);
	cout << "������� ������� ����� (��):  ";
	GetCorrectNumber(new_pipe.diam);
	cout << "��������� ����� (1 - � �������; 0 - ��������):  ";
	GetCorrectNumber(new_pipe.inrepair);
	cout << "������� ID �����:  ";
	GetCorrectNumber(new_pipe.ID);
	
	return in;
}
//�������� �����
ostream& operator << (ostream& out, const pipe& new_pipe)
{
	if (new_pipe.len == 0)
		out << "��� �����." << endl;
	else
	{
		out << "������������ �������:  " << new_pipe.km_mark << endl;
		out << "����� �����:  " << new_pipe.len << "��" << endl;
		out << "������� �����:  " << new_pipe.diam << "��" << endl;
		(new_pipe.inrepair) ? out << "����� � �������." << endl : out << "����� ��������." << endl;
		out << "ID �����:  " << new_pipe.ID << endl;
	}
	return out;
}

//���������� �������
istream& operator >> (istream& in, station& new_station)
{
	cout << "������� �������� �������:  ";
	cin.ignore();
	getline(cin, new_station.title);
	cout << "������� ���-�� �����:  ";
	GetCorrectNumber(new_station.workshop);
	cout << "������� ���-�� ���������� �����:  ";
	GetCorrectNumber(new_station.active_workshop);
	while (new_station.workshop < new_station.active_workshop)
	{
		cout << "������! ��������� ���-�� ���������� �����!" << endl << "������� ���������� ������:  ";
		GetCorrectNumber(new_station.active_workshop);
	}
	cout << "������� ������������� ������� �� A �� G:  ";
	cin >> new_station.efficiency;
	while (!(new_station.efficiency >= "A" && new_station.efficiency <= "G" && new_station.efficiency.length() == 1))
	{
		cout << "������! ������� ���������� ������:  ";
		cin >> new_station.efficiency;
	}
	cout << "������� ID �������:  ";
	GetCorrectNumber(new_station.ID);

	return in;
}
//�������� �������
ostream& operator << (ostream& out, const station& new_station)
{
	if (new_station.workshop == 0)
		out << "��� �������." << endl;
	else
	{
		out << "�������� �������:  " << new_station.title << endl;
		out << "���-�� �����:  " << new_station.workshop << endl;
		out << "���-�� ���������� �����:  " << new_station.active_workshop << endl;
		out << "�������������:  " << new_station.efficiency << endl;
		out << "ID �������:  " << new_station.ID << endl;
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
		cout << "����" << endl;
		cout << "1. �������� �����" << endl;
		cout << "2. �������� �������" << endl;
		cout << "3. ������� ��� �������" << endl;
		cout << "4. ������������� �����" << endl;
		cout << "5. ������������� �������" << endl;
		cout << "6. ���������" << endl;
		cout << "7. ���������" << endl;
		cout << "8. �����" << endl;
		cout << "------------------------------------" << endl << endl;

		cout << "��� �����: ";
		int choice;
		GetCorrectNumber(choice);

		switch (choice)
		{
		case 1:
		{
			cout << endl << "<  ���������� �����  >" << endl << endl;
			//pipe = AddPipe();
			cin >> pipe;
			break;
		}
		case 2:
		{
			cout << endl << "<  ���������� �������  >" << endl << endl;
			//station = AddStation();
			cin >> station;
			break;
		}
		case 3:
		{
			cout << endl <<  "<  ��� �������  >" << endl << endl;
			//ShowPipe(pipe);
			//ShowStation(station);
			cout << pipe << endl;
			cout << station << endl;
			break;
		}
		case 4:
		{
			cout << endl << "<  �������������� �����  >" << endl << endl;
			EditPipe(pipe);
			break;
		}
		case 5:
		{
			cout << endl << "<  �������������� �������  >" << endl << endl;
			EditStation(station);
			break;
		}
		case 6:
		{
			cout << endl << "<  ��������  >" << endl << endl;
			ofstream fout;
			string fname;
			cout << "������� ��� �����:  ";
			cin.ignore();
			getline(cin, fname);
			fout.open(fname+".txt");

			if (!fout.is_open())
				cout << "������ �������� �����!" << endl;
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
			cout << endl << "<  ��������  >" << endl << endl;
			ifstream fin;
			string fname;
			cout << "������� ��� �����:  ";
			cin.ignore();
			getline(cin, fname);
			fin.open(fname+".txt");
			int number;

			if (!fin.is_open())
				cout << "������ �������� �����!" << endl;
				
			else
			{
				fin >> number;
				if (number == 1)
					DownloadPipe(pipe, fin);
				else
					cout << "��� �����." << endl;
				fin >> number;
				if (number == 1)
					DownloadStation(station, fin);
				else
					cout << "��� �������." << endl;
				fin.close();
			}
			break;
		}
		case 8:
			cout << endl << "<  �����  >" << endl << endl;
			return 0;
			break;
		default:
			cout << "������! ������� �����" << endl;
			break;
		}
	}

	return 0;
}