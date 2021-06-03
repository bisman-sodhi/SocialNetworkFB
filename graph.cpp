#include <iostream>
#include <vector>
#include "graph.h"

using namespace std;

void Graph::addFriend(string friend1, string friend2){
    //friend1 and friend2 have to already be in the graphVec
    
    bool foundFriendship = false; 
    //foundFriendship = searchFriendship(friend1, friend2);
    
    if(foundFriendship == false){
        for (auto& node: graphVec) {

            if (node.mName == friend1) {

                GraphNode* friendNode = new GraphNode(friend2);
                node.friends.push_back(friendNode);

            }

        }  
    }
    else {
        cout << "Already friends \n";
        return;
    }
}

bool Graph::searchFriendship(string friend1, string friend2){
    bool ans1 = false;
    bool ans2 = false; 
    //if(searchPerson(friend1)){}
    for(auto& x : graphVec){

        if(x.mName == friend1){
            GraphNode * temp = &x; 
            while(temp->nextNode != NULL){
                
                if(temp->nextNode->mName == friend2){
                    ans1 = true;
                }
                else{ 
                    temp->nextNode = temp->nextNode->nextNode;
                }
            }
        }
        //repeat the same process if friend2 is found first in the vector
        else if(x.mName == friend2){
            GraphNode * temp = &x; 
            while(temp->nextNode != NULL){
                if(temp->nextNode->mName == friend1){
                    ans2 = true;
                }
                else{ 
                    temp->nextNode = temp->nextNode->nextNode;
                }
            }            
        }

    }
    return (ans1 && ans2);
}

/*
GraphNode & Graph::searchPerson(string person){
    for(auto & x : graphVec){
        if(x.mName == person){
            return x;
        }
    }
}
*/

void Graph::addPerson(string person){
    graphVec.push_back(GraphNode(person));
}

void Graph::printFriends(string person){
    
    /*for(auto x : graphVec){
        if(x.mName == person){
            GraphNode * temp = &x; 
            while(temp->nextNode != NULL){
                cout << temp->nextNode->mName << endl;
                temp = temp->nextNode; 
            }
        }
    }*/

    for (auto& node: graphVec) {

        if (node.mName == person) {

            for (auto& item: node.friends) {

                cout << item->mName << endl;

            }

        }

    }
}

void Graph::printFriendsAge(string person){
    
    for(auto x : graphVec){
        if(x.mName == person){
            GraphNode * temp = &x; 
            while(temp->nextNode != NULL){
                cout << temp->nextNode->mName << endl;
                temp = temp->nextNode; 
            }
        }
    }
}    
