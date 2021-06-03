#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <bitset>
using namespace std;

string OriginalLines[117];  //Lines of the original code to be compressed
string CompressedLines[118];
int CompressedLineLength = 0;
int FrequencyList[117];     //Frequency of unique lines
string Dictionary[16];      //Dictionary for compression
vector<string> vectDictionary;
std::vector<string>::iterator it;
string compared[16];
int ones[16];
bool HitFlag = false;
string PreviousLine;
string CurrentLine;
string CompressedLine;
int SimilarCount = 0;
string FiveBitLookup[32] = { "00000","00001","00010","00011","00100","00101","00110",
							"00111","01000","01001","01010","01011","01100","01101",
							"01110","01111","10000","10001","10010","10011","10100",
							"10101","10110","10111","11000","11001","11010","11011",
							"11100","11101","11110","11111" };
string FourBitLookup[16] = { "0000","0001","0010","0011","0100","0101","0110","0111",
							"1000","1001","1010","1011","1100","1101","1110","1111" };
string ThreeBitLookup[8] = { "000","001","010","011","100","101","110","111" };
string BitMasks[5] = { "1010","1001","1011","1101","1110" };
int BitMaskOnes[5] = { 2,2,3,3,3 };