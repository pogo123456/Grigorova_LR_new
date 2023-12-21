#include <iostream>
#include <fstream>
#include <Windows.h>
#include <chrono>
#include <format>
#include "Pipe.h"
#include "Station.h"
#include "Header.h"
#include "logger.h"
#include "Graph.h"

using namespace std;
using namespace chrono;

unordered_map <int, Pipe> pipes = {};
unordered_map <int, Station> stations = {};

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

	Logger logger;
	logger.log("�����");

	wokrWithGraph graph;

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
		cout << " 11. ������� �������" << endl;
		cout << " 12. �������� ����������" << endl;
		cout << " 13. ������� ����������" << endl;
		cout << " 14. �������������� ���������� �����" << endl;
		cout << "------------------------------------" << endl << endl;
		cout << "��� �����: ";

		int choice = 0;
		GetCorrectNumber(choice);
		switch (choice)
		{
		case 0:
			cout << endl << "<  �����  >" << endl << endl;
			logger.log("�����");
			return 0;
			break;
		case 1:
		{
			cout << endl << "<  ���������� �����  >" << endl << endl;
			logger.log("���������� ����� (������)");
			AddPipe();
			logger.log("���������� ����� (�����)");
			break;
		}
		case 2:
		{
			cout << endl << "<  ���������� �������  >" << endl << endl;
			logger.log("���������� ������� (������)");
			AddStation();
			logger.log("���������� ������� (�����)");
			break;
		}
		case 3:
		{
			cout << endl <<  "<  ��� �������  >" << endl << endl;
			logger.log("�������� ��� ������� (������)");
			AllObject();
			logger.log("�������� ��� ������� (�����)");
			break;
		}
		case 4:
		{
			cout << endl << "<  �������������� �����  >" << endl << endl;
			logger.log("�������������� ����� (������)");
			EditPipe();
			logger.log("�������������� ����� (�����)");
			break;
		}
		case 5:
		{
			cout << endl << "<  �������������� �������  >" << endl << endl;
			logger.log("�������������� ������� (������)");
			EditStation();
			logger.log("�������������� ������� (�����)");
			break;
		}
		case 6:
		{
			cout << endl << "<  ��������  >" << endl << endl;
			logger.log("���������� � ���� (������)");
			SaveToFile();
			logger.log("���������� � ���� (�����)");
			cout << "������ ������� ��������� � ����.";
			break;
		}
		case 7:
		{
			cout << endl << "<  ��������  >" << endl << endl;
			logger.log("�������� �� ����� (������)");
			LoadToFile();
			logger.log("�������� �� ����� (�����)");
			cout << "������ ������� ��������� �� �����.";
			break;
		}
		case 8:
		{
			cout << endl << "<  ����� �����  >" << endl << endl;
			logger.log("����� ����� (������)");
			graph.SearchPipes(pipes);
			logger.log("����� ����� (�����)");
			break;
		}
		case 9:
		{
			cout << endl << "<  ����� �������  >" << endl << endl;
			logger.log("����� ������� (������)");
			graph.SearchStations(stations);
			logger.log("����� ������� (�����)");
			break;
		}
		case 10:
		{
			cout << endl << "<  �������  >" << endl << endl;
			logger.log("������� (������)");
			DeleteObject();
			logger.log("������� (�����)");
			break;
		}
		case 11:
		{
			cout << endl << "<  ������� �������  >" << endl << endl;
			logger.log("������� ������� (������)");
			graph.ConnectInGraph(pipes, stations);
			logger.log("������� ������� (�����)");
			break;
		}
		case 12:
		{
			cout << endl << "<  �������� ����������  >" << endl << endl;
			logger.log("�������� ���������� (������)");
			if (pipes.size() == 0)
				cout << "����� �� ������ � ����!" << endl;
			if (stations.size() == 0)
				cout << "������� �� ������ � ����!" << endl;
			int connectCount = 0;
			for (const auto& elem : pipes)
				if (!elem.second.ConnectionNotBusy())
				{
					cout << "������� 1 [" << elem.second.CSid1 << "] - ����� [" << elem.first << "] - ������� 2 [" << elem.second.CSid2 << "]" << endl;
					connectCount++;
				}
			cout << "����������: " << connectCount << endl;
			logger.log("�������� ���������� (�����)");
			break;
		}
		case 13:
		{
			cout << endl << "<  �������� ����������  >" << endl << endl;
			logger.log("�������� ���������� (������)");
			if (pipes.size() == 0)
				cout << "� ����� ���� ���!" << endl;
			else
			{
				cout << "������� ID �����, ������� ����� �������: ";
				int delPipe;
				GetCorrectNumber(delPipe);
				while (pipes.find(delPipe) == pipes.end())
				{
					cout << "\nPipe with this ID not exist! Please, try again: ";
					GetCorrectNumber(delPipe);
				}
				if (pipes[delPipe].ConnectionNotBusy())
				{
					cout << "����� �� ���������� � �����." << endl;
				}
				else
				{
					pipes[delPipe].DeleteConnection();
					cout << "���������� ������� �������." << endl;
				}
			}
			logger.log("�������� ���������� (�����)");
			break;
		}
		case 14:
		{
			cout << endl << "<  �������������� ���������� �����  >" << endl << endl;
			logger.log("���������� ����� (������)");
			vector <int> sortStations = graph.topologSort(pipes, stations);
			for (int id : sortStations)
			{
				cout << id << " ";
			}
			cout << endl;
			logger.log("���������� ����� (�����)");
			break;
		}
		default:
			cout << "������! ������� �����" << endl;
			break;
		}
	}

	return 0;
}