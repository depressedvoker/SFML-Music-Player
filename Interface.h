#pragma execution_character_set("utf-8")
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <iomanip>
using namespace std;

class Interface {
private:
	string regname, regpass, veripass;
	int regchoice;

public:
	void registration();
	void registeracc(string name, string pass);
	int login(string name, string pass);
	string Getname();
};
