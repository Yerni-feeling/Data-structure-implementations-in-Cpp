//============================================================================
// Name         : MyVector.cpp
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 16-03-2019
// Date Modified: 16-02-2020 
// Copyright    : All rights are reserved
// Description  : Vector implmentation in C++
//============================================================================
#include<iostream>
#include<cstdlib>
#include <stdexcept>

using namespace std;
template <typename T>
class MyVector
{
	private:
		T *data;						//pointer to int(array) to store elements
		int v_size;						//current size of vector (number of elements in vector)
		int v_capacity;					//capacity of vector
	public:
		MyVector();						//No argument constructor
		MyVector(int cap);				//One Argument Constructor
		MyVector(MyVector& other);		//Copy Constructor
		~MyVector();					//Destructor
		void push_back(T element);		//Add an element at the end of vector
		int size() const;				//Return current size of vector
		int capacity() const;			//Return capacity of vector
		bool empty() const; 			//Rturn true if the vector is empty, False otherwise
		T& at(int index); 				//return reference to the element at index
		const T& front();				//Returns reference to the first element in the vector
		const T& back();				//Returns reference to the Last element in the vector
		const MyVector<T>& operator=(const MyVector<T>& other);		//overloaded assignment operator

};
//=======================================
int main()
{

	
	MyVector<int> v1;


	cout<<"Size: "<<v1.size()<<endl;
	cout<<"Capacity: "<<v1.capacity()<<endl;

	for(int i=0; i<10; i++)
		v1.push_back(i);
	
	MyVector<int> v2(v1);
	//v2=v1;
	v1.at(1)=100;		// modify v1;
	
	cout<<"Front: "<<v1.front()<<endl;
	cout<<"Back: "<<v1.back()<<endl;
	cout<<"Size: "<<v1.size()<<endl;
	cout<<"Capacity: "<<v1.capacity()<<endl;

	for(int i=0; i<v1.size(); i++)
		cout<<"v1.at("<<i<<")="<<v1.at(i)<<"\t v2.at("<<i<<")="<<v2.at(i)<<endl;

	return EXIT_SUCCESS;
}
//========================================
template <typename T>
MyVector<T>::MyVector()
{
	this->v_size=0;
	this->v_capacity=0;
}
//========================================
template <typename T>
MyVector<T>::MyVector(int cap)
{
	this->v_size=0;
	this->v_capacity=cap;
	this->data = new T[v_capacity];
}
//========================================
template <typename T>
MyVector<T>::MyVector(MyVector &other)
{
		this->v_size = other.v_size;
		this->v_capacity = other.v_capacity;
		this->data = new T[v_capacity];
		for(int i=0; i<v_size; i++)
			this->data[i]=other.data[i];
}
//========================================
template <typename T>
MyVector<T>::~MyVector()
{
	delete[] this->data;
}
//========================================
template <typename T>
int MyVector<T>::size() const
{
	return this->v_size;
}
//========================================
template <typename T>
int MyVector<T>::capacity() const
{
	return this->v_capacity;
}
//========================================
template <typename T>
bool MyVector<T>::empty() const
{
	return (this->v_size == 0);
}
//========================================
template <typename T>
void MyVector<T>::push_back(T element)
{

	if(this->v_size==0)								//if first elements
	{
		this->v_capacity=1;
		this->data = new T[v_capacity];
	}
	else if(this->v_size>=this->v_capacity-1)
	{
		v_capacity = v_capacity*2;					//doube the Capacity
		T *data2=new T[v_capacity];				//allocate space in heap for bigger array

		for(int i=0; i<v_size; i++)	//copy elements to array
			data2[i]=data[i];

		delete[] data;	//delete original/old array

		data = data2;	//let pointer point to new/bigger array

	}
	this->data[v_size++]=element;  ///add new element to the array
}
//========================================
template <typename T>
T& MyVector<T>::at(int index)
{
	if(index>=0 and index<v_size)
		return data[index];
	else 
		 throw out_of_range("Vector Index out of range...!");
}
//========================================
template <typename T>
const T& MyVector<T>::front()
{
	if(v_size>0)
		return data[0];
	else
		throw out_of_range("Vector is Empty..");
}
//========================================
template <typename T>
const T& MyVector<T>::back()
{
	if(v_size>0)
		return data[v_size-1];
	else
		throw out_of_range("Vector is Empty..");
}
//======================================
template <typename T>
const MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other)
{
	if(this != &other)
	{
		delete[] this->data; 					//delete exisiting array
		this->v_size = other.v_size;
		this->v_capacity = other.v_capacity;
		this->data = new T[v_capacity];
		for(int i=0; i<v_size; i++)				//copy contents from other.data to this->data;
			this->data[i]=other.data[i];
	}
	return *this;
}
//=====================================