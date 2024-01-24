#include "DoublyLinkedList_.h"
doublyNode::doublyNode(string songName)
{
	this->songName = songName;
	this->next = NULL;
	this->prev = NULL;
}

DoublyLinkedList::DoublyLinkedList() { head = NULL; i = 0; }

void DoublyLinkedList::insertAtEnd(string data)
{
	doublyNode* n = new doublyNode(data);
	if (head == NULL)
	{
		head = n;
		return;
	}
	doublyNode* temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = n;
	n->prev = temp;
}

void DoublyLinkedList::displaySuggestions()
{
	SetConsoleOutputCP(CP_UTF8);
	cout << "\n\x1b[33m════════════════════════ Song Suggestions ════════════════════════\x1b[0m\n";

	doublyNode* temp = head;
	int index = 1;

	while (temp != NULL)
	{
		cout << "\x1b[36m" << index << ".\x1b[0m " << "♪♫ " << temp->songName << "\n";
		temp = temp->next;
		index++;
	}

	cout << "\n\x1b[33m═════════════════════════════════════════════════════════════════\x1b[0m\n";
}

pair<string, int> DoublyLinkedList::getsong(int index)
{
	bool flag = false;
	doublyNode* temp = NULL;
	temp = head;
	if (head == NULL)
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
		return make_pair(temp->songName, index);
	}
	else
	{
		return make_pair(head->songName, 0);
	}
}