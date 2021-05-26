#include "RedBlack.h"

Node::Node(string name) {

    mName = name;
    mColor = Color::RED;

    mParent = NULL;
    mLeft = NULL;
    mRight = NULL;

}

string Node::name() {

    return mName;

}

Color Node::color() {

    return mColor;

}

int Node::order() {

    return mOrder;

}

Node* Node::parent() {

    return mParent;

}

Node* Node::left() {

    return mLeft;

}

Node* Node::right() {

    return mRight;

}

Node* Node::sibling() {

    if (parent() == NULL) {

        return NULL;

    }

    if (parent()->left() == this) {

        return parent()->right();

    }

    return parent()->left();

}

Node* Node::uncle() {

    if (parent() == NULL || parent()->parent() == NULL) {

        return NULL;

    }

    if (parent()->parent()->left() == parent()) {

        return parent()->parent()->right();

    }

    return parent()->parent()->left();

}

Node* Node::grandparent() {

    if (parent() == NULL || parent()->parent() == NULL) {

        return NULL;

    }

    return parent()->parent();

}

bool Node::onLeft() {

    return this == parent()->left();

}

void Node::setParent(Node* node) {

    mParent = node;

}

void Node::setLeft(Node* node) {

    mLeft = node;

}

void Node::setRight(Node* node) {

    mRight = node;

}

void Node::setColor(Color color) {

    mColor = color;

}

void Node::setOrder(int order) {

    mOrder = order;

}

Tree::Tree() {

    mRoot = NULL;
    mCount = 0;

}

Node* Tree::root() {

    return mRoot;

}

int Tree::count() {

    return mCount;

}

set<Node*> Tree::searched() {

    return mSearched;

}

void Tree::rotation(Node* node) {

    if (node == root()) {

        node->setColor(Color::BLACK);
        return;

    }

    if (node->parent()->color() == Color::RED) {

        if (node->uncle() != NULL && node->uncle()->color() == Color::RED) {

            node->parent()->setColor(Color::BLACK);
            node->uncle()->setColor(Color::BLACK);
            node->grandparent()->setColor(Color::RED);

            rotation(node->grandparent());

        }
        else {

            if (node->parent()->onLeft()) {

                if (node->onLeft()) {
                    
                    swapColors(node->parent(), node->grandparent());

                }
                else {

                    leftRotation(node->parent());
                    swapColors(node, node->grandparent());

                }

                rightRotation(node->grandparent());

            }
            else {

                if (node->onLeft()) {

                    rightRotation(node->parent());
                    swapColors(node, node->grandparent());

                }
                else {

                    swapColors(node->parent(), node->grandparent());

                }

                leftRotation(node->grandparent());

            }

        }

    }

}

void Tree::leftRotation(Node* node) {

    Node* parent = node->right();
    node->setRight(parent->left());

    if (parent->left() != NULL) {

        parent->left()->setParent(node);

    }

    parent->setParent(node->parent());
    if (parent->parent() == NULL) {

        mRoot = parent;

    }
    else if (node->onLeft()) {

        node->parent()->setLeft(parent);

    }
    else {

        node->parent()->setRight(parent);

    }

    parent->setLeft(node);
    node->setParent(parent); 

}

void Tree::rightRotation(Node* node) {

    Node* parent = node->left();
    node->setLeft(parent->right());

    if (parent->right() != NULL) {

        parent->right()->setParent(node);

    }

    parent->setParent(node->parent());
    if (parent->parent() == NULL) {

        mRoot = parent;

    }
    else if (node->onLeft()) {

        node->parent()->setLeft(parent);

    }
    else {

        node->parent()->setRight(parent);

    }

    parent->setRight(node);
    node->setParent(parent);

}

void Tree::swapColors(Node* node1, Node* node2) {

    Color color = node1->color();
    node1->setColor(node2->color());
    node2->setColor(color);

}

void Tree::traversal(Node* node, Node* min, Node* max, set<Node*>& nodes) {

    if (node == NULL) {

        return;

    }

    if (node->left()->name() < min->name() && node->right()->name() > max->name()) {

        traversal(node->left(), min, max, nodes);
        nodes.insert(node);
        traversal(node->right(), min, max, nodes);

    }

    /*nodes.insert(node);

    if (node->right()->name() > max->name()) {

        traversal(node->right(), min, max, nodes);

    }*/

}

Node* Tree::getMin() {

    Node* min = mRoot;

    while (min->left() != NULL) {

        min = min->left();

    }

    return min;

}

Node* Tree::getMax() {

    Node* max = mRoot;

    while(max->right() != NULL) {

        max = max->right();

    }

    return max;

}

Node* Tree::search(Node* node, string name) {

    if (node->name() == name || node == NULL) {

        return node;

    }
    if (node->name() > name) {

        return search(node->left(), name);

    }

    return search(node->right(), name);
    
}

void Tree::rangeSearch(Node* min, Node* max) {

    mSearched.clear();
    Node* minNode = search(root(), min->name());
    Node* maxNode = search(root(), max->name());

    mSearched.insert(minNode);

    if (minNode->name() < root()->name()) {

        traversal(root(), min, max, mSearched);

    }
    else if (minNode->name() == root()->name()) {

        traversal(minNode->left(), min, max, mSearched);

    }
    else {

        traversal(minNode, min, max, mSearched);

    }

    mSearched.insert(maxNode);

}

void Tree::insertion(string name) {

    Node* node = new Node(name);
    node->setOrder(count());
    mCount++;

    if (mRoot == NULL) {

        mRoot->setColor(Color::BLACK);
        mRoot = node;
        return;

    }
    else {

        Node* temp = search(root(), name);

        if (temp->name() == name) {

            return;

        }

        node->setParent(temp);
        
        if (temp->name() > name) {

            temp->setLeft(node);

        }
        else {

            temp->setRight(node);

        }

    }

    if (node->parent()->color() == Color::BLACK) {

        return;

    }
    else {

        rotation(node);

    }

}