#pragma once
#include <string>
#include <iostream>
//#include <unordered_map>
//#include <unordered_set>
#include <fstream>

using namespace std;

class Pipe
{
public:
		static int max_id;
		string km_mark = "";
		bool inrepair = true;
		Pipe()
		{
			ID = max_id++;
		}
		string OutputStatus();
		friend istream& operator >> (istream& in, Pipe& pipe);
		friend ostream& operator << (ostream& out, Pipe& pipe);
		void EditPipe();
		void Savepipe(ofstream& file);
		void DownloadPipe(ifstream& file);
		int GetId() 
		{ 
			return ID; 
		}
private:
		double len = 0;
		int diam = 0;
		int ID = 0;
};