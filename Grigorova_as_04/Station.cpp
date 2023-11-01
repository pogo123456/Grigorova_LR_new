#include "Station.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Header.h"

int Station::max_id_cs = 1;

int Station::GetId()
{
	return ID;
}

istream& operator >> (istream& in, Station& new_station)
{
	new_station.ID = ++new_station.max_id_cs;
	cout << "������� �������� ID:  " << new_station.ID << endl;
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
	return in;
}

ostream& operator << (ostream& out, const Station& new_station)
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

void EditStation(Station& edit_station)
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

ofstream& operator << (ofstream& fout, const Station& station)
{
	fout << station.title << endl
		<< station.workshop << endl
		<< station.active_workshop << endl
		<< station.efficiency << endl
		<< station.ID << endl;
	cout << "������ ������� ��������� � ����." << endl;
	return fout;
}


ifstream& operator >> (ifstream& fin, Station& station)
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