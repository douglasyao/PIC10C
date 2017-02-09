/** @file hw2.cpp
 @author Douglas Yao
 @date 4/8/2016
 
 Creates base class Thing that stores a particle with a position and derived classes that store a certain property. Also creates a Board class that stores a collection of Things.
 
 */

#include <iostream>
#include <vector>
#include <string>

class Board;


/** @class Thing
 @brief Base class for particle. Stores a position.
 */
class Thing {
public:
    Thing(int pos) : position(pos) {};
    virtual Thing* clone() const = 0;
    virtual int get_position() const {return position;};
    virtual void print(std::ostream& out) const {};
    virtual ~Thing() {};
protected:
    int position;
    static int IDgen;
    int ID;
};

int Thing::IDgen = 0; // initializing static int IDgen with 0


/** @class ThingA
 @brief Stores a particle that has an additional string property. Derived from Thing class.
 */
class ThingA: public Thing {
public:
    ThingA(int pos, std::string prop, const Board& b); // regular constructor
    ThingA(const ThingA& thing); // copy constructor
    void print(std::ostream& out) const;
    virtual ~ThingA();
    ThingA* clone() const; // clone idiom

private:
    std::string property;
    const Board& board;
    int ID;
};



/** @class ThingB
 @brief Stores a particle that has an additional double property. Derived from Thing class.
 */
class ThingB : public Thing {
public:
    ThingB(int pos, double prop, const Board& b); // regular constructor
    ThingB(const ThingB& thing); // copy constructor
    void print(std::ostream& out) const;
    virtual ~ThingB();
    ThingB* clone() const; // clone idiom
    
private:
    double property;
    const Board& board;
    int ID;
};



/** @class Board
 @brief Stores a collection of particles
 */
class Board {
public:
    Board() {}; // default constructor
    Board(const Board& copy); // copy constructor
    void swap (Board& other);
    Board& operator=(Board copy); // copy/swap idiom
    
    bool ParticleInPosition(int pos) const;
    void AddAParticle(int pos, std::string prop);
    bool AddBParticle(int pos, double prop);
    bool operator[](int n);
    bool operator()();
    
    virtual ~Board();
    
    friend std::ostream& operator<<(std::ostream& out, const Board& board);
private:
    std::vector<Thing*> things;
};



int main() {
    Board Z;
    Z.AddAParticle(0, "red");
    Z.AddBParticle(9, 2.71828);
    
    Board Y(Z);
    
    Y.AddAParticle(2, "green");
    
    Y = Z;
    
    return 0;
}



/** Constructor for ThingA object
 @param pos is the position 
 @param prop is the string property
 @param b is the Board on which the ThingA is located
 */
ThingA::ThingA(int pos, std::string prop, const Board& b) : Thing(pos), property(prop), board(b) {
    ID = ++IDgen; // creates unique ID
    std::cout << "Constructing ThingA #" << ID << std::endl; // prints out construction
};



/** Copy constructor for ThingA object
 @param thing whose values will be used to initialize object
 */
ThingA::ThingA(const ThingA& thing) : Thing(thing.position), property(thing.property), board(thing.board) {
    ID = ++IDgen; // creates unique ID
    std::cout << "Constructing ThingA #" << ID << std::endl; // prints out construction
}



/** Destructor for ThingA object
 */
ThingA::~ThingA() {
    std::cout << "Destructing ThingA #" << ID << std::endl; // prints out destruction
}



/** Constructor for ThingB object
 @param pos is the position
 @param prop is the double property
 @param b is the Board on which the ThingB is located
 */
ThingB::ThingB(int pos, double prop, const Board& b) : Thing(pos), property(prop), board(b) {
    ID = ++IDgen; // creates unique ID
    std::cout << "Constructing ThingB #" << ID << std::endl; // prints out construction
};



/** Copy constructor for ThingB object
 @param thing whose values will be used to initialize object
 */
ThingB::ThingB(const ThingB& thing) : Thing(thing.position), property(thing.property), board(thing.board) {
    ID = ++IDgen; // creates unique ID
    std::cout << "Constructing ThingB #" << ID << std::endl; // prints out contruction
}



/** Destructor for ThingB object
 */
ThingB::~ThingB() {
    std::cout << "Destructing ThingB #" << ID << std::endl; // prints out destruction
}



/** Prints out the type, position, and property of a ThingA object
 @param out is the output stream
 */
void ThingA::print(std::ostream& out) const {
    out << "A:" << get_position() << ":" << property;
}



/** Prints out the type, position, and property of a ThingB object
 @param out is the output stream
 */
void ThingB::print(std::ostream& out) const {
    out << "B:" << get_position() << ":" << property;
}



/** Creates a clone of ThingA object on the heap
 @return a pointer to the clone
 */
ThingA* ThingA::clone() const {
    
    ThingA* thing = nullptr;
    try {
        thing = new ThingA (*this); // try allocating memory on heap
    }
    catch (std::exception& e) {
        std::cerr << "Failure at ThingA::clone()" << std::endl;
        thing = nullptr;
    }
    return thing;
}



/** Creates a clone of ThingB object on the heap
 @return a pointer to the clone
 */
ThingB* ThingB::clone() const {
    
    ThingB* thing = nullptr;
    try {
        thing = new ThingB (*this); // try allocating memory on heap
    }
    catch (std::exception& e) {
        std::cerr << "Failure at ThingB::clone()" << std::endl;
        thing = nullptr;
    }
    return thing;
}



/** Copy constructor for Board object
 @param copy is the Board used to initialize object
 */
Board::Board(const Board& copy) {
    
    for (size_t i = 0, n = copy.things.size(); i < n; ++i) {
    
        Thing* thing = copy.things[i]->clone();
        things.push_back(thing);
    }
}



/** Swaps two Boards
 @param other is the board to be swapped with
 */
void Board::swap(Board& other) {
    std::swap(things, other.things);
}



/** Overloaded operator= for Board
 @param copy is the Board object to be set equal to
 @return the Board object
 */
Board& Board::operator=(Board copy) {
    copy.swap(*this);
    return *this;
}



/** Destructor for Board object
 */
Board::~Board() {
    for (const auto& x : things)
        delete x;
}



/** Returns true if a particle has position matching input position
 @param pos is the input position
 @return true or false
 */
bool Board::ParticleInPosition(int pos) const {
    for (size_t i = 0; i < things.size(); ++i)
        if (things[i]->get_position() == pos)
            return true;
    return false;
};



/** Adds a ThingA object to Board
 @param pos is the integer position of the ThingA
 @param prop is the string property of the ThingA
*/
void Board::AddAParticle(int pos, std::string prop) {
    ThingA* thing = new ThingA(pos, prop, *this);
    things.push_back(thing);
}



/** Adds a ThingB object to Board
 @param pos is the integer position of the ThingB
 @param prop is the double property of the ThingB
 @return true if the particle was successfully added, false if not
 */
bool Board::AddBParticle(int pos, double prop) {
    
    // If no particle is at position pos, then add, otherwise don't add.
    if (!ParticleInPosition(pos)) {
        ThingB* thing = new ThingB(pos, prop, *this);
        things.push_back(thing);
        return true;
    }
    return false;
}



/** Overloads operator<< for Board object
 @param out is the stream object with which to output
 @param board is the Board object
 @return the stream object
 */
std::ostream& operator<<(std::ostream& out, const Board& board) {
    for (const auto& x : board.things) {
        x->print(out);
        out << std::endl;
    }
    return out;
}



/** Overloads operator[] for Board object so that it returns true if any particles on the board have position equal to the input value
 @param n is the input value
 @return a bool
 */
bool Board::operator[](int n) {
    for (const auto& x : things)
        if (x->get_position() == n)
            return true;
    return false;
}



/** Overloads operator() for Board object so that it returns true if any particles in Board share the same position
 @return a bool
 */
bool Board::operator()() {
    if (things.size() == 1) return true; // if Board stores only one particle
    
    else {
        for (size_t i = 0, n = things.size(); i < n-1; ++i) {
            int pos = things[i]->get_position();
            for (size_t j = i+1; j < n; ++j) {
                if (pos == things[j]->get_position())
                    return true;
            }
        }
        return false;
    }
}
