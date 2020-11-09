//============================================================================
// Name         : lab4.1.cpp
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 22-10-2020
// Date Modified: 22-10-2020 
// Copyright    : All rights are reserved
// Description  : Singly Linked-List
//============================================================================
#include<iostream>
#include<string>
#include<fstream>
#include<exception>
using namespace std;
//====================================
class Node
{
	private:
		int elem; //data element 
		Node* next; //Link (pointer) to the next Node
		
	public:
		Node(int elem) : elem(elem)
		{}
		friend class MyLinkedList ;

};
//=====================================
class MyLinkedList
{
	private:
		Node* head; // pointer to the head of list
	public:
		MyLinkedList (); // empty list constructor
		~MyLinkedList (); // destructor to clean up all nodes
		bool empty() const; // is list empty?
		const int& front() const; // get the element/data from the front Node
		void addFront(const int& elem); // add a new Node at the front of the list
		void removeFront(); // remove front Node from the list
		void display() const;
		void loadData(string); //read a file and load it into the linked list
		void dumpData(string) const; //write the linked list to a file
		void sort();  // sort the elements of the list
};
//=====================================
void listCommands()
{
	cout<<"List of available Commands:"<<endl
		<<"display            : Display the Linked List"<<endl
		<<"add <element>      : Add <element> to the front of the Linked List"<<endl
		<<"remove             : Remove the front node of the Linked List"<<endl
		<<"load <file_name>   : Load the data from <file> and add it into the Linked List"<<endl
		<<"dump <file_name>   : Dump the contents of the Linked list to <file>"<<endl
		<<"sort               : Sort the Linked List using Bubble Sort Algorithm"<<endl
		<<"help               : Display the list of available commands"<<endl
		<<"exit               : Exit the Program"<<endl;
}
//=======================================
// main function
int main()
{

	MyLinkedList myList;

	listCommands();
	string user_input;
	string command;
	string parameter;

	do
	{
		cout<<">";
		getline(cin,user_input);

		command = user_input.substr(0,user_input.find(" "));
		parameter = user_input.substr(user_input.find(" ")+1);
		
		if(command=="display") 				myList.display();
		else if(command=="add")				myList.addFront(stoi(parameter));
		else if(command=="remove")			myList.removeFront();
		else if(command=="load")			myList.loadData(parameter);
		else if(command == "dump")			myList.dumpData(parameter);
		else if(command == "sort")			myList.sort();
		else if(command == "help")			listCommands();
		else if(command == "exit")			break;
		else 								cout<<"Invalid Commad !!"<<endl;
	}while(command!="exit");

	return EXIT_SUCCESS;
}
//====================================
// constructor
MyLinkedList::MyLinkedList ()
{
	this->head = NULL;
}
//====================================
// destructor to clean up all nodes
MyLinkedList::~MyLinkedList () 
{
	while(!empty())
		removeFront();
	this->head = NULL;
}
//====================================
// Check if the list is empty or not
bool MyLinkedList::empty() const 
{
	return this->head == NULL;
}
//====================================
// return the value/elemnt at the front of the lsit
const int& MyLinkedList::front() const
{
	if(!empty())
		return this->head->elem;
	else
		throw out_of_range("List is Empty");
}
//====================================
// add a node at the front of list
void MyLinkedList::addFront(const int& elem)
{
	Node *tmp = this->head;
	this->head = new Node(elem);
	this->head->next = tmp;
}
//====================================
// remove the first node from the list
void MyLinkedList::removeFront()
{
	if(!empty())
	{
		Node *tmp = this->head;
		this->head = this->head->next;
		delete tmp;
	}

}
//====================================
// display all nodes of the linked list
void MyLinkedList::display() const
{
	Node *ptr=head;
	cout<<"Head->";
	while(ptr!=NULL)
	{
		cout<<ptr->elem<<"->";
		ptr=ptr->next;
	}
	cout<<"Null"<<endl;
}
//====================================
// sort the elments of the list using bubble_sort
void MyLinkedList::sort()
{
	if(head==NULL) return;

	Node *curr;
	bool swapped;
	do
	{
		curr = head;		//reset current to the head (for next round)
		swapped = false;
		while(curr->next!=NULL)
		{
			if(curr->elem > curr->next->elem)   //swap if the element of current node is bigger thant the elment of next node
			{
				int tmp = curr->elem;
				curr->elem = curr->next->elem;
				curr->next->elem = tmp;
				swapped = true;
			}
			curr = curr->next;    //move the current node
		}
	}while(swapped);
}
//==============================================
//Load data from a file and add it to the Linked List
void MyLinkedList::loadData(string path)
{
	ifstream fin(path);
	if(!fin)
	{
		cout<<"Can't open fil1e.txt"<<endl;
		return;
	}

	while(TRUE)
	{
		int data;
		fin>>data;
		if(fin.eof()) break;
		
		addFront(data);
	}

	fin.close();

}
//=============================================
//Dump/write the contents of the list to a file
void MyLinkedList::dumpData(string path) const
{
	ofstream fout(path);
	if(!fout)
	{
		cout<<"Can't open file: "<<endl;
		return;
	}
	Node *ptr = head;

	while(ptr!=NULL)
	{
		fout<<(ptr->elem)<<endl;
		ptr = ptr->next;
	}
	fout.close();
}
//==================================================

