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
string PreviousLine;
string CurrentLine;
int SimilarCount = 0;
string IndexLookup[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
string BitMasks[5] = { "1010","1001","1011","1101","1110" };
int BitMaskOnes[5] = { 2,2,3,3,3 };