#include "Graph.h"
#include "Pipe.h"
#include "Station.h"
#include "Header.h"
#include "Header.h"
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

const int INF = 999999999;

void wokrWithGraph::EditPipes(vector<Pipe*>& edit_pipes)
{
	cout << endl << "Хотите изменить статус трубы?" << endl;
	cout << "1. Да" << endl << "2. Нет" << endl << "Ваш выбор:  ";
	int choice = 0;
	GetCorrectNumber(choice);
	switch (choice)
	{
	case 1:
		bool inrepaire;
		cout << "Новый статус (1 - В ремонте, 0 - Работает):  ";
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
		cout << "Ошибка! Введите корректные данные:  " << endl;
		break;
	}
}

void wokrWithGraph::SearchPipes(unordered_map<int, Pipe>& pipes)
{
	while (true)
	{
		int choice = 0;
		cout << "По какому критерию найти трубу?" << endl;
		cout << "1. Киллометровая отметка" << endl << "2. Статус трубы" << endl << "3. Назад" << endl << "Ваш выбор:  ";
		GetCorrectNumber(choice);
		switch (choice)
		{
		case 1:
		{
			string name;
			cout << endl << "Киллометрая отметка: ";
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
				cout << "Трубы с таким именем нет." << endl;
			else
				EditPipes(p);
		}
		break;
		case 2:
		{
			bool inrepair;
			cout << "Cтатус трубы: в ремонте? (1 - Да, 0 - Нет): ";
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
				cout << "Трубы с таким статусом нет." << endl;
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
			cout << "Ошибка! Введите корректные данные";
			break;
		}
	}
}

void wokrWithGraph::EditStations(vector<Station*>& edit_stations)
{
	cout << endl << "Хотите изменить кол-во работающих цехов?" << endl;
	cout << "1. Да" << endl << "2. Нет" << endl << "Ваш выбор: ";
	int choice = 0;
	GetCorrectNumber(choice);
	switch (choice)
	{
	case 1:
		cout << "Введите новый процент активных цехов (0-100): ";
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
		cout << "Ошибка! Введите корректные данные:  " << endl;
		break;
	}
}

void wokrWithGraph::SearchStations(unordered_map <int, Station>& stations)
{
	while (true)
	{
		int choice = 0;
		cout << "По какому критерию найти станцию?" << endl;
		cout << "1. Название" << endl << "2. Процент активных цехов" << endl << "3. Назад" << endl << "Ваш выбор:  ";
		GetCorrectNumber(choice);
		switch (choice)
		{
		case 1:
		{
			string name;
			cout << "Название: ";
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
				cout << "Станции с таким названием нет." << endl;
			else
				EditStations(cs);
		}
		break;
		case 2:
		{
			int percent = 0;
			cout << "Введите процент активных цехов (0-100 с погрешностью в 5%): ";
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
				cout << "Станции с таким процентом нет." << endl;
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
			cout << "Ошибка! Введите корректные данные";
			break;
		}
	}
}

bool wokrWithGraph::HasConnection(const unordered_map<int, Pipe>& Pipes, const int& CSid1, const int& CSid2)
{
	bool hasPipe = false;
	for (auto& elem : Pipes)
	{
		if ((elem.second.CSid1 == CSid1 && elem.second.CSid2 == CSid2)
			|| (elem.second.CSid1 == CSid2 && elem.second.CSid2 == CSid1))
		{
			hasPipe = true;
		}
	}
	return hasPipe;
}

void wokrWithGraph::ConnectInGraph(unordered_map<int, Pipe>& Pipes, unordered_map<int, Station>& Stations)
{
	int pipeDiameter = 0;
	cout << "Ведите диаметр трубы: ";
	pipeDiameter = GetCorrectDiam(500, 1400);
	int idConnectedPipe = 0;

	for (auto& elem : Pipes)
	{
		if (elem.second.GetDia() == pipeDiameter && elem.second.ConnectionNotBusy())
		{
			idConnectedPipe = elem.first;
			break;
		}
	}

	Pipe* connectedPipe{};
	if (idConnectedPipe == 0)
	{
		bool flag = true;
		while (flag)
		{
			cout << "Нет трубы с таким диаметром!" << endl;
			cout << "Хотите добавить трубу?" << endl
				<< "1. Да" << endl
				<< "2. Нет" << endl
				<< "Ваш выбор:  ";
			int choice = 0;
			GetCorrectNumber(choice);
			switch (choice)
			{
			case 1:
			{
				Pipe pipe0;
				cin >> pipe0;
				connectedPipe = &pipe0;
				Pipes.insert(make_pair(connectedPipe->GetId(), *connectedPipe));
				flag = false;
			}
			break;
			case 2:
				return;
			default:
				cout << "Ошибка! Введите снова" << endl;
				break;
			}
		}
	}
	else
	{
		connectedPipe = &Pipes[idConnectedPipe];
	}

	if (idConnectedPipe != 0)
	{
		cout << "Введите ID первой станции: ";
		int CSid1;
		GetCorrectNumber(CSid1);
		while (Stations.find(CSid1) == Stations.end())
		{
			cout << "Станция с таким ID занята! Попробуйте снова:" << endl;
			GetCorrectNumber(CSid1);
		}

		cout << "Введите ID второй станции: ";
		int CSid2;
		GetCorrectNumber(CSid2);
		while (Stations.find(CSid2) == Stations.end() || CSid2 == CSid1 || HasConnection(Pipes, CSid1, CSid2))
		{
			cout << "Станция с таким ID занята! Попробуйте снова:" << endl;
			GetCorrectNumber(CSid1);
		}
		connectedPipe->Connect(CSid1, CSid2);
	}
}

vector<int> wokrWithGraph::topologSort(unordered_map<int, Pipe>& Pipes, unordered_map<int, Station>& Stations)
{
	vector<int> result;
	unordered_map<int, int> enterEdges;

	for (auto& elem : Pipes)
	{
		enterEdges[elem.second.CSid2]++;
	}

	queue<int> que;
	for (auto& elem : Stations)
	{
		if (enterEdges.find(elem.first) == enterEdges.end())
		{
			que.push(elem.first);
		}
	}

	while (!que.empty())
	{
		int curStation = que.front();
		que.pop();
		result.push_back(curStation);

		for (auto& elem : Pipes)
		{
			if (elem.second.CSid1 == curStation)
			{
				enterEdges[elem.second.CSid2]--;
				if (enterEdges[elem.second.CSid2] == 0)
				{
					que.push(elem.second.CSid2);
				}
			}
		}
	}
	return result;
}

//float wokrWithGraph::Dijkstra(vector<vector<int>>& a, int index_1, int index_2)
//{
//	int size = a.size();
//
//	vector<vector<int>> d(size, vector<int>(size));
//	vector<vector<int>> v(size, vector<int>(size));
//
//	for (int i = 0; i < size; i++)
//		for (int j = 0; j < size; j++)
//		{
//			d[i][j] = INF;
//			v[i][j] = 0;
//		}
//
//	int temp, minindex, min;
//
//
//	d[index_1][index_1] = 0;
//	for (int count = 0; count < size; count++)
//	{
//		min = INF;
//		for (int i = 0; i < size; i++)
//		{
//			if (v[index_1][i] == 0 && d[index_1][i] <= min)
//			{
//				min = d[index_1][i];
//				minindex = i;
//			}
//		}
//
//		v[index_1][minindex] = 1;
//
//		for (int i = 0; i < size; i++)
//		{
//			if (!v[index_1][i] && a[minindex][i] != INF && d[index_1][minindex] != INF && d[index_1][minindex] + a[minindex][i] < d[index_1][i])
//			{
//				d[index_1][i] = d[index_1][minindex] + a[minindex][i];
//			}
//		}
//	}
//
//	return d[index_1][index_2];
//}

//void wokrWithGraph::shortestPath()
//{
//	if (graph.size() != 0)
//	{
//		vector <int> index = filterCS();
//
//		for (int i = 0; i < index.size(); i++)
//		{
//			cout << "Station " << i + 1 << endl;
//			stations[index[i]].View(index[i]);
//		}
//
//		int index_1;
//		int index_2;
//
//		while (1)
//		{
//			cout << "Choose first CS";
//			index_1 = index[tryChoose(1, index.size()) - 1];
//			cout << "Choose last CS";
//			index_2 = index[tryChoose(1, index.size()) - 1];
//			if (index_1 == index_2)
//				cout << "Second CS must be different" << endl;
//			else
//				break;
//		}
//
//		vector <int> vert;
//		int n = 0; bool temp1 = false; bool temp2 = false; int ind_1 = -1; int ind_2 = -1;
//
//		for (auto it = connections.begin(); it != connections.end(); it++)
//		{
//			bool t1 = true;
//			bool t2 = true;
//			for (int i = 0; i < vert.size(); i++)
//			{
//				if (vert[i] == it->first.first)
//					t1 = false;
//				if (vert[i] == it->first.second)
//					t2 = false;
//			}
//
//			if (t1)
//			{
//				vert.push_back(it->first.first);
//
//				if (it->first.first == index_1)
//				{
//					temp1 = true;
//					ind_1 = vert.size() - 1;
//				}
//				else if (it->first.first == index_2)
//				{
//					temp2 = true;
//					ind_2 = vert.size() - 1;
//				}
//			}
//			if (t2)
//			{
//				vert.push_back(it->first.second);
//
//				if (it->first.second == index_1)
//				{
//					temp1 = true;
//					ind_1 = vert.size() - 1;
//				}
//				else if (it->first.second == index_2)
//				{
//					temp2 = true;
//					ind_2 = vert.size() - 1;
//				}
//			}
//
//			n += int(t1) + int(t2);
//		}
//
//		vector<vector<int>> matrix(n, vector<int>(n, INF));
//
//		for (int i = 0; i < n; i++)
//			for (int j = 0; j < n; j++)
//			{
//				matrix[i][j] = i == j ? 0 : connections.contains(make_pair(vert[i], vert[j])) ? pipes[connections[make_pair(vert[i], vert[j])]].getLength() : INF;
//			}
//
//		if (temp1 and temp2)
//		{
//			int path = Dijkstra(matrix, ind_1, ind_2);
//			if (path < INF)
//				cout << "Shortest path from CS with ID " << index_1 << " to CS with ID " << index_2 << " is " << path << endl << endl;
//			else
//				cout << "There is no way from CS with ID " << index_1 << " to CS with ID " << index_2 << endl << endl;
//		}
//		else
//			cout << "There is no way from CS with ID " << index_1 << " to CS with ID " << index_2 << endl << endl;
//
//	}
//	else
//	{
//		cout << "There is noi connections.\nWould you like to add some?\n\n";
//		cout << "1. Add connections\n2. Return to menu";
//		if (-tryChoose(1, 2) + 2)
//			addConnect();
//	}
//
//}

