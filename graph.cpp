#include <iostream>
#include <vector>
#include "graph.h"

using namespace std;

void Graph::addFriend(string friend1, string friend2, int index){
    //friend1 and friend2 have to already be in the graphVec
    
    bool foundFriendship = false; 
    //foundFriendship = searchFriendship(friend1, friend2);
    
    if(foundFriendship == false){

        GraphNode& node = graphVec[index];
        if (node.mName == friend1) {

            GraphNode* friendNode = new GraphNode(friend2);
            node.friends.push_back(friendNode);
            
        }
    }
    else {
        cout << "Already friends \n";
        return;
    }
}

void Graph::addPerson(string person){
    graphVec.push_back(GraphNode(person));
} 

bool Graph::searchFriendship(string friend2, int index) {

    vector<GraphNode*> friends = graphVec[index].friends;
    for (auto& person: friends) {

        if (person->mName == friend2) {

            return true;

        }

    }

    return false;

}