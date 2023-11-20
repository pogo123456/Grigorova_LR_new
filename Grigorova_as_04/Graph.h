#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Pipe.h"
#include "Station.h"

using namespace std;


class wokrWithGraph
{
public:
	struct Graph
	{

	};
	unordered_map <int, Pipe> pipes;
	unordered_map <int, Station> stations;
	friend istream& operator>> (istream& in, wokrWithGraph& s);
	friend ostream& operator<<(ostream& out, unordered_set<int> s);
	friend ofstream& operator << (ofstream& fout, const Station& station);
	friend ifstream& operator >> (ifstream& fin, Station& Station);
	friend ofstream& operator << (ofstream& fout, const Pipe& pipe);
	friend ifstream& operator >> (ifstream& fin, Pipe& pipe);
	unordered_map <int, Graph> graphs;
};

