#include "GlobalSpace.h"
#include "Functions.h"
#include "FunctionList.h"
using namespace std;


int main() {
    readOriginal();
    frequencySelect();
    dictionarySelect();
    for (size_t i = 0; i < 16; i++)
    {
      cout << Dictionary[i] << endl;
    }
    makeDictionaryVector();


    for (size_t i = 0; i < 117; i++)
    {


        string test = OriginalLines[i];
        HitFlag = false;

        isDictionaryHit(test);

        if (HitFlag == false) {
            isIndirectHit(test);
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
            cout << "uncompressed line" << endl;
        }
    }
}
