#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Station
{
public:
	static int max_id_s;
	string title = "";
	int workshop = 0;
	int active_workshop = 0;
	int ID = 0;
	string efficiency = "A";

	friend istream& operator >> (istream& in, Station& station);
	friend ostream& operator << (ostream& out, const Station& station);
	friend void EditStation(Station& edit_station);
	friend ofstream& operator << (ofstream& fout, const Station& station);
	friend ifstream& operator >> (ifstream& fin, Station& Station);
	
	void OutputWorkshopStatus() const;
	double GetPercentOfActiveWorkshops() const;
	int GetId();
	string GetName() const;
	int GetWorkshops() const;
	int GetActWorkshops() const;
};