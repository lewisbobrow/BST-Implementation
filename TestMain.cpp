//
// TestMain.cpp
// Author: Lewis Bobrow
// Due Date: 02/27/19
// Description: Unittesting file for the BinarySearchTree class and functions.
//

#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>

#include "BinarySearchTree.h"

using namespace std;

int main(){
    cout << "creating binary search tree for testing" << endl;
    BinarySearchTree TestTree;
    cout << "inserting numbers 2-10" << endl;
    TestTree.insert(2);
    TestTree.insert(3);
    TestTree.insert(4);
    TestTree.insert(5);
    TestTree.insert(6);
    TestTree.insert(7);
    TestTree.insert(8);
    TestTree.insert(9);
    TestTree.insert(10);
    cout << "tree height: " << TestTree.tree_height() << endl;
    cout << "contains 6: " << TestTree.contains(6) << endl;
    cout << "contains 11: " << TestTree.contains(11) << endl;
    cout << "removing 6 and inserting 11" << endl;
    TestTree.insert(11);
    TestTree.remove(6);
    cout << "contains 6: " << TestTree.contains(6) << endl;
    cout << "contains 11: " << TestTree.contains(11) << endl;
    cout << "inserting duplicates of 2, 4 and 10" << endl;
    TestTree.insert(2);
    TestTree.insert(4);
    TestTree.insert(10);
    cout << "total nodes in tree: " << TestTree.count_total() << endl;
    cout << "unique nodes in tree: " << TestTree.node_count() << endl;
    cout << "inserting numbers 12-16" << endl;
    TestTree.insert(12);
    TestTree.insert(13);
    TestTree.insert(14);
    TestTree.insert(15);
    TestTree.insert(16);
    cout << "tree height: " << TestTree.tree_height() << endl;
    cout << "removing duplicate of 2";
    TestTree.remove(2);
    cout << "contains 2: " << TestTree.contains(2) << endl;
    cout << "removing 3-14 (including dublicates)" << endl;
    TestTree.remove(3);
    TestTree.remove(4);
    TestTree.remove(4);
    TestTree.remove(5);
    TestTree.remove(6);
    TestTree.remove(7);
    TestTree.remove(8);
    TestTree.remove(9);
    TestTree.remove(10);
    TestTree.remove(10);
    TestTree.remove(11);
    TestTree.remove(12);
    TestTree.remove(13);
    TestTree.remove(14);
    cout << "tree height: " << TestTree.tree_height() << endl;
    cout << "end of test" << endl;
}
