#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Pipe.h"
#include "Station.h"
#include "Header.h"


using namespace std;

unordered_map <int, Pipe> pipes;
unordered_map <int, Station> stations;

void SearchPipes(unordered_map <int, Pipe>& pipes) 
{
	while (true)
	{
		int choice = 0;
		cout << "�� ������ �������� ����� �����?" << endl;
		cout << "1. ������������� �������" << endl << "2. ������ �����" << endl << "3. �����" << endl << "��� �����:  ";
		GetCorrectNumber(choice);
		switch (choice)
		{
		case 1:
		{
			string name;
			cout << endl << "����������� �������: ";
			cin.ignore();
			getline(cin, name);

			vector <Pipe*> p;
			for (auto& pair : pipes)
			{
				if (pair.second.GetName().find(name) != string::npos)
				{
					cout << endl << pair.second << endl;
					p.push_back(&(pair.second));
				}
			}
			if (p.empty())
				cout << "����� � ����� ������ ���." << endl;
			else
				EditPipes(p);
		}
		break;
		case 2:
		{
			bool inrepair;
			cout << "C����� �����: � �������? (1 - ��, 0 - ���): ";
			GetCorrectNumber(inrepair);

			vector<Pipe*> p;
			for (auto& pair : pipes) {
				if (pair.second.GetStatus() == inrepair)
				{
					cout << endl << pair.second << endl;
					p.push_back(&(pair.second));
				}
			}
			if (p.empty())
				cout << "����� � ����� �������� ���." << endl;
			else
				EditPipes(p);
		}
		break;
		case 3:
		{
			return;
			break;
		}
		default:
			cout << "������! ������� ���������� ������";
			break;
		}
	}
}

void SearchStations(unordered_map <int, Station>& stations) 
{
	while (true)
	{
		int choice = 0;
		cout << "�� ������ �������� ����� �������?" << endl;
		cout << "1. ��������" << endl << "2. ������� �������� �����" << endl << "3. �����" << endl << "��� �����:  ";
		GetCorrectNumber(choice);
		switch (choice)
		{
		case 1:
		{
			string name;
			cout << "��������: ";
			cin.ignore();
			getline(cin, name);

			vector<Station*> cs;
			for (auto& pair : stations) 
			{
				if (pair.second.GetName().find(name) != string::npos)
				{
					cout << endl << pair.second << endl;
					cs.push_back(&(pair.second));
				}
			}
			if (cs.empty())
				cout << "������� � ����� ��������� ���." << endl;
			else
				EditStations(cs);
		}
		break;
		case 2:
		{
			int percent = 0;
			cout << "������� ������� �������� ����� (0-100 � ������������ � 5%): ";
			GetCorrectNumber(percent);

			vector<Station*> cs;
			for (auto& pair : stations) {
				if (pair.second.GetPercentOfActiveWorkshops() > (percent - 5.0) && pair.second.GetPercentOfActiveWorkshops() < (percent + 5.0))
				{
					cout << endl << pair.second << endl;
					cs.push_back(&(pair.second));
				}
			}
			if (cs.empty())
				cout << "������� � ����� ��������� ���." << endl;
			else
				EditStations(cs);
		}
		break;
		case 3:
		{
			return;
			break;
		}
		default:
			cout << "������! ������� ���������� ������";
			break;
	}
	}
}

void AddPipe()
{
	Pipe pipe;
	cin >> pipe;
	pipes.insert(make_pair(pipe.GetId(), pipe));
}

void AddStation()
{
	Station station;
	cin >> station;
	stations.insert(make_pair(station.GetId(), station));
}

void AllObject()
{
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
}

void EditPipe()
{
	if (pipes.size() == 0)
		cout << "���� ��� �������������� ���." << endl;
	else
	{
		Pipe pipe = SelectElement(pipes);
		EditPipe(pipe);

	}
}

void EditStation()
{
	if (stations.size() == 0)
		cout << "������� ��� �������������� ���." << endl;
	else
	{
		Station station = SelectElement(stations);
		EditStation(station);
	}
}

void SaveToFile()
{
	ofstream fout;
	string fname;
	cout << "������� ��� �����:  ";
	cin.ignore();
	getline(cin, fname);
	fout.open(fname + ".txt");

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
}

void LoadToFile()
{
	ifstream fin;
	string fname;
	cout << "������� ��� �����:  ";
	cin.ignore();
	getline(cin, fname);
	fin.open(fname + ".txt");

	if (!fin.is_open())
		cout << "������ �������� �����!" << endl;

	else
	{
		int sizePipe = 0;
		fin >> sizePipe;
		if (sizePipe == 0)
			cout << "����� ���." << endl;
		while (sizePipe-- > 0)
		{
			Pipe pipe;
			fin >> pipe;
			pipes.insert(make_pair(pipe.GetId(), pipe));
		}

		int sizeStation = 0;
		fin >> sizeStation;
		if (sizeStation == 0)
			cout << "������� ���." << endl;
		while (sizeStation-- > 0)
		{
			Station station;
			fin >> station;
			stations.insert(make_pair(station.GetId(), station));
		}

		fin.close();
	}
}

void DeleteObject()
{
	cout << "1. ������� �����" << endl << "2. ������� �������" << endl << "��� �����:  ";
	int choice = 0;
	GetCorrectNumber(choice);
	switch (choice)
	{
	case 1:
	{
		if (pipes.size() == 0)
			cout << "��� ��������� ����." << endl;
		else
		{
			cout << endl << "������� ID �����, ������� ����� �������:  ";
			int idToDelete = 0;
			GetCorrectNumber(idToDelete);

			if (pipes.find(idToDelete) == pipes.end())
				cout << "����� � ����� ID �� ����������." << endl;
			else
			{
				pipes.erase(idToDelete);

				cout << endl << "����� �������." << endl;

				for (auto& pair : pipes)
					cout << pair.second << endl;
			}
		}
	}
	break;
	case 2:
	{
		if (stations.size() == 0)
			cout << "��� ��������� �������." << endl;
		else
		{
			cout << endl << "������� ID �������, ������� ����� �������:  ";
			int idToDelete = 0;
			GetCorrectNumber(idToDelete);

			if (pipes.find(idToDelete) == pipes.end())
				cout << "����� � ����� ID �� ����������." << endl;
			else
			{
				stations.erase(idToDelete);

				cout << endl << "������� �������." << endl;

				for (auto& pair : stations)
					cout << pair.second << endl;
			}
		}
	}
	break;
	case 3:
		return;
		break;
	default:
		cout << "������! ������� �����" << endl;
		break;
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	while (true)
	{
		cout  << endl << "------------------------------------" << endl;
		cout << " ����" << endl;
		cout << " 0. �����" << endl;
		cout << " 1. �������� �����" << endl;
		cout << " 2. �������� �������" << endl;
		cout << " 3. ������� ��� �������" << endl;
		cout << " 4. ������������� �����" << endl;
		cout << " 5. ������������� �������" << endl;
		cout << " 6. ���������" << endl;
		cout << " 7. ���������" << endl;
		cout << " 8. ����� �����" << endl;
		cout << " 9. ����� �������" << endl;
		cout << " 10. �������" << endl;
		cout << "------------------------------------" << endl << endl;

		cout << "��� �����: ";
		int choice = 0;
		GetCorrectNumber(choice);

		switch (choice)
		{
		case 0:
			cout << endl << "<  �����  >" << endl << endl;
			return 0;
			break;
		case 1:
		{
			cout << endl << "<  ���������� �����  >" << endl << endl;
			AddPipe();
			break;
		}
		case 2:
		{
			cout << endl << "<  ���������� �������  >" << endl << endl;
			AddStation();
			break;
		}
		case 3:
		{
			cout << endl <<  "<  ��� �������  >" << endl << endl;
			AllObject();
			break;
		}
		case 4:
		{
			cout << endl << "<  �������������� �����  >" << endl << endl;
			EditPipe();
			break;
		}
		case 5:
		{
			cout << endl << "<  �������������� �������  >" << endl << endl;
			EditStation();
			break;
		}
		case 6:
		{
			cout << endl << "<  ��������  >" << endl << endl;
			SaveToFile();
			cout << "������ ������� ��������� � ����.";
			break;
		}
		case 7:
		{
			cout << endl << "<  ��������  >" << endl << endl;
			LoadToFile();
			cout << "������ ������� ��������� �� �����.";
			break;
		}
		case 8:
		{
			cout << endl << "<  ����� �����  >" << endl << endl;
			SearchPipes(pipes);
			break;
		}
		case 9:
		{
			cout << endl << "<  ����� �������  >" << endl << endl;
			SearchStations(stations);
			break;
		}
		case 10:
			cout << endl << "<  �������  >" << endl << endl;
			DeleteObject();
			break;
		default:
			cout << "������! ������� �����" << endl;
			break;
		}
	}

	return 0;
}