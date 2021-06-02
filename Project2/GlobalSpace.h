#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string OriginalLines[117];  //Lines of the original code to be compressed
int FrequencyList[117];     //Frequency of unique lines
string Dictionary[16];      //Dictionary for compression