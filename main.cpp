#include "RedBlack.h"
#include "graph.h"
#include "parse.h"

#include <iostream>
#include <string>
#include <sstream>
#include <climits>
#include "Common.h"

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

int counter;

int main() {

    Tree* tree = new Tree();
    Graph graph;
    counter = 0;

    int x;
    bool intialized = false;
    cout << "Welcome!" << endl;

    do {

        cout << "1) Intialize the network." << endl;
        cout << "2) Insert a new user." << endl;
        cout << "3) Insert a friendship." << endl;
        cout << "4) Print all." << endl;
        cout << "5) List user's info." << endl;
        cout << "6) List friends' info." << endl;
        cout << "7) List range of users' info." << endl;
        cout << "8) Exit." << endl;
        cout << "Which operation do you want to make? (1,2,3,4,5,6,7,8): ";
        cin >> x;

        while  (x != 1 && x != 2 && x != 3 && x != 4 && x != 5 && x!= 6 && x!= 7 && x!=8) {

            cout << "wrong operation!" << endl;
            cout << "Which operation do you want to make? (1,2,3,4,5,6,7,8): ";
            cin >> x;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');

        }

        if (x == 1) {

            if (intialized) {

                cout << "Already intialized the network." << endl;
                continue;

            }

            string file;
            cout << "Enter file name:" << endl;
            cin >> file;

            file = file + ".csv";
            read_csv(file, graph, tree);

            int i = 1;
            
            for (auto& item: graph.graphVec) {

                for (auto& person: item.friends) {

                    Node* treeNode = tree->search(tree->root(), person->mName);
                    person->dataIndex = treeNode->order();

                }

            }

            intialized = true;

        }
        else if (x == 2) {

            string firstName, lastName, name, age, occupation;
            cout << "Enter user's name:" << endl;
            cin >> firstName >> lastName;
            name = firstName + ' ' + lastName;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');

            cout << "Enter user's age:" << endl;
            cin >> age;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');

            cout << "Enter user's occupation:" << endl;
            cin >> occupation;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');

            graph.addPerson(name);
            addNewPerson(name, age, occupation, graph);
            tree->insertion(name);

        }
        else if (x == 3) {

            string first1, last1, first2, last2, friend1, friend2;
            cout << "Enter friend 1:" << endl;
            cin >> first1 >> last1;
            friend1 = first1 + ' ' + last1;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Enter friend 2:" << endl;
            cin >> first2 >> last2;
            friend2 = first2 + ' ' + last2;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');

            Node* node1 = tree->search(tree->root(), friend1);
            Node* node2 = tree->search(tree->root(), friend2);

            graph.addFriend(friend1, friend2, node1->order());
            graph.addFriend(friend2, friend1, node2->order());

        }
        else if (x == 4) {

            if (tree->count() == 0) {

                cout << "No users in network." << endl;
                continue;

            }

            tree->rangeSearch(tree->getMin(), tree->getMax());

            for (auto& user: tree->searched()) {

                string name = graph.graphVec[user->order()].mName;

                cout << user->name() << endl;
                cout << "   Age: " << strip(readDataAge(user->order())) << endl;
                cout << "   Occupation: " << strip(readDataJob(user->order())) << endl;
                cout << "   Friends: " << endl; 
                
                GraphNode node = graph.graphVec[user->order()];
                for (auto& person: node.friends) {

                    cout << "       " << person->mName << endl;

                }

            }

        }
        else if (x == 5) {

            string first, last, user;
            cout << "Enter user: " << endl;
            cin >> first >> last;
            user = first + ' ' + last;

            Node* node = tree->search(tree->root(), user);
            if (user != node->name()) {

                cout << "User is not in network." << endl;
                continue; 

            }

            cout << node->name() << endl;
            cout << "   Age: " << strip(readDataAge(node->order())) << endl;
            cout << "   Occupation: " << strip(readDataJob(node->order())) << endl;
            cout << "   Friends: " << endl; 

            GraphNode graphNode = graph.graphVec[node->order()];
            for (auto& person: graphNode.friends) {

                cout << "       " << person->mName << endl;

            }

        }
        else if (x == 6) {

            string first, last, user;
            cout << "Enter user: " << endl;
            cin >> first >> last;
            user = first + ' ' + last;

            Node* node = tree->search(tree->root(), user);
            if (user != node->name()) {

                cout << "User is not in network." << endl;
                continue; 

            }

            GraphNode* graphNode = &graph.graphVec[node->order()];
            cout << graphNode->mName << endl;

            for (auto& person: graphNode->friends) {

                cout << person->mName << endl;
                cout << "   Age: " << strip(readDataAge(person->dataIndex)) << endl;
                cout << "   Occupation: " << strip(readDataJob(person->dataIndex)) << endl;

            }

        }
        else if (x == 7) {

            string firstLower, lastLower, firstUpper, lastUpper, lower, upper;
            cout << "Enter lower bound: " << endl;
            cin >> firstLower >> lastLower;
            lower = firstLower + ' ' + lastLower;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Enter upper bound: " << endl;
            cin >> firstUpper >> lastUpper;
            upper = firstUpper + ' ' + lastUpper;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');

            if (tree->count() == 0) {

                continue;

            }

            tree->rangeSearch(lower, upper);

            for (auto& user: tree->searched()) {

                cout << user->name() << endl;
                cout << "   Age: " << strip(readDataAge(user->order())) << endl;
                cout << "   Occupation: " << strip(readDataJob(user->order())) << endl;
                cout << "   Friends: " << endl;

                GraphNode node = graph.graphVec[user->order()];
                for (auto& person: node.friends) {

                    cout << "       " << person->mName << endl;

                }

            }

        }

    }
    while (x != 8);

}