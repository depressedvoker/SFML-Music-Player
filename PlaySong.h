#pragma execution_character_set("utf-8")
#pragma once
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<iostream>
#include <string>
#include"DoublyLinkedList_.h"
#include"Stack.h"
#include "Queue_.h"
#include<Windows.h>
#include <fstream>
#include"Interface.h"
#include<iomanip>
using namespace std;
class PlaySong
{
private:

	sf::Music music;
	sf::Time currentPosition;
	sf::Time newPosition;
	Interface& ii;
	Stack ss;
	Queue_ qq;
	int currentIndex;
	bool isPlaying;
	string songName;
	DoublyLinkedList ll;
public:
	PlaySong(Interface& interfaceobj);
	void playSong();
	void songsinstack();
	void songsinPlaylist();
	int player();
	int SearchSong(string fileName);
	void GuestMode();
};
