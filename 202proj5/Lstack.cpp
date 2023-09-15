/*
** File: Lstack.cpp
** Assignment Name: Project 5 – UMBC Process Manager
** Author: Nikki Cayas
** Date: 12/5/22
** Course/ Section: CMSC 202 Section 52 (FA2022)
** E-mail: ncayas1@umbc.edu
** Description: This cpp file defines each of the methods for the Lstack class
*/

#ifndef LSTACK_CPP
#define LSTACK_CPP
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Templated node class used in templated linked list
template <class T>
class Node {
   public:
  Node( const T& data ); //Constructor
  T& GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data; //Templated data for node
  Node<T>* m_next; //Templated node pointer to next node
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = nullptr;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
   return m_data;
}

//Sets the data in a Node
template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Lstack {
 public:
  // Name: Lstack() (Linked List Stack) - Default Constructor
  // Desc: Used to build a new templated stack (as a linked list) m_head = top
  // Preconditions: None
  // Postconditions: Creates a new lstack where m_head points to nullptr and m_size = 0
  // Required
  Lstack();
  // Name: ~Lstack() - Destructor
  // Desc: Used to destruct a Lstack
  // Preconditions: There is an existing lstack with at least one node
  // Postconditions: An lstack is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks. (Allowed to use Clear in this function)
  // Required
 ~Lstack();
  // Name: Lstack (Copy Constructor)
  // Preconditions: Creates a copy of existing LStack
  //                Requires an existing Lstack
  // Hint: Make sure that the copy is not inverted
  // Postconditions: Copy of existing Lstack
  // Required
  Lstack(const Lstack&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Requires two Lstacks holding the same type of data
  //                After running, both stacks are identical with no memory loss
  //                Requires an existing Lstack
  // Postconditions: Two identical Lstack
  // Hint: Make sure that the destination Lstack has the same data in the same order as source
  // Required
  Lstack<T>& operator= (Lstack&);
  // Name: Push
  // Preconditions: Takes in data. Creates new node. 
  //                Requires an existing Lstack
  // Postconditions: Adds a new node to the top of the lstack.
  // Required
  void Push(const T&);
  // Name: Pop
  // Preconditions: Requires an existing Lstack with at least one node 
  // Postconditions: Removes top node in the lstack.
  // Assume that the Lstack has at least one node (Will check prior to call)
  // Required
  void Pop();
  // Name: Display
  // Preconditions: Outputs the lstack.
  // Postconditions: Displays the data in each node of lstack
  // Required (used only for testing lstack_test)
  void Display();
  // Name: Top
  // Preconditions: Requires an existing Lstack
  // Postconditions: Returns whatever data is on top
  // Required
  T Top();
  // Name: IsEmpty
  // Preconditions: Requires an existing Lstack
  // Postconditions: Returns true if the Lstack is empty else false.
  // Required
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires an existing Lstack
  // Postconditions: Returns m_size
  // Required
  int GetSize();
  // Name: Find()
  // Preconditions:  Requires an existing Lstack
  // Postconditions: Iterates and if it finds the thing, returns index, else -1
  // Required
  int Find(T&);
  // Name: Clear
  // Preconditions:  Requires an existing Lstack
  // Postconditions: Removes all nodes in Lstack
  // Required
  void Clear();
  // Name: At(int)
  // Preconditions:  Requires an existing Lstack
  // Postconditions: Returns the data at a specific index;
  //                 Index will be checked prior to call (assume int is valid)
  // Required
  T At (int x);
private:
  Node <T> *m_head; //Node pointer for the head
  int m_size; //Number of nodes in stack
};

//**********Implement Lstack Class Here***********
//**********All Functions Are Required Even If Not Used for Processor**************

// Name: Lstack() (Linked List Stack) - Default Constructor
// Desc: Used to build a new templated stack (as a linked list) m_head = top
// Preconditions: None
// Postconditions: Creates a new lstack where m_head points to nullptr and m_size = 0
// Required
template <class T>
Lstack<T>::Lstack()
{
   m_head = nullptr;
   m_size = 0;
}
// Name: ~Lstack() - Destructor
// Desc: Used to destruct a Lstack
// Preconditions: There is an existing lstack with at least one node
// Postconditions: An lstack is deallocated (including dynamically allocated nodes)
//                 to have no memory leaks. (Allowed to use Clear in this function)
// Required
template <class T>
Lstack<T>::~Lstack()
{
   //creates pointer to traverse thru linked list
   Node<T>* curr = m_head;
   //iterates thru linked list
   while (curr != nullptr)
   {
      //curr pointer points to next node & then previous node is deallocated
      m_head = curr;
      curr = curr -> GetNext();
      delete m_head;
   }
   //linked list values are set back to their default values of nullptr or 0
   m_head = nullptr;
   m_size = 0;
}
// Name: Lstack (Copy Constructor)
// Preconditions: Creates a copy of existing LStack
//                Requires an existing Lstack
// Hint: Make sure that the copy is not inverted
// Postconditions: Copy of existing Lstack
// Required
template <class T>
Lstack<T>::Lstack(const Lstack& other)
{
   //clears current lstack
   Clear();
   //sets current m_size equal to the new m_size
   m_size = other.m_size;
   //creates curr1 pointer that will iterate through the other lstack
   Node<T>* curr1 = other.m_head;
   //allocates new m_head for current stack based on m_head of the other lstack
   Node<T>* newHead = new Node<T> (curr1 -> GetData());
   m_head = newHead;
   //creates curr2 pointer that will iterate through the current lstack
   Node<T>* curr2 = m_head;
   //iterates through other lstack
   while (curr1 -> GetNext() != nullptr)
   { 
      //allocates new node based on data within the other lstack and connects it to the last node in the current lstack
      curr1 = curr1 -> GetNext();
      Node<T>* newNode = new Node<T>(curr1 -> GetData());
      curr2 -> SetNext(newNode);
      curr2 = curr2 -> GetNext();
   }
}
// Name: operator= (Overloaded Assignment Operator)
// Preconditions: Requires two Lstacks holding the same type of data
//                After running, both stacks are identical with no memory loss
//                Requires an existing Lstack
// Postconditions: Two identical Lstack
// Hint: Make sure that the destination Lstack has the same data in the same order as source
// Required
template <class T>
Lstack<T>& Lstack<T>::operator= (Lstack& other)
{
   if (this != &other)
   {
      //clears current lstack
      Clear();
      //sets current m_size equal to the new m_size
      m_size = other.m_size;
      //creates curr1 pointer that will iterate through the other lstack
      Node<T>* curr1 = other.m_head;
      //allocates new m_head for current stack based on m_head of the other lstack
      Node<T>* newHead = new Node<T> (curr1 -> GetData());
      m_head = newHead;
      //creates curr2 pointer that will iterate through the current lstack
      Node<T>* curr2 = m_head;
      //iterates through other lstack
      while (curr1 -> GetNext() != nullptr)
      { 
         //allocates new node based on data within the other lstack and connects it to the last node in the current lstack
         curr1 = curr1 -> GetNext();
         Node<T>* newNode = new Node<T>(curr1 -> GetData());
         curr2 -> SetNext(newNode);
         curr2 = curr2 -> GetNext();
      }
   }
   return *this;
}
// Name: Push
// Preconditions: Takes in data. Creates new node. 
//                Requires an existing Lstack
// Postconditions: Adds a new node to the top of the lstack.
// Required
template <class T>
void Lstack<T>::Push(const T& data)
{
   //dynamically allocates new node
   Node<T>* newNode = new Node(data);
   //inserts node at the beginning of the linked list
   newNode -> SetNext(m_head);
   m_head = newNode;
   //increments m_size
   m_size++;
}
// Name: Pop
// Preconditions: Requires an existing Lstack with at least one node 
// Postconditions: Removes top node in the lstack.
// Assume that the Lstack has at least one node (Will check prior to call)
// Required
template <class T>
void Lstack<T>::Pop()
{
   //creates temp variable
   Node<T>* top = m_head;
   //removes node at the beginning of the linked list
   m_head = m_head -> GetNext();
   delete top;
   //decrements m_size
   m_size--;
}
// Name: Display
// Preconditions: Outputs the lstack.
// Postconditions: Displays the data in each node of lstack
// Required (used only for testing lstack_test)
template <class T>
void Lstack<T>::Display()
{
   //creates local count variable
   int count = 0;
   Node<T>* curr = m_head;
   //iterates through linked list
   while (curr != nullptr)
   {
      count++;
      //displays each node's number and its data
      cout << "Node " << count << ": . " << curr -> GetData();
      curr = curr -> GetNext();
   }
}
// Name: Top
// Preconditions: Requires an existing Lstack
// Postconditions: Returns whatever data is on top
// Required
template <class T>
T Lstack<T>::Top()
{
   return m_head -> GetData();
}
// Name: IsEmpty
// Preconditions: Requires an existing Lstack
// Postconditions: Returns true if the Lstack is empty else false.
// Required
template <class T>
bool Lstack<T>::IsEmpty()
{
   return (m_head == nullptr);
}
// Name: GetSize
// Preconditions: Requires an existing Lstack
// Postconditions: Returns m_size
// Required
template <class T>
int Lstack<T>::GetSize()
{
   return m_size;
}
// Name: Find()
// Preconditions:  Requires an existing Lstack
// Postconditions: Iterates and if it finds the thing, returns index, else -1
// Required
template <class T>
int Lstack<T>::Find(T& data)
{
   //creates temp variable for iterating
   Node<T>* curr = m_head;
   //iterates through linked list
   for (int i = 0; i < m_size; i++)
   {
      //if "thing" is found, index number is returned
      if (curr -> GetData() == data)
      {
         return i;
      }
      curr = curr -> GetNext();
   }
   //if "thing" isnt found, -1 is returned
   return -1;
}
// Name: Clear
// Preconditions:  Requires an existing Lstack
// Postconditions: Removes all nodes in Lstack
// Required
template <class T>
void Lstack<T>::Clear()
{
   //creates pointer to traverse through linked list
   Node<T>* curr = m_head;
   //iterates thru linked list
   while (curr != nullptr)
   {
      //curr pointer points to next node & then previous node is deallocated
      m_head = curr;
      curr = curr -> GetNext();
      delete m_head;
   }
   //linked list values are set back to their default values of nullptr or 0
   m_head = nullptr;
   m_size = 0;
}
// Name: At(int)
// Preconditions:  Requires an existing Lstack
// Postconditions: Returns the data at a specific index;
//                 Index will be checked prior to call (assume int is valid)
// Required
template <class T>
T Lstack<T>::At (int x)
{
   //creates temp node that will traverse through the list
   Node<T>* curr = m_head;
   //iterates through the list until the given index is reached
   for (int i = 0; i < x; i++)
   {
      curr = curr -> GetNext();
   }
   //returns the data of the node at that index
   return curr -> GetData();
}

#endif
