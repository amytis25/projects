/* 
 * Stack.h
 *
 * Description: Implementation of a linked list-based Stack ADT class - SHSL list
 * Class Invariant: LIFO order
 *                  Top of Stack located at the back of SHSL list.
 *
 * Author: Simon Schaufele and Amytis Saghafi
 * Date: Feb 16 2024
 */
 
class Stack {

    private:

        //  Description:  Nodes for a singly-linked list - Do not modify!
        class StackNode {
            public:
                int data  ;
                StackNode * next ;  
     
                StackNode (int n){
                    this-> data = n;
                    this -> next = nullptr;
                }
        };


        
/* Put your code here! */       
        StackNode * top ;
        //Stack * elements ;
        unsigned int elementCount = 0; 

    public:

    /* Put your code here! */ 
    // default constructor
    Stack ();
    
    // copy constructor
    Stack (const Stack& old);

    //Destructor
    ~Stack ();
    
    // pre-codition: N/A
    // Postcondition: This Stack is unchanged.
    // Description: Returns true if this Stack is empty otherwise false.
    // Time Efficiency: O(1)
    bool isEmpty ();


    //pre-codition: N/A
    //post-condtion: the integer toBeAdded is added to the top of the stack
    // Description: Adds a new element to the top of this Stack.
    // Returns true if the addition is successful otherwise false.
    // Time Efficiency: O(1)
    bool push (int toBeAdded);

    // Description: Removes the top element of this Stack.
    // Returns true if the removal is successful otherwise false.
    // Precondition: The Stack is not empty.
    // Time Efficiency: O(1)
    bool pop ();

    // Description: Returns the top of this Stack.
    // Precondition: The Stack is not empty.
    // Postcondition: This Stack is unchanged.
    // Exceptions: Throws EmptyStackException if this Stack is empty.
    // Time Efficiency: O(1)
    int peek ();

    

  


};
