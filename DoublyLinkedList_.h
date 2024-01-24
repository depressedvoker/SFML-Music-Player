#pragma execution_character_set("utf-8")
#pragma once
#include <iostream>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include <fstream>
using namespace std;
class doublyNode
{
public:
	string songName;
	doublyNode* next;
	doublyNode* prev;
	doublyNode(string songName);
};
class DoublyLinkedList
{
private:
	doublyNode* head;
	int i;
public:
	sf::Music music;
	DoublyLinkedList();
	void insertAtEnd(string data);
	void displaySuggestions();
	pair<string, int> getsong(int index);
};