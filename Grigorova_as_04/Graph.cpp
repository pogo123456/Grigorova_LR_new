#include "Graph.h"
#include "Pipe.h"
#include "Station.h"
#include "Header.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int wokrWithGraph::Graph::max_idg = 0;

void wokrWithGraph::EditPipes(vector<Pipe*>& edit_pipes)
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

void wokrWithGraph::SearchPipes(unordered_map<int, Pipe>& pipes)
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

void wokrWithGraph::EditStations(vector<Station*>& edit_stations)
{
	cout << endl << "������ �������� ���-�� ���������� �����?" << endl;
	cout << "1. ��" << endl << "2. ���" << endl << "��� �����: ";
	int choice = 0;
	GetCorrectNumber(choice);
	switch (choice)
	{
	case 1:
		cout << "������� ����� ������� �������� ����� (0-100): ";
		float percent;
		GetCorrectNumber(percent);

		for (auto& cs : edit_stations)
		{
			cs->active_workshop = round(cs->workshop * percent / 100);
			cout << endl << "ID: " << cs->ID << " - ";
			cs->OutputWorkshopStatus();
		}
		break;
	case 2:
		return;
	default:
		cout << "������! ������� ���������� ������:  " << endl;
		break;
	}
}

void wokrWithGraph::SearchStations(unordered_map<int, Station>& stations)
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

void wokrWithGraph::DeleteObject()
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

void wokrWithGraph::SaveToFile()
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

void wokrWithGraph::LoadToFile()
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

