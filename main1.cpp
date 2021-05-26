#include "RedBlack.h"

#include <iostream>
#include <string>
#include <sstream>

int main() {

    Tree* tree = new Tree();
    // Graph graph();
    // DataFile data();
    int x;

    do {

        cout << "Welcome!" << endl;
        cout << "1) Intialize the network." << endl;
        cout << "2) Insert a new user." << endl;
        cout << "3) Insert a friendship." << endl;
        cout << "4) Print all." << endl;
        cout << "5) List friends' info." << endl;
        cout << "6) List info." << endl;
        cout << "7) Exit." << endl;
        cout << "Which operation do you want to make? (1,2,3,4,5,6,7):";
        cin >> x;

        while  (x != 1 && x != 2 && x != 3 && x != 4 && x != 5 && x!= 6) {

            cout << "wrong operation!" << endl;
            cout << "Which operation do you want to make? (1,2,3,4,5,6,7):";
            cin >> x;

        }

        if (x == 1) {

            string file;
            cout << "Enter file name:" << endl;
            cin >> file;

            file = file + ".csv";
            // read_csv(file);

        }
        else if (x == 2) {

            cout << "Enter user's name, age, and occupation:" << endl;
            string name, age, occupation;
            cin >> name >> age >> occupation;
            // data.profile(name, age, occupation);

        }
        else if (x == 3) {

            cout << "Enter friends:" << endl;
            string friend1, friend2;
            cin >> friend1 >> friend2;
            // graph.addFriendship(friend1, friend2);
            // data.addFriendship(friend1, friend2);

        }
        else if (x == 4) {

            if (tree->count() == 0) {

                cout << "No users in network.  Choose another operation." << endl;
                cin >> x;

            }

            tree->rangeSearch(tree->getMin(), tree->getMax());

            for (auto& user: tree->searched()) {

                cout << user->name() << endl;
                cout << "   Age: " << endl; // graph[user.order()].age
                cout << "   Occupation: " << endl; // graph[user.order()].occupation
                cout << "   Friends: " << endl; // graph[user.order()].friends

            }

        }
        else if (x == 5) {

            string user;
            cout << "Enter user: " << endl;
            cin >> user;

            //for (auto& friend: friends) {

                cout << endl; //graph[user.order()].name
                cout << "   Age: " << endl; // graph[user.order()].age
                cout << "   Occupation: " << endl; // graph[user.order()].occupation

            //}

        }
        else if (x == 6) {

            string lower, upper;
            cout << "Enter lower and upper bound: " << endl;
            cin >> lower >> upper;

            tree->rangeSearch(tree->search(tree->root(), lower), tree->search(tree->root(), upper));

            for (auto& user: tree->searched()) {

                cout << user->name() << endl;
                cout << "   Age: " << endl; // graph[user.order()].age
                cout << "   Occupation: " << endl; // graph[user.order()].occupation
                cout << "   Friends: " << endl; // graph[user.order()].friends

            }

        }

    }
    while (x != 7);

}