#include <iostream>
#include <fstream>
#include <string>
#include "closed_hash_function.h"
#include "closed_hash_table.h"

using namespace std;

int p(int i);

ClosedHashTable::ClosedHashTable(int table_size, ClosedHashFunction *hf) : table_size(table_size) {
    this->hf = hf;
    this->table = new int[this->table_size];
    this->states = new ClosedTableState[this->table_size];

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    /*  Write your codes if you need  */
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

ClosedHashTable::~ClosedHashTable() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    /*  Write your codes if you need  */
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    delete[] this->table;
    delete[] this->states;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void ClosedHashTable::print_table(ostream &out) {
    for (int i=0; i < this->table_size; i++) {
        out << i << ": ";
        if (this->states[i] == CLOSED_EMPTY)
            out << "empty" << endl;
        else if (this->states[i] == CLOSED_DELETED)
            out << "deleted" << endl;
        else if (this->states[i] == CLOSED_OCCUPIED)
            out << this->table[i] << endl;
        else
            out << "unknown state" << endl;
    }
}

void ClosedHashTable::insert(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    int hash_key, h;
    h = hf->closedhashing(key);
    for (int i = 0; i < table_size; i++) {
        hash_key = (h + p(i)) % table_size;

        if (states[hash_key] == CLOSED_EMPTY) { // for only empty slot
            table[hash_key] = key;
            states[hash_key] = CLOSED_OCCUPIED;
            break;
        }
    }
    
    return;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

void ClosedHashTable::erase(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    int hash_key, h;
    h = hf->closedhashing(key);
    for (int i = 0; i < table_size; i++) {
        hash_key = (h + p(i)) % table_size;

        if (states[hash_key] == CLOSED_OCCUPIED && table[hash_key] == key) { // for only occupied slot
            table[hash_key] = 0;
            states[hash_key] = CLOSED_DELETED;
            break;
        }
    }

    return;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

int p(int i) { // Probing function
    return i != 0 ? i * i + i + 1 : 0;
}
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
