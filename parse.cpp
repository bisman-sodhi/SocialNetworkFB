#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "graph.h"
#include "parse.h"
#include "RedBlack.h"
#include "Common.h"

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

string readDataName(int lineNumber){
    
    ifstream temp; 
    temp.open("data.txt");
    temp.seekg(0, ios::end);
    // i think the line length is 54 because it 53 bits + "\0" end line character
    int length = temp.tellg();
    char holdName[20];
    int position = ( (lineNumber) * 54);
    temp.seekg(position, ios::beg);
    char a2[20];
    temp.read(a2, 20);

    return a2;
    
}

string readDataAge(int lineNumber){
    
    ifstream temp; 
    temp.open("data.txt");
    temp.seekg(0, ios::end);
    // i think the line length is 54 because it 53 bits + "\n" end line character
    int length = temp.tellg();
    char holdName[3];
    int position = ( (lineNumber) * 54) + 20;
    temp.seekg(0, ios::beg);
    temp.seekg(position, ios::beg);
    char a2[3];
    temp.read(a2, 3);

    return a2;
}

string readDataJob(int lineNumber){
    
    ifstream temp; 
    temp.open("data.txt");
    temp.seekg(0, ios::end);
    // i think the line length is 54 because it 53 bits + "\n" end line character
    int length = temp.tellg();
    char holdName[3];
    int position = ( (lineNumber) * 54) + 23;
    temp.seekg(0, ios::beg);
    temp.seekg(position, ios::beg);
    char a2[30];
    temp.read(a2, 30);

    return a2;
    
}

void addNewPerson(string name, string age, string job, Graph& g){
    //converting string to char
    char forName[20]; 
    strncpy(forName, name.c_str(), sizeof(forName));
    char forAge[3];
    strncpy(forAge, age.c_str(), sizeof(forAge));
    char forJob[30];
    strncpy(forJob, job.c_str(), sizeof(forJob));   
    //opening file to read
    ofstream outfile;
    //outfile.open("data.txt", ios::in); 
    outfile.open("data.txt", std::ios::app);
    //Global Initialiation of Graph
    //g.addPerson(name);
    // inserting into Profile Data
    outfile.seekp(0, ios::end);
    int fileLength = outfile.tellp();
    int position = fileLength/54;
    outfile.seekp(position, ios::beg);
    outfile << forName;
    string hold = "";
    int nameSize = sizeof(forName);    
    int usedNameSize = strlen(forName);
    while(usedNameSize < nameSize){
        hold = hold + "@";
        usedNameSize++; 
    }
    outfile << hold;
    //writring age 
    outfile << age;
    string aAge = "";
    int ageSize = sizeof(forAge);
    int usedAgeSize = strlen(forAge);
    while(usedAgeSize < ageSize){
        aAge = aAge + "@";
        usedAgeSize++;
    }
    outfile << aAge; 
    outfile << job;
    string jJob = "";
    int jobSize = sizeof(forJob);
    int usedJobSize = strlen(forJob);
    while(usedJobSize < jobSize){
        jJob = jJob + "@";
        usedJobSize++;
    }
    outfile << jJob; 
    //add endline
    outfile << "\n";
    counter++;
}

void read_csv(string fileName, Graph& g, Tree* t){
    ifstream inputFile(fileName);
    string line;
    
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
        t->insertion(name);

        string data; 
        stringstream friends(Friend);
        while(getline(friends, data, ',')){
            g.addFriend(name, data, counter);
        }
        counter++;

        int nameSize = sizeof(forName);    
        int usedNameSize = strlen(forName);
        outfile << forName;
        string hold = "";
        while(usedNameSize < nameSize){
            hold = hold + "@";
            usedNameSize++; 
        }

        outfile << hold; 
        
        const char * a = "@";
        int ageSize = sizeof(forAge);
        int usedAgeSize = strlen(forAge);
        for(usedAgeSize; strlen(forAge) < ageSize; usedAgeSize++){
            strcat(forAge, a);
        }

        const char * j = "@"; 
        int jobSize = sizeof(forJob);
        int usedForJob = strlen(forJob);
        for(usedForJob; strlen(forJob) < jobSize; usedForJob++){
            strcat(forJob, j); 
        }

        outfile <<  forAge << forJob << endl;
    }
    
}




