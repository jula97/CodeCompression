#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <bitset>
using namespace std;

string OriginalLines[117];  //Lines of the original code to be compressed
int FrequencyList[117];     //Frequency of unique lines
string Dictionary[16];      //Dictionary for compression
vector<string> vectDictionary;
std::vector<string>::iterator it;
string compared[16];
int ones[16];
bool HitFlag = false;