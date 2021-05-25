#include <iostream>
#include <vector>
#include "graph.h"
#include "global.h"
#include "parse.h"
#include "profileData.h"

using namespace std;

int gVecIndex; 

int main() {
    gVecIndex = 0; 
/*
    //GraphNode person("a");
    //GraphNode person2("b");
    string a = "a";
    string b = "b"; 
    string c = "c"; 
    string d = "d"; 

    Graph g(a);
    g.addPerson(b);
    g.addPerson(c);
    g.addPerson(d);

    g.addFriend(a, b);
    g.addFriend(a,c);
    g.addFriend(b,d);

    cout << "a's friends are ";
    g.printFriends(a);
    cout << "b's friends are "; 
    g.printFriends(b);
    cout << "c's friends are "; 
    g.printFriends(c);
    cout << "d's friends are "; 
    g.printFriends(d); 
    

    for(auto x : g.graphVec){
        cout << "name is " << x.mName << " next node is " << x.nextNode->mName << endl;
    }


    for(auto x : g.graphVec){
        while (x.nextNode !=  NULL){
            cout << x.nextNode->mName << endl;
            x.nextNode = x.nextNode->nextNode;
        }
    }
*/
    read_csv("usersNew_10.csv");

    return 0; 
}