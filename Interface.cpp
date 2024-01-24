#include "Interface.h"
using namespace std;

void Interface::registration() {
logout:
	int regchoice;
	cout << "\n\n\x1b[33m╔══════════════════════════════════════════════════════════╗\x1b[0m\n";
	cout << "\x1b[35m║                         Sign in                          ║\x1b[0m\n";
	cout << "\x1b[33m╚══════════════════════════════════════════════════════════╝\x1b[0m\n";
	cout << "\n";

	cout << "\x1b[36m" << " 1. Login" << "\x1b[0m" << endl;
	cout << "\x1b[36m" << " 2. Register New Account" << "\x1b[0m" << endl;
	cout << "\n";
	Sleep(700);
	cout << " Enter your choice: ";


	while (!(cin >> regchoice)) {
		cout << "\n Incorrect input. Please try again: ";
		cin.ignore();
	}

	while (regchoice < 1 || regchoice > 2) {
		cout << "\n Invalid choice. Please try again: ";
		cin >> regchoice;
	}

	if (regchoice == 1) {
		cout << "\n\n Welcome! Please provide your necessary information:\n";
		cout << "    Enter your Name: ";
		cin >> regname;
		cout << "    Enter your Password: ";
		cin >> regpass;
		if (login(regname, regpass) == 0) {
			goto logout;
		}
	}
	else if (regchoice == 2) {
		cout << "\n\n Welcome new member! Please enter your information:\n";
		cout << "    Enter your First Name: ";
		cin >> regname;
		cout << "    Type a Password: ";
		cin >> regpass;
		while (1) {
			cout << "    Enter the password again for verification: ";
			cin >> veripass;
			if (regpass == veripass) {
				cout << "\n Password verified. Please continue!\n";
				break;
			}
			else {
				cout << "\n Passwords did not match. Please choose another password:\n";
				cin >> regpass;
			}
		}
		registeracc(regname, regpass);
	}
}

void Interface::registeracc(string name, string pass) {
	ofstream loginfile("credentials.txt", ios::app);
	loginfile << "username:" + name << " "
		<< "password:" + pass << endl;
	Sleep(1000);
	cout << " Account successfully created!\n";
	Sleep(1000);
	cout << " You have been automatically logged in to your account!\n";
	Sleep(1000);
	loginfile.close();
	string userFileName1 = name + "LikedSongs.txt";
	string userFileName2 = name + "Playlist.txt";
	ofstream userFile1(userFileName1);
	ofstream userFile2(userFileName2);
	if (userFile1.is_open() && userFile2.is_open()) {
		userFile1.close();
		userFile2.close();
		cout << " Successfully created user files.\n";
		Sleep(1000);
		SetConsoleOutputCP(CP_UTF8);
		cout << "\n\x1b[36m Welcome " << name << ". Enjoy!\x1b[0m\n";
	}
	else {
		cout << " Failed to create user files!\n";
	}
}

int Interface::login(string name, string pass) {
	string namecheck, passcheck;
	ifstream loginfile("credentials.txt");
	int success = 0;
	if (loginfile.is_open()) {
		while (loginfile >> namecheck >> passcheck) {
			if ("username:" + name == namecheck && "password:" + pass == passcheck) {
				Sleep(400);
				cout << "\n Login Successful!\n";
				Sleep(400);
				SetConsoleOutputCP(CP_UTF8);
				cout << "\n\x1b[36m Welcome "<<name<<". Enjoy!\x1b[0m\n";
				success = 1;
				Sleep(700);
				break;
			}
		}
		if (success == 0) {
			cout << "Login Unsuccessful!\n";
			cout << "Returning to the main menu in 3... ";
			Sleep(700);
			cout << "2... ";
			Sleep(700);
			cout << "1... \n\n\n\n\n";
		}
		loginfile.close();
	}
	return success;
}

string Interface::Getname() {
	return regname;
}