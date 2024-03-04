/*
 * Circles.cpp
 *
 * Class Description: class represeting 2 circles in two-dimensional cartiesien space.
 *
 * Class Invariant: 'Radius' > '0.0'
 * 
 * Author: Amytis Saghafi , asa414@sfu.ca
 * Modified on: Jan. 2023
 */
#include "Circle.h"
#include <cctype>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;
Circle::Circle (int x, int y, double radius){
    setX(x);
    setY(y);
    setRadius(radius);
}
Circle::Circle (){
    x= 0.0;
    y= 0.0;
    radius = 10.0;
    
};

int Circle::getX (){//returns the circle's centre x coordinate
    return x;
}
int Circle::getY (){//returns the circle's centre y coordinate
    return y;
}
int Circle::setX (int X_u){
    x = X_u;
    return x;
    //cout << "Setting X as " << x << "." << endl;
}
int Circle::setY (int Y_u){
    y = Y_u;
    return y;
    //cout << "setting Y as "<< y << "." << endl;
}
double Circle::getRadius(){//returns the circle's radius
    return radius;
}
void Circle::move ( int horiz , int vert){ 
    //moves the circle the given horizontal and vertical distances
    //(therefore changing its x and y member attributes)
    x = x + horiz;
    y = y + vert;
}
void Circle::setRadius (double r){ //changes the circle's radius to r, or to 10.0 if r is invalid
    if (r> 0.0){
        radius = r;
    }else {
        radius = 10.0;
    }
    //cout << "Radius has been set as " << radius << "." << endl;
}


double Circle::computeArea(){
    //computes and returns the circle's area
    double area = 0.0;
    area = PI * pow(radius,2);
    return area;

}
void Circle::displayCircle(){
    //displays the circle's member attributes like this:
    //x = 0, y = 11, radius =0.
    cout << "x = " << x << ", y = " << y << ", radius = " << radius << endl;

}

    //returns true if c intersects the calling circle
bool Circle::intersect(Circle C){
    //returns true if c intersects the calling circle

            double distance = 0;
            distance = sqrt((pow(C.x - x,2)+pow(C.y - y,2)));
            const double epsilon = 1e-6;
            double sumcondition = 0;
            double diffcondition= 0;
            sumcondition = (abs(radius + C.radius)+epsilon);
            diffcondition = (abs(radius - C.radius)+epsilon);

           //cout << "distance = " << distance << " and sum condition = " << sumcondition << "and diif condition =" << diffcondition <<endl;
            
                if (distance <= sumcondition && distance >= diffcondition){
                    return true;
                } else {
                    return false;
                }
            


            

}

