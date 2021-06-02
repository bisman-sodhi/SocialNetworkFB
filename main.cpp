#include "RedBlack.h"
#include "graph.h"
#include "parse.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string strip(string str) {

    int len = str.length();
    string newStr = "";

    for (int i = 0; i < len; i++) {

        if (str[i] != '@') {

            newStr += str[i];

        }
        else {

            break;

        }
    
    }

    return newStr;

}

int main() {

    Tree* tree = new Tree();
    Graph graph;

    int x;
    cout << "Welcome!" << endl;

    do {

        cout << "1) Intialize the network." << endl;
        cout << "2) Insert a new user." << endl;
        cout << "3) Insert a friendship." << endl;
        cout << "4) Print all." << endl;
        cout << "5) List friends' info." << endl;
        cout << "6) List info." << endl;
        cout << "7) Exit." << endl;
        cout << "Which operation do you want to make? (1,2,3,4,5,6,7): ";
        cin >> x;

        while  (x != 1 && x != 2 && x != 3 && x != 4 && x != 5 && x!= 6 && x!= 7) {

            cout << "wrong operation!" << endl;
            cout << "Which operation do you want to make? (1,2,3,4,5,6,7): ";
            cin >> x;

        }

        if (x == 1) {

            string file;
            cout << "Enter file name:" << endl;
            cin >> file;

            file = file + ".csv";
            read_csv(file, graph, tree);

            int i = 1;
            
            for (auto& item: graph.graphVec) {

                GraphNode* node = &item;
                while (node->nextNode != NULL) {

                    node = node->nextNode;
                    Node* treeNode = tree->search(tree->root(), node->mName);
                    node->dataIndex = treeNode->order();

                }

            }

        }
        else if (x == 2) {

            string name, age, occupation;
            cout << "Enter user's name:" << endl;
            cin >> name;

            cout << "Enter user's age:" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> age;

            cout << "Enter user's occupation:" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> occupation;
            graph.addPerson(name);
            // write onto disk

        }
        else if (x == 3) {

            string friend1, friend2;
            cout << "Enter friend 1:" << endl;
            cin >> friend1;
            cout << "Enter friend 2:" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> friend2;

            graph.addFriend(friend1, friend2);
            graph.addFriend(friend2, friend1);
            
            // add friendship to profile data

        }
        else if (x == 4) {

            if (tree->count() == 0) {

                cout << "No users in network.  Choose another operation." << endl;
                cin >> x;

            }

            tree->rangeSearch(tree->getMin(), tree->getMax());

            for (auto& user: tree->searched()) {

                string name = graph.graphVec[user->order()].mName;

                cout << user->name() << endl;
                cout << "   Age: " << strip(readDataAge(user->order())) << endl;
                cout << "   Occupation: " << strip(readDataJob(user->order())) << endl;
                cout << "   Friends: " << endl; // read from profile data at line user->order() + 1

            }

        }
        else if (x == 5) {

            string user;
            cout << "Enter user: " << endl;
            cin >> user;

            Node* node = tree->search(tree->root(), user);
            GraphNode* graphNode = &graph.graphVec[node->order()];
            cout << graphNode->mName << endl;

            while (graphNode->nextNode != NULL) {

                graphNode = graphNode->nextNode;
                cout << graphNode->mName << endl;
                cout << "   Age: " << strip(readDataAge(graphNode->dataIndex)) << endl;
                cout << graphNode->dataIndex << endl;
                cout << "   Occupation: " << strip(readDataJob(graphNode->dataIndex)) << endl;

            }

            break;

        }
        else if (x == 6) {

            string lower, upper;
            cout << "Enter lower bound: " << endl;
            cin >> lower;
            cout << "Enter upper bound: " << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> upper;

            tree->rangeSearch(tree->search(tree->root(), lower), tree->search(tree->root(), upper));

            for (auto& user: tree->searched()) {

                cout << user->name() << endl;
                cout << "   Age: " << strip(readDataAge(user->order())) << endl;
                cout << "   Occupation: " << strip(readDataJob(user->order())) << endl;
                cout << "   Friends: " << endl; // graph[user.order()].friends

            }

        }

    }
    while (x != 7);

}