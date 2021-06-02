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
    int count = 0;
    int max = 0;

    int FrequencyCopy[117];
    std::copy(FrequencyList, FrequencyList + 117, FrequencyCopy);  //copy the frequencyList to sort
    int n = sizeof(FrequencyList) / sizeof(FrequencyList[0]);
    sort(FrequencyCopy, FrequencyCopy + n, greater<int>());  // sorting according to frequency

    max = FrequencyCopy[count];

    while (max != 0)
    {
        for (size_t i = 0; i < 117; i++)
        {
            if (FrequencyList[i] == max) {
                Dictionary[count] = OriginalLines[i]; //adding to dictionary according to frequency
                FrequencyList[i] = 0;
                count++;
            }
        }
        if (count == 16) {
            break;
        }
        else {
            max = FrequencyCopy[count];
        }
    }
}
