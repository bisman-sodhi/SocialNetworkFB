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

vector<Node*> Tree::searched() {

    return mSearched;

}

void Tree::rotation(Node* node) {

    if (node == root()) {

        node->setColor(Color::BLACK);
        return;

    }

    Node* uncle = node->uncle();
    Node* parent = node->parent();
    Node* grandparent = node->grandparent();

    if (parent->color() == Color::RED) {

        if (uncle != NULL && uncle->color() == Color::RED) {

            parent->setColor(Color::BLACK);
            uncle->setColor(Color::BLACK);
            grandparent->setColor(Color::RED);

            rotation(grandparent);

        }
        else {

            if (parent->onLeft()) {

                if (node->onLeft()) {
                    
                    swapColors(parent, grandparent);

                }
                else {

                    swapColors(node, grandparent);
                    leftRotation(parent);

                }

                rightRotation(grandparent);

            }
            else {

                if (node->onLeft()) {

                    rightRotation(parent);
                    swapColors(node, grandparent);

                }
                else {

                    swapColors(parent, grandparent);

                }

                leftRotation(grandparent);

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

void Tree::traversal(Node* node, vector<Node*>& nodes, string min, string max) {

    if (node == NULL) {

        return;

    }

    if (node->name() >= min) {

        traversal(node->left(), nodes, min, max);

    }

    if (node->name() >= min && node->name() <= max) {

        nodes.push_back(node);

    }

    if (node->name() <= max) {

        traversal(node->right(), nodes, min, max);

    }

}

string Tree::getMin() {

    Node* min = mRoot;

    while (min->left() != NULL) {

        min = min->left();

    }

    return min->name();

}

string Tree::getMax() {

    Node* max = mRoot;

    while(max->right() != NULL) {

        max = max->right();

    }

    return max->name();

}

Node* Tree::search(Node* node, string name) {

    if (node->name() == name) {

        return node;

    }

    if (node->name() > name) {

        if (node->left() == NULL) {

            return node;

        }

        return search(node->left(), name);

    }

    if (node->right() == NULL) {

        return node;

    }

    return search(node->right(), name);
    
}

void Tree::rangeSearch(string min, string max) {

    mSearched.clear();
    traversal(root(), mSearched, min, max);

}

void Tree::insertion(string name) {

    Node* node = new Node(name);
    node->setOrder(count());
    mCount++;

    if (mRoot == NULL) {

        mRoot = node;
        mRoot->setColor(Color::BLACK);
        return;

    }
    else {

        Node* temp = search(root(), name);

        if (temp != NULL && temp->name() == name) {

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