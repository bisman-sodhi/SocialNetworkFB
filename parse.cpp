#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "graph.h"
#include "global.h"
#include "parse.h"
#include "profileData.h"

using namespace std; 


string stripQuotes(std::string temp) {
    temp.erase(
        remove(temp.begin(), temp.end(), '\"' ),
        temp.end());
    return temp;
}


string getField(std::stringstream &ss) {
    string data;
    std::getline(ss, data, ',');
    return stripQuotes(data);
}

string getFriends(stringstream &ss){
    string data; 
    getline(ss, data);
    return stripQuotes(data); 
}

string getOneFriend(string &s) {
    string data;
    stringstream ss(s); 
    while(ss.good()){
       // getline(ss, data, ",");
    }
    return data; 
}

void consumeColumnNames(ifstream &myFile) {
    std::string line;
    std::string colname;

    // Extract the first line in the file
    std::getline(myFile, line);

    // Create a stringstream from line
    std::stringstream ss(line);

    // Read the column names (for debugging)
    // Extract each column name for debugging
    while(std::getline(ss, colname, ',')) {
        //std::cout << colname << std::endl;
    }
}


void read_csv(string fileName){
    ifstream inputFile(fileName);
    string line;
    Graph g; 

    
    //read the column names  
    consumeColumnNames(inputFile); 
    ofstream outfile;
    outfile.open("data.txt", ios::out); 

    while(getline(inputFile, line)){
        stringstream ss(line);

        //getting individuals pieces from line
        string name = getField(ss);
        string age = getField(ss);
        string job = getField(ss);
        string Friend = getFriends(ss);
        
        //converting string to char
        char forName[20]; 
        strncpy(forName, name.c_str(), sizeof(forName));
        char forAge[3];
        strncpy(forAge, age.c_str(), sizeof(forAge));
        char forJob[30];
        strncpy(forJob, job.c_str(), sizeof(forJob));   

        //inserting to vector
        g.addPerson(name); 
        string data; 
        stringstream friends(Friend);
        while(getline(friends, data)){
            g.addFriend(name, data);
        }

        outfile << forName << forAge << forJob << endl;
    }

    cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
    cout << "graph name check" << endl;
    for(auto x : g.graphVec){
        cout << "name is " << x.mName << endl;
        cout << "friends are "; 
        g.printFriends(x.mName); 

    }

    //Testing individual cases
    cout << "printing elizabeth's friends \n"; 
    g.printFriends("Elizabeth Yang");
    
}




