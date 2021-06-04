#include "GlobalSpace.h"
#include "Functions.h"
#include "FunctionList.h"
using namespace std;


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
            if (i == lineNo-1) {
                doRLEEncoding();
            }
        }
        PreviousLine = CurrentLine;
    }

    writeCompressed();
    MyFile << "xxxx" << endl;
    writeDictionary();
}
