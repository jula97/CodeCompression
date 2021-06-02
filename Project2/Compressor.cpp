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
        cout << Dictionary[i]  << endl;
    }
}
