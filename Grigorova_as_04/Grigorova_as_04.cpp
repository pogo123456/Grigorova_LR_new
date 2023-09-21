#include <iostream>
#include <string>
#include <fstream>

//using namespace std;
using namespace std;

struct pipe
{
	string km_mark = "";
	double len = 0;
	int diam = 0;
	bool inrepair = true;
}; 

struct station
{
	string title = "";
	int workshop = 0;
	int active_workshop = 0;
	char efficiency = 'A';
};

void InputInt(int& var)
{
	cin >> var;
	while (cin.fail() || cin.peek() != '\n' || var <= 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Try again: ";
		cin >> var;
	}
}

void InputDouble(double& var)
{
	cin >> var;
	while (cin.fail() || cin.peek() != '\n' || var <= 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Try again: ";
		cin >> var;
	}
}

void InputBool(bool& var)
{
	cin >> var;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Try again: ";
		cin >> var;
	}
}

pipe AddPipe()
{
	pipe new_pipe;
	cout << "Please, enter kilometer mark:  ";
	cin.ignore();
	getline(cin, new_pipe.km_mark);
	cout << "Please, enter pipe length(km):  ";
	InputDouble(new_pipe.len);
	cout << "Please, enter pipe diameter(mm):  ";
	InputInt(new_pipe.diam);
	cout << "Please, enter pipe inrepair? (1-yes, 0-no):  ";
	InputBool(new_pipe.inrepair);

	return new_pipe;
}

station AddStation()
{
	station new_station;
	cout << "Please, enter station name:  ";
	cin.ignore();
	getline(cin, new_station.title);
	cout << "Please, enter number of workshops:  ";
	InputInt(new_station.workshop);
	cout << "Please, enter number of active workshops:  ";
	InputInt(new_station.active_workshop);
	while (new_station.workshop < new_station.active_workshop)
	{
		cout << "Error! Quantity exceeded" << endl << "Enter correct data: " << endl;
		InputInt(new_station.active_workshop);
	}
	cout << "Please, enter efficiency from A to G:  ";
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
		if (new_pipe.inrepair)//?????????
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
		cout << "No pipe" << endl;
	else
	{
		if (edit_pipe.inrepair)
		{
			cout << "Pipe under repair. Want to fix it?" << endl;
			cout << "1. Yes" << endl << "2. No" << endl << "Your choice: ";
			InputInt(choice);
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
			InputInt(choice);
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
		InputInt(choice);
		switch (choice)
		{
		case 1:
			cout << "Please, enter number of active workshops: ";
			InputInt(edit_station.active_workshop);
			while (edit_station.active_workshop > edit_station.workshop)
			{
				cout << "Erorr! Quantity exceeded." << endl << "Number of workshops: " << edit_station.workshop << endl;
				cout << "Enter correct data: ";
				InputInt(edit_station.active_workshop);
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
		cout << endl << "Menu: " << endl;
		cout << "1. Add pipe" << endl;
		cout << "2. Add station" << endl;
		cout << "3. All object" << endl;
		cout << "4. Edit pipe" << endl;
		cout << "5. Edit station" << endl;
		cout << "6. Save" << endl;
		cout << "7. Download" << endl;
		cout << "0. Exit" << endl << endl;

		cout << "Your choice: ";
		int choice = 0;
		InputInt(choice);

		switch (choice)
		{
		case 1:
		{
			cout << "Add pipe" << endl;
			pipe = AddPipe();
			break;
		}
		case 2:
		{
			cout << "Add station" << endl;
			station = AddStation();
			break;
		}
		case 3:
		{
			cout << "All object" << endl;
			ShowPipe(pipe);
			ShowStation(station);
			break;
		}
		case 4:
		{
			cout << "Edit pipe" << endl;
			EditPipe(pipe);
			break;
		}
		case 5:
		{
			cout << "Edit station" << endl;
			EditStation(station);
			break;
		}
		case 6:
		{
			cout << "Save";
			break;
		}
		case 7:
		{
			cout << "Download";
			break;
		}
		case 0:
			return 0;
			break;
		default:
			cout << "Error!!! Try again." << endl;
			break;
		}
	}

	return 0;
}