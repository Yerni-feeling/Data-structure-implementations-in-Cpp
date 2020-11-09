#include<iostream>
#include<string>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdio.h> 
#include <stdlib.h> 
#include<time.h>
#include <vector>




using namespace std;
//variable required to track students and use it to enroll function later
string list_of_names;




//User class, that has common property of admin and student class, so those classes can inherit from User class
class User {

    public:
        int auth;

    protected:

        int  ID;
        string FirstName, LastName,Username,Password;
    //login and password trackers
        string inputUsername;
        string inputPassword;
   
};


//Admin class that inherits from user class
class Admin: public User {
    private:

    public:
        //public functions of the class
        void loginadmin();
        void addCourse();
        void viewCourseByCourseID();
        void registerNewStudent();
        
        void viewAllCourses();      
        void getAdminAccounts();
};





//Linked list calling with a node class being StudentNode
class StudentNode: public User{
    private:
        string  ListOfCourses;
        //access to the next node with a next pointer
        StudentNode *next;

    
    public: 
        StudentNode(int&, string&, string&, string&, string&, string&);
         friend class StudentList ;


};
class StudentList: public User {
    private:
        //head pointer for the linked list student
        StudentNode * head;

    public:

        StudentList();
        ~StudentList();
        void removeFront();
        void loginstudent();
        void enroll();
        void withdraw();
        void getStudentAccounts();
        void addStudentData();
        bool empty() const;

};




//our own instance of data structure, to make it compact to access it later
struct CourseData {
    string CourseID, MaxCapacity, CurrentCapacity ;
    string CourseName, InstructorName, CourseSection, CourseLocation;
    string ListOfStudents;
};
//own operator difinition required forr display function later in the code
ostream& operator<<(ostream &os, const CourseData &data) {
 
    os <<data.CourseName<<" "<<data.MaxCapacity<<" "<<data.CurrentCapacity<<" "<<data.CourseName<<" "<<data.InstructorName<<" "<<data.CourseSection<<" "<<data.CourseLocation;  
    return os;
}
//Course linked list instance
class CourseNode {
    private:
        CourseData elem;
        //
        CourseNode* next;

    public:
        CourseNode(CourseData elem) : elem(elem)
		{}  
        friend class Courses ;

};

class Courses {
    private:
        
        CourseNode *head;
    public:     
        Courses();
        ~Courses();
        void getCources();
        void addCoursesdata();
        bool empty() const;
        void removeFront();
        void addFront(const CourseData& elem);
        void loadData();
        void display() const;
        void viewFreeCourses() const;
        void dumpData() const;
        void deleteCourse();
        void changeInstructor();
        void enroll();
        void detailCourses();
        void showStudents();
        void viewStudentsByCourseID();
        void viewCoursesByStudentID();
        void withdraw();


        

};
//functions for student and admin to output a help message and show how to call aother fucntions
void listCommandsforAdmin()
{
	cout<<"List of available Commands:"<<endl
        <<"display                      : Display All Cources"<<endl
		<<"free-courses                 : Shows all non-empty courses"<<endl
		<<"add-course                   : Add a course "<<endl
		<<"delete-course              : Delete a course"<<endl
		<<"create-student             : Create a student to the system"<<endl
		<<"change-instructor            : Change instructor of the course"<<endl
		<<"detail-course                : Show a detail of particular course"<<endl
        <<"show-students                : Shows all students in a class by CourseID"<<endl
       //<< "student-courses              :: Shows all courses in a class of specific student"<<endl
		<<"exit                         : Exit the Program"<<endl;
}
void listCommandsforStudent()
{
	cout<<"List of available Commands:                        "<<endl
		<<"display                       :  Display All Cources"<<endl
		<<"free-courses                  :  Shows all non-empty courses"<<endl
        <<"register                      :  Register to a particular course"<<endl
        <<"withdraw                      :  Withdraw from a course"<<endl
		<<"exit                          : Exit the Program"<<endl;
}





int main()
{   
    //calling and object instances of the classes above
    //user class object
    User userObject;
    //admin class object
    Admin adminObject;
    //cources class object
    Courses coursesObject;
    StudentList studentListObject; 
    string command;
	string parameter;
    //file reading
    ifstream usersFile("MyUniversityAdmin.csv");
    ifstream studentFile("MyUniversityStudents.csv");
    //first opening message to define the user type
    cout<<"Please type 0 if you are student and 1 if you are admin:  ";
   //obtain a first input
    cin>>userObject.auth;


    string user_input;
    int a=0;

    //coursesObject.display();
    //if the user chose 1, i.e admin panel then this function executes        
    if (userObject.auth==1) {
        cout<<"You are in Admin display"<<endl;
        //calling function frrom the class objects to check for admin validity
        adminObject.loginadmin();
        coursesObject.loadData();       
        listCommandsforAdmin();
        do {
            //track user input to call ffunction according to the input
            cout<<">";
            getline(cin,user_input);
            command = user_input.substr(0,user_input.find(" "));
            if(command=="display")                 coursesObject.display();
            else if(command=="free-courses")            coursesObject.viewFreeCourses(); 
            else if(command=="add-course")                   coursesObject.addCoursesdata(); 
            else if(command=="delete-course")           coursesObject.deleteCourse();
            else if(command=="create-student")           coursesObject.dumpData();
            else if(command=="change-instructor")           coursesObject.changeInstructor();
            else if(command=="show-students")           coursesObject.viewStudentsByCourseID();
            //else if(command=="student-courses")          coursesObject.viewCoursesByStudentID();
            else if(command=="detail-course")           coursesObject.detailCourses();  
            else if (command == "exit")                 break;
            else                                    cout<<"New Command !!"<<endl;
        }while(command!="exit");
    }
    else if (userObject.auth==0){
            cout<<"You are in Student display"<<endl;
            //calling function frrom the class objects to check for student validity
            studentListObject.loginstudent();
            coursesObject.loadData();
            //coursesObject.display();        
            listCommandsforStudent();
            do {
             //track user input to call ffunction according to the input
            cout<<">";
            getline(cin,user_input);
            command = user_input.substr(0,user_input.find(" "));
            parameter = user_input.substr(user_input.find(" ")+1);
            if(command=="display")                 coursesObject.display();
            if(command=="free-courses")            coursesObject.viewFreeCourses();
            //if(command=="add-course")            coursesObject.addCoursesdata(); 
            if(command=="register")           coursesObject.enroll();
            if(command=="withdraw")           coursesObject.withdraw();
            if (command == "exit")                 break;
            else                                 cout<<"New Command !!"<<endl;
            }while(command!="exit");

    }
    else {
        cout<<"Incorrect data";
    }

    

    return EXIT_SUCCESS;
    return 0;
}       




//Checks whther data entered corresponds with database in a csv file
void Admin::loginadmin() {
    cout<<"Please enter your username: "<<endl;
    cin >> inputUsername;
    cout<<"Please enter your password: "<<endl;
    cin >> inputPassword;
    //Our search pattern that we will be searching
    string userAndPass = inputUsername + "," + inputPassword; // Search pattern
    string partline;

    int offset;
    //file reading
    ifstream usersFile;

    usersFile.open ("MyUniversityAdmin.csv");

    //hellping variables to manipulate with a string and its substring
    string line;
    int poscomma;
    int endpos;
    line = line.substr((line.find(",")*3 + 3),line.find("\n"));


    bool found = false; 
    //if file open and exists we call getline function to go through file line by line, and it stops and the end of file
    //as an eof() function
    if(usersFile.is_open()){    
        while(getline(usersFile,line) && !found) {
            //obtaing last two words with a comma to compare it with a searching word
            poscomma = line.find(",") +1;
            endpos = line.find("\n");
            partline = line.substr(poscomma, endpos);

            poscomma = partline.find(",")+1;
            endpos = partline.find("\n");
            partline =  partline.substr(poscomma, endpos);

            poscomma = partline.find(",")+1;
            endpos = partline.find("\n");
            partline =  partline.substr(poscomma, endpos);  

            line = partline;
            //cout<<line<<"erer"<<endl;
       
            //cout<<"User and pass : "<<userAndPass<<"test"<<endl;
            
            // if they are euqal then found=true and while loop breaks
            if(line == userAndPass)
            {
                found = true;
            }
            
        }
        //file close
        usersFile.close();
        //if found- message with a username that is appropriate to log in
        if(found) {
                cout << "Welcome "<< inputUsername << '\n';
        }
        else {
            // otherwise keeps asking a correct username and password untill correctly entered
            cout << "\nUsername and/or password incorrect!\n";
            loginadmin();
        }
    }
}




//simialr ffunction for the student log in system
void StudentList::loginstudent() {
    cout<<"Please enter your username: "<<endl;
    cin >>inputUsername;
    cout<<"Please enter your password: "<<endl;
    cin >>inputPassword;

    string userAndPass = inputUsername + "," + inputPassword; // Search pattern
    string partline;

    int offset;

    ifstream studentFile;
    studentFile.open ("MyUniversityStudents.csv");


    string line;
    int poscomma;
    int endpos;
    string a,b,c,d,e;//
    bool found = false; 
    line = line.substr((line.find(",")*3 + 3),line.find("\n"));
    if(studentFile.is_open()){    
        while(getline(studentFile,line) && !found) {
            //stringstream sst(line); 
            //getline(getline(getline(getline(getline (sst,a,','),b,','),c, ','),d,','),e,' ');
            
            poscomma = line.find(",") +1;
            endpos = line.find("\n");
            partline = line.substr(poscomma, endpos);


            poscomma = partline.find(",")+1;
            endpos = partline.find("\n");
            partline =  partline.substr(poscomma, endpos);


            poscomma = partline.find(",")+1;
            endpos = partline.find("\n");
            partline =  partline.substr(poscomma, endpos);  

            line = partline;

            if(line == userAndPass)
            {
                found = true;

                list_of_names=inputUsername;
            }
            
        }
        if(found==true) {
                cout << "Welcome "<< inputUsername << '\n';
        }
        else {
            cout << "\nUsername and/or password incorrect!\n";
            loginstudent();
        }
    }
    studentFile.close();
}
// StudentList constructor
StudentList::StudentList(){
    this->head = NULL;
}
//Course constructor
Courses::Courses ()
{
	this->head = NULL;
}


//Destructor
StudentList::~StudentList(){
    while(!empty())
		removeFront();
	this->head = NULL;
}


//Destructor
Courses::~Courses ()
{
	while(!empty())
		removeFront();
	this->head = NULL;
}


//Check for empty linked list
bool StudentList::empty() const 
{
	return this->head == NULL;
}


//Check for empty linked list
bool Courses::empty() const 
{
	return this->head == NULL;
}

void Courses::viewCoursesByStudentID(){
    
}



//Course enroll functions
void Courses::enroll() 

{   

    //checks whther the course if full or not
    CourseNode *ptr=head;
    CourseData a;
    bool b=false;
    //go through all nodes and checks for ffree cources
	while(ptr!=NULL)
	{   
        if (ptr->elem.CurrentCapacity!=ptr->elem.MaxCapacity) {
        b=true;
    }
    ptr=ptr->next;
	}
    


    string line;
    string courseid, course_section;
    cout<<"What is a courseID: ";
    cin>>courseid;
    cout<<"What is the  course section: ";
    cin>>course_section;

    string first;
    ofstream outfile;
    outfile.open("course_students_output.csv",ios_base::app);
    ifstream file;
    file.open("course_students.csv");
    
    if ( outfile.is_open() ){ 
        while ( getline(file, line) ) { 
            stringstream sst(line); 
            string section;

            getline(getline(sst,first,','), section, ',');
            if (courseid==first && course_section==section && b==true) {
                sst <<"\n"<<first<<","<<section<<","<<list_of_names<<";";
                outfile << sst.str();
                cout<<"You were successfully enrolled";
            }
       }
    }
    if (b==false) {
        cout<<"Course was not found or it can be full"<<endl;
    }

    file.close();
    outfile.close();
}



//front node remove function
void StudentList::removeFront()
{
	if(!empty())
	{
        //tmp pointer to store head
		StudentNode *tmp = this->head;
        //change head
		this->head = this->head->next;
        //delete and old head
		delete tmp;
	}

}



//Simialrly, front node remove function
void Courses::removeFront()
{
	if(!empty())
	{
		CourseNode *tmp = this->head;
		this->head = this->head->next;
		delete tmp;
	}

}




//Add front functions
void Courses::addFront(const CourseData& elem)
{
	CourseNode *tmp = this->head;
	this->head = new CourseNode(elem);
	this->head->next = tmp;
}




//withdraw from a course function

void Courses::withdraw(){
    ifstream infile;    
    infile.open("course_students_output.csv");
    string course_id;
    string course_section;
    string names;
    string line;
    cout<<"Choose a course id:  ";
    cin>>course_id;
    cout<<"Choose a course_section:  ";
    cin>>course_section;
    infile.open("course_students_output.csv");
    string word1,word2,word3;
    bool a=false;
    if(infile.is_open()){  
        while(getline(infile, line)) {
            stringstream sst(line);
            getline(getline(getline (sst,word1,','),word2,','),word3, ';');
            if (course_id==word1 && course_section==word2 && list_of_names==word3) {
                a=true;
                word1=" ";
                word2=" ";
                word3=" ";
                cout<<"You successfully withdrew"<<endl;
    
            }
            
        }
    }
    if (a==false) {
        cout<<"No such data"<<endl;
    }
}


//
//add course for admin
void Courses::addCoursesdata()
{
    CourseData a;
    string firstname, lastname,third,forth,z,x,c,v;
    cout<<"Provide a CourseID: ";
	cin>>firstname;
    cout<<"Provide a CourseName: ";
    cin>>lastname;
    cout<<"Provide a Maximum capacity: ";
    cin>>third;

    
    
    do  {
            
            cout<<"Number of students cant be more than maximum capacity, Provide a current number of students ";
            cin>>forth;

            
        }while (stoi(forth)>stoi(third));
    
    
    cout<<"Provide Instructor's name: ";
    cin>>z;
    cout<<"Provide Course Section:  ";
    cin>>x;
    cout<<"Provide a Course Location:  ";
    cin>>c;
    a.CourseID=firstname;
    a.MaxCapacity=third;
    a.CurrentCapacity=forth;
    a.CourseName=lastname;
    a.InstructorName=z;
    a.CourseSection=x;
    a.CourseLocation=c;
    addFront(a);

   //appends data to the end of the MyUniversityCourses.csv and course_students.csv in order to save them and manipulate with them later
    ofstream outfile;
    outfile.open("MyUniversityCourses.csv", ios_base::app);
    outfile<<"\n"<<lastname<<firstname<<","<<third<<","<<forth<<","<<z<<","<<x<<","<<c<<endl; 
    ofstream course_file;
    course_file.open("course_students.csv", ios_base::app);
    course_file<<a.CourseID<<","<<a.CourseSection<<","<<endl; 
    cout<<"Course was successfully created"<<endl;
    
    
    
}
//delete a course
void Courses::deleteCourse()
{   
    string a;
    //elem.CourseID
    CourseNode *ptr=head;
    cout<<"what is course id: ";
    cin>>a;
    int counter=0;
    int stat;
    //go through all nodes
    while(ptr!=NULL)
	{
		counter+=1;
        //make a counter to find index position that we want to delete -node
        if (a==ptr->elem.CourseID) {
            stat=counter;

        }

		ptr=ptr->next;
	}   
    //if the linked list is of the size one
    CourseNode * tmp1=head;
    if (stat==1) {
        head=tmp1->next;
        free(tmp1);
        return; 
    }
    //use our counter to delete a node
    for(int i=0; i<stat-2;i++){
        tmp1=tmp1->next;
    }
    CourseNode * tmp2=tmp1->next;
    tmp1->next=tmp2->next;
    free(tmp2);
    cout<<"Course successfull deleted";

}



//function to change instructor of the course for admin users
void Courses::changeInstructor()
{   
    
    string name, id;
    cout<<"What course's instructor you want to change(provide a CourseID): ";
    cin>>id;
    cout<<"What is a new instructor's name: ";
    cin>>name;
    ofstream ofs("MyUniversityCourses.csv", std::ofstream::trunc);
    CourseNode *temp=head;
    bool a=false;
    //go through all nodes
    while(temp!=NULL)
	{   
        // if the id is in our database
        if (id==temp->elem.CourseID) {
            //change a new value
            temp->elem.InstructorName=name;
            cout<<"Instructor has been changed"<<endl;
            a=true;

        }
        //change a data with a new one
        ofs<<temp->elem.CourseName<<","<<temp->elem.CourseID<<","<<temp->elem.MaxCapacity<<","<<temp->elem.CurrentCapacity<<","<<temp->elem.InstructorName<<","<<temp->elem.CourseSection<<","<<temp->elem.CourseLocation<<"\n";

		temp=temp->next;
	}  

    if (a==false) {
        cout<<"Such course was not found"<<endl;
    }

}


//show all students function
void Courses::showStudents()
{   
    string classid;
    cout<<"Provide the CourseID from course to see list of enrolled students: ";
    cin>>classid;
    CourseNode *ptr=head;
    while(ptr!=NULL)
	{

        if (classid==ptr->elem.CourseID) {
            
            cout<<ptr->elem.ListOfStudents;
            }

		ptr=ptr->next;
	}   

}



void Courses::detailCourses()
{   
    
    string id;
    cout<<"What is a course you want see details of(provide a CourseID): ";
    cin>>id;
    CourseNode *ptr=head;
    //go through all nodes in alinked list
    bool a=false;
    while(ptr!=NULL)
	{
        
        //if existed
        if (id==ptr->elem.CourseID) {
            //show all details
            a=true;
            cout<<"\n CourseID: "<<ptr->elem.CourseID<<"\n MaxCapacity: "<<ptr->elem.MaxCapacity<<"\n CurrentCapacity: "<<ptr->elem.CurrentCapacity<<"\n CourseName: "<<ptr->elem.CourseName<<"\n InstructorName:  "<<ptr->elem.InstructorName<<"\n CourseSection: "<<ptr->elem.CourseSection<<"\n CourseLocation: "<<ptr->elem.CourseLocation<<" "<<endl;
        }

		ptr=ptr->next;
	}   
    if (a==false) {
        cout<<"Such course was not found"<<endl;
    }
    
}


void Courses::viewStudentsByCourseID(){
    


    string id;
    cout<<"Insert a courseID to see list of students: ";
    cin>>id;
    ifstream infile;    
    string line;
    string save;

    CourseNode *ptr = head;
    bool a=false;
    while(ptr!=NULL)
	{   
        if (id==ptr->elem.CourseID) {
		save=ptr->elem.CourseID;
    }
    ptr=ptr->next;
	}
    
    string course_section;
    string list_of_students;
    infile.open("course_students_output.csv");
    if(infile.is_open()){  
        while(getline(infile, line)) { 
            stringstream sst(line); 
            string courseid;
            getline(getline(getline (sst,courseid,','),course_section,','),list_of_students, ';');
            
            if (courseid==save) {
                cout<<list_of_students<<endl;
                a=true;
            }
            
        


        }

    }
    if (a==false) {
        cout<<"Students were not found"<<endl;
    }
    
    
}



void Courses::loadData()
{
    
    ifstream infile;
    //string path;s
    infile.open("MyUniversityCourses.csv");
    string line;
    CourseNode *current = head;
    int i=1;
    int k=0;
    CourseData a;

    if(infile.is_open()){  
    while(getline(infile, line)) { 


        string firstname, lastname,third,forth,z,x,c,v;
        vector<string> vect;

        stringstream sst(line); 

        getline(getline(getline(getline(getline(getline(getline (sst, firstname, ','),lastname, ','),third, ','),forth,','),z, ','),x, ','),c, ',');

        a.CourseID=lastname;
        a.MaxCapacity=third;
        a.CurrentCapacity=forth;
        a.CourseName=firstname;
        a.InstructorName=z;
        a.CourseSection=x;
        a.CourseLocation=c;
        a.ListOfStudents=v;
        //a.ListOfStudents=v;
        addFront(a);




    i++;
    }

    }
    infile.close();
    }       




//ffunction to append a new data for students in a students csv file
void Courses::dumpData() const
{
    string name,lastname,username,password;
    cout<<"Enter student's name: ";
    cin>>name;
    cout<<"Enter student's lastname: ";
    cin>>lastname;

    srand( time(NULL) );
    int number_id = rand() % 9000 + 1000;
    int password_1=rand() % 9000 + 1000;
    string s=to_string(number_id);
    string k=to_string(password_1);
    username=name+s;
    password=lastname+k;
    ofstream outfile;
    outfile.open("MyUniversityStudents.csv", ios_base::app);
    outfile<<"\n"<<number_id<<","<<name<<","<<lastname<<","<<username<<","<<password; 
}


//display all cources function
void Courses::display() const
{
	CourseNode *ptr=head;
	//cout<<"Head->";
	while(ptr!=NULL)
	{
		cout<<ptr->elem<<endl; //"->";
		ptr=ptr->next;
	}   

}



void Courses::viewFreeCourses() const

{
	CourseNode *ptr=head;
    CourseData a;
    bool b=false;
    //go through all nodes and checks for ffree cources
	while(ptr!=NULL)
	{   
        if (ptr->elem.CurrentCapacity!=ptr->elem.MaxCapacity) {
		cout<<ptr->elem<<endl; //"->";
        b=true;
    }
    ptr=ptr->next;
	}
    if (b==false) {
        cout<<"Such courses were not found"<<endl;
    }

}


    
