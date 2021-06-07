#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>

using namespace std;

struct GraphNode {

    string mName;
    int dataIndex; 
    GraphNode * nextNode;
    vector<GraphNode*> friends;
    GraphNode() : mName(""), nextNode(NULL) {}; 
    GraphNode(string inName) : mName(inName), nextNode(NULL) {}; 
    GraphNode(string inName, GraphNode * inPtr) : mName(inName), nextNode(inPtr) {};

    //pointer to ProfileData: integer index of person's information on disk
    //pointer to left/right


};

class Graph {
   // private: 
        //vector<GraphNode> graphVec; 
        //pair<GraphNode, GraphNode> friends; 

    public: 
        //constructor
        vector<GraphNode> graphVec;
        int gVecIndex;

        Graph(string inVec) {
            graphVec.resize(10); 
            graphVec[0] = GraphNode(inVec);
        };
        
        Graph(){
            gVecIndex = 0;
        }
        
        
        //member functions: 
        void addFriend(string friend1, string friend2, int index);
        //could change return type from bool to something else
        bool searchFriendship(string friend2, int index);
        GraphNode & searchPerson(string person); 
        void addPerson(string person); 
        void printFriends(string person);
        void printFriendsAge(string person);



};

#endif