#ifndef PARSE_H
#define PARSE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>
#include "graph.h"
#include "RedBlack.h"

using namespace std; 


void consumeColumnNames(ifstream &myFile);
string getField(stringstream &ss);
string stripQuotes(std::string temp);
string readDataName(int lineNumber);
string readDataJob(int lineNumber);
string readDataAge(int lineNumber);
void addNewPerson(string name, string age, string job, Graph& g);
void read_csv(string fileName, Graph& g, Tree* t);

#endif