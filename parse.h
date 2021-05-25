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
#include "global.h"
#include "profileData.h"

using namespace std; 

void read_csv(string fileName);
void consumeColumnNames(ifstream &myFile);
string getField(stringstream &ss);
string stripQuotes(std::string temp);

#endif