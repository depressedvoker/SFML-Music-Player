#pragma execution_character_set("utf-8")
#pragma once
#include <iostream>
#include <string>
#include<fstream>
#include<Windows.h>
#include"Interface.h"
using namespace std;

class StackNode {
public:
	StackNode* next;
	string stackedSongs;
	StackNode(string stackedSongs, StackNode* next);
};

class Stack {
private:
	StackNode* top;
	Interface& ii;
	StackNode* LatestNode;
public:
	Stack(Interface& interfaceobj);
	void push(string data);
	void displayLikedSongs();
	bool empty();
	pair<string, int> getstackedsong(int index);
	void Loadsongs();
};
