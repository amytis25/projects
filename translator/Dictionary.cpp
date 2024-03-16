/*
 * Dictionary.cpp
 * 
 * Description: Dictonary data collection ADT class.
 *              BST-based implementation.
 *              Duplicated elements not allowed.
 *              
 * Author: Amytis Saghafi and Simon Schaufele
 * Date of last modification: Mar 15 2024
 */

#include "Dictionary.h"
#include <iostream>
using std:: cout;


 // Constructor and destructor:
   Dictionary::Dictionary() {  // Default constructor
    keyValuePairs = new BST();
   }  
   Dictionary::~Dictionary() { 
  
    }                            // Destructor 
   
   // Dictionary operations
      
   // Description: Returns the number of elements currently stored in the Dictionary.
   // Postcondition: This method does not change the Dictionary.
   unsigned int Dictionary::getElementCount() const{
    if (keyValuePairs == nullptr){
      return 0;
    } else {
      return keyValuePairs -> getElementCount();
    }
   }
    
   // Description: Puts "newElement" (association of key-value) into the Dictionary.
   // Precondition: "newElement" does not already exist in the Dictionary.
   //               This is to say: no duplication allowed.
   // Exception: Throws the exception "UnableToInsertException" 
   //            when newElement cannot be inserted in the Dictionary.  
   // Exception: Throws the exception "ElementAlreadyExistsException" 
   //            if "newElement" already exists in the Dictionary.  
   void Dictionary::put(WordPair & newElement){
     try {
        keyValuePairs->insert(newElement);
    } catch (const ElementAlreadyExistsException &e) {
              //cout << "Element already exists: " << newElement << endl;
          } catch (const UnableToInsertException &e) {
              //cout << "Unable to insert element: " << newElement << endl;
          }
}
   // Description: Gets "newElement" (i.e., the associated value of a given key) 
   //              from the Dictionary.
   // Precondition: Dictionary is not empty.
   // Exception: Throws the exception ElementDoesNotExistException
   //            if the key is not found in the Dictionary.
   // Exception: Throws the exception EmptyDataCollectionException if the Dictionary is empty.
   // Postcondition: This method does not change the Dictionary.
   WordPair & Dictionary::get(WordPair & targetElement) const{
    try {
        return keyValuePairs->retrieve(targetElement);
      } catch (const ElementDoesNotExistException &e) {
            // Handle the case where the element does not exist in the BST
            //cout << "Element not found in the BST" << endl;
            throw ElementDoesNotExistException();
        } catch (const EmptyDataCollectionException &e) {
            // Handle the case where the BST is empty
            //cout << "BST is empty" << endl;
            throw EmptyDataCollectionException ();
        } catch (...) {
            // Handle any other exceptions
            //cout << "An error occurred during retrieval" << endl;
        }
        return targetElement;
}
   // Description: Prints the content of the Dictionary.
   // Precondition: Dictionary is not empty.
   // Exception: Throws the exception EmptyDataCollectionException if the Dictionary is empty.
   // Postcondition: This method does not change the Dictionary.
   void Dictionary::displayContent(void visit(WordPair &)) const{
    try {
        keyValuePairs->traverseInOrder(visit);
    } catch (EmptyDataCollectionException& e) {
        cout << "Dictionary is empty!" << endl;
    }
}
 // end Dictionary