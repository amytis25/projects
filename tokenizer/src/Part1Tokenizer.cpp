//============================================================================
//
//% Student Name 1: Amytis Saghafi
//% Student 1 #: 301455814
//% Student 1 asa414 (email): stu1 (asa414@sfu.ca)
//
//
//% Below, edit to list any people who helped you with the code in this file,
//%      or put <none> if nobody helped (the two of) you.
//
// Helpers: _everybody helped us/me with the assignment (list names or put <none>)_<none>_
//
// Also, list any resources beyond the course textbook and the course pages on Piazza
// that you used in making your submission.
//
// Resources:  _<material provided during lecture and under files on canvas>__________
//
//%% Instructions:
//% * Put your name(s), student number(s), userid(s) in the above section.
//% * Enter the above information in Test.cpp if you are submitting that file too.
//% * Edit the "Helpers" line and "Resources" line.
//% * Your group name should be "P1_<userid1>_<userid2>" (eg. P1_stu1_stu2)
//% * Form groups as described at:  https://courses.cs.sfu.ca/docs/students
//% * Submit one or two files to courses.cs.sfu.ca
//
// Name        : Part1Tokenizer.cpp
// Description : Tokenizer
// Original Version Copyright (c) 2023 Simon Fraser University
//============================================================================
#include <iostream>
#include <istream>
#include "Part1Tokenizer.hpp"

using namespace std;

// Accepts a stream and returns a vector of tokens with any remaining preprocessing lines stripped out
// Input: a stream
// Output: a vector of tokens
vector<string> tokenizeCodeStrip(istream& code) {

	// *** Fill in implementation and likely delete the below lines ***
	vector<string> resultvec;
	string linefromcode;
	const string WS {" \t"};
  	const string operationsigns {"=+-;,<>~/%*|"};
  	const string semicolon {";"};
  	const string digits {"0123456789"};
  	const string decimal {"."};
  	const string naturale {"eE"};
   const string quotationmarks {"\"\""};
	const string hashtag {"#"};
	const string oroperator {"||"};
	const string singlequote {"'"};

	while (!code.eof()){
      getline(code,linefromcode);

      //declarations
      string::size_type index1{0};
      string::size_type whitespace{0};
      string::size_type indexop{0};
      string::size_type word{0};
      string::size_type operand{0};
      string::size_type firstquote {0};
      string::size_type lastquote {0};
      string::size_type firstdigit {0};
      string::size_type lastdigit {0};
      string::size_type nextdigit {0};
      string::size_type enddigit {0};
      string::size_type firstor {0};
      string::size_type lastor {0};
      string::size_type isthereE {0};
      string::size_type nextop {0};
      string::size_type wheredot {0};
      string::size_type ishashtag {0};
      string::size_type afterfirstq {0};
      string::size_type afterlastq {0};
      string::size_type wheresemi {0};
      string::size_type aftersemi {0};
      string::size_type apostrophe {0};
      string::size_type notapo{0};
      string::size_type nextapo{0};
      string::size_type lastnotq{0};
      string::size_type afterdecimal{0};
      string::size_type enddecimal{0};
      string::size_type beginingdecimal{0};



      while (index1 < linefromcode.length()){

         word = {linefromcode.find_first_not_of(WS, index1)};// find first character
         whitespace = linefromcode.find_first_of(WS, word);// find first white space after character

         // punctuation
         wheredot = linefromcode.find_first_of(decimal , index1); //find the first "."
         apostrophe = linefromcode.find_first_of(singlequote , index1); // find the first "'"
         notapo = linefromcode.find_first_not_of(singlequote , apostrophe);// find first not of "'"
         nextapo = linefromcode.find_first_of(singlequote , notapo); // find the next "'"

         // operation signs
         operand = {linefromcode.find_first_of(operationsigns, index1)};// find first operand
         indexop = linefromcode.find_first_not_of(operationsigns, operand);// find if multiple operands
         nextop = linefromcode.find_first_of(operationsigns, indexop);//find the next set of operation signs

         //quotation marks ""
         firstquote = linefromcode.find_first_of(quotationmarks, index1); // first quotation mark
         afterfirstq = firstquote+1;// after "  \"  "
         lastquote = linefromcode.find_first_of(quotationmarks, afterfirstq); // next quotation mark
         lastnotq = linefromcode.find_first_not_of(quotationmarks, lastquote); //find end of quote ( after "  \"  " )
            //makes sure lastnotq value is usuable
            if (lastnotq > linefromcode.length()){
               afterlastq = lastquote+1;
            }
            else {
               afterlastq = lastnotq;
            }

         // numbers
         firstdigit = linefromcode.find_first_of(digits,index1); // first number
         lastdigit = linefromcode.find_first_not_of(digits,firstdigit); //end of number or first not number
         nextdigit = linefromcode.find_first_of(digits,lastdigit); // first of the next number
         enddigit = linefromcode.find_first_not_of(digits,nextdigit); // end of the next number or first not number
         afterdecimal = wheredot+1; //the place after "."
         enddecimal = lastdigit+1; //the place after "." at the end of number
         beginingdecimal = firstdigit - 1; // the place before "." at the begining of the number

         firstor = linefromcode.find_first_of(oroperator,index1); // first or
         lastor = linefromcode.find_first_not_of(oroperator,firstor); //end last or

         isthereE = linefromcode.find_first_of(naturale, firstdigit); // is there a exponents in the number
         ishashtag = linefromcode.find_first_of(hashtag, index1); // first hashtag

         wheresemi = linefromcode.find_first_of(semicolon, index1); // where is the first semicolon
         aftersemi = linefromcode.find_first_not_of(semicolon, wheresemi); // where is the first not semicolon


         // # if its for the preprocessor skip line
         if (ishashtag == word){
            break;
         }
         // if string starts with "'"
         else if (apostrophe == word){
            // if another "'" isn't found go to the next whitespace and disregard every character in between
            if (nextapo > linefromcode.length()){
            index1 = whitespace;
            resultvec.push_back(linefromcode.substr(apostrophe, 0));
            }
            //if another "'" is found treat as quotation marks( i.e. ' ... ')
            else {
               index1 = nextapo +1;
               resultvec.push_back(linefromcode.substr(apostrophe, index1 - apostrophe));
            }
         }
         //period
         else if (wheredot == word && wheredot != beginingdecimal){
            index1 = wheredot +1 ;
            resultvec.push_back(linefromcode.substr(wheredot, 0));
         }
         // numbers
         else if (firstdigit==word){

            //if e is the first character after the word include it as exponents
            if (isthereE == lastdigit){
               index1 = enddigit;
               resultvec.push_back(linefromcode.substr(firstdigit, enddigit -firstdigit));
            }
            //if "." between two numbers treat as decimal point
            else if (wheredot == lastdigit && afterdecimal==nextdigit){
               index1 = enddigit;
               resultvec.push_back(linefromcode.substr(firstdigit, enddigit -firstdigit));
            }
            //if "." before a number, include as a decimal
            else if (wheredot == beginingdecimal){
               index1 = lastdigit;
               resultvec.push_back(linefromcode.substr(wheredot, lastdigit-firstdigit));

            }
            //if "." after a number, include as a decimal
            else if (wheredot == lastdigit){
               index1 = enddecimal;
               resultvec.push_back(linefromcode.substr(firstdigit, enddecimal-firstdigit));

            }
            //otherwise just put the first number
            else {
               index1 = lastdigit;
               resultvec.push_back(linefromcode.substr(firstdigit, lastdigit-firstdigit));
            }
         }
         //quotation mark
         else if (firstquote == word){
            //if last quote within range put everything in between in a string
            if(lastquote < linefromcode.length()){
            index1 = afterlastq;
            resultvec.push_back(linefromcode.substr(firstquote, afterlastq - firstquote));

            }
            //otherwise put an empty string
            else {
               index1 = linefromcode.length();
            resultvec.push_back(linefromcode.substr(word, 0));
            }
         }

         //if there is a white space before an operand separate characters based on whitespace
         else if (whitespace < operand){
            index1 = whitespace;
            resultvec.push_back(linefromcode.substr(word, index1 - word));

         }
         //operands
         else {
            int difference = 0;
            //make sure difference is valid
            if (indexop < linefromcode.length()){
               difference = indexop - operand;
            } else {
               difference = linefromcode.length() - operand;
            }
            //if the first character is not an operand put everything up to the operand into a string
            if (word < operand){
               resultvec.push_back(linefromcode.substr(word, operand - word));
            }

            //if there are no white spaces and strings are between two operands
            else if (indexop!=whitespace && whitespace > nextop && whitespace < linefromcode.length()){
                            resultvec.push_back(linefromcode.substr(word, nextop - word));
               }
            //  or ( " || " )
            if (firstor== operand){
               //make sure last or is valid but put empty strings for "|" signs
               if (lastor < linefromcode.length()){
                  index1 = lastor;
                  resultvec.push_back(linefromcode.substr(firstor, 0));
               }else {
                  index1 = linefromcode.length();
                  resultvec.push_back(linefromcode.substr(firstor, 0));

               }
            }
            // if the difference is less than 2, a single operand, put that into a string
            else if (difference < 2){
            index1 = indexop;

               resultvec.push_back(linefromcode.substr(operand,indexop-operand));

            }
            // otherwise
            else {
              string::size_type lastop = indexop-1;
              //if there is a semicolon separate it
              if (lastop == wheresemi){
                 index1 = aftersemi;
                 resultvec.push_back(linefromcode.substr(operand,wheresemi-operand));
                 resultvec.push_back(linefromcode.substr(wheresemi,aftersemi-wheresemi));

              }
              //accept two operands and set the searching index to the following character
              else {
               index1 = operand +2;
               resultvec.push_back(linefromcode.substr(operand,2));

              }
            }

         }
      }
	}

return resultvec;

}
