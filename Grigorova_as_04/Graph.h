#pragma once
#include <unordered_map>
#include "Pipe.h"
#include "Station.h"

class wokrWithGraph
{
public:
	unordered_map <int, Pipe> pipes;
	unordered_map <int, Station> stations;
	
	void EditPipes(vector <Pipe*>& edit_pipes);
	void SearchPipes(unordered_map <int, Pipe>& pipes);
	void EditStations(vector <Station*>& edit_stations);
	void SearchStations(unordered_map <int, Station>& stations);
	void DeleteObject();
	void SaveToFile();
	void LoadToFile();
};

