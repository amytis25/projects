/* 
 * Stack.cpp
 *
 * Description: Implementation of a linked list-based Stack ADT class - SHSL list
 * Class Invariant: LIFO order
 *                  Top of Stack located at the back of SHSL list.
 *
 * Author: Simon Schaufele and Amytis Saghafi
 * Date: Feb 16 2024
 */
 
 #include "Stack.h"
 #include <iostream>

using std::cout;
using std::endl;
using std::runtime_error;
 //constructor

 Stack::Stack() : topNode(nullptr){ }

 //Destructor
 Stack::~Stack(){
    while (topNode != nullptr) {
        StackNode* temp = topNode;
        topNode = topNode -> next;
        delete temp;
    }
 }


void Stack::push(int val) {
    StackNode* newNode = new StackNode(); // Create a new node
    newNode->data = val; // Assign the value to the data member of the new node
    newNode->next = nullptr; // Ensure the new node points to nullptr as it's at the back of the list
    

    if (isEmpty()) {
        topNode = newNode; // If the list is empty, set topNode to newNode
    } else {
        newNode->next = topNode; // Set the next pointer of the new node to the current topNode
        topNode = newNode; // Update topNode to point to the newly pushed node
    }
}

//Pop removes the top element from the stack
int Stack::pop()  {
    // Check if the stack is empty
    if (isEmpty()) {
        throw runtime_error("Stack is empty");
    }

    // Retrieve the top element's value
    int poppedValue = topNode->data;

    // Update topNode to point to the next node
    StackNode* temp = topNode;
    topNode = topNode->next;

    // Delete the node containing the popped value
    delete temp;

    // Return the popped value
    return poppedValue;
}
//Peek to return the top element
int Stack::peek() const {
    if (isEmpty()) {
        throw runtime_error("Stack is empty");
    }
    return topNode -> data;
}

//Check if stack is empty
bool Stack::isEmpty() const {
    return topNode == nullptr;
}