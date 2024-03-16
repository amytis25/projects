/*
 * BST.cpp
 * 
 * Description: Binary Search Tree data collection ADT class.
 *              Link-based implementation.
 *              Duplicated elements are not allowed.
 *
 * Class invariant: It is always a BST.
 * 
 * Author: Simon Schaufele and Amytis Saghafi
 * Date of last modification: Mar 15 2024
 */
 
#include "BST.h"
#include "WordPair.h"
#include <iostream>
#include <stack>
#include <functional>
using std::cout;
using std::endl;
using std::nothrow;


// You cannot change the prototype of the public methods of this class.
// Remember, if you add public methods to this class, our test driver 
// - the one with which we will mark this assignment - 
// will not know about them since, in order to create it, we will have 
// used only the public method prototypes below.


/* Constructors and destructor */

   // Default constructor
   BST::BST() { }            

   // Copy constructor
   BST::BST(const BST & aBST) {
    // Define a lambda function for recursive tree traversal and deletion
    std::function<void(BSTNode*)> deleteTree = [&](BSTNode* current) {
        if (current == nullptr)
            return;

        // Recursively delete the left and right subtrees
        deleteTree(current->left);
        deleteTree(current->right);

        // Delete the current node
        delete current;
    };

    // Define a lambda function for deep copy within the copy constructor
    std::function<BSTNode*(BSTNode*)> deepCopy = [&](BSTNode* current) -> BSTNode* {
        if (current == nullptr)
            return nullptr;

        // Create a new node with the same data as the current node
        BSTNode* newNode = nullptr;
        try {
            newNode = new BSTNode(current->element);
        } catch (std::bad_alloc& e) {
            // If memory allocation fails, throw an exception
            throw UnableToInsertException("Unable to allocate memory for new node.");
        }

        // Recursively copy the left and right subtrees
        try {
            newNode->left = deepCopy(current->left);
            newNode->right = deepCopy(current->right);
        } catch (...) {
            // If any other exception occurs during copying, delete the partially copied tree and re-throw
            deleteTree(newNode); // Delete partially copied tree
            throw; // Re-throw the exception
        }

        return newNode;
    };

    try {
        // Call the locally defined deepCopy function to copy the tree rooted at aBST.root
        root = deepCopy(aBST.root);
    } catch (...) {
        // If any exception occurs during the deep copy process, re-throw
        throw;
    }

    // Copy the element count
    elementCount = aBST.elementCount;
}

/* Getters and setters */

   // Description: Returns the number of elements currently stored in the binary search tree.   
   // Postcondition: This method does not change the binary search tree.
   // Time efficiency: O(1)
   unsigned int BST::getElementCount() const {     

     return this->elementCount;
	 
   }
   

/* BST Operations */

   // Description: Inserts an element into the binary search tree.
   //              This is a wrapper method which calls the recursive insertR( ).
   // Precondition: "newElement" does not already exist in the binary search tree.
   // Exception: Throws the exception "UnableToInsertException" when newElement 
   //            cannot be inserted because the "new" operator failed. 
   // Exception: Throws the exception "ElementAlreadyExistsException" 
   //            if "newElement" already exists in the binary search tree.
   // Time efficiency: O(log2 n)   
   void BST::insert(WordPair & newElement) {
    try {
        // Check if the tree is empty
        if (root == nullptr) {
            // Create a new node for the root
            root = new BSTNode(newElement);
            // Increment the element count
            elementCount++;
        } else {
            // Call the recursive insertR method to insert the element
            if (!insertR(new BSTNode(newElement), root)) {
                // If insertR returns false, it means the element already exists
                throw ElementAlreadyExistsException("Element already exists in the binary search tree.");
            }
        }
    } catch (std::bad_alloc& e) {
        // If memory allocation fails, throw an UnableToInsertException
        throw UnableToInsertException("Unable to insert element due to memory allocation failure.");
    }
}
   
   // Description: Recursive insertion into a binary search tree.
   //              Returns true when "anElement" has been successfully inserted into the 
   //              binary search tree. Otherwise, returns false.
   bool BST::insertR(BSTNode * newBSTNode, BSTNode * current) {  
    // Base case: If the current node is null, insert the new node here
    if (current == nullptr) {
        return true; // Return true to indicate successful insertion
    }
    
    // Compare the element of the new node with the element of the current node
    if (newBSTNode->element < current->element) {
        // If the new node should be inserted into the left subtree
        if (current->left == nullptr) {
            // If the left child is null, insert the new node here
            current->left = newBSTNode;
            elementCount++; // Increment the element count
            return true;
        } else {
            // Recursively insert into the left subtree
            return insertR(newBSTNode, current->left);
        }
    } else if (newBSTNode->element > current->element) {
        // If the new node should be inserted into the right subtree
        if (current->right == nullptr) {
            // If the right child is null, insert the new node here
            current->right = newBSTNode;
            elementCount++; // Increment the element count
            return true;
        } else {
            // Recursively insert into the right subtree
            return insertR(newBSTNode, current->right);
        }
    } else {
        // Element already exists, cannot insert
        return false; // Return false to indicate failure
    }
}
   // Description: Retrieves "targetElement" from the binary search tree.
   //              This is a wrapper method which calls the recursive retrieveR( ).
   // Precondition: Binary search tree is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //            if the binary search tree is empty.
   // Exception: Propagates the exception "ElementDoesNotExistException" 
   //            thrown from the retrieveR(...)
   //            if "targetElement" is not found in the binary search tree.
   // Postcondition: This method does not change the binary search tree.
   // Time efficiency: O(log2 n)
   WordPair& BST::retrieve(WordPair & targetElement) const {
      
     if (elementCount == 0)  {
        throw EmptyDataCollectionException("Binary search tree is empty.");
    }
	WordPair* translated = nullptr;
    try {translated = &retrieveR(targetElement, root);
    } catch (const ElementDoesNotExistException &e) {
            // Handle the case where the element does not exist in the BST
            //cout << "Element not found in the BST" << endl;
            throw ElementDoesNotExistException ();
        } catch (const EmptyDataCollectionException &e) {
            // Handle the case where the BST is empty
            //cout << "BST is empty" << endl;
            throw EmptyDataCollectionException ();
        } catch (...) {
            // Handle any other exceptions
            //cout << "An error occurred during retrieval" << endl;
        }

    
     return *translated;
   }

   // Description: Recursive retrieval from a binary search tree.
   // Exception: Throws the exception "ElementDoesNotExistException" 
   //            if "targetElement" is not found in the binary search tree.
   // Postcondition: This method does not change the binary search tree.
   WordPair& BST::retrieveR(WordPair & targetElement, BSTNode * current) const {

    // If the current node is null, the target element is not found
    if (current == nullptr) {
        // Throw an exception to indicate that the element does not exist
        throw ElementDoesNotExistException("Element does not exist in the binary search tree.");
    }

    // Compare the target element with the data in the current node
    if (targetElement < current->element) {
        // If the target element is less than the data in the current node,
        // recursively search in the left subtree
        return retrieveR(targetElement, current->left);
    } else if (targetElement > current->element) {
        // If the target element is greater than the data in the current node,
        // recursively search in the right subtree
        return retrieveR(targetElement, current->right);
    } else {
        // If the target element is equal to the data in the current node,
        // return the data in the current node
        return current->element;
    }
}
         
   
   // Description: Traverses the binary search tree in order.
   //              This is a wrapper method which calls the recursive traverseInOrderR( ).
   //              The action to be done on each element during the traverse is the function "visit".
   // Precondition: Binary search tree is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //            if the binary search tree is empty.
   // Postcondition: This method does not change the binary search tree.
   // Time efficiency: O(n)     
   void BST::traverseInOrder(void visit(WordPair &)) const {
     
     if (elementCount == 0)  
       throw EmptyDataCollectionException("Binary search tree is empty.");

     traverseInOrderR(visit, root);
     
    return;
   }

   // Description: Recursive in order traversal of a binary search tree.   
   // Postcondition: This method does not change the binary search tree. 
   void BST::traverseInOrderR(void visit(WordPair &), BSTNode* current) const { 
   
    if (current != nullptr) {

    
    // Recursively traverse the left subtree
    traverseInOrderR(visit, current->left);


    // Visit the current node by calling the visit function
    visit(current->element);


    // Recursively traverse the right subtree
    traverseInOrderR(visit, current->right);
    }
}