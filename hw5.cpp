/** @file hw5.cpp
 @author Douglas Yao
 @date 2/8/2016
 
Creates base class Point2D that stores a point and derived classes ColorPoint2D and WeightedPoint2D that store a point along with a color or weight. Prints out user inputted points.
 
 */

#include <iostream>
#include <vector>
#include <string>


/** @class Point2D
 @brief Stores a point
 
 This class is designed to store a point in two dimensions.
 
 */

class Point2D {
public:
    Point2D();
    Point2D(double new_x, double new_y);
    virtual void print() const;
    virtual ~Point2D() {}
private:
    double x;
    double y;
    
};



/** @class ColorPoint2D
 @brief Stores a point and color
 
 This class is designed to store a point in two dimensions as well as a color. Derived from Point2D class.
 
 */

class ColorPoint2D : public Point2D {
public:
    ColorPoint2D (double new_x, double new_y, std::string new_color);
    void print() const;
private:
    std::string color;
};



/** @class WeightedPoint2D
 @brief Stores a point and weight
 
 This class is designed to store a point in two dimensions as well as a weight. Derived from Point2D class.
 
 */

class WeightedPoint2D : public Point2D {
public:
    WeightedPoint2D (double new_x, double new_y, double new_weight);
    void print() const;
private:
    double weight;
};



/** @class Points
 @brief Stores a collection of Point2D pointers
 
This class stores a collection of Point2D pointers pointing to objects located on the heap. Deallocates the memory when the class objects go out of scope.
 
 */

class Points {
public:
    void push_back(Point2D* point);
    virtual ~Points();
    size_t size() const;
    void print(int i) const;
private:
    std::vector<Point2D*> points;
};



int main() {
    
    std::cout << "Welcome to Point Printer! You can create three different kinds of points:" << std::endl << std::endl;
    std::cout << "1. Point2D, e.g., (2,6.5)" << std::endl;
    std::cout << "2. ColorPoint2D, e.g., blue(-4.5,3.5)" <<std::endl;
    std::cout << "3. WeightedPoint2D, e.g., .12(3.6,8.7)" << std::endl << std::endl;
    std::cout << "Enter 0 when you are finished." << std::endl << std::endl;
    
    int selection;
    Points points;
    std::cout << "Selection: ";
    std::cin >> selection;
    
    // user decides what type of point to input
    while (selection != 0) {
        
        // if Point2D is selected
        if (selection == 1) {
            
            double x, y;
            std::cout << "x = ";
            std::cin >> x;
            std::cout << "y = ";
            std::cin >> y;
            
            // stores point on heap
            points.push_back(new Point2D(x,y));
        }
        
        // if ColoredPoint2D is selected
        if (selection == 2) {
            
            double x, y;
            std::string color;
            std::cout << "x = ";
            std::cin >> x;
            std::cout << "y = ";
            std::cin >> y;
            std::cout << "color = ";
            std::cin.ignore();
            std::getline(std::cin,color);
            
            // stores point on heap
            points.push_back(new ColorPoint2D(x,y,color));
        }
        
        // if WeightedPoint2D is selected
        if (selection == 3) {
            
            double x, y, weight;
            std::cout << "x = ";
            std::cin >> x;
            std::cout << "y = ";
            std::cin >> y;
            std::cout << "weight = ";
            std::cin >> weight;
            
            // stores point on heap
            points.push_back(new WeightedPoint2D(x,y,weight));
        }
        
        std::cout << "Selection: ";
        std::cin >> selection;
        
    }
    
    std::cout << std::endl << "Your points are" << std::endl << std::endl;
    
    // outputs points
    for (size_t i=1, n = points.size(); i <= n; ++i) {
        std::cout << i << ". ";
        points.print(i-1);
        std::cout << std::endl;
    
    }
    
    
    return 0;
}



/** Default constructor for Point2D class
 
 */

Point2D::Point2D() {
    x = 0;
    y = 0;
}



/** Non-default constructor for Point2D class
 
 @param new_x is the x-coordinate of the point
 @param new_y is the y-coordinate of the point
 
 */

Point2D::Point2D(double new_x, double new_y) {
    x = new_x;
    y = new_y;
}



/** Prints out coordinates of Point2D point
 
 */

void Point2D::print() const {
    std::cout << "(" << x << "," << y << ")";
}



/** Constructor for ColorPoint2D class
 
 @param new_x is the x-coordinate of the point
 @param new_y is the y-coordinate of the point
 @param new_color is the color of the point
 
 */

ColorPoint2D::ColorPoint2D(double new_x, double new_y, std::string new_color) : Point2D(new_x, new_y), color(new_color) {}



/** Prints out coordinates and color of ColorPoint2D point
 
 */

void ColorPoint2D::print() const {
    std::cout << color;
    Point2D::print();
}



/** Constructor for WeightedPoint2D class
 
 @param new_x is the x-coordinate of the point
 @param new_y is the y-coordinate of the point
 @param new_weight is the weight of the point
 
 */

WeightedPoint2D::WeightedPoint2D(double new_x, double new_y, double new_weight) : Point2D(new_x, new_y), weight(new_weight) {}



/** Prints out coordinates and weight of WeightedPoint2D point
 
 */

void WeightedPoint2D::print() const {
    std::cout << weight;
    Point2D::print();
}



/** Stores a Point2D pointer in the Points object
 
 */

void Points::push_back(Point2D* point) {
    points.push_back(point);
}



/** Destructor for Points class. Deallocates heap memory for each point.
 
 */

Points::~Points() {
    for (auto& x : points)
        delete x;
}



/** Returns the number of points in Points object
 
 @return size of Points
 
 */

size_t Points::size() const{
    return points.size();
}



/** Prints out a point in Points object
 
 @param n is the position of the pointer to be printed out
 
 */

void Points::print(int n) const {
    points[n]->print();
}
