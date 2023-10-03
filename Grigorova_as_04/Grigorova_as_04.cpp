#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

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
	string efficiency = "A";
};

void InputInt(int& var)
{
	cin >> var;
	while (cin.fail() || cin.peek() != '\n' || var <= 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "����������� ��������� ������! ���������� �����:  ";
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
		cout << "����������� ��������� ������! ���������� �����:  ";
		cin >> var;
	}
}

void InputBool(bool& var)
{
	cin >> var;
	while (cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "����������� ��������� ������! ���������� �����:  ";
		cin >> var;
	}
}

pipe AddPipe()
{
	pipe new_pipe;
	cout << "������� ������������ �������:  ";
	cin.ignore();
	getline(cin, new_pipe.km_mark);
	cout << "������� ����� ����� (��):  ";
	InputDouble(new_pipe.len);
	cout << "������� ������� ����� (��):  ";
	InputInt(new_pipe.diam);
	cout << "��������� ����� (1 - � �������; 0 - ��������):  ";
	InputBool(new_pipe.inrepair);

	return new_pipe;
}

station AddStation()
{
	station new_station;
	cout << "������� �������� �������:  ";
	cin.ignore();
	getline(cin, new_station.title);
	cout << "������� ���-�� �����:  ";
	InputInt(new_station.workshop);
	cout << "������� ���-�� ���������� �����:  ";
	InputInt(new_station.active_workshop);
	while (new_station.workshop < new_station.active_workshop)
	{
		cout << "������! ��������� ���-�� ���������� �����!" << endl << "������� ���������� ������:  ";
		InputInt(new_station.active_workshop);
	}
	cout << "������� ������������� ������� �� A �� G:  ";
	cin >> new_station.efficiency;
	while (!(new_station.efficiency >= "A" && new_station.efficiency <= "G" && new_station.efficiency.length() == 1))
	{
		cout << "������! ������� ���������� ������:  ";
		cin >> new_station.efficiency;
	}

	return new_station;
}

void ShowPipe(const pipe& new_pipe)
{
	if (new_pipe.len == 0)
		cout << "��� �����." << endl;
	else
	{
		cout << "������������ �������:  " << new_pipe.km_mark << endl;
		cout << "����� �����:  " << new_pipe.len << "��" << endl;
		cout << "������� �����:  " << new_pipe.diam << "��" << endl;
		(new_pipe.inrepair) ? cout << "����� � �������." << endl : cout << "����� ��������." << endl;
	}
}

void ShowStation(const station& new_station)
{
	if (new_station.workshop == 0)
		cout << "��� �������." << endl;
	else
	{
		cout << "�������� �������:  " << new_station.title << endl;
		cout << "���-�� �����:  " << new_station.workshop << endl;
		cout << "���-�� ���������� �����:  " << new_station.active_workshop << endl;
		cout << "�������������:  " << new_station.efficiency << endl;
	}
}

void EditPipe(pipe& edit_pipe)
{
	if (edit_pipe.len == 0)
		cout << "��� �����." << endl;
	else
	{
		edit_pipe.inrepair = !edit_pipe.inrepair;
		cout << "������ ����� �������." << endl;
	}
}

void EditStation(station& edit_station)
{
	int choice = 0;
	if (edit_station.workshop == 0)
		cout << "��� �������." << endl;
	else
	{
		cout << "������ �������� ���-�� ���������� �����?" << endl;
		cout << "1. ��" << endl << "2. ���" << endl << "��� �����: ";
		InputInt(choice);
		switch (choice)
		{
		case 1:
			cout << "������� ����� ���-�� ���������� �����:  ";
			InputInt(edit_station.active_workshop);
			while (edit_station.active_workshop > edit_station.workshop)
			{
				cout << "������! ��������� ���-�� ���������� �����!" << endl << "���-�� ���� �����:  " << edit_station.workshop << endl;
				cout << "������� ���������� ������:  ";
				InputInt(edit_station.active_workshop);
			}
			break;
		case 2:
			return;
			break;
		default:
			cout << "������! ������� ���������� ������:  ";
			break;
		}
	}
}

void SavePipe(pipe& new_pipe, ofstream& fout)
{
	fout << new_pipe.km_mark << endl
		<< new_pipe.len << endl
		<< new_pipe.diam << endl
		<< new_pipe.inrepair << endl;
	cout << "������ ����� ��������� � ����." << endl;
	fout.close();
}

void SaveStation(station& new_station, ofstream& fout)
{
	fout << new_station.title << endl
		<< new_station.workshop << endl
		<< new_station.active_workshop << endl
		<< new_station.efficiency << endl;
	cout << "������ ������� ��������� � ����." << endl;
	fout.close();
}

void DownloadPipe(pipe& pipe, ifstream& fin)
{
	fin.ignore();
	getline(fin, pipe.km_mark);
	fin >> pipe.len;
	fin >> pipe.diam;
	fin >> pipe.inrepair;
	cout << "������ ����� ��������� �� �����." << endl;
}

void DownloadStation(station& station, ifstream& fin)
{
	fin.ignore();
	getline(fin, station.title);
	fin >> station.workshop;
	fin >> station.active_workshop;
	fin >> station.efficiency;
	cout << "������ ������� ��������� �� �����." << endl;
}

int main()
{
	pipe pipe;
	station station;

	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	while (true)
	{
		cout  << endl << "------------------------------------" << endl;
		cout << "����" << endl;
		cout << "1. �������� �����" << endl;
		cout << "2. �������� �������" << endl;
		cout << "3. ������� ��� �������" << endl;
		cout << "4. ������������� �����" << endl;
		cout << "5. ������������� �������" << endl;
		cout << "6. ���������" << endl;
		cout << "7. ���������" << endl;
		cout << "8. �����" << endl;
		cout << "------------------------------------" << endl << endl;

		cout << "��� �����: ";
		int choice;
		InputInt(choice);

		switch (choice)
		{
		case 1:
		{
			cout << endl << "<  ���������� �����  >" << endl << endl;
			pipe = AddPipe();
			break;
		}
		case 2:
		{
			cout << endl << "<  ���������� �������  >" << endl << endl;
			station = AddStation();
			break;
		}
		case 3:
		{
			cout << endl <<  "<  ��� �������  >" << endl << endl;
			ShowPipe(pipe);
			ShowStation(station);
			break;
		}
		case 4:
		{
			cout << endl << "<  �������������� �����  >" << endl << endl;
			EditPipe(pipe);
			break;
		}
		case 5:
		{
			cout << endl << "<  �������������� �������  >" << endl << endl;
			EditStation(station);
			break;
		}
		case 6:
		{
			cout << endl << "<  ��������  >" << endl << endl;
			ofstream fout;
			string fname;
			cout << "������� ��� �����:  ";
			cin.ignore();
			getline(cin, fname);
			fout.open(fname);

			if (!fout.is_open())
				cout << "������ �������� �����!" << endl;
			else
			{
				if (pipe.len == 0)
					fout << 0 << endl;
				else
				{
					fout << 1 << endl;
					SavePipe(pipe, fout);
				}
				if (station.workshop == 0)
					fout << 0 << endl;
				else
				{
					fout << 1 << endl;
					SaveStation(station, fout);
				}
				
				fout.close();
			}
			break;
		}
		case 7:
		{
			cout << endl << "<  ��������  >" << endl << endl;
			ifstream fin;
			string fname;
			cout << "������� ��� �����:  ";
			cin.ignore();
			getline(cin, fname);
			fin.open(fname);
			int number;

			if (!fin.is_open())
				cout << "������ �������� �����!" << endl;
				
			else
			{
				fin >> number;
				if (number == 1)
					DownloadPipe(pipe, fin);
				else
					cout << "��� �����." << endl;
				fin >> number;
				if (number == 1)
					DownloadStation(station, fin);
				else
					cout << "��� �������." << endl;
				fin.close();
			}
			break;
		}
		case 8:
			cout << endl << "<  �����  >" << endl << endl;
			return 0;
			break;
		default:
			cout << "������! ������� �����" << endl;
			break;
		}
	}

	return 0;
}