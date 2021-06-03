#ifndef REDBLACK_H
#define REDBLACK_H

#include <string>
#include <set>
#include <vector>
#include <iostream>

using namespace std;

enum class Color {
    RED,
    BLACK
};

class Node {
private:

    string mName;
    Color mColor;
    int mOrder;
    Node *mParent, *mLeft, *mRight;

public:

    Node(string name);

    string name();
    Color color();
    int order();
    Node* parent();
    Node* left();
    Node* right();

    Node* sibling();
    Node* uncle();
    Node* grandparent();
    bool onLeft();

    void setParent(Node* node);
    void setLeft(Node* node);
    void setRight(Node* node);
    void setColor(Color color);
    void setOrder(int order);

};

class Tree {
private:
    Node *mRoot;
    int mCount;
    vector<Node*> mSearched;

public:

    Tree();

    Node* root();
    int count();
    vector<Node*> searched();

    void rotation(Node* node);
    void leftRotation(Node* node);
    void rightRotation(Node* node);
    void swapColors(Node* node1, Node* node2);

    //void traversal(Node* node, vector<Node*>& nodes);
    void traversal(Node* node, vector<Node*>& nodes, string min, string max);
    string getMin();
    string getMax();

    Node* search(Node* node, string name);
    void rangeSearch(string min, string max);
    void insertion(string name);

};

#endif