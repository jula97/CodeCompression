void readOriginal() {
    ifstream inFile("original.txt");
    string line;
    int lineNo = 0;
    while (getline(inFile, line)) {
        OriginalLines[lineNo] = line;
        lineNo++;
    }
    inFile.close();
}

void frequencySelect() {
    string line;
    string OriginalCopy[117];
    std::copy(OriginalLines, OriginalLines + 117, OriginalCopy);

    for (size_t i = 0; i < 117; i++)
    {
        line = OriginalCopy[i];
        if (OriginalCopy[i] != "0") {
            int frequency = 0;
            for (size_t j = 0; j < 117; j++)  //find the frequency of occurance of a line
            {
                if (OriginalCopy[j] == line) {
                    frequency++;
                    OriginalCopy[j] = "0";
                }
            }
            FrequencyList[i] = frequency;
        }
    }
}

void dictionarySelect() {
    int FrequencyCopy[117];
    std::copy(FrequencyList, FrequencyList + 117, FrequencyCopy); //copying the frequency list for sorting
    int n = sizeof(FrequencyList) / sizeof(FrequencyList[0]);
    sort(FrequencyCopy, FrequencyCopy + n, greater<int>()); //sorting the Frequencies
    
    int count = 0;
    int max = FrequencyCopy[count];

    while (max != 0){
        for (size_t i = 0; i < 117; i++){
            if (FrequencyList[i] == max) {
                Dictionary[count] = OriginalLines[i]; //assigning dictionary entries
                FrequencyList[i] = 0;
                count++;
                if (count == 16) { 
                    return; 
                }
            }
        }
        max = FrequencyCopy[count]; 
    }
}

void makeDictionaryVector() {
    for (size_t i = 0; i < 16; i++){
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
    for (size_t i = 0; i < 16; i++){
        MyFile << Dictionary[i] << endl;
    }
}