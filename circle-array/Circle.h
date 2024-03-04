/*
 * Circles.h
 *
 * Class Description: class represeting 2 circles in two-dimensional cartiesien space.
 *
 * Class Invariant: 'Radius' > '0.0'
 * 
 * Author: Amytis Saghafi , asa414@sfu.ca
 * Modified on: Jan. 2023
 */

class Circle {
    private:
    /*
Attributes
The Circle class must have the following (private) member attributes:
x coordinate (an int), can be negative
y coordinate (an int), can be negative
radius (a double), must be greater than 0.0
*/
        int x = 0.0; // x-coordinate 
        int y = 0.0; //y-coordinate 
        double radius = 0.0; // radius > 0.0
        double area = 0.0;
        double PI = 3.14159265359;

        
    public:
        
/*
Operations
The Circle class must have the following (public) operations (i.e., member methods):
A default constructor that creates a circle of radius 10 and centred at coordinates (0,0)
A constructor with parameters for x, y, and radius
Do you need a destructor?
*/
Circle ();

Circle (int x, int y, double radius);

int getX ();//returns the circle's centre x coordinate
 

int getY ();//returns the circle's centre y coordinate

int setX (int X_u);

int setY (int Y_u);

double getRadius();//returns the circle's radius

void move ( int horiz , int vert); 
    //moves the circle the given horizontal and vertical distances
    //(therefore changing its x and y member attributes)

void setRadius (double r); //changes the circle's radius to r, or to 10.0 if r is invalid

double computeArea();
    //computes and returns the circle's area


void displayCircle();
    //displays the circle's member attributes like this:
    //x = 0, y = 11, radius =0.

bool intersect(Circle c);
    //returns true if c intersects the calling circle


};
