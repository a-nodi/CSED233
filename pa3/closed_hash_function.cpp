#include "closed_hash_function.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int pow(int x, int n);
int base2to10(int n);
int base10to2(int n);

int ClosedHashFunction::closedhashing(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    int squared, mid, hash_key;
    squared = base10to2(key * key); // squeare key and change base to 2
    mid = (squared / int(pow(10, key_size - index_size / 2))) % int(pow(10, index_size)); // extract base 2 hashkey
    hash_key = base2to10(mid); // change hashkey's base to 10 

    return hash_key;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
  
}


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////


int pow(int x, int n) {
    int result = 1;

    for (int i = 0; i < n; i++) result *= x;
    return result;
}

int base2to10(int n) {
    int decimal = 0;
    for (int i = 0; n > 0; i++, n /= 10) {
        if (n % 2 != 0) decimal += pow(2, i);
    }
    return decimal;
}

int base10to2(int n) {
    int binary = 0;
    for (int i = 0; n > 0; i++, n /= 2) binary += (n % 2) * pow(10, i);
    
    return binary;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
