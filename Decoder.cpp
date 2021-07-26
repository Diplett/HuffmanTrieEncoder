#include "Decoder.h"

using namespace std;

Decoder::Decoder(int size, const vector<WordEntry>& vec) : HashTable(size) {
    for (WordEntry word : vec) {
        put(word);
    }
}

int Decoder::computeHash(WordEntry& word) {
    return word.getCode() % size;
}

bool Decoder::contains(WordEntry& word) {
    int hashValue = computeHash(word);
    for (WordEntry wordInList : hashTable[hashValue]) {
        if (wordInList.getCode() == word.getCode()) {
            return true;
        }
    }
    return false;
}

string Decoder::search(WordEntry& word) {
    int hashValue = computeHash(word);
    for (WordEntry wordInList : hashTable[hashValue]) {
        if (wordInList.getCode() == word.getCode()) {
            return wordInList.getWord();
        }
    }
    return "NULL";
}

string Decoder::search(int key) {
    WordEntry word("NULL", key);
    return search(word);
}