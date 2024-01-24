#include "Queue_.h"
node::node(string data)
{
	this->data = data;
	next = NULL;
}
Queue_::Queue_(Interface& temp) :ii(temp)
{
	front = NULL;
	rear = NULL;
}
bool Queue_::empty()
{
	return front == NULL;
}
void Queue_::displayPlaylist()
{
	cout << "\n\x1b[33m════════════════════════ Playlist ════════════════════════\x1b[0m\n";

	node* temp = front;
	int index = 1;

	if (front == NULL)
	{
		cout << "\x1b[36mPlaylist is empty. Add some songs and enjoy the music!\x1b[0m\n";
		return;
	}

	while (temp != NULL)
	{
		cout << "\x1b[36m" << index << ".\x1b[0m " << "♪♫ " << temp->data << endl;
		temp = temp->next;
		index++;
	}

	cout << "\n\x1b[33m══════════════════════════════════════════════════════════\x1b[0m\n";
}

void Queue_::enqueue(string data)
{
	node* temp = new node(data);
	if (empty())
	{
		rear = front = temp;
	}
	else
	{
		rear->next = temp;
		rear = temp;
	}
}
void Queue_::LoadSongs()
{
	ifstream ReadFromPlaylist(ii.Getname() + "Playlist.txt");
	if (ReadFromPlaylist.is_open())
	{
		string songName;
		while (getline(ReadFromPlaylist, songName))
		{
			enqueue(songName);
		}
		ReadFromPlaylist.close();
	}
	else
	{
		cout << "Unable To Open" << ii.Getname() + "Playlist.txt";
	}
}
pair<string, int> Queue_::getQueuedSong(int index)
{
	bool flag = false;
	node* temp = NULL;
	temp = front;
	if (front == NULL)
	{
		cout << "No songs in the list." << endl;
		return make_pair("", -1);
	}
	for (int j = 0; j < index; j++)
	{
		if (temp->next == NULL)
		{
			flag = true;
			break;
		}
		else
		{
			temp = temp->next;
		}
	}
	Sleep(500);
	if (flag == false)
	{
		return make_pair(temp->data, index);
	}
	else
	{
		return make_pair(front->data, 0);
	}
}