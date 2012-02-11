#pragma once



#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

#include <windows.h>


static string fichierLogs = "logs.txt";


class Debug {
	static Debug* _singleton;


	Debug();
	~Debug();

public:

	bool print(const string& message);


	static Debug* getInstance();
	static Debug* destruction();

};
