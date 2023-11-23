#pragma once
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

class Logger 
{
    ofstream logFile;
    int logNumber = 0;
public:
    Logger() 
    {
        logFile.open("logger.txt");
    }

    ~Logger() 
    {
        if (!logFile.is_open())
            cout << "Ошибка открытия файла \"logger.txt\"" << endl;
        else
            logFile.close();
    }

    template <typename T>
    void log(const T& message) 
    {
        if (!logFile.is_open())
            cout << "Ошибка открытия файла \"logger.txt\"" << endl;
        else
        {
            /*auto now = std::chrono::system_clock::now();
            std::time_t end_time = std::chrono::system_clock::to_time_t(now);*/
            logFile << " [" << logNumber << "] " << message << endl;
            logNumber++;
        }
    }
};
