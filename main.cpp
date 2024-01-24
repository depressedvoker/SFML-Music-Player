#pragma execution_character_set("utf-8")
#include <iostream>
#include <fstream>
#include <iomanip>
#include <SFML/Audio.hpp>
#include "DoublyLinkedList_.h"
#include "Interface.h"
#include "PlaySong.h"
#include <Windows.h>

using namespace std;

void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

int main() {
	SetConsoleTitle(L"Music Player");
	SetConsoleOutputCP(CP_UTF8);
	Interface ii;
	PlaySong pp(ii);

	int userChoice;
		do {
			try {
				clearScreen();

				cout << "\n\n\t\t\x1b[36m                        ♪♫ Welcome To Your Music Player! ♫♪\x1b[0m\n\n";

				cout << "\t\t\x1b[35m╔══════════════════════════════════════════════════════════════════════════════╗\n"
					<< "\t\t║                                       MENU                                   \x1b[0m║\n"
					<< "\t\t╚══════════════════════════════════════════════════════════════════════════════╝\n\n";

				cout << "\t\t\x1b[32m1.\x1b[0m Register or Login\n"
					<< "\t\t\x1b[32m2.\x1b[0m Guest Mode\n"
					<< "\t\t\x1b[32m3.\x1b[0m Exit\n\n";

				cout << "\t\t═════════════════════════════════════════════════════════════════════════════════\n"
					<< "\t\tEnter your choice: ";
				cin >> userChoice;

				switch (userChoice) {
				case 1:
					clearScreen();
					cout << "\n\t\t    \x1b[35mRegistration or Login\x1b[0m";
					ii.registration();
					pp.playSong();
					break;

				case 2:
					clearScreen();
					pp.GuestMode();
					break;

				case 3:
					cout << "\n\t\t\x1b[31mExiting the Music Player.\x1b[0m\n";
					break;

				default:
					cout << "\n\t\t\x1b[31mInvalid choice. Please try again.\x1b[0m\n";
					break;
				}

				if (userChoice != 3) {
					cout << "\n\n\t\tPress Enter to continue...";
					cin.ignore();
					cin.get();
				}
			}
			catch (exception& e) {
				cout << "\n\t\t\x1b[31mError: " << e.what() << "\x1b[0m\n";
				cout << "\n\t\tPress Enter to continue...";
				cin.ignore();
				cin.get();
			}
		} while (userChoice != 3);

	return 0;
}