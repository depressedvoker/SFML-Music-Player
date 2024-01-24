#include "Stack.h"
StackNode::StackNode(string stackedSongs, StackNode* next)
{
	this->stackedSongs = stackedSongs;
	this->next = NULL;
}
Stack::Stack(Interface& interfaceobj) : ii(interfaceobj)
{
	top = nullptr;
}

void Stack::push(string data) {
	StackNode* node = new StackNode(data, top);
	if (top == nullptr) {
		top = node;
	}
	else
	{
		node->next = top;
		top = node;
		LatestNode = node;
	}
}
void Stack::displayLikedSongs()
{
	cout << "\n\x1b[33m════════════════════════ Liked Songs ════════════════════════\x1b[0m\n";

	StackNode* temp = top;
	int index = 1;

	if (top == NULL)
	{
		cout << "\x1b[36mNo liked songs yet. Discover some great tunes!\x1b[0m\n";
		return;
	}

	while (temp != NULL)
	{
		cout << "\x1b[36m" << index << ".\x1b[0m " << "♥ " << temp->stackedSongs << endl;
		temp = temp->next;
		index++;
	}

	cout << "\n\x1b[33m-------------------------------------------------------------\x1b[0m\n";
}

bool Stack::empty()
{
	if (top == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

pair<string, int> Stack::getstackedsong(int index)
{
	bool flag = false;
	StackNode* temp = NULL;
	temp = top;
	if (top == NULL)
	{
		cout << "No songs in the list." << endl;
		return make_pair("", -1);
	}
	for (int j = 0; j < index; j++)
	{
		if (temp->next == NULL)
		{
			flag = true;
		}
		else
		{
			temp = temp->next;
		}
	}
	Sleep(500);
	if (flag == false)
	{
		return make_pair(temp->stackedSongs, index);
	}
	else
	{
		return make_pair(LatestNode->stackedSongs, 0);
	}
}
void Stack::Loadsongs()
{
	ifstream read(ii.Getname() + "LikedSongs.txt");
	if (read.is_open()) {
		string item;
		while (getline(read, item)) {
			push(item);
		}
		read.close();
	}
	else {
		cout << "Unable To Open" << ii.Getname() + "LikedSongs.txt";
	}
}