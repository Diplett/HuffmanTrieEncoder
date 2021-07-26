#include "HashTable.h"

using namespace std;

HashTable::HashTable(int size) {
    hashTable = new list<WordEntry>[size];
    this->size = size;
}

void HashTable::put(WordEntry& word) {
    if (contains(word) == true) {
        return;
    }
    else {
        hashTable[computeHash(word)].push_back(word);
    }
}
