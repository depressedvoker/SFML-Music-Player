#include "PlaySong.h"
PlaySong::PlaySong(Interface& interfaceobj) : ii(interfaceobj), ss(ii), qq(ii) {
	ifstream read("suggestions.txt");
	if (read.is_open()) {
		string songName;
		while (getline(read, songName)) {
			ll.insertAtEnd(songName);
		}
		read.close();
	}
	else {
		cout << "\n\t\t\x1b[31mUnable to open the suggestions file. Please check permissions.\x1b[0m" << endl;
	}
}

void PlaySong::playSong() {
	cout << "\n\n";
	cout << "\t\t\x1b[33m-- Choose Your Music Adventure --\x1b[0m\n";
	cout << "\t\t1. Play Songs from Suggestions\n";
	cout << "\t\t2. Play Songs from Liked Songs\n";
	cout << "\t\t3. Play Songs from Playlist\n";
	cout << "\n\t\tEnter your choice: ";
	int choice;
	cin >> choice;

	switch (choice) {
	case 2:
		system("cls");
		songsinstack();
		break;
	case 3:
		system("cls");
		songsinPlaylist();
		break;
	default:
		system("cls");
		ll.displaySuggestions();

		cout << "\n\t\tEnter Your Choice For The Song                           Or                          Search '0': ";
		bool flag = false;
		int indexChoice;
		int index;
		cin >> indexChoice;
		while (true) {
			if (indexChoice == 0|| flag==true) {
				index = SearchSong("suggestions.txt");
			}
			else {
				index = indexChoice;
			}
			currentIndex = index - 1;
			isPlaying = true;
			while (isPlaying) {
				auto songInfo = ll.getsong(currentIndex);
				songName = songInfo.first;
				currentIndex = songInfo.second;
				string filePath = "C:\\Users\\fahim\\Desktop\\Projectt-dsa\\Projectt\\yes\\yes\\Songs\\" + songName + ".mp3";

				if (!music.openFromFile(filePath)) {
					cout << "\n\t\t\x1b[31mFailed to load music file: " << songName << "\x1b[0m" << endl;
					break;
				}
				else {
					music.play();
					cout << "\n\n\t\t\x1b[32m♪♫ Now Playing: " << songName << " ♫♪\x1b[0m\n";
					cout << "\n\t\t[Space] Pause/Play\n";
					cout << "\t\t[Right/Left Arrow] Next/Previous\n";
					cout << "\t\t[L] Add to Liked Songs\n";
					cout << "\t\t[P] Add to Playlist\n";
					cout << "\t\t[+] Increase Volume\n";
					cout << "\t\t[-] Decrease Volume\n";
					cout << "\t\t[0] Search\n";
					cout << "\t\t[S] Skip Current Song\n";
					cout << "\t\t[F] Skip Forward (10 Seconds)\n";
					cout << "\t\t[B] Skip Backward (10 Seconds)\n";
					cout << "\t\t[Esc] Stop Song\n";
					cout << "\t\t[R] Return To Main Menu\n";
					int n;
					n=player();
					if(n==0)
					{
						flag = true;
						break;
					}
				}
			}
		}
	}
}

int PlaySong::player()
{
	while (true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			isPlaying = false;
			cout << "Music stopped." << endl;
			music.stop();
			return 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
		{
			return 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (music.getStatus() == sf::Music::Playing)
			{
				music.pause();
				cout << "Paused..." << endl;
			}
			else
			{
				music.play();
				cout << "Playing..." << endl;
			}
			sf::sleep(sf::milliseconds(200));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			music.stop();
			currentIndex++;
			break;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			music.stop();
			currentIndex--;
			break;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			bool alreadyin = false;
			ofstream ofs(ii.Getname() + "LikedSongs.txt", std::ios::app);
			ifstream ifs(ii.Getname() + "LikedSongs.txt");
			if (ofs.is_open())
			{
				string line;
				while (getline(ifs, line))
				{
					if (line == songName)
					{
						cout << "Song already exists in Liked Songs." << endl;
						alreadyin = true;
					}
				}
				if (!alreadyin)
				{
					ofs << songName << endl;
					cout << "Song added to Liked Songs" << endl;
				}
			}
			ifs.close();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			bool in = false;
			ofstream PlaylistFile(ii.Getname() + "Playlist.txt", std::ios::app);
			ifstream playlist(ii.Getname() + "Playlist.txt");
			if (PlaylistFile.is_open())
			{
				string line;
				while (getline(playlist, line))
				{
					if (line == songName)
					{
						cout << "Song already exists in your playlist." << endl;
						in = true;
					}
				}
				if (!in)
				{
					PlaylistFile<< songName << endl;
					cout << "Song added to playlist." << endl;
				}
			}
			playlist.close();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		{
			float currentVolume = music.getVolume();
			currentVolume += 10.0f;
			if (currentVolume > 100.0f) {
				currentVolume = 100.0f;
				cout << "Already at max volume" << endl;
			}
			else
				cout << "Volume increased to " << currentVolume << endl;
			music.setVolume(currentVolume);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
		{
			float currentVolume = music.getVolume();
			currentVolume -= 10.0f;
			if (currentVolume < 0.0f) {
				currentVolume = 0.0f;
				cout << "Already Muted" << endl;
			}
			else
				cout << "Volume decreased to " << currentVolume << endl;
			music.setVolume(currentVolume);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			music.stop();
			currentIndex++;
			break;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			currentPosition = music.getPlayingOffset();
			newPosition = currentPosition + sf::seconds(10);
			music.setPlayingOffset(newPosition);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			currentPosition = music.getPlayingOffset();
			newPosition = currentPosition - sf::seconds(10);
			music.setPlayingOffset(newPosition);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			music.stop();
			throw runtime_error("Return to main menu");
		}
		sf::sleep(sf::milliseconds(100));
	}
	return 1;
}

void PlaySong::songsinPlaylist() {
	qq.LoadSongs();
	qq.displayPlaylist();
	cout << "\n\t\tEnter Your Choice For The Song                           Or                          Search '0': ";
	bool flag = false;
	int indexChoice;
	int index;
	cin >> indexChoice;
	while (true) {
		if (indexChoice == 0|| flag==true)
		{
			index = SearchSong(ii.Getname() + "Playlist.txt");
		}
		else {
			index = indexChoice;
		}
		currentIndex = index - 1;
		isPlaying = true;
		while (isPlaying) {
			auto songInfo = qq.getQueuedSong(currentIndex);
			songName = songInfo.first;
			currentIndex = songInfo.second;
			string filePath = "C:\\Users\\fahim\\Desktop\\Projectt-dsa\\Projectt\\yes\\yes\\Songs\\" + songName + ".mp3";
			if (!music.openFromFile(filePath)) {
				cout << "\n\t\t\x1b[31mFailed to load music file: " << songName << "\x1b[0m" << endl;
				break;
			}
			music.play();
			cout << "\n\n\t\t\x1b[32m♪♫ Now Playing: " << songName << " ♫♪\x1b[0m\n";
			cout << "\n\t\t[Space] Pause/Play\n";
			cout << "\t\t[Right/Left Arrow] Next/Previous\n";
			cout << "\t\t[L] Add to Liked Songs\n";
			cout << "\t\t[+] Increase Volume\n";
			cout << "\t\t[-] Decrease Volume\n";
			cout << "\t\t[0] Search\n";
			cout << "\t\t[S] Skip Current Song\n";
			cout << "\t\t[F] Skip Forward (10 Seconds)\n";
			cout << "\t\t[B] Skip Backward (10 Seconds)\n";
			cout << "\t\t[Esc] Stop Song\n";
			cout << "\t\t[R] Return To Main Menu\n";
			int n;
			n=player();
			if(n==0)
			{
				flag = true;
				break;
			}
		}
	}
}

void PlaySong::songsinstack() {
	ss.Loadsongs();
	ss.displayLikedSongs();
	cout << "\n\t\tEnter Your Choice For The Song                           Or                          Search '0': ";
	bool flag = false;
	int indexChoice;
	int index;
	cin >> indexChoice;
	while (true) {
		if (indexChoice == 0|| flag==true)
		{
			index = SearchSong(ii.Getname() + "LikedSongs");
		}
		else {
			index = indexChoice;
		}
		currentIndex = index - 1;
		isPlaying = true;
		while (isPlaying) {
			auto songInfo = ss.getstackedsong(currentIndex);
			songName = songInfo.first;
			currentIndex = songInfo.second;
			string filePath = "C:\\Users\\fahim\\Desktop\\Projectt-dsa\\Projectt\\yes\\yes\\Songs\\" + songName + ".mp3";
			if (!music.openFromFile(filePath)) {
				cout << "\n\t\t\x1b[31mFailed to load music file: " << songName << "\x1b[0m" << endl;
				break;
			}
			music.play();
			cout << "\n\n\t\t\x1b[32m♪♫ Now Playing: " << songName << " ♫♪\x1b[0m\n";
			cout << "\n\t\t[Space] Pause/Play\n";
			cout << "\t\t[Right/Left Arrow] Next/Previous\n";
			cout << "\t\t[P] Add to Playlist\n";
			cout << "\t\t[+] Increase Volume\n";
			cout << "\t\t[-] Decrease Volume\n";
			cout << "\t\t[0] Search\n";
			cout << "\t\t[S] Skip Current Song\n";
			cout << "\t\t[F] Skip Forward (10 Seconds)\n";
			cout << "\t\t[B] Skip Backward (10 Seconds)\n";
			cout << "\t\t[Esc] Stop Song\n";
			cout << "\t\t[R] Return To Main Menu\n";
			int n;
			n=player();
			if(n==0)
			{
				flag = true;
				break;
			}
		}
	}
}

int PlaySong::SearchSong(string fileName) {
	while(true){
		cout << "\nEnter the keyword to search: ";
		string keyword;
		cin.ignore();
		getline(cin, keyword);

		ifstream file(fileName);

		if (!file.is_open()) {
			cerr << "Error: Unable to open file suggestions.txt" << endl;
			return -1;
		}

		string line;
		int index = 0;

		while (getline(file, line)) {
			index++;

			if (line.find(keyword) != string::npos) {
				file.close();
				return index;
			}
		}
		cout << "\n\t\t\x1b[31mNo results found for '" << keyword << "'\x1b[0m" << endl;
		file.close();
	}
}

void PlaySong::GuestMode() {
	system("cls");
	cout << "\n\n \x1b[32mLogged in as a Guest..." << "\x1b[0m\n";
	ll.displaySuggestions();
	cout << "\n\t\tEnter Your Choice For The Song                           Or                          Search '0': ";
	bool flag = false;
	int indexChoice;
	int index;
	cin >> indexChoice;
	while (true) {
		if (indexChoice == 0 || flag == true) {
			index = SearchSong("suggestions.txt");
		}
		else {
			index = indexChoice;
		}
		currentIndex = index - 1;
		isPlaying = true;
		while (isPlaying) {
			auto songInfo = ll.getsong(currentIndex);
			songName = songInfo.first;
			currentIndex = songInfo.second;
			string filePath = "C:\\Users\\fahim\\Desktop\\Projectt-dsa\\Projectt\\yes\\yes\\Songs\\" + songName + ".mp3";

			if (!music.openFromFile(filePath)) {
				cout << "\n\t\t\x1b[31mFailed to load music file: " << songName << "\x1b[0m" << endl;
				break;
			}
			else {
				music.play();
				cout << "\n\n\t\t\x1b[32m♪♫ Now Playing: " << songName << " ♫♪\x1b[0m\n";
				cout << "\n\t\t[Space] Pause/Play\n";
				cout << "\t\t[Right/Left Arrow] Next/Previous\n";
				cout << "\t\t[+] Increase Volume\n";
				cout << "\t\t[-] Decrease Volume\n";
				cout << "\t\t[0] Search\n";
				cout << "\t\t[S] Skip Current Song\n";
				cout << "\t\t[F] Skip Forward (10 Seconds)\n";
				cout << "\t\t[B] Skip Backward (10 Seconds)\n";
				cout << "\t\t[Esc] Stop Song\n";
				cout << "\t\t[R] Return To Main Menu\n";
				int n;
				n = player();
				if (n == 0)
				{
					flag = true;
					break;
				}
			}
		}
	}
}
