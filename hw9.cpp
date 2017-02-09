/** @file hw9.cpp
 @author Douglas Yao
 @date 3/7/2016
 
 Creates classes TreeNode, TreeIterator, and BinarySearchTree which are used to create a binary search tree that stores integers.
 */

#include <iostream>

class BinarySearchTree;
class TreeNode;
class TreeIterator;



/** @class TreeNode
 @brief creates a TreeNode
 This class creates a node containing an integer on the heap. Nodes will be linked together to form a binary search tree.
 */
class TreeNode {
public:
    TreeNode(int new_n);
    void insert_node(TreeNode* new_node);
    void delete_nodes();
private:
    int n;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    
    friend class BinarySearchTree;
    friend class TreeIterator;
};



/** @class TreeIterator
 @brief creates a TreeIterator
 This class creates an iterator that can navigate between the nodes of a binary search tree.
 */
class TreeIterator {
public:
    TreeIterator(TreeNode* new_position, BinarySearchTree* new_container);
    TreeIterator& operator++();
    TreeIterator operator++(int unused);
    TreeIterator& operator--();
    TreeIterator operator--(int unused);
    int operator*() const;
    
    friend bool operator!=(const TreeIterator& rhs, const TreeIterator& lhs);
private:
    TreeNode* position;
    BinarySearchTree* container;
    
    friend class BinarySearchTree;
};



/** @class BinarySearchTree
 @brief creates a BinarySearchTree
 This class creates a binary tree that stores integers.
 */
class BinarySearchTree {
public:
    BinarySearchTree();
    ~BinarySearchTree();
    void insert(int n);
    void erase(int n);
    TreeIterator begin();
    TreeIterator end();
    int smallest() const;
    int largest() const;
private:
    TreeNode* root;
    friend class TreeIterator;
};



int main() {
    
    // Create binary search tree, give it values {2,3,5,11,13,17}
    BinarySearchTree bst;
    bst.insert(3); bst.insert(2); bst.insert(11);
    bst.insert(13); bst.insert(5); bst.insert(17);
    
    // Prints to the console: 2,3,5,11,13,17,
    for (auto x : bst) std::cout << x << ",";
    std::cout << std::endl;
    
    bst.erase(6); // {2,3,5,11,13,17}, no effect
    bst.erase(11); // {2,3,5,13,17}
    
    auto start = std::begin(bst);
    auto stop = std::end(bst);
    
    int value = 17;
    bool keep_looking = true;
    
    // Find a 17 in the list
    while (start != stop && keep_looking)
        if (*start++ == value)
            keep_looking = false;
    --start;
    
    // Prints "17 is in the list."
    if (start != stop) std::cout << *start << " is in the list." << std::endl;
    
    return 0;
}



/** Constructor for TreeNode class
 @param new_n is the integer to be stored in the node
 */
TreeNode::TreeNode(int new_n) {
    n = new_n;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}



/** Inserts a node into a binary search tree
 @param new_node is a pointer to the new node to be added
 */
void TreeNode::insert_node(TreeNode* new_node) {
    
    // if new node is smaller than a given node
    if (new_node->n < n) {
        
        // if left is empty, then new node is placed there
        if (left == nullptr) {
            left = new_node;
            new_node->parent = this;
        }
        
        // if not, then call function again
        else left->insert_node(new_node);
    }
    
    // if new node larger than a given node
    else if (new_node->n > n) {
        
        // if right is empty, then new node is placed there
        if (right == nullptr) {
            right = new_node;
            new_node->parent = this;
        }
        
        // if not, then call function again
        else right->insert_node(new_node);
    }
    
    // if new node is equal to the given node, it is deleted
    else {
        delete new_node;
    }
    return;
}



/** Deallocates a node and all its children nodes
 */
void TreeNode::delete_nodes() {
    
    if (left != nullptr) // deletes left subtree of given node
        left->delete_nodes();
    
    if (right != nullptr) // deletes right subtree of given node
        right->delete_nodes();
    
    delete this; // deletes given node
}



/** Constructor for TreeIterator class
 @param new_position is a pointer a TreeNode
 @param new_container is a pointer to the BinarySearchTree that contains the TreeNode
 */
TreeIterator::TreeIterator(TreeNode* new_position, BinarySearchTree* new_container) {
    position = new_position;
    container = new_container;
}



/** Increments the TreeIterator to the node containing the next largest value in the tree
 @return is the TreeIterator passed by reference
 */
TreeIterator& TreeIterator::operator++() {
    
    TreeNode* move;
    
    // if node has right child
    if (position->right != nullptr) {
        
        // leftmost node of right subtree will be next largest node
        move = position->right;
        while (move->left != nullptr)
            move = move->left;
        position = move;
        return *this;
    }
    
    // if node does not have right child
    else {
        
        // if node is left child of parent node
        if (position->parent->left == position) {
            
            // parent node is next largest node
            position = position->parent;
            return *this;
        }
        
        // if node is right child of parent node
        else {
            move = position->parent;
            
            // find next node whose left child is an ancestor of the input node. This will be the next largest node.
            while (move->parent != nullptr)
                if (move->parent->left != move)
                    move = move->parent;
            
            if (move->parent != nullptr)
                position = move->parent;
            
            // if no such node exists, then node is rightmost node in tree. Return nullptr.
            else
                position = nullptr;
            
            return *this;
        }
    }
}



/** Postfix increment operator for the TreeIterator. Assumes the prefix increment is defined.
 @param unused is an unused integer used to distinguish between prefix and postfix increment
 @return is a copy of the TreeIterator before it was incremented
 */
TreeIterator TreeIterator::operator++(int unused) {
    TreeIterator copy = *this;
    ++(*this);
    return copy;
}



/** Decrements the TreeIterator to the node containing the next smallest value in the tree
 @return is the TreeIterator passed by reference
 */
TreeIterator& TreeIterator::operator--() {
    TreeNode* move;
    
    // if node is located after last node
    if (position == nullptr) {
        move = container->root;
        
        // find rightmost node in tree
        while (move->right != nullptr)
            move = move->right;
        
        position = move; // TreeIterator points to last node
        return *this;
    }
    
    // if node has left child
    if (position->left != nullptr) {
        
        // rightmost node of left subtree will be next smallest node
        move = position->left;
        while (move->right != nullptr)
            move = move->right;
        position = move;
        return *this;
    }
    
    // if node does not have left child
    else {
        
        // if node is right child of parent node
        if (position->parent->right == position) {
            
            // parent node is next smallest node
            position = position->parent;
            return *this;
        }
        
        // if node is left child of parent node
        else {
            
            // find next node whose right child is an ancestor of the input node. This will be the next smallest node.
            move = position->parent;
            while (move->parent->right != move && move->parent != nullptr)
                move = move->parent;
            
            if (move->parent != nullptr)
                position = move->parent;
            
            // if node is leftmost node in tree, do nothing
            return *this;
        }
    }
}



/** Postfix decrement operator for the TreeIterator. Assumes that prefix decrement operator is defined.
 @param unused distinguishes between prefix and postfix decrement
 @return is a copy of the TreeIterator before it was decremented
 */
TreeIterator TreeIterator::operator--(int unused) {
    TreeIterator copy = *this;
    --(*this);
    return copy;
}



/** Dereferences the TreeIterator
 @return is the integer stored in the node pointed to by the TreeIterator
 */
int TreeIterator::operator*() const {
    if (position != nullptr)
        return position->n;
    else return 0;
}



/** Compares two TreeIterators and returns true if they do not point to the same TreeNode
 @return true if the TreeIterators do not point to the same TreeNode
 */
bool operator!=(const TreeIterator& rhs, const TreeIterator& lhs) {
    return rhs.position != lhs.position;
}



/** Constructor for BinarySearchTree object
 */
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}



/** Destructor for BinarySearchTree object. Assumes that TreeNode::delete_nodes is defined.
 */
BinarySearchTree::~BinarySearchTree() {
    root->delete_nodes(); // calls delete_nodes on root, which will delete all nodes in tree
    return;
}


/** Inserts a new node into the tree. Assumes that TreeNode::insert_node is defined.
 @param n is the integer to be stored in the new node
 */
void BinarySearchTree::insert(int n) {
    TreeNode* new_node = new TreeNode(n);
    
    // if tree is empty
    if (root == nullptr) root = new_node;
    
    else root->insert_node(new_node);
    return;
}



/** Erases a given integer value from the tree
 @param n is the value to be erased
 */
void BinarySearchTree::erase(int n) {
    
    TreeNode* to_be_removed = root;
    TreeNode* parent = nullptr;
    bool found = false;
    
    // finds node whose integer matches the integer to be erased
    while (!found && to_be_removed != nullptr) {
        
        // if n is smaller than given node, then left subtree is searched
        if (to_be_removed->n < n) {
            parent = to_be_removed;
            to_be_removed = to_be_removed->right;
        }
        
        // if n is larger than given node, then right subtree is searched
        else if (n < to_be_removed->n) {
            parent = to_be_removed;
            to_be_removed = to_be_removed->left;
        }
        else found = true;
    }
    
    // if n is not in tree, then do nothing
    if (!found) return;
    
    // if node containing n has one child
    if (to_be_removed->left == nullptr || to_be_removed->right == nullptr) {
        
        TreeNode* new_child;
        
        if (to_be_removed->left == nullptr) // if node has right child
            new_child = to_be_removed->right;
        
        else // if node has left child
            new_child = to_be_removed->left;
        
        if (parent == nullptr) // if node to be removed is root
            root = new_child;
        
        // if node to be removed is located to left of parent
        else if (parent->left == to_be_removed) {
            parent->left = new_child; // links parent to child of node to be removed
            new_child->parent = parent;
        }
        
        // if node to be removed is located to right of parent
        else {
            parent->right = new_child; // links parent to child of node to be removed
            new_child->parent = parent;
        }
        
        delete to_be_removed; // erases node
        return;
    }
    
    // if node to be removed has two children
    TreeNode* smallest_parent = to_be_removed;
    TreeNode* smallest = to_be_removed->left;
    
    // finds next smallest node, which is the rightmost node of the left subtree
    while (smallest->right != nullptr) {
        smallest_parent = smallest;
        smallest = smallest->right;
    }
    
    to_be_removed->n = smallest->n; // replaces value of node to be removed with value of next smallest node
    
    // deletes next smallest node
    if (smallest_parent == to_be_removed) { // if next smallest node is left child of parent
        smallest_parent->left = smallest->left; // links parent node with children
        
        if (smallest->left != nullptr)
            smallest->left->parent = smallest_parent;
    
        delete smallest; // deletes next smallest node
    }
    
    // if next smallest node is right child of parent
    else {
        smallest_parent->right = smallest->left; // links parent node with children
        
        if (smallest->left != nullptr)
            smallest->left->parent = smallest_parent;
        
        delete smallest; // deletes next smallest node
    }
    return;
    
}



/** Returns a TreeIterator to the node containing the smallest value in the tree
 @return the TreeIterator
 */
TreeIterator BinarySearchTree::begin() {
    TreeNode* begin = root;
    
    // finds leftmost node
    while (begin->left != nullptr)
        begin = begin->left;
    
    TreeIterator it(begin, this);
    
    return it;
}



/** Returns a TreeIterator to one after the largest node in the tree
 @return the TreeIterator
 */
TreeIterator BinarySearchTree::end() {
    TreeNode* end = nullptr;
    
    TreeIterator it(end, this);

    return it; // returns TreeIterator storing a nullptr
}



/** Finds the smallest integer stored in the tree
 @return the integer
 */
int BinarySearchTree::smallest() const {
    TreeNode* smallest = root;
    
    // finds leftmost node
    while (smallest->left != nullptr)
        smallest = smallest->left;
    
    return smallest->n;
}



/** Finds the largest integer stored in the tree
 @return the integer
 */
int BinarySearchTree::largest() const {
    TreeNode* largest = root;
    
    // finds rightmost node
    while (largest->right != nullptr)
        largest = largest->right;
    
    return largest->n;
}
