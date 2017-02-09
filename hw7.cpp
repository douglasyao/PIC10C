/** @file hw7.cpp
 @author Douglas Yao
 @date 5/13/2016
 
 Creates a binary search tree of Point2D objects.
 
 */

#include <iostream>
#include "tree.h"
#include <string>
#include <functional>


/** @class Point2D
 @brief Stores a point
 This class is designed to store a point in two dimensions.
 */
class Point2D {
public:
    Point2D() {};
    Point2D(int new_x, int new_y);
    int get_x() const {return x;}; // accessors
    int get_y() const {return y;};
    friend std::ostream& operator<<(std::ostream& out, const Point2D& p);
private:
    int x;
    int y;
};


/** @class PointOrderx
 @brief Order class for Point2D object using x-values
 */
class PointOrderx {
public:
    bool operator()(const Point2D& rhs, const Point2D& lhs);
};


/** @class PointOrdery
 @brief Order class for Point2D object using y-values
 */
class PointOrdery {
public:
    bool operator()(const Point2D& rhs, const Point2D& lhs);
};



int main() {
    
    // Create binary search tree, give it values {2,3,5,11,13,17}
    BinarySearchTree<int> bst;
    bst.insert(3); bst.insert(2); bst.insert(11);
    bst.insert(13); bst.insert(5); bst.insert(17);
    
    // Prints to the console: 2,3,5,11,13,17,
    for(auto x : bst) std::cout << x << ",";
    std::cout << std::endl;
    
    BinarySearchTree<Point2D, PointOrderx> points_by_x;
    points_by_x.insert( Point2D(1,2) );
    points_by_x.insert( Point2D(7,3) );
    points_by_x.insert( Point2D(2,1) );
                       
    // Prints to the console: (1,2),(2,1),(7,3),
    for(auto x : points_by_x) std::cout << x << ",";
    std::cout << std::endl;
    
    BinarySearchTree<Point2D, PointOrdery> points_by_y;
    points_by_y.insert( Point2D(1,2) );
    points_by_y.insert( Point2D(7,3) );
    points_by_y.insert( Point2D(2,1) );
    
    // Prints to the console : (2,1),(1,2),(7,3),
    for(auto x : points_by_y) std::cout << x << ",";
    std::cout << std::endl;
    
    BinarySearchTree<std::string, std::greater<std::string>> names;
    names.insert( "Luke" );
    names.insert( "Kanye" );
    names.insert( "Pentatonix" );
    
    // Prints to the console: Pentatonix,Luke,Kanye,
    for(auto x : names) std::cout << x << ",";
    std::cout << std::endl;
    
    return 0;
}


/** Constructor for Point2D object
 @param new_x is the x value
 @param new_y is the y value
 */
Point2D::Point2D(int new_x, int new_y) {
    x = new_x;
    y = new_y;
}



/** Overloaded bitshift operator for outputting
 @param out is the output stream object
 @param p is the point to be outputted
 @return the output stream
 */
std::ostream& operator<<(std::ostream& out, const Point2D& p) {
    out << "(" << p.x << "," << p.y << ")";
    return out;
}



/** Overloaded function operator that compares x values of points
 @param lhs is the left hand point
 @param rhs is the right hand point
 @return true if the x value of lhs is less than the x value of rhs
 */
bool PointOrderx::operator()(const Point2D& lhs, const Point2D& rhs) {
    return lhs.get_x() < rhs.get_x();
}



/** Overloaded function operator that compares y values of points
 @param lhs is the left hand point
 @param rhs is the right hand point
 @return true if the y value of lhs is less than the y value of rhs
 */
bool PointOrdery::operator()(const Point2D& lhs, const Point2D& rhs) {
    return lhs.get_y() < rhs.get_y();
}
