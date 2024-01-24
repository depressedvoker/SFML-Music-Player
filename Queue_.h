#pragma execution_character_set("utf-8")
#pragma once
#include <iostream>
#include"Interface.h"
using namespace std;
class node
{
public:
	string data;
	node* next;
	node(string data);
};
class Queue_
{
private:
	node* front;
	node* rear;
	Interface& ii;
public:
	Queue_(Interface& temp);
	void enqueue(string data);
	bool empty();
	void displayPlaylist();
	pair<string, int> getQueuedSong(int index);
	void LoadSongs();
};
