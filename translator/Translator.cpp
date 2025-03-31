/*
 * Translator.cpp
 * 
 * Description: Dictonary data collection ADT class.
 *              BST-based implementation.
 *              Duplicated elements not allowed.
 *              
 * Author: Amytis Saghafi and Simon Schaufele
 * Date of last modification: Mar 15 2024
 */
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <istream>
#include "BST.h"
#include "Dictionary.h"
#include "WordPair.h"
#include "ElementAlreadyExistsException.h"
#include "ElementDoesNotExistException.h"
#include "EmptyDataCollectionException.h"
#include "UnableToInsertException.h"

using std::cin; 
using std::cout;
using std::endl;
using std::ifstream;
using std::nothrow;

// prototypes
bool menu ();
void newWord();
WordPair search ();
void getDictionary(string filename);
void visitWordPair(WordPair &wp);

//global variable

Dictionary *myDict = new(nothrow) Dictionary();

//functions
void visitWordPair(WordPair &wp){
  cout << wp << endl;
}

bool menu (){
   
   char input = 0; 
   bool done = false;
   cout << "Choose an option:" << endl;
        cout << "[1] enter a new word + translation" << endl;
        cout << "[2] find a translation" << endl;
        cout << "[3] view dictionary" << endl;
        cout << "[4] exit program" << endl;
        cout << "select a number corresponding to an action please: ";

        cin >> input;
        cout << endl;
        
         
       switch (input){
            case '1' : newWord(); break;
            case '2': search(); break;
            case '3' : myDict-> displayContent(visitWordPair); break;
            case '4' : cout << "exiting program ... bye !" << endl;
                        done = true;
                        break;
            
        }
        return done; 
}
void newWord (){
   string english;
   string translation;

   cout << "enter new word in english:";
   cin >> english;
   cout << endl;

   cout << "enter " << english << "'s translation:";
   cin >> translation;
   cout << endl;

  WordPair * newElement = new WordPair(english , translation);
try { 
    myDict-> put(*newElement);
    cout << *newElement << " was added to dictionary." << endl;
   cout << "new number of words is: " << myDict ->getElementCount() << endl;
   }
catch (ElementAlreadyExistsException & e){
  cout << "word already exists!"<< endl;
}
}

WordPair search (){
   string target;
   WordPair * found = nullptr;

   cout << "enter english word to search for: ";
   cin >> target;
   cout << endl;
   WordPair * targetElement;
   try {
      targetElement = new WordPair(target);
      found = new WordPair(myDict->get(*targetElement));
      cout << *found << "was found."<< endl;
      return *found;
      }
      catch(ElementDoesNotExistException & anException) {
            cout << "*** NOT FOUND! *** : " << anException.what() << endl;
      }
return *found;
}

void getDictionary(string filename){
     string aLine = "";
    string aWord = "";
    string englishW = "";
    string translationW = "";
    string delimiter = ":";
    size_t pos = 0;
    WordPair translated;

          ifstream myfile(filename);
      if (myfile.is_open()) {
        cout << "Reading from a file:" << endl;  // For debugging purposes
        while ( getline (myfile,aLine) ) {
          pos = aLine.find(delimiter);    
          englishW = aLine.substr(0, pos);
          aLine.erase(0, pos + delimiter.length());
          translationW = aLine;
          WordPair aWordPair(englishW, translationW);
          
		  // insert aWordPair into "testing" using a try/catch block
      
      
        //cout << "inserting : " << aWordPair;
        try{
          myDict->put(aWordPair);
        }
        catch (ElementAlreadyExistsException & e){
          //it already exists
        }
        
        //cout << "here"<< endl;
    
      //cout << "elementcount:" << testing -> getElementCount()<< endl;
        }
      }
        myfile.close();

}

 int main () {
   char input = 0;
   bool done = false;
   string filename;
   cout << "Enter the filename: ";
   cin >> filename;
   cout << endl;
   getDictionary(filename);
   cout << myDict-> getElementCount() << " words in the dictionary"<< endl;
while (!done){
   cout << "input 1 to open menu or 0 to close the program: " ;
   cin >> input;
     switch (input){
            case '1' : done = menu(); break;
            case '0' : cout << "exiting program ... bye !" << endl;
                        done = true;
                        break;
     } 
     }
    return 0;
 }