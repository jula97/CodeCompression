#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <bitset>
#include <map>

//#include "GlobalSpace.h"
//#include "Functions.h"
//#include "FunctionList.h"
using namespace std;
typedef std::pair <int, int> IntPair;

vector<string> OriginalLines;  //Lines of the original code to be compressed
vector<int> FrequencyList;     //Frequency of unique lines
string Dictionary[16];      //Dictionary for compression
vector<string> vectDictionary;
std::vector<string>::iterator it;
string compared[16];
int ones[16];
bool HitFlag = false;
string PreviousLine;
string CurrentLine;
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
string CompressedLine;
vector<string> CompressedCode;
int TotalLength;
ofstream MyFile("filename.txt");
int lineNo;
map<string, int> freqMap;
vector <IntPair> pairs;

void readOriginal() {
    ifstream inFile("original.txt");
    string line;
    lineNo = 0;
    while (getline(inFile, line)) {
        OriginalLines.push_back(line);
        lineNo++;
    }
    inFile.close();
    //cout << lineNo << endl;
}

void frequencySelect() {
    string line;
    vector<string> OriginalCopy;
    for (int j = 0; j < OriginalLines.size(); j++) {
        OriginalCopy.push_back(OriginalLines[j]);
    }
    //long multi = 0.001;
    for (size_t i = 0; i < lineNo; i++)
    {
        line = OriginalCopy[i];
        if (OriginalCopy[i] != "0") {
            int frequency = 0;
            for (size_t j = 0; j < lineNo; j++)  //find the frequency of occurance of a line
            {
                if (OriginalCopy[j] == line) {
                    frequency++;
                    OriginalCopy[j] = "0";
                }
            }
            //freqMap.insert(pair<string, int>(line , frequency));
            FrequencyList.push_back(frequency);
            pairs.push_back(std::make_pair(i, frequency));
            //cout << "gg" << endl;
        }
    }
}

void dictionarySelect() {
    sort(FrequencyList.begin(), FrequencyList.end(), greater<int>());

    int count = 0;
    int max = FrequencyList[count];

    while (count != 16) {
        for (size_t i = 0; i < pairs.size(); i++) {
            pair<int, int> temp = pairs[i];
            if (max == temp.second) {
                Dictionary[count] = OriginalLines[temp.first];
                count++;
                pairs[i].second = 0;
                max = FrequencyList[count];
                break;
            }
        }
    }
}

void makeDictionaryVector() {
    for (size_t i = 0; i < 16; i++) {
        vectDictionary.push_back(Dictionary[i]);
    }
}

void isDictionaryHit(string line) {
    it = std::find(vectDictionary.begin(), vectDictionary.end(), line);
    if (it != vectDictionary.end())
    {
        HitFlag = true;
        int s1 = it - vectDictionary.begin();
        CompressedLine = "111" + FourBitLookup[s1];
        //cout << CompressedLine << endl;
        CompressedCode.push_back(CompressedLine);
    }
}

int hammingWeight(string n) {
    int count = 0;
    for (size_t i = 0; i < 32; i++) {
        if (n[i] == '1') {
            count++;
        }
    }
    return count;
}

void isOneBitMismatch() {
    for (size_t l = 0; l < 16; l++) {
        if (ones[l] == 1) {
            int idx = compared[l].find("1");
            if (idx != string::npos) {
                CompressedLine = "011" + FiveBitLookup[idx] + FourBitLookup[l];
                //cout << CompressedLine << endl;
                CompressedCode.push_back(CompressedLine);
                HitFlag = true;
                return;
            }
        }
    }
}

void isTwoBitMismatch() {
    for (size_t j = 0; j < 16; j++) {
        if (ones[j] == 2) {
            int idx = compared[j].find("11");
            if (idx != string::npos) {
                CompressedLine = "100" + FiveBitLookup[idx] + FourBitLookup[j];
                //cout << CompressedLine << endl;
                CompressedCode.push_back(CompressedLine);
                HitFlag = true;
                return;
            }
        }
    }
}

void isFourBitMismatch() {
    for (size_t k = 0; k < 16; k++) {
        if (ones[k] == 4) {
            int idx = compared[k].find("1111");
            if (idx != string::npos) {
                CompressedLine = "101" + FiveBitLookup[idx] + FourBitLookup[k];
                //cout << CompressedLine << endl;
                CompressedCode.push_back(CompressedLine);
                HitFlag = true;
                return;
            }
        }
    }
}

void isBitmaskMismatch() {
    int idx = -1;
    for (size_t j = 0; j < 16; j++) {
        if ((ones[j] == 2) || (ones[j] == 3)) {
            for (size_t k = 0; k < 5; k++)
            {
                idx = compared[j].find(BitMasks[k]);
                if ((idx != string::npos) && ones[j] == BitMaskOnes[k]) {
                    CompressedLine = "010" + FiveBitLookup[idx] + BitMasks[k] + FourBitLookup[j];
                    //cout << CompressedLine << endl;
                    CompressedCode.push_back(CompressedLine);
                    HitFlag = true;
                    return;
                }
            }
        }
    }
}

void isTwoBitMismatch2() {
    int found = -1;
    int idx = -1;
    for (size_t j = 0; j < 16; j++) {
        if (ones[j] == 2) {
            idx = compared[j].find("1");
            found = compared[j].find("1", idx + 1);
            if ((idx != string::npos) || (found != string::npos)) {
                CompressedLine = "110" + FiveBitLookup[idx] + FiveBitLookup[found] + FourBitLookup[j];
                //cout << CompressedLine << endl;
                CompressedCode.push_back(CompressedLine);
                HitFlag = true;
                return;
            }
        }
    }
}

void isIndirectHit(string line) {
    for (size_t i = 0; i < 16; i++) {
        auto result = std::bitset<32>(Dictionary[i]) ^ std::bitset<32>(line);
        compared[i] = result.to_string();
        ones[i] = hammingWeight(compared[i]);
    }
}

void doRLEEncoding() {
    CompressedLine = "001" + ThreeBitLookup[SimilarCount - 1];
    //cout << CompressedLine << endl;
    CompressedCode.push_back(CompressedLine);
    SimilarCount = 0;
}

void writeCompressed() {
    for (size_t j = 0; j < CompressedCode.size(); j++) {
        int s3 = 32 - TotalLength % 32;
        if (s3 + 1 > CompressedCode[j].length()) {
            MyFile << CompressedCode[j];
            if (((TotalLength + CompressedCode[j].length()) % 32) == 0) {
                MyFile << endl;
            }
        }
        else {
            string s4 = CompressedCode[j].substr(0, s3);
            string s5 = CompressedCode[j].substr((s3), (CompressedCode[j].length() - s3));
            if (((TotalLength + CompressedCode[j].length()) % 32) == 0) {
                MyFile << s4 << endl;
                if (s5.length() > 32) {
                    MyFile << s5.substr(0, 32) << endl;
                    MyFile << s5.substr(32, s5.length() - 32) << endl;
                }
                else {
                    MyFile << s5 << endl;
                }
            }
            else {
                MyFile << s4 << endl;
                if (s5.length() > 32) {
                    MyFile << s5.substr(0, 32) << endl;
                    MyFile << s5.substr(32, s5.length() - 32);
                }
                else {
                    MyFile << s5;
                }
            }
        }
        TotalLength += CompressedCode[j].length();
    }
    for (size_t k = 0; k < 32 - (TotalLength % 32); k++) {
        MyFile << "0";
    }
    MyFile << endl;
}

void writeDictionary() {
    for (size_t i = 0; i < 16; i++) {
        MyFile << Dictionary[i] << endl;
    }
}


int main() {
    readOriginal();
    frequencySelect();
    dictionarySelect();
    makeDictionaryVector();

    for (size_t i = 0; i < lineNo; i++) {
        CurrentLine = OriginalLines[i];
        if (CurrentLine != PreviousLine) {
            if (SimilarCount != 0) {
                doRLEEncoding();
            }
            HitFlag = false;
            isDictionaryHit(CurrentLine);
            if (HitFlag == false) {
                isIndirectHit(CurrentLine);
                isOneBitMismatch();
            }
            if (HitFlag == false) {
                isTwoBitMismatch();
            }
            if (HitFlag == false) {
                isFourBitMismatch();
            }
            if (HitFlag == false) {
                isBitmaskMismatch();
            }
            if (HitFlag == false) {
                isTwoBitMismatch2();
            }
            if (HitFlag == false) {
                CompressedLine = "000" + CurrentLine;
                CompressedCode.push_back(CompressedLine);
            }
        }
        else if (CurrentLine == PreviousLine) {
            SimilarCount++;
            if (SimilarCount == 8) {
                doRLEEncoding();
                CurrentLine = "AAAA";
            }
            if (i == lineNo - 1) {
                doRLEEncoding();
            }
        }
        PreviousLine = CurrentLine;
    }

    writeCompressed();
    MyFile << "xxxx" << endl;
    writeDictionary();
}
