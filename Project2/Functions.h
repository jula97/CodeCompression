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

int largestFreq(int arr[], int n) {
    int i;
    int max = arr[0];
    for (i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void dictionarySelect() {
    int count = 0;
    int max = largestFreq(FrequencyList, 117);
    while (max != 0)
    {
        for (size_t i = 0; i < 117; i++)
        {
            if (FrequencyList[i] == max) {
                Dictionary[count] = OriginalLines[i];
                FrequencyList[i] = 0;
                count++;
            }
        }
        if (count == 16) {
            break;
        }
        else {
            max = largestFreq(FrequencyList, 117);
        }
    }
}

