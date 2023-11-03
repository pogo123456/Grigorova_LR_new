#pragma once
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <fstream>

using namespace std;

class Pipe
{
	//они изначально являются приватными
	static int max_id_p;
	string km_mark = "";
	bool inrepair = true;
	double len = 0;
	int diam = 0;
	int ID = 0;
public:
	bool GetStatus();
	void OutputPipeStatus();
	friend istream& operator >> (istream& in, Pipe& pipe);
	friend ostream& operator << (ostream& out, Pipe& pipe);
	friend void EditPipe(Pipe& edit_pipe);
	friend void EditPipes(vector <Pipe*>& edit_pipes);
	int GetId();
	string GetName() const;
	friend ofstream& operator << (ofstream& fout, const Pipe& pipe);
	friend ifstream& operator >> (ifstream& fin, Pipe& pipe);
};