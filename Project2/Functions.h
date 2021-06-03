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
        //long long value;
        //std::istringstream iss(Dictionary[i]);
        //iss >> value;
        vectDictionary.push_back(Dictionary[i]);
    }
}

void isDictionaryHit(string line) {
    it = std::find(vectDictionary.begin(), vectDictionary.end(), line);
    if (it != vectDictionary.end())
    {
        HitFlag = true;
        std::cout << "Element " << line << " found at position : ";
        std::cout << it - vectDictionary.begin() << " (counting from zero) \n";
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
                cout << "One bit Mismatch" << endl;
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
                cout << "Two bit Mismatch" << endl;
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
                cout << "Four bit Mismatch" << endl;
                HitFlag = true;
                return;
            }
        }
    }
}

void isBitmaskMismatch() {
    string BitMasks[5] = {"1010","1001","1011","1101","1110"};
    int idx = -1;
    for (size_t j = 0; j < 16; j++) {
        if ((ones[j] == 2) || (ones[j] == 3)) {
            for (size_t k = 0; k < 5; k++)
            {
                idx = compared[j].find(BitMasks[k]);
                if (idx != string::npos) { break; }
            }
            if (idx != string::npos) {
                cout << "Bitmask Mismatch" << endl;
                HitFlag = true;
                return;
            }
        }
    }
}


void isTwoBitMismatch2() {
    for (size_t j = 0; j < 16; j++) {
        if (ones[j] == 2) {
            int idx = compared[j].find("11");
            if (idx == string::npos) {
                cout << "Two bit not consecutive Mismatch" << endl;
                HitFlag = true;
                return;
            }
        }
    }
}


void isIndirectHit(string line) {
    for (size_t i = 0; i < 16; i++){
        auto result = std::bitset<32>(Dictionary[i]) ^ std::bitset<32>(line);
        compared[i] = result.to_string();
        ones[i] = hammingWeight(compared[i]);
    }
}