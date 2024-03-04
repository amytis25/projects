/*
 * circle_array.cpp
 * 
 * Class Description: stores and manipulates circle objects.
 *       
 * Class Invariant:               
 *
 * Author: Amytis Saghafi, asa414@sfu.ca
 * Last modified: Jan. 2024
 */
/*
1. Prompt the user to enter the number of Circle objects to create.
Similarly to Exercise 1 above, in this program, the number of elements (i.e., pointers to Circleobjects) stored in the array is actually equal to the array size. Therefore, 
this value not onlyrepresents the array size, but it also represents the number of elements stored in the array.
2. You may wish to validate this number: what if the user entered a negative number?
3. Create a dynamically allocated array of that size.
4. For each cell in the array ...
Prompt the user to enter the centre coordinates (x,y) and the radius of a circle.
Instantiate a Circle object with these values, then store the pointer (memory address) to this Circle object in the array.
5. At this point in your program, feel free to manipulate each/some of these Circle objects by calling their appropriate methods. For example, you could move the Circle objects around and see if they intersect.
6. Finally, print the content of the entire array, i.e., for each cell:
Print the value of the index of the cell.
Print the Circle object to which the pointer stored in this cell is pointing using theappropriate Circle method.
Print the area of this Circle object, setting precision to 6 figures.
7. Delete the dynamically allocated array before terminating the program.
8. This program returns 0.
*/
#include <iomanip>
#include <iostream>
using std::cin;
using std::cout; 
using std::setprecision;
using std::fixed;
using std::endl; 

#include "Circle.h"

//Circle:: Circle (int x, int y, double radius);
int getSizeofArray ();
    void setCircle(Circle circleArray[], int arraySize);
    void moveCircle (Circle circleArray[], int arraySize);
    void changeRadius(Circle circleArray[], int arraySize);
    void PrintCircle(Circle circleArray[], int arraySize);
    void PrintIntersectingCircles (Circle circleArray[], int arraySize);


int main (){
    /*
    [1] enter a new array of circles
    [2] move a circle
    [3] change the radius of a circle
    [4] print circles
    [5] exit
    select a number corresponding to an action please: 
    */
    
    Circle *circleArray = nullptr;
    int action = 0;
    char input = 0;
    bool done = false;
    int arraySize = 0;
    while (done != true){
        cout << "Welcome!" << endl;
        cout << "[1] enter a new array of circles" << endl;
        cout << "[2] move a circle" << endl;
        cout << "[3] change the radius of a circle" << endl;
        cout << "[4] print circles " << endl;
        cout << "[5] print circle intersections" << endl;
        cout << "[6] exit program" << endl;
        cout << "select a number corresponding to an action please: ";

        cin >> input;
        cout << endl;
            action = input;
        
        switch (input){
            case '1' : 
                arraySize = getSizeofArray();
                circleArray = new Circle[arraySize];
                setCircle(&circleArray[arraySize], arraySize); 
                break;
            case '2': moveCircle (&circleArray[arraySize], arraySize); break;
            case '3' : changeRadius(&circleArray[arraySize], arraySize); break;
            case '4' : PrintCircle(&circleArray[arraySize], arraySize); break;
            case '5' : PrintIntersectingCircles(&circleArray[arraySize], arraySize); break;
            case '6' : cout << "\n----Bye!\n" << endl; 
                      done = true; break;
        }
        /*if (action = 1){
            //set new array of circles
            
            arraySize = getSizeofArray();
            circleArray = new Circle[arraySize];
            setCircle(&circleArray[arraySize], arraySize);

        } else if (action = 2) {
            //move a circle
            moveCircle (&circleArray[arraySize], arraySize);

        } else if (action = 3){
            //change the radius
            changeRadius(&circleArray[arraySize], arraySize);

        } else if (action = 4){
            // print circles
            PrintCircle(&circleArray[arraySize], arraySize);
            PrintIntersectingCircles(&circleArray[arraySize], arraySize);
            cout << endl;

        } else {
            //delete [] circleArray[arraySize];
            break;}

    }*/

    
}
}

int getSizeofArray (){
   int arraySize = 0;
         cout << "Enter the number of Circle objects to create: ";
        cin >> arraySize;
        // Validate the input
        if (arraySize < 0) {
            cout << endl<< "Invalid input. Please enter a non-negative number." << endl<< endl;
            getSizeofArray();
        } 
   
    return arraySize;
    }

    void setCircle(Circle circleArray[], int arraySize){
    for (int i = 0; i<arraySize; i++){
        int x=0;
        int y=0;
        int radius = 0;
        cout << "Enter the x-co-ordinate of circle #" << (i+1)<< " : ";
        cin>> x;
        circleArray[i].setX(x);
       
        cout << "Enter the y-co-ordinate of circle #" << (i+1)<< " : ";
        cin>> y;
        circleArray[i].setY(y);
    
        cout << "Enter the radius of circle #" << (i+1)<< " : ";
        cin>> radius;
        circleArray[i].setRadius(radius);
        
        circleArray[i]= Circle(x,y,radius);
        cout << endl;
    }

}
int getCircleNum (int arraySize){
    int circleNum = 0;
    int input = 0;
    cout << "enter the number of the circle you'd like to modify: ";
    cin >> input;
    cout << endl;
    if (input>0 && input < (arraySize+1)){
        circleNum = (input-1);
        return circleNum;

    } else {
        cout << "invalid circle number! enter a number between 1 and " << arraySize+1 << "." << endl;
        getCircleNum(arraySize);
    }
    return circleNum;

}
void moveCircle (Circle circleArray[], int arraySize){
    int circleNum = 0;
    circleNum = getCircleNum(arraySize);
    int x_move = 0;
    int y_move = 0;
    cout << "circle "<< circleNum+1 <<  "has the following properties: " << endl;
    circleArray[circleNum].displayCircle() ;
    cout << "How much would you like to move the circle horizontally? ";
    cin >> x_move;
    cout << endl;
    cout << "How much would you like to move the circle vertically? ";
    cin >> y_move;
    cout << endl;

    circleArray[circleNum].move(x_move,y_move);

    cout << "the new properties are: "<< endl;
    circleArray[circleNum].displayCircle() ;

}
void changeRadius(Circle circleArray[], int arraySize){
    int circleNum = 0;
    int newRad = 0;
    circleNum = getCircleNum(arraySize);
    cout << "circle "<< circleNum+1 <<  "has a radius of " << circleArray[circleNum].getRadius()<< endl;
    cout << "What would you like to change the radius to?";
    cin >> newRad;
    cout << endl;
    circleArray[circleNum].setRadius(newRad);

}
void PrintCircle(Circle circleArray[], int arraySize){
    for (int i = 0; i < arraySize; i++) {
        double area = circleArray[i].computeArea();
        int x = circleArray[i].getX();
        int y = circleArray[i].getY();
        double radius = circleArray[i].getRadius();
        cout << endl;
        cout << "Circle #" << (i+1) << " has the following properties: "<< endl;
        //circleArray[i].displayCircle() ;
        cout << "x = " << x << ", y = " << y << ", radius = " << radius <<", and area = " << setprecision(6) << area << endl;
        cout << endl;
    }
}
void PrintIntersectingCircles (Circle circleArray[], int arraySize){
    for (int i = 0; i < arraySize; i++) {
        for (int j = (i+1); j < arraySize; j++){
            int numOfFirstCircle = (i + 1);
            int numOfSecondCircle = (j + 1);
            if (circleArray[i].intersect(circleArray[j])== true){
                cout << "Circle " << numOfFirstCircle << " and " << numOfSecondCircle << " intersect." << endl;
            }
        }
}
}