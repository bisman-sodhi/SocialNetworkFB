#ifndef PROFILE_H
#define PROFILE_H
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include "graph.h"
#include "global.h"

using namespace std; 

struct profileData
{
    /*
    char name[20];
    char age[3];
    char job[30];

    profileData() : name(""), age(""), job("") {};
    profileData(char inName[20], char inAge[3], char inJob[30] ) {
        name[20] = inName[20]; 
        age[3] = inAge[3]; 
        job[30] = inJob[30]; 

        cout << name  << " "<< age << " " << job << endl;
    }
    */
    string name; 
    string age;
    string job;
    profileData(string inName, string inAge, string inJob){
        name = inName;
        age = inAge;
        job = inJob; 
        cout << name  << " "<< age << " " << job << endl;
    }

    //write a outstream function on disk;
    void onDisk(string name, string age, string job){
        string line; 
        ofstream outFile;
        outFile.open("ProDataFile.txt", ios::out); 

        outFile << name << "," << age <<"," << job << endl; 

    } 

};



#endif