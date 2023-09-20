#include <iostream>
#include <string>
#include <fstream>

//using namespace std;
using namespace std;

struct pipe
{
	string km_mark = "";
	double len = 0;
	double diam = 0;
	bool inrepair = true;
}; 

struct station
{
	string title = "";
	int workshop = 0;
	int active_workshop = 0;
	double efficiency = 'A';
};

void CheckInput(int& var)
{
	cin >> var;
	while (cin.fail() || var <= 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Try again";
		cin >> var;
	}
}

void CheckInput(double& var)
{
	cin >> var;
	while (cin.fail() || var <= 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Try again";
		cin >> var;
	}
}

void CheckInput(bool& var)
{
	int input;
	cin >> input;
	while (cin.fail() || !(input == 0 || input == 1))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Try again";
		cin >> input;
	}
	var = input == 1;
}

pipe AddPipe()
{
	pipe new_pipe;
	cout << "Please, enter kilometer mark: " << endl;
	cin.ignore();
	getline(cin, new_pipe.km_mark);
	cout << "Please, enter pipe length(km): " << endl;
	CheckInput(new_pipe.len);
	cout << "Please, enter pipe diameter(mm): " << endl;
	CheckInput(new_pipe.diam);
	cout << "Please, enter pipe inrepair? (1-yes, 0-no): " << endl;
	CheckInput(new_pipe.inrepair);

	return new_pipe;
}

station AddStation()
{
	station new_station;
	cout << "Please, enter station name: " << endl;
	cin.ignore();
	getline(cin, new_station.title);
	cout << "Please, enter number of workshops: " << endl;
	CheckInput(new_station.workshop);
	cout << "Please, enter number of active workshops: " << endl;
	CheckInput(new_station.active_workshop);
	while (new_station.workshop < new_station.active_workshop)
	{
		cout << "Error! Quantity exceeded" << endl << "Enter correct data: " << endl;
		cin >> new_station.active_workshop;
	}
	cout << "Please, enter efficiency from A to G: " << endl;
	cin >> new_station.efficiency;
	while (!(new_station.efficiency >= 'A' && new_station.efficiency <= 'G'))
	{
		cout << "Error! Enter correct data: " << endl;
		cin >> new_station.efficiency;
	}

	return new_station;
}

void ShowPipe(const pipe& new_pipe)
{
	if (new_pipe.len == 0)
		cout << "No pipe." << endl;
	else
	{
		cout << "Pipe length: " << new_pipe.len << endl;
		cout << "Pipe diameter: " << new_pipe.diam << endl;
		cout << "Kilometer mark: " << new_pipe.km_mark << endl;
		if (new_pipe.inrepair)
			cout << "Pipe under repair." << endl;
		else
			cout << "The pipe is working." << endl;
	}
}

void ShowStation(const station& new_station)
{
	if (new_station.workshop == 0)
		cout << "No station." << endl;
	else
	{
		cout << "Station name: " << new_station.title << endl;
		cout << "Number of workshops: " << new_station.workshop << endl;
		cout << "Number of active workshops: " << new_station.active_workshop << endl;
		cout << "Effectiveness: " << new_station.efficiency << endl;
	}
}

void EditPipe(pipe& edit_pipe)
{
	int choice = 0;
	if (edit_pipe.len == 0)
		cout << "" << endl;
	else
	{
		if (edit_pipe.inrepair == true)
		{
			cout << "Pipe under repair. Want to fix it?" << endl;
			cout << "1. Yes" << endl << "2. No" << endl << "Your choice: ";
			cin >> choice;
			switch (choice)
			{
			case 1:
				edit_pipe.inrepair = false;
				cout << "Now the pipe is working." << endl;
				break;
			case 2:
				return;
				break;
			default:
				cout << "Error! Enter correct data: " << endl;
				break;
			}
		}
		else
		{
			cout << "The pipe is working. Want to fix it?" << endl;
			cout << "1. Yes" << endl << "2. No" << endl << "Your choice: ";
			cin >> choice;
			switch (choice)
			{
			case 1:
				edit_pipe.inrepair = true;
				cout << "Now pipe under repair." << endl;
				break;
			case 2:
				return;
				break;
			default:
				cout << "Error! Enter correct data: " << endl;
				break;
			}
		}
	}
}

void EditStation(station& edit_station)
{
	int choice = 0;
	if (edit_station.workshop == 0)
		cout << "No station." << endl;
	else
	{
		cout << "Want to fix number?" << endl;
		cout << "1. Yes" << endl << "2. No" << endl << "Your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Please, enter number of active workshops: ";
			cin >> edit_station.active_workshop;
			while (edit_station.active_workshop > edit_station.workshop)
			{
				cout << "Erorr! Quantity exceeded." << endl << "Number of workshops: " << edit_station.workshop << endl;
				cout << "Enter correct data: ";
				cin >> edit_station.active_workshop;
			}
			break;
		case 2:
			return;
			break;
		default:
			cout << "Error!Enter correct data: " << endl;
			break;
		}
	}
}

//void Save()
//{
//	ofstream out;
//	out.open("datas.txt"); 
//	if (out.is_open())
//	{
//		for (const pipe& pipe)
//		{
//			out << "Kilometer mark : " << pipe.km_mark << endl 
//				<< "Pipe length: " << pipe.len << endl 
//				<< "Pipe diameter: " << pipe.diam << endl 
//				<< "Pipe status: " << pipe.inrepair << endl;
//		}
//
//		for (const station& station)
//		{
//			out << "Station name: " << station.title << endl 
//				<< "Number of workshops: " << station.workshop << endl 
//				<< "Number of active workshops: " << station.active_workshop << endl 
//				<< "Effectiveness: " << station.efficiency << endl;
//		}
//	}
//	out.close();
//	cout << "File has been written" << endl;
//}
//
//void Download()
//{
//	string line;
//
//	ifstream in("datas.txt");
//	if (in.is_open())
//	{
//		while (getline(in, line))
//		{
//			cout << line << endl;
//		}
//	}
//	in.close();
//	cout << "File has been extracted" << endl;
//}

int main()
{
	pipe pipe;
	station station;

	while (true)
	{
		cout << "Menu: " << endl;
		cout << "1. Add pipe" << endl;
		cout << "2. Add station" << endl;
		cout << "3. All object" << endl;
		cout << "4. Edit pipe" << endl;
		cout << "5. Edit station" << endl;
		cout << "6. Save" << endl;
		cout << "7. Download" << endl;
		cout << "0. Exit" << endl;

		int choice;
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			cout << "Add pipe" << endl;
			pipe = AddPipe();
			cin >> choice;
		}
		case 2:
		{
			cout << "Add station" << endl;
			station = AddStation();
			cin >> choice;
		}
		case 3:
		{
			cout << "All object" << endl;
			ShowPipe(pipe);
			ShowStation(station);
			cin >> choice;
		}
		case 4:
		{
			cout << "Edit pipe" << endl;
			EditPipe(pipe);
			cin >> choice;
		}
		case 5:
		{
			cout << "Edit station" << endl;
			EditStation(station);
			cin >> choice;
		}
		case 6:
		{
			cout << "Save";
			cin >> choice;
		}
		case 7:
		{
			cout << "Download";
			cin >> choice;
		}
		case 0:
			return 0;
			break;
		default:
			cout << "Error!!! Try again." << endl;
			cin >> choice;
		}
	}

	return 0;
}