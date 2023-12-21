#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Pipe
{
public:
	static int max_id_p;
	string km_mark = "";
	bool inrepair = true;
	double len = 0;
	int diam = 0;
	int ID = 0;
	int CSid1 = 0;
	int CSid2 = 0;

	int GetId();
	int GetDia();

	bool GetStatus();
	int GetLen();
	void OutputPipeStatus();
	string GetName() const;
	bool ConnectionNotBusy() const;
	void Connect(const int& id1, const int& id2);
	void DeleteConnection();

	friend istream& operator >> (istream& in, Pipe& pipe);
	friend ostream& operator << (ostream& out, const Pipe& pipe);
	friend void EditPipe(Pipe& edit_pipe);
	friend ofstream& operator << (ofstream& fout, const Pipe& pipe);
	friend ifstream& operator >> (ifstream& fin, Pipe& pipe);
};