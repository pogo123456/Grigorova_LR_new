#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Pipe.h"
#include "Station.h"
#include "Header.h"
#include "logger.h"
#include "Graph.h"

using namespace std;

unordered_map <int, Pipe> pipes;
unordered_map <int, Station> stations;

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
			graph.SaveToFile();
			logger.log("���������� � ���� (�����)");
			cout << "������ ������� ��������� � ����.";
			break;
		}
		case 7:
		{
			cout << endl << "<  ��������  >" << endl << endl;
			logger.log("�������� �� ����� (������)");
			graph.LoadToFile();
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
			cout << endl << "<  �������  >" << endl << endl;
			logger.log("������� (������)");
			graph.DeleteObject();
			logger.log("������� (�����)");
			break;
		default:
			cout << "������! ������� �����" << endl;
			break;
		}
	}

	return 0;
}