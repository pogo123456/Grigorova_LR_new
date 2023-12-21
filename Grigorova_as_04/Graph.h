#pragma once
#include <unordered_map>
#include "Pipe.h"
#include "Station.h"


class wokrWithGraph
{
public:
	void EditPipes(vector <Pipe*>& edit_pipes);
	void SearchPipes(unordered_map <int, Pipe>& pipes);
	void EditStations(vector <Station*>& edit_stations);
	void SearchStations(unordered_map <int, Station>& stations);
	bool HasConnection(const unordered_map<int, Pipe>& Pipes, const int& CSid1, const int& CSid2);
	void ConnectInGraph(unordered_map<int, Pipe>& Pipes, unordered_map<int, Station>& Stations);
	vector<int> topologSort(unordered_map<int, Pipe>& Pipes, unordered_map<int, Station>& Stations);
	float Dijkstra(vector<vector<int>>& a, int index_1, int index_2);
	/*void shortestPath();*/
};

