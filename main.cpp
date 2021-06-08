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

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

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
            
            for (auto& item: graph.graphVec) {

                for (auto& person: item.friends) {

                    Node* treeNode = tree->search(tree->root(), person->mName);
                    person->dataIndex = treeNode->order();

                }

            }

            intialized = true;

        }
        else if (x == 2) {

            string firstName, lastName, name, age, occupation, friends, friendName;
            cout << "Enter user's name:" << endl;
            getline(cin, name);

            cout << "Enter user's age:" << endl;
            cin >> age;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');

            cout << "Enter user's occupation:" << endl;
            getline(cin, occupation);

            cout << "Enter user's friends: " << endl;
            getline(cin, friends);
            stringstream ss(friends);

            graph.addPerson(name);
            int count = 1;

            while (getline(ss, friendName, ',')) {

                Node* node = tree->search(tree->root(), friendName);
                if (node->name() != friendName) {

                    cout << "Friend " << count << " is not in network." << endl;
                    count++;
                    continue;

                }

                graph.addFriend(name, friendName, counter);
                graph.addFriend(friendName, name, node->order());
                graph.graphVec[counter].friends.back()->dataIndex = node->order();
                graph.graphVec[node->order()].friends.back()->dataIndex = counter;
                count++;

            }

            addNewPerson(name, age, occupation, graph);
            tree->insertion(name);

        }
        else if (x == 3) {

            if (tree->count() == 0) {

                cout << "No users in network." << endl;
                continue;

            }

            string first1, last1, first2, last2, friend1, friend2;
            cout << "Enter friend 1:" << endl;
            getline(cin, friend1);
            cout << "Enter friend 2:" << endl;
            getline(cin, friend2);

            Node* node1 = tree->search(tree->root(), friend1);
            Node* node2 = tree->search(tree->root(), friend2);

            if (node1->name() != friend1 && node2->name() != friend2) {

                cout << "Both friends are not in the network." << endl;
                continue;

            }
            if (node1->name() != friend1) {

                cout << "Friend 1 is not in the network." << endl;
                continue;

            }
            if (node2->name() != friend2) {

                cout << "Friend 2 is not in the network." << endl;
                continue;

            }
            if (node1->name() == node2->name()) {

                cout << "User cannot be friends with themselves." << endl;
                continue;

            }
            if (graph.searchFriendship(friend2, node1->order())) {

                cout << "Users are already friends." << endl;
                continue;

            }

            graph.addFriend(friend1, friend2, node1->order());
            graph.graphVec[node1->order()].friends.back()->dataIndex = node2->order();

            graph.addFriend(friend2, friend1, node2->order());
            graph.graphVec[node2->order()].friends.back()->dataIndex = node1->order();

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
            getline(cin, user);

            if (tree->count() == 0) {

                cout << "User is not in network." << endl;
                continue; 

            }

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
            getline(cin, user);

            if (tree->count() == 0) {

                cout << "User is not in network." << endl;
                continue; 

            }

            Node* node = tree->search(tree->root(), user);
            if (user != node->name()) {

                cout << "User is not in network." << endl;
                continue; 

            }

            GraphNode* graphNode = &graph.graphVec[node->order()];
            cout << "Person: " << graphNode->mName << endl;

            if (graphNode->friends.size() == 0) {

                cout << "No friends." << endl;
                continue;

            }

            for (auto& person: graphNode->friends) {

                cout << person->mName << endl;
                cout << "   Age: " << strip(readDataAge(person->dataIndex)) << endl;
                cout << "   Occupation: " << strip(readDataJob(person->dataIndex)) << endl;

            }

        }
        else if (x == 7) {

            string firstLower, lastLower, firstUpper, lastUpper, lower, upper;
            cout << "Enter lower bound: " << endl;
            getline(cin, lower);
            cout << "Enter upper bound: " << endl;
            getline(cin, upper);

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