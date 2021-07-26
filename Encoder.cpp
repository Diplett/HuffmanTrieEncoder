#include "Encoder.h"

using namespace std;

Encoder::Encoder(int size, const vector<WordEntry>& vec) : HashTable(size) {
    for (WordEntry word : vec) {
        put(word);
    }
}

int Encoder::computeHash(WordEntry& word) {
    unsigned long long stringHash = 5381;
    for (char strChar : word.getWord()) {
        stringHash = (stringHash * 33) + strChar;
    }
    return stringHash % this->size;
}

bool Encoder::contains(WordEntry& word) {
    int hashValue = computeHash(word);
    for (WordEntry wordInList : hashTable[hashValue]) {
        if (wordInList.getWord() == word.getWord()) {
            return true;
        }
    }
    return false;
}

int Encoder::search(WordEntry& word) {
    int hashValue = computeHash(word);
    for (WordEntry wordInList : hashTable[hashValue]) {
        if (wordInList.getWord() == word.getWord()) {
            return wordInList.getCode();
        }
    }
    return -1;
}

int Encoder::search(const string& key) {
    WordEntry word(key);
    return search(word);
}