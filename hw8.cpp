/** @file hw8.cpp
 @author Douglas Yao
 @date 2/29/2016
 
Creates classes List, Node, and Iterator which are used to create a linked list of ints. Performs various operations on list.
 
 */

#include <iostream>

class Node;
class List;
class Iterator;



/** @class Node
 @brief Creates a node
 This class is designed to create a node containing an integer on the heap. Nodes will be linked together to form a linked list.
 */
class Node {
public:
    Node();
    Node(int new_n);
    int operator*() const;
private:
    int n;
    Node* previous;
    Node* next;
    friend class List;
    friend class Iterator;
};



/** @class List
 @brief Creates a linked list
 This class is designed to manage a collection of Node objects like a linked list.
 */
class List {
public:
    List();
    ~List();
    Iterator begin();
    Iterator end();
    Iterator insert(Iterator pos, int n);
    Iterator erase(Iterator pos);
    
    void push_back(int n);
    void swap_nodes(Iterator node1, Iterator node2);
    void print();
    
    void reverse();
    void push_front(int n);
    void swap(List& other);
    int get_size() const;
    void downsize();
    int maximum();
    void sort();
    void merge(List& list2);
    
private:
    int size;
    Node* first;
    Node* last;
    friend class Iterator;
};



/** @class Iterator
 @brief Creates an iterator
 This class is designed to create an iterator that can nagivate between the Nodes of a List.
 */
class Iterator {
public:
    Iterator(Node* new_position, List* new_container);
    Iterator& operator++();
    Iterator operator++(int unused);
    Iterator& operator+=(int n);
    Iterator& operator--();
    Iterator operator--(int unused);
    Iterator& operator-=(int unused);
    int operator*() const;
    
    friend bool operator==(const Iterator& lhs, const Iterator& rhs);
    friend bool operator!=(const Iterator& lhs, const Iterator& rhs);
private:
    Node* position;
    List* container;
    friend class List;
};



int main () {
    
    List list;
    int n;
    
    std::cout << "Please input a set of nonnegative numbers for a List (Enter -1 when you are finished):\n";
    std::cin >> n;
    
    // user-inputted integers are added to List
    while (n != -1) {
        list.push_back(n);
        std::cin >> n;
    }
    
    // prints out List
    std::cout << "Your list is\n";
    list.print();
    std::cout << std::endl << std::endl;
    
    int index;
    int value;
    
    std::cout << "Select an index for insertion (enter -1 when finished): ";
    std::cin >> index;
    
    // user inserts integers at certain indices
    while (index != -1) {
    
        std::cout << "Select a value for insertion: ";
        std::cin >> value;
        
        // Iterator points to first Node of List
        Iterator it = list.begin();
        
        // Iterator is incremented by index
        for (int i = 0; i < index; ++i)
            ++it;
        
        list.insert(it,value);
        
        std::cout << "Select an index for insertion (enter -1 when finished): ";
        std::cin >> index;
    }
    
    std::cout << "\nThe augmented List is\n";
    list.print();
    std::cout << std::endl << std::endl;
    
    std::cout << "The maximum of the List is: " << list.maximum() << std::endl;
    
    std::cout << "The size of the List is: " << list.get_size() << std::endl;
    
    std::cout << "When we remove every second value from this list we are left with\n";
    list.downsize();
    list.print();
    
    std::cout << "\nWhen we sort this downsized list we obtain\n";
    list.sort();
    list.print();
    
    std::cout << "\nAnd this sorted list in reverse order is\n";
    list.reverse();
    list.print();

    std::cout << "\nIf we merge this list with the list (2,3,5,7,11) we obtain\n";
    List list2;
    list2.push_back(2);
    list2.push_back(3);
    list2.push_back(5);
    list2.push_back(7);
    list2.push_back(11);
    
    list.merge(list2);
    list.print();
    
    std::cout << std::endl;
    
    return 0;
}



/** Default constructor for Node class
 */
Node::Node() {
    n = 0; // default value is 0
    previous = nullptr; // 'previous' and 'next' nodes don't exist yet, so set to 'null'
    next = nullptr;
}



/** Non-default constructor for Node class
 @param new_n is integer stored in Node
 */
Node::Node(int new_n) {
    n = new_n;
    previous = nullptr;
    next = nullptr;
}



/** Dereference operator for Node object
 @return value of integer stored in Node object
 */
int Node::operator*() const {
    return n;
}



/** Default constructor for List class
 */
List::List() {
    first = nullptr; // pointers to first and last Nodes of List are created
    last = nullptr;
    size = 0;
}



/** Destructor for List class
 */
List::~List() {
    
    // creates Iterator that points to first Node of List
    Iterator i(first, this);
    
    // deallocates each Node
    while (i.position != nullptr) {
        delete i.position;
        ++i;
    }
}



/** Returns an Iterator to first Node of List
 @return Iterator to first Node of List
 */
Iterator List::begin() {
    Iterator it(first, this); // creates Iterator to first Node of List
    return it;
}



/** Returns an Iterator to one after the last Node of List
 @return Iterator to one after the last Node of List
 */
Iterator List::end() {
    Iterator it(nullptr, this); // creates Iterator to nullptr, which is located after final Node
    return it;
}



/** Inserts a Node containing an integer at a certain position of the List indicated by an Iterator. New Node will be placed in the position before the Node pointed to by the Iterator. Returns an Iterator pointing to the new Node.
 @param pos is an Iterator pointing to a Node in the List
 @param n is the integer to be stored in the Node
 @return Iterator pointing to the new Node
 */
Iterator List::insert(Iterator pos, int n) {
    
    // if Iterator is pointing to one after the final Node of the List
    if (pos.position == nullptr) {
        push_back(n); // new Node is created at end of List
        Iterator it(last, this); // Iterator points to new Node
        return it;
    }
    
    else {
        Node* after = pos.position;
        Node* before = after->previous;
        Node* new_node = new Node(n); // new Node is created on the heap
        new_node->previous = before; // 'previous' of new Node is set to 'previous' of Node pointed to by pos
        new_node->next = after; // 'next' of new Node is set to Node pointed to by pos
        after->previous = new_node; // 'previous' of Node pointed to by pos is set to new Node
        
        // if pos pointed to first Node of List
        if (before == nullptr)
            first = new_node; // new Node is first Node in List
        
        else
            before->next = new_node; // 'next' of 'previous' of Node pointed to by pos is set to new Node
        
        ++size;
        Iterator it(new_node, this); // creates Iterator pointing to new Node
        return it;
    }
}



/** Erases a Node at a certain position of the List indicated by an Iterator. Returns an Iterator pointing to one after the erased Node.
 @param pos is an Iterator pointing to a Node in the List
 @return Iterator pointing to one after the erased Node
 */
Iterator List::erase(Iterator pos) {
    
    // if position is not located off the end of the List
    if (pos.position != nullptr) {
        Node* erase = pos.position;
        Node* before = erase->previous;
        Node* after = erase->next;
        
        // if Node to be erased is the first Node in the list
        if (erase == first)
            first = after; // the Node that comes after the erased Node is set to the first Node
        
        else
            before->next = after; // 'next' of 'previous' of erased Node is set to 'next' of erased Node
        
        // if Node to be erased is the last Node in the list
        if (erase == last)
            last = before; // the Node that comes before the erased Node is set to the last Node
        
        else
            after->previous = before; // 'previous' of 'next' of erased Node is set to 'previous' of erased Node
        
        delete erase; // Node is erased
        --size;
        Iterator i(after, this); // creates Iterator to 'next' of erased Node
        return i;
    }
    
    // if position is located off the list, then nothing is erased
    else return pos;
}



/** Adds Node containing integer to end of List
 @param n is the integer to be added
 */
void List::push_back(int n) {
    
    // creates Node containing integer n on the heap
    Node* new_node = new Node(n);
    
    // if List is empty
    if (last == nullptr) {
        first = new_node; // List will contain only one Node, so 'first' and 'last' both point to it
        last = new_node;
        ++size;
    }
    
    // if List is not empty
    else {
        new_node->previous = last; // Previous last Node in list is set to 'previous' of new Node
        last->next = new_node; // new Node is set to 'next' of previous last Node
        last = new_node; // current last Node is set to new Node
        ++size;
    }
}



/** Swaps the position of two Nodes in a List
 @param node1 is an Iterator pointing to the first Node
 @param node2 is an Iterator pointing to the second Node
 */
void List::swap_nodes (Iterator node1, Iterator node2) {
    
    // if both Iterators are not pointing to the same Node
    if (node1 != node2) {
        insert(node1, *node2); // inserts integer stored in second Node to position of first Node
        insert(node2, *node1); // inserts integer stored in first Node to position of second Node
        erase(node1); // erases first Node
        erase(node2); // erases second Node
    }
}



/** Prints out all the Nodes in a List
 */
void List::print() {
    Iterator it = begin(); // creates Iterator pointing to first Node of List
    std::cout << "(";
    
    // outputs each Node of List
    for (int i = 0, n = get_size(); i < n-1; ++i) {
        std::cout << *it << ",";
        ++it;
    }
    std::cout << *it << ")";
}



/** Reverses the order of the Nodes in a List
 */
void List::reverse() {
    
    // swaps first Node with last Node, second Node with second to last Node, etc.
    for (int i = 0, n = get_size(); i < n/2; ++i) {
        Iterator it = begin();
        Iterator end (last, this);
        it += i;
        end -= i;
        swap_nodes(it, end);
    }
}



/** Adds Node containing integer to front of List
 @param n is the integer to be added
 */
void List::push_front(int n) {
    
    // creates Node containing integer n on the heap
    Node* new_node = new Node(n);
    
    // if List is empty
    if (last == nullptr) {
        first = new_node;
        last = new_node;
        ++size;
    }
    
    // if list is not empty
    else {
        new_node->next = first; // previous first Node in list is set to 'next' of new Node
        first->previous = new_node; // new Node is set to 'previous' of previous first Node
        first = new_node; // current first Node is set to new Node
        ++size;
    }
}



/** Swaps two Lists
 @param other is the List to be swapped with
 */
void List::swap(List& other) {
    
    // first Nodes of Lists are swapped, which swaps the entire Lists because each subsequent Node is linked to the first Node
    Node* copy = first;
    first = other.first;
    other.first = copy;
}


/** Returns the number of Nodes in a List
 @return size of List
 */
int List::get_size() const {
    return size;
}



/** Removes every second value from a List
 */
void List::downsize() {
    Iterator it = begin();
    ++it;
    
    // every other Node is erased
    for (int i = 0, n = get_size(); i < n; ++i) {
        it = erase(it);
        ++it;
    }
}



/** Returns the largest integer stored in a List
 @return value of largest integer
 */
int List::maximum() {
    Iterator max = begin();
    Iterator pos = begin();
    
    // compares each Node with largest Node
    for (int i = 0, n = get_size(); i < n; ++i) {
        
        // if Node is larger than largest Node, it becomes the new largest Node
        if (*pos > *max)
            max = pos;
        ++pos;
    }
    return *max;
}



/** Sorts List from smallest to largest
 */
void List::sort() {
    
    for (int i = 0, n = get_size(); i < n; ++i) {
        Iterator start = begin();
        start += i;
        Iterator min = start;
        Iterator pos = start;
        
        // compares each Node with smallest Node
        for (int j = i; j < n; ++j) {
            
            // if Node is smaller than smallest Node, it becomes the new smallest Node
            if (*pos < *min)
                min = pos;
            ++pos;
        }
        
        // once smallest Node is determined, it is swapped with the Node at front
        swap_nodes(start, min);
    }
    
}


/** Merges two Lists by alternating elements from each List until the end of one is reached, then appending the rest of the elements from the other List
 @param list2 is the List to be merged with
 */
void List::merge(List& list2) {
    Iterator it1 = begin();
    ++it1;
    Iterator it2 = list2.begin();
    
    // elements from second List are added to every other position of first List until the end of either Lists is reached
    while (it1.position != nullptr && it2.position != nullptr) {
        it1 = insert(it1,*it2);
        it1 += 2;
        ++it2;
    }
    
    // if elements remain in the second List, they are appended to the end of the first List
    while (it2.position != nullptr) {
        push_back(*it2);
        ++it2;
    }
}


/** Constructor for Iterator class
 @param new_position is a pointer to a Node
 @param new_container is a pointer to the List that contains the Nodes the Iterator points to
 */
Iterator::Iterator(Node* new_position, List* new_container) {
    position = new_position;
    container = new_container;
}



/** Moves Iterator forward by one Node
 @return a reference to an Iterator to the next Node
 */
Iterator& Iterator::operator++() {
    
    // if Iterator is pointing after the end of the List
    if (position == nullptr)
        return *this; // returns nullptr
    
    
    // if Iterator is pointing to end of List
    else if (position->next == nullptr){
        position = nullptr;
        return *this; // returns nullptr
    }
    
    else  {
        position = position->next; // moves Iterator forward
        return *this;
    }
}



/** Moves Iterator forward by one Node
 @return a copy of the Iterator before being moved
 */
Iterator Iterator::operator++(int unused) {
    Iterator copy = *this;
    ++(*this);
    return copy;
}



/** Increments Iterator a certain number of times
 @param n is the number of times to increment the Iterator
 @return a reference to the Iterator after being incremented
 */
Iterator& Iterator::operator+=(int n) {
    for (int i = 0; i < n; ++i) {
        ++(*this);
    }
    return *this;
}



/** Moves Iterator backward by one Node
 @return a reference to an Iterator to the previous Node
 */
Iterator& Iterator::operator--() {
    
    // if Iterator is not pointing to first Node of List
    if (position != container->first) {
        
        // if Iterator is pointing after end of List
        if (position == nullptr) {
            position = container->last; // Iterator is moved to end of List
            return *this;
        }
        
        else {
            position = position->previous; // moves Iterator backward
            return *this;
        }
    }
    
    // if Iterator is pointing to first Node of List
    else {
        position = nullptr;
        return *this; // returns nullptr
    }
}



/** Moves Iterator backward by one Node
 @return a copy of the Iterator before being moved
 */
Iterator Iterator::operator--(int unused) {
    Iterator copy = *this;
    --(*this);
    return copy;
}



/** Decrements Iterator a certain number of times
 @param n is the number of times to be decremented
 @return is a reference to the Iterator after being decremented
 */
Iterator& Iterator::operator-=(int n) {
    for (int i = 0; i < n; ++i) {
        --(*this);
    }
    return *this;
}



/** Dereference operator for Iterator
 @return value of the integer contained in the Node pointed to by the Iterator
 */
int Iterator::operator*() const {
    
    // if Iterator is not pointing after end of List
    if (position != nullptr)
        return position->n;
    else return 0;
}



/** Checks if two Iterators are pointing to the same element
 @param lhs is the right hand Iterator
 @param rhs is the right hand Iterator
 @return true if the two Iterators are pointing to the same element;
 */
bool operator==(const Iterator& lhs, const Iterator& rhs) {
    return lhs.position == rhs.position;
}



/** Checks if two Iterators are pointing to the same element
 @param lhs is the right hand Iterator
 @param rhs is the right hand Iterator
 @return true if the two Iterators are not pointing to the same element;
 */
bool operator!=(const Iterator& lhs, const Iterator& rhs) {
    return lhs.position != rhs.position;
}




