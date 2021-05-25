#include <iostream>
#include <vector>
#include "graph.h"
#include "global.h"

using namespace std;

void Graph::addFriend(string friend1, string friend2){
    //friend1 and friend2 have to already be in the graphVec
    
    bool foundFriendship = false; 
    //foundFriendship = searchFriendship(friend1, friend2);
    
    if(foundFriendship == false){
        for(auto &x : graphVec){
            if(x.mName == friend1){
                while(x.nextNode != NULL){
                    x.nextNode = x.nextNode->nextNode;
                }
                x.nextNode = new GraphNode(friend2);     
            }
            if(x.mName == friend2){
                while(x.nextNode != NULL){
                    x.nextNode = x.nextNode->nextNode;
                }
                x.nextNode = new GraphNode(friend1);              
            }
        }   
    }
    else {
        cout << "Already friends \n";
        return;
    }
}

bool Graph::searchFriendship(string friend1, string friend2){

    //if(searchPerson(friend1)){}
    for(auto& x : graphVec){
       
        if(x.mName == friend1){
            
            while(x.nextNode != NULL){
                
                if(x.nextNode->mName == friend2){
                    return true;
                }
                else{ 
                    x.nextNode = x.nextNode->nextNode;
                }
            }
        }
        //repeat the same process if friend2 is found first in the vector
        else if(x.mName == friend2){
            while(x.nextNode != NULL){
                if(x.nextNode->mName == friend1){
                    return true;
                }
                else{ 
                    x.nextNode = x.nextNode->nextNode;
                }
            }            
        }

    }
    return false;
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
    graphVec[gVecIndex] = GraphNode(person);
    gVecIndex++; 
}

void Graph::printFriends(string person){
    
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