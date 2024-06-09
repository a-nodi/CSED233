#include "open_hash_function.h"
#include <iostream>
#include <fstream>
#include <string>


using namespace std;


int OpenHashFunction::openhashing(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    // Digit folding method
    int sum;

    for (sum = 0; key != 0; key /= 10) {
        sum += key % 10;
    }
    
    return sum % index_size;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
