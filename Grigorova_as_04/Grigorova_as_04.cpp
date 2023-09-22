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
		cout << "����� �����:  " << new_pipe.len << endl;
		cout << "������� �����:  " << new_pipe.diam << endl;
		(new_pipe.inrepair) ? cout << "����� � �������." << endl << endl : cout << "����� ��������." << endl;
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
	int choice = 0;
	if (edit_pipe.len == 0)
		cout << "��� �����." << endl;
	else
	{
		if (edit_pipe.inrepair)
		{
			cout << "����� � �������. �������� ������?" << endl;
			cout << "1. ��" << endl << "2. ���" << endl << "��� �����: ";
			InputInt(choice);
			switch (choice)
			{
			case 1:
				edit_pipe.inrepair = false;
				cout << "������ ����� ��������." << endl;
				break;
			case 2:
				return;
				break;
			default:
				cout << "������! ������� ���������� ������:  ";
				break;
			}
		}
		else
		{
			cout << "����� ��������. �������� ������?" << endl;
			cout << "1. ��" << endl << "2. ���" << endl << "��� �����: ";
			InputInt(choice);
			switch (choice)
			{
			case 1:
				edit_pipe.inrepair = true;
				cout << "������ ����� � �������." << endl;
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

void Save(const pipe& new_pipe, const station& new_station)
{
	string path = "";
	ofstream fout;

	cout << "������� �������� �����:  ";
	cin >> path;

	fout.open(path + ".txt", ofstream::app);

	if (!fout.is_open())
		cout << "������ �������� �����!" << endl;
	else
	{
		
		if (new_pipe.len == 0)
			fout << "��� �����." << '\n';
		else
		{
			fout << "������������ �������:  " << new_pipe.km_mark << '\n';
			fout << "����� �����:  " << new_pipe.len << '\n';
			fout << "������ �����:  " << new_pipe.diam << '\n';
			fout << "��������� �����:  " << new_pipe.inrepair << '\n';
		}
		fout << "\n";
		if (new_station.workshop == 0)
			fout << "��� �������." << "\n";
		else
		{
			fout << "�������� �������:  " << new_station.title << "\n";
			fout << "���-�� �����:  " << new_station.workshop << "\n";
			fout << "���-�� ���������� �����:  " << new_station.active_workshop << "\n";
			fout << "�������������:  " << new_station.efficiency << "\n";
		}
	}

	fout.close();
}

void Download()
{
	string path = "";
	ifstream fin;

	cout << "������� �������� �����:  ";
	cin >> path;

	fin.open(path + ".txt");

	if (!fin.is_open())
	{
		cout << "������ �������� �����!!" << endl;
	}
	else
	{
		string str;
		while (!fin.eof())
		{
			str = "";
			getline(fin, str);
			cout << str << endl;
		}
	}

	fin.close();

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
			Save(pipe, station);
			break;
		}
		case 7:
		{
			cout << endl << "<  ��������  >" << endl << endl;
			Download();
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