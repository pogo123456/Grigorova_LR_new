#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include "Pipe.h"
#include "Station.h"
#include "Header.h"
#include <unordered_map>
#include <unordered_set>
#include "Pipe.cpp"
#include "Station.cpp"
#include <vector>

using namespace std;

unordered_map <int, Pipe> pipes;
unordered_map <int, Station> stations;

bool check_p_name(Pipe& p, string km_mark)
{
	return (p.GetName().find(km_mark) != string::npos);
}

bool check_p_status(Pipe& p, bool status) 
{
	return (p.GetStatus() == status);
}

bool check_s_name(Station& s, string title) 
{
	return (s.GetName().find(title) != string::npos);
}

bool check_s_unworking(Station& s, double pers) 
{
	return (s.GetPercentOfActiveWorkshops() >= pers);
}

unordered_set <int> search_p(unordered_map <int, Pipe>& pipes) 
{
	int choice = 0;
	unordered_set <int> id;
	cout << "������ ����� ��:" << endl;
	cout << "1. ��������" << endl;
	cout << "2. ������" << endl;
	cout << "��� �����";
	GetCorrectNumber(choice);
	if (choice == 1) 
	{
		string km_mark;
		cout << "������� �������� �����: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		getline(cin, km_mark);
		id = search_p_by_parametr(pipes, check_p_name, km_mark);
	}
	else 
	{
		bool k;
		cout << "������� ������ ����� (1 - � �������; 0 - ��������): ";
		GetCorrectNumber(k);
		id = search_p_by_parametr(pipes, check_p_status, k);
	}
	return id;
}

unordered_set<int> search_s(unordered_map <int, Station>& stations) 
{
	int choice;
	unordered_set <int> id;
	cout << "������ ������� ��:" << endl;
	cout << "1. ��������" << endl;
	cout << "2. ������� �������������� �����" << endl;
	cout << "��� �����";
	GetCorrectNumber(choice);
	if (choice == 1) 
	{
		string title;
		cout << "������� �������� �������: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		getline(cin, title);
		id = search_s_by_parametr(stations, check_s_name, title);

	}
	else 
	{
		double k;
		cout << "������� ������� �������������� �����: ";
		GetCorrectNumber(k);
		id = search_s_by_parametr(stations, check_s_unworking, k);
	}
	return id;
}

void SearchPipes() 
{
	if (pipes.size() != 0) {
		auto x = search_p(pipes);
		if (x.size() != 0) {
			for (auto& i : x)
				cout << pipes[i] << endl;
		}
		else
			cout << "�� ���������� ����� �����." << endl;
	}
	else
		cout << "����� �� �������." << endl;
}

void SearchStation() 
{
	vector <int> x;
	if (stations.size() != 0) {
		auto x = search_s(stations);
		if (x.size() != 0) {
			for (auto& i : x)
				cout << stations[i] << endl;
		}
		else
			cout << "�� ���������� ����� �������.";
	}
	else
		cout << "������� �� �������." << endl;
}

int main()
{
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
		cout << "8. ����� �����" << endl;
		cout << "9. ����� �������" << endl;
		cout << "0. �����" << endl;
		cout << "------------------------------------" << endl << endl;

		cout << "��� �����: ";
		int choice = 0;
		GetCorrectNumber(choice);

		switch (choice)
		{
		case 1:
		{
			cout << endl << "<  ���������� �����  >" << endl << endl;
			Pipe pipe;
			cin >> pipe;
			pipes.insert(make_pair(pipe.GetId(), pipe));
			break;
		}
		case 2:
		{
			cout << endl << "<  ���������� �������  >" << endl << endl;
			Station station;
			cin >> station;
			stations.insert(make_pair(station.GetId(), station));
			break;
		}
		case 3:
		{
			cout << endl <<  "<  ��� �������  >" << endl << endl;
			Pipe pipe;
			Station station;

			if (pipes.size() == 0)
				cout << "���� ���." << endl;
			for (auto& pair : pipes)
				cout << pair.second;

			if (stations.size() == 0)
				cout << "������� ���." << endl;
			for (const auto& pair : stations)
				cout << pair.second;
			break;
		}
		case 4:
		{
			cout << endl << "<  �������������� �����  >" << endl << endl;
			Pipe pipe = SelectElement(pipes);
			EditPipe(pipe);
			break;
		}
		case 5:
		{
			cout << endl << "<  �������������� �������  >" << endl << endl;
			Station station = SelectElement(stations);
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
				fout << pipes.size() << endl;
				for (const auto& pair : pipes)
					fout << pair.second;

				fout << stations.size() << endl;
				for (const auto& pair : stations)
					fout << pair.second;
				
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
			int number = 0;

			if (!fin.is_open())
				cout << "������ �������� �����!" << endl;
				
			else
			{
				int sizePipe = 0;
				if (sizePipe == 0)
					cout << "����� ���." << endl;
				while (sizePipe-- > 0)
				{
					Pipe pipe;
					cin >> pipe;
					pipes.insert(make_pair(pipe.GetId(), pipe));
				}

				int sizeStation = 0;
				if (sizeStation == 0)
					cout << "������� ���." << endl;
				while (sizeStation-- > 0)
				{
					Station station;
					cin >> station;
					stations.insert(make_pair(station.GetId(), station));
				}

				fin.close();
			}
			break;
		}
		case 8:
		{
			cout << endl << "<  ����� �����  >" << endl << endl;
			/*SearchPipes();*/
			break;
		}
		case 9:
		{
			cout << endl << "<  ����� �������  >" << endl << endl;
			/*SearchStation();*/
			break;
		}
		case 0:
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