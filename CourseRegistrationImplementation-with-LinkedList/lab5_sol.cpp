//============================================================================
// Name         : lab5.cpp
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 13-03-2019
// Date Modified: 16-10-2020 
// Copyright    : All rights are reserved
// Description  : Convert Infix expression to PostFix and then evaluate it
//============================================================================
#include<iostream>
#include<string>
#include<exception>
#include<math.h>
#include<stack>
#include<ctype.h>

using namespace std;

bool isOperator(char); //Helper method which checks if the input char is an operator
int convertOpToInt (char); //Helper mehtod which converts operators into int so their precdence can be compared
bool isleq(char, char); //Helper method which compare two operators  and return True if first operator has less or equal predence than the right operator
string infix2postfix(string);   //Helper Method which converts an infix notaiton into a postfix notation (lab4)
float evaluate(string postfix);		//Method which will evaluate a PostfixExpression and return the result
//=============Stack Class ================
template <typename T>
class Stack
{
	private:
		T *array;
		int n;	//number of current elements in the Stack
		int N;	//Array Size (Capacity)
	public:
		Stack(int N=50); //we set default capacity of stack as 50
		~Stack();
		void push(T);	//Push an elemet in the stack
		void pop();	//pop/remove the element at the tos 
		T& top();	//return reference of the top element
		int size();	//return current size of Stack
		bool empty();	//returns true if the stack is Empty
};
//=============Main funciton ==============
int main()
{

	while(true)
	{
		string infix;  						//Infix expression
		cout<<"Enter an Infix Expression: ";
		cin>>infix;
	
		if(infix=="exit") 
			break;

		string postfix = infix2postfix(infix);	//Postfix Expression
		cout<<"The postfix form is: "<<postfix<<endl;
		float ans=evaluate(postfix);			//evaluate the postfix Expresion
		cout<<infix<<"="<<ans<<endl;		//print the final answer
	}

	return EXIT_SUCCESS;
}
//=====================================================================
bool isOperator(char ch)
{
	if( ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^')
		return true;
	else
		return false;

}
//Helper mehtod which converts operators into int so their precdence can be compared
int convertOpToInt (char ch)
{
    if (ch=='+' || ch=='-') return 1;
    if (ch=='*' || ch=='/') return 2;
    if (ch=='^') return 3;
    return 0;
}

//Helper method which compare two operators and return True if first operator
//has less or equal predence than the right operator
bool isleq(char opA, char opB)
{
	return (convertOpToInt(opA)<=convertOpToInt(opB));
}

// Method which converts an Infix Notaiton to a Postfix notation
string infix2postfix(string infix)
{
	Stack <char> mystack;
	string postfix="";

	//1.	Push “(“onto Stack, and add “)” to the end of INFIX.
	infix=infix+')';
	mystack.push('(');

	//2.	Scan INFIX from left to right and repeat Step 3 to 6 for each element of X 
	//until the Stack is empty.3.	If an operand 

	int i=0;
	while(!mystack.empty())
	{	
		char ch = infix[i++];
		//3.	If an operand is found, add it to POSTFIX.
		if (isalnum(ch))
			postfix=postfix+ch;
		//4.	If a left parenthesis is found, push it onto Stack.
		else if(ch=='(')
			mystack.push(ch);
		//5.	If an operator is found, then: 
		else if(isOperator(ch))
		{	//a.	Repeatedly pop from Stack and add to POSTFIX each operator (on the top of Stack) 
			//which has the same precedence as or higher precedence than operator.
			while (isOperator(mystack.top()) and isleq(ch,mystack.top()))
			{
				postfix+=mystack.top();
				mystack.pop();
			}
			//b.	Add operator to Stack.
			mystack.push(ch);
		}
		//.6.	If a ")" is found, then: 
		else if(ch==')')
		{
			//a.	Repeatedly pop from Stack and add to POSTFIX each operator 
			//(on the top of Stack) until a "(" found.
			while(mystack.top()!='(')
			{
				postfix+=mystack.top();
				mystack.pop();
			}
			//b.	Remove the "(" from the stack
			mystack.pop();
		}
	}
	return postfix;
}
// //Method which will evaluate a PostfixExpression and return the result
float evaluate(string postfix)		
{	
	Stack <float> myStack;				//1. Create a stack of type float to store the operands
	for(int i=0; i<postfix.length(); i++)		//2. Scan the postfix expression from left to right for every element
	{
		if(isdigit(postfix[i]))				//	 a. if an operand is found push it to the stack
			myStack.push(int(postfix[i])-48);
		
		else if(isOperator(postfix[i]))		//   b. if an operator is found pop 2 elements from the stack,
		{								//      apply the operator on it and push the result back to the stack
			float a = myStack.top(); myStack.pop();
			float b = myStack.top(); myStack.pop();
			switch(postfix[i])
			{
				case '+': myStack.push(b+a); break;
				case '-': myStack.push(b-a); break;
				case '*': myStack.push(b*a); break;
				case '/': myStack.push(b/a); break;
				case '^': myStack.push(pow(b,a)); break;
			}
		}
	}
	return myStack.top();				//3. return the value from the top of the stack (i.e. the final answer)
}
//================Implemenation of Stack Class===================
template <typename T>
Stack<T>::Stack(int N) : N(N), n(0)
{
	array = new T[N];
}
template <typename T>
Stack<T>::~Stack()
{
	if(array!=nullptr)		delete[] array;
}
template <typename T>
void Stack<T>::push(T element)	//Push an elemet in the stack
{
	if(n<N)		array[n++] = element;
	else 		throw runtime_error("Stack Overflow");
}
template <typename T>
void Stack<T>::pop() //pop/remove the element at the tos 
{
	if(n>0)		n--;
	else 		throw runtime_error("Stack is Empty");
}
template <typename T>
T& Stack<T>::top()	//return reference of the top element
{
	if(n>0)		return array[n-1];
	else 		throw runtime_error("Stack is Empty");	
}
template <typename T>
int Stack<T>::size()	//retuns the current size of the stack
{
	return n;
}
template <typename T>
bool Stack<T>::empty()	//returns true if the stack is empty, false otherwise
{
	return n==0;
}
//=============================================
