/*
 * BinarySearchTree.cpp
 *
 * Author: Lewis Bobrow
 *
 * Due Date: 02/27/19
 *
 * Description: Implementation of BinarySearchTree class
 */

#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>

#include "BinarySearchTree.h"

using namespace std; 

// Input: Nothing
// Returns: Nothing
// Does: Constructor. Initializes values.
BinarySearchTree::BinarySearchTree()
{   
    root = NULL;
}

// Input: Nothing
// Returns: Nothing
// Does: Destructor. Frees all occupied memory and removes all nodes.
BinarySearchTree::~BinarySearchTree()
{
        post_order_delete(root);
        root = NULL;
}

// Input: Node
// Returns: Nothing
// Does: traverses through the tree recursively in post-order and removes
//       all nodes and frees memory.
void BinarySearchTree::post_order_delete(Node *node)
{
    if(node == NULL){
        return;
    }
    post_order_delete(node->left);
    post_order_delete(node->right);
    delete node;
}

// Input: Reference to a source instance of a binary search tree
// Returns: Nothing
// Does: Copy constructor. Copies the source tree.
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source)
{
        root = pre_order_copy(source.root);
}

// Input: Reference to a binary search tree
// Returns: Reference to a binary search tree
// Does: Assignment overload. original values in tree are deleted, and copies
//       values from source into tree.
BinarySearchTree &BinarySearchTree::operator= (const BinarySearchTree &source)
{
    if(this != &source){
        post_order_delete(this->root);
        this->root = pre_order_copy(source.root);
    }
    return *this;
}

// Input: Node
// Returns: Node
// Does: Recursively copies the whole tree from the Node into a new node
//       by traversing the tree pre-order.
Node *BinarySearchTree::pre_order_copy(Node *node) const
{
    if (node == NULL){
        return NULL;
    }
    Node *temp = new Node();
    temp->data = node->data;
    temp->count = node->count;
    temp->left = pre_order_copy(node->left);
    temp->right = pre_order_copy(node->right);
    return temp;
}

// Input: Nothing
// Returns: Int
// Does: Public version of find_min. Recursively calls the private function. 
int BinarySearchTree::find_min() const
{
        if (root == NULL)
            return INT_MIN;
        return find_min(root)->data;
}

// Input: Node
// Returns: Node
// Does: Go through the tree until Node with smallest value is found.
Node *BinarySearchTree::find_min(Node *node) const
{
    Node *cur = node;
    while(cur->left != NULL){
        cur = cur->left;
    }
    return cur;
}

// Input: Nothing
// Returns: Int
// Does: Public version of find_max. Recursively calls the private function.
int BinarySearchTree::find_max() const
{
    if (root == NULL)
        return INT_MAX;
    return find_max(root)->data;
}

// Input: Node
// Returns: Node
// Does: Go through the tree until the Node with largest value is found.
Node *BinarySearchTree::find_max(Node *node) const
{
    Node *cur = node;
    while(cur->right != NULL){
        cur = cur->right;
    }
    return cur;
}

// Input: Int
// Returns: Bool
// Does: Public version of contains. Recursively calls the private function.
bool BinarySearchTree::contains(int value) const
{
    if(root == NULL){
        return false;
    } else{
        return contains(root, value);
    } 

}

// Input: Node, int
// Returns: Bool
// Does: Checks if the tree contains a node whose data is equal to value.
bool BinarySearchTree::contains(Node *node, int value) const
{
    while(node != NULL){
        if(node->data == value){
            return true;
        } else if(node->data > value){
            node = node->left;
        } else{
            node = node->right;
        }
    }
    return false;
}

// Input: Int, Node
// Returns: Node
// Does: Returns the Node whose data is equal to value.
Node *BinarySearchTree::atValue(int value, Node *correctNode) const
{
    Node *temp = root;
        while(temp != NULL){
            if(temp->data == value){
                correctNode = temp;
                break;
            } else if(temp->data > value){
                temp = temp->left;
            } else{
                temp = temp->right;
            }
        }
    return correctNode;
}

// Input: Int
// Returns: Nothing
// Does: Public version of insert.
void BinarySearchTree::insert(int value)
{
    insert(root, NULL, value);
}

// Input: Node, Node, Int
// Returns: Nothing
// Does: Inserts a Node into the tree, preserving the BST invariants.
//       If the value is already in the tree, increases multiplicity.
void BinarySearchTree::insert(Node *node, Node *parent, int value)
{
    if(contains(node, value)){
        atValue(value, NULL)->count += 1;
        return;
    }
    if(node == NULL){
        Node *temp = new Node;
        temp->left = NULL;
        temp->right = NULL;
        temp->count = 1;
        temp->data = value;
        if(root == NULL){
            root = temp;
        } else{
            if(parent->data < value){
                parent->right = temp;
            } else{
                parent->left = temp;
            }
        }
    } else{
        if(node->data > value){
            return insert(node->left, node, value);
        } else{
            return insert(node->right, node, value);
        }
    }            
}

// Input: Int 
// Returns: Bool
// Does: Public version of remove.
bool BinarySearchTree::remove(int value)
{
        return remove(root, NULL, value);
}

// Input: Node, Node, Int
// Returns: Bool
// Does: Removes a Node from the tree, preserving the BST invariants.
//       If the Node's multiplicity is greater than 1, decreases the
//       multiplicity.
bool BinarySearchTree::remove(Node *node, Node *parent, int value)
{   
    if(!contains(node, value)){
        return false;
    }
    if(node == NULL){
        return false;
    } else{
        if(atValue(value, NULL)->count > 1){
            atValue(value, NULL)->count--;
            return true;
        } else{
            if(node->data > value){
                remove(node->left, node, value);
            } else if (node->data < value){
                remove(node->right, node, value);

            // no children 
            } else{
                if(node->right == NULL && node->left == NULL){
                    delete node;
                    if(parent->data < value){
                        parent->right = NULL;
                    } else{
                        parent->left = NULL;
                    }

                // 1 child
                } else if(node->right == NULL){
                    Node *temp = node->left;
                    delete node;
                    if(parent->data < value){
                        parent->right = temp;
                    } else{
                        parent->left = temp;
                    }

                // 1 child
                } else if(node->left == NULL){
                    Node *temp = node->right;
                    delete node;
                    if(parent->data < value){
                        parent->right = temp;
                    } else{
                        parent->left = temp;
                    }

                // 2 children
                } else{
                    Node *temp = find_min(node->right);
                    parent = find_parent(root, temp);
                    node->data = temp->data;
                    node->count = temp->count;
                    if(temp->right == NULL){
                        if(parent->right == temp){
                            parent->right = NULL;
                        } else{
                            parent->left = NULL;
                        }
                    } else{
                        if(parent->right == temp){
                            parent->right = temp->right;
                        } else{
                            parent->left = temp->right;
                        }
                    }
                    delete temp;
                }
            }
            return true;       
        }
    }
}

// Input: Nothing
// Returns: Int
// Does: Public version of tree_height. 
int BinarySearchTree::tree_height() const
{
        return tree_height(root);
}

// Input: Node
// Returns: Int
// Does: Returns the height of the tree by iterating through the tree 
//       recursively.
int BinarySearchTree::tree_height(Node *node) const
{
    if(node == NULL){
        return -1;
    }
    int left = tree_height(node->left);
    int right = tree_height(node->right);
    return 1 + std::max(left, right);
}

// Input: Nothing
// Returns: Int
// Does: Public version of node_count.
int BinarySearchTree::node_count() const
{
        return node_count(root);
}

// Input: Node
// Returns: Int
// Does: Returns the total number of nodes.
int BinarySearchTree::node_count(Node *node) const
{
    if (node == NULL)
        return 0;
    else {
        return (1 + node_count(node->right) + node_count(node->left));
    }
}

// Input: Nothing
// Returns: Int
// Does: Public version of count_total.
int BinarySearchTree::count_total() const
{
        return count_total(root);
}

// Input: Node
// Returns: Int
// Does: Returns the sum of all the node values (including duplicates).
int BinarySearchTree::count_total(Node *node) const
{
    if (node == NULL)
        return 0;
    else {
        return ((node->data)*(node->count) + count_total(node->right)
               + count_total(node->left));
    }
}

// Input: Nothing
// Returns: Nothing
// Does: Prints the tree using the helper function printPretty.
void BinarySearchTree::print_tree() const
{
        printPretty(root, 1, 0, std::cout);
}

// Input: Node, Node
// Returns: Node
// Does: Returns the parent of the given child.
Node *BinarySearchTree::find_parent(Node *node, Node *child) const
{
        if (node == NULL) return NULL;

        // if either the left or right is equal to the child,
        // we have found the parent
        if (node->left == child or node->right == child) {
                return node;
        }

        // Use the binary search tree invariant to walk the tree
        if (child->data > node->data) {
                return find_parent(node->right, child);
        } else {
                return find_parent(node->left, child);
        }
}
