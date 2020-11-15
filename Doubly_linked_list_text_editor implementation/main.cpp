#include<iostream>
#include<string>
#include<iomanip>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;


typedef string Elem;
//Our global function to show which commands are vailable in the code during running
void listOfCommand()
{
	cout<<"List of available Commands:"<<endl
        <<"cursorDown                   :  Set the cursor to be in the line after its current position"<<endl
		<<"cursorUp                     : Set the cursor to be in the line before its current position."<<endl
		<<"moveCursorToLine             : Set the cursor to be the line indexed i"<<endl
		<<"cursorLineNum                :  Return the line number (i.e. index) of where the cursor is"<<endl
		<<"insertLineAfterCursor        : Insert a new line (containing the new sentence) after the line the current cursor is at"<<endl
		<<"insertLineBeforeCursor       : Insert a new line (containing the new sentence) before the line the current cursor is at, moving the cursor to the new line inserted"<<endl
		<<"replaceAtCursor              :  Replace the sentence at the current cursor with the sentence given as an argument, keeping the cursor at this line"<<endl
        <<"removeAtCursor               : Remove the line at the current cursor; setting the cursor to now be the position of the next line"<<endl
        << "maintainSentancePerLine      : Make sure that each line in the entire text contains one sentence only. "<<endl
        << "printAtCursor                : Print the line, where the cursor is, to the terminal."<<endl
        << "printAll                     : Print the entire text (i.e. all sentences) to the terminal."<<endl
		<<"exit                         : Exit the Program"<<endl;
}
// node class to implement doubly linked list
class Node {
        public:
        //pointers 
            Node* next;
            Node* prev;
            Elem elem;
            friend class Sequence;
            //initializer
            Node(): next(NULL), prev(NULL)
            {}
            Node(Elem elem) : elem(elem)
            {}
    };

// Sequence class implemented with doubly linked list
class Sequence { 
    public:
        Node *head;
        Node *tail;
        //Number of elements in a ll
        int N;
        //cursor to track position
        int cursor;
        // nested class Iterator
        class Iterator {
        private:
            Node *iter;
                        
        public:
            friend class Sequence; 
            //Iterator constructor
            Iterator(Node* curr) {
                iter=curr;  
            } 
            Elem& operator*(){
                return iter->elem;
            }
            bool operator==(const Iterator& p)const {
                return iter == p.iter;  
            }
            bool operator!=(const Iterator& p)const {
                return  p!= p.iter;  
            }
            Iterator& operator++() {
                iter = iter->next;
                return *this;   
            }
            Iterator& operator--() {
                iter = iter->prev; 	
                return *this;   
            }
        };


        Iterator point;
        Sequence();// Doubly-Linked List constructor
        ~Sequence();//destructor
        //display function that is called from Text Editor class methods to display file
        void display() {
                Node* ptr=new Node();
                ptr = head;
                while(ptr != NULL) {
                    cout<< ptr->elem <<endl;
                    ptr = ptr->next;
                }

        }
        //Supportive method to display a cursor line
        void display_at_cursor() {
                Node* ptr=new Node();
                ptr = head;
                int counter=0;
                while(ptr != NULL) {
                    // condition
                    if (counter==cursor) {
                        cout<< ptr->elem <<endl;
                    }
                    counter+=1;
                    ptr = ptr->next;
                }

        }
        //insert a new Node with data e
        void insert_node(Elem e) {
            Node *newNode = new Node();
            newNode->elem = e;
            newNode->next = NULL;
            newNode->prev = tail;
            //if head==NULL
            if (!head)
                head = newNode;

            if (tail)
                tail->next = newNode;
            tail = newNode;
            //Increment size
            ++N;
        }
        int size(); // size of the Doubly LL
        //Supportive method that is called from Text editor class's methods 
        void save() {
            string option;
            string name;
            cout<<"Do you want to save changes done to the file(type 1 if yes and 0 if no): ";
            cin>>option;
            if (stoi(option)==1) {
                cout<<"please provide a file name: ";
                cin>>name;
                if (name=="initial_text") {
                    //remove current text
                    fclose(fopen("initial_text.txt", "w"));
                    // insert new text to the empty file
                    ofstream file;
                    file.open(name+".txt", ios::app);
                    Node* ptr=new Node();
                    ptr = head; 
                    while(ptr != NULL) {
                        file << ptr->elem<<endl;
                        ptr = ptr->next;
                         }
                }
                else  {
                    ofstream file;
                    file.open(name+".txt", ios::app);
                    Node* ptr=new Node();
                    ptr = head; 
                    while(ptr != NULL) {
                        file << ptr->elem<<endl;
                        ptr = ptr->next;
                    }
                file.close();
                }
            }
        }
        bool isEmpty() const;// check whther Doubly linked list is empty
        void insertBefore(Iterator p,  Elem e);// Insert Before
        void insertAfter(Iterator p, Elem e);//
        void eraseAtPosition(Iterator p);//
        Iterator& before( Iterator& point){
            return --point;
        }
        Iterator& after( Iterator& point){
            return ++point;
        }
        int IndexOf(const Iterator& p) const {   
            Iterator q = begin();
            int j = 0;
            while (q != p) // until finds p
            {++q; ++j;} // iterate
            return j;
        }
        Iterator begin() const {                 
            return Iterator(head);   //head->next)
        }
        Iterator end(){                 
            return Iterator(tail);
        }
        Iterator atIndex(int index) const {   
            Iterator p = begin();
            for (int j = 0; j < index; j++)
            ++p; 
            return p;
        }
        void insertAtIndex(int index, const Elem& e);
        void eraseAtIndex(int index);
        Iterator& insertFront(const Elem& e){
            insertAtIndex(0,e);

        }
        Iterator& insertBack(const Elem& e){
            insertAtIndex(1,e);
        }
        void eraseFront();
        void eraseBack();
        const Elem& frontElement() const; 
        const Elem& backElement() const;

};

//Text editor class with methods that will bee called by user
//uses our Sequence  class to implemment it methods
class TextEditor{
    public:
    // cursor set to -1 as was supposed by the problem ask
        int cursor=-1;
        //list is called as an object to the Sequence class
        Sequence list;
        //empty check
        bool isEmpty() {
            list.isEmpty();
        }
        //size of text, or line numbers
        int size(){
            return list.N;
        }
        //cursor check for last line position
        bool isCursorAtLastLine(){
             if (list.N==1) {
                 return true;
             }
            else if (list.isEmpty()) {
                return true;
            }
            else if (cursor==list.N) {
                return true;
            }
            else
                return false;
        }
        //change cursor position D
        void cursorDown(){
            cursor+=1;
            //cout<<cursor;
            //cout<<list.N;
            if (cursor==list.N+1){
                cout<<"No line after, cannot change cursor, cursor is at the bottom"<<endl;
                cursor-=1;
            }
            else{
                cout<<"Cursor is seet to the line number "<<cursorLineNum()+1<<endl;
            }

        }
        //change cursor position U
        void cursorUp(){
            cursor-=1;
            if (cursor<=-1){
                cout<<"No line above, cursor on the top line or file empty"<<endl;
                cursor+=1;
            }
            else {
                cout<<"Cursor is seet to the line number "<<cursorLineNum()+1<<endl;
            }

        }

        void moveCursorToLine(string a){
            cout<<"New cursor position: ";
            cin>>a;
            if (stoi(a)>list.N) {
                cout<<"There is  no such line, choose another"<<endl;
            }
            else if (stoi(a)<=-1) {
                cout<<"There is  no such line, choose another"<<endl;
            }
            else {
                cursor=stoi(a);
            }
            cout<<"Cursor is set to the line number "<<cursor<<endl;
        }

        int cursorLineNum(){
            return cursor;
        }
        void insertLineAfterCursor(string sentence){
            cout<<"Put a new sentence: ";
            cin>>sentence;
            //calling method from sequence and nesting atIndex mehod to obtain iterator address from the cursor index
            list.insertAfter(list.atIndex(cursor),sentence);
            cout<<"Cursor is seet to the line number "<<cursorLineNum()<<endl;
            
        }
        void insertLineBeforeCursor(string sentence){
            cout<<"Put a new sentence ";
            cin>>sentence;
            list.insertBefore(list.atIndex(cursor),sentence);
            cout<<"Cursor is seet to the line number "<<cursorLineNum()<<endl;

        }
        void replaceAtCursor(string sentence){
            cout<<"Put a new sentence:  ";
            cin>>sentence;
            //we first delete a line with a cursor position then append a line before the previous line
            list.eraseAtPosition(list.atIndex(cursor));
            list.insertBefore(list.atIndex(cursor-1),sentence);
            cout<<"Cursor is seet to the line number "<<cursorLineNum()<<endl;


            
        }
        void removeAtCursor(){
            //list.eraseAtPosition(list.atIndex(cursor));
             list.eraseAtPosition(list.atIndex(cursor));
             cout<<"Cursor is seet to the line number "<<cursorLineNum()<<endl;


            
        }   
        // rearrange text by searching for the . ? ! marks
        void maintainSentancePerLine(){
                ifstream infile("initial_text.txt",ios::in);
                string current;
                string temp=" ";
                int count=0;
                //vector<string> vec;
                while(getline(infile, current))
                {
                    for(int i=0;i<current.size();i++) {
                        temp+=current[i];
                        //condition
                        if(current[i]=='.' || current[i]=='?' || current[i]=='!') {
                            list.insert_node(temp);
                            count++;
                            temp="";
                        }
                        
                    }
                }
                //remove empty nodes
                list.head = list.head->next->next;  
                list.head->prev = NULL;
                list.N -= 2; 
        }
        //use help method from sequence
        void printAtCursor(){
            list.display_at_cursor();

        }
        void printAll(){

            list.display();
        }
        void exit1(){
            list.save();
        }


};


int main() {
    string x;
    ifstream inFile;
    string user_input;
    string command;
    TextEditor list_object;
    Sequence l_object;
    string parameter;
    inFile.open("initial_text.txt");
    cout<<"Welcome to the text editor implemented in C++"<<endl;
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    while (getline(inFile,x)) {
        cout << x << endl ;
    }

    inFile.close();
    list_object.maintainSentancePerLine();
    listOfCommand();
    do {
    cout<<">";
    getline(cin,user_input);
    command = user_input.substr(0,user_input.find(" "));
    parameter = user_input.substr(user_input.find(" ")+1);
    if(command=="cursorDown")                 list_object.cursorDown();
    else if(command=="cursorUp")            list_object.cursorUp(); 
    else if(command=="moveCursorToLine")                   list_object.moveCursorToLine(parameter); 
    else if(command=="cursorLineNum")           list_object.cursorLineNum();
    else if(command=="insertLineAfterCursor")           list_object.insertLineAfterCursor(parameter);
    else if(command=="insertLineBeforeCursor")           list_object.insertLineBeforeCursor(parameter);
    else if(command=="replaceAtCursor")           list_object.replaceAtCursor(parameter);
    else if(command=="removeAtCursor")           list_object.removeAtCursor();
    else if(command=="maintainSentancePerLine")           list_object.maintainSentancePerLine();  
    else if(command=="printAtCursor")           list_object.printAtCursor();  
    else if(command=="printAll")           list_object.printAll();    
    else if (command == "exit")                 list_object.exit1();
    }  while(command!="exit");

};
//constructor
Sequence::Sequence() : point(0)  {
        N = 0;
                        
        head = new Node();              
        tail  = new Node();
        head->next = tail;          
        tail->prev = head;
        point.iter=head;

}
//destructor definition
Sequence::~Sequence() {
    Node *current = head;
    while (current)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

int Sequence::size()           
{ 
    return N; 
}

bool Sequence::isEmpty() const {
    return (N == 0);
}

void Sequence::eraseFront(){ 
    eraseAtPosition(begin()); 
}

void Sequence::eraseBack(){ 
    eraseAtPosition(--end()); 
}


void Sequence::eraseAtPosition( Iterator p){    
    if ( p.iter== head )
        {
            head = head -> next;
            head -> prev = 0;

            delete p.iter;
        }
    else if ( p.iter  == tail )
                cout<<"empty";
    else
        {
            Node* before = (p.iter) -> prev;
            Node * after = (p.iter) -> next;

            before -> next = after;
            after -> prev = before;

            delete p.iter;
          }
    N--;                 
}

void Sequence::insertBefore(Iterator p, Elem e ){

        Node* new_node = new Node(e);

        new_node -> next = head;

        head -> prev = new_node;

        head = new_node;

        N++;

}
void Sequence::insertAfter(Iterator p, Elem e){

    Node* node_before_new = p.iter;

    Node* node_after_new = node_before_new -> next;

    Node* new_node = new Node(e); 

    node_before_new -> next = new_node;

    new_node -> prev = node_before_new;


    new_node -> next = node_after_new;  

    node_after_new -> prev = new_node;

    N++; 


}
const Elem& Sequence::frontElement() const // get front element
{
    if(!isEmpty())
        return this->head->next->elem;
    else
        throw runtime_error("List is Empty");
}

const Elem& Sequence::backElement() const // get back element
{
    if(!isEmpty())
        return this->tail->prev->elem;
    else
        throw runtime_error("List is Empty");
}

void Sequence::insertAtIndex(int index, const Elem& e){
    Node* newNode = new Node(); 
    newNode->elem = e;
    newNode->next = NULL;
    newNode->prev = NULL;


    //check if  position > 0
    if(index < 1) {
        cout<<"\nposition should be >= 1.";
    } else if (index == 1) {

    //if the position is 1 - make new node as head
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    } else {

    //make a temp node and traverse to the 
    //   node previous to the position
        Node* temp = head;
        for(int i = 1; i < index-1; i++) {
        if(temp != NULL) {
            temp = temp->next;
        }
        }
    
        //previous node is not null
        if(temp != NULL) {
            newNode->next = temp->next;
            newNode->prev = temp;
            temp->next = newNode;
        if(newNode->next != NULL)
            newNode->next->prev = newNode;  
        } else {
        
        //When the previous node is null
        cout<<"\nThe previous node is null.";
        } 
    }
}


void Sequence::eraseAtIndex(int index){
        if (index <= N){
        Node* temp = tail;    
        for (int i = 0; i <= index; i++){
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        N--;
        cout<<"success";
    }

}