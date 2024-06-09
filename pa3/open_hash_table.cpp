#include <iostream>
#include <fstream>
#include <string>
#include "open_hash_function.h"
#include "open_hash_table.h"

using namespace std;

HashNode* search_end(HashNode* hash_node);
HashNode* search_parent(HashNode* hash_node, int key);

OpenHashTable::OpenHashTable(int table_size, OpenHashFunction *hf) : table_size(table_size) {
    this->hf = hf;
    table = new HashNode*[this->table_size];
    for(int i = 0; i < this->table_size; i++){
        table[i] = NULL;
    }
    this->states = new OpenTableState[this->table_size];

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    /*  Write your codes if you need  */
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

OpenHashTable::~OpenHashTable() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    /*  Write your codes if you need  */
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    delete[] table;
    delete[] this->states;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void OpenHashTable::print_table(ostream &out) {
    for (int i=0; i < this->table_size; i++) {
        out << i << ": ";
        if (this->states[i] == OPEN_EMPTY){
            out << "empty" << endl;
        }else if (this->states[i] == OPEN_OCCUPIED){
          HashNode* cur;
          cur = table[i];
          while(cur->next != NULL){
              out << cur->key ;
              out << ", ";
              cur = cur->next;
          }
            out << cur->key << endl;
        }else{
            out << "unknown state" << endl;
        }
    }
}

void OpenHashTable::insert(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    int hash_key = hf->openhashing(key);
    HashNode* temp = new HashNode(key);

    if (table[hash_key] == NULL) {
        table[hash_key] = temp;
        states[hash_key] = OPEN_OCCUPIED; // Change state
    }
    else search_end(table[hash_key])->next = temp;
    
    return;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

void OpenHashTable::erase(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    HashNode* target_parent;
    HashNode* target;

    int hash_key = hf->openhashing(key);
    if (table[hash_key] == NULL) return; // no element in slot
    else if (table[hash_key]->next == NULL && table[hash_key]->key != key) return; // 1 element, no target
    else if (table[hash_key]->next == NULL && table[hash_key]->key == key) { // 1 element, target exists
        delete table[hash_key];
        table[hash_key] = NULL;
        states[hash_key] = OPEN_EMPTY;
    }
    else { // many element
        target_parent = search_parent(table[hash_key], key);
        // cout << "del, key " << key << " " << target_parent
        if (target_parent == NULL) { // target is first element or D.N.E
            if (table[hash_key]->key == key) { // target is first element
                target = table[hash_key];
                table[hash_key] = target->next;
                delete target;
                target = NULL;
            }
            else return; // target D.N.E
        }
        else { // target is not first element and exist
            target = target_parent->next;
            target_parent->next = target->next;
            delete target;
            target = NULL;
        }
    }

    return;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

HashNode* search_end(HashNode* hash_node) {
    // Search end of table's linked list
    if (hash_node->next == NULL) return hash_node;
    else return search_end(hash_node->next);
}


HashNode* search_parent(HashNode* hash_node, int key) {
    // Search target's parent in table
    if (hash_node == NULL || hash_node->next == NULL || hash_node->key == key) return NULL;
    else if (hash_node->next->key == key) return hash_node;
    else return search_parent(hash_node->next, key);
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
