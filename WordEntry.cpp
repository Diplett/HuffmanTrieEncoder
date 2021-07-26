#include "WordEntry.h"

using namespace std;

WordEntry::WordEntry(const string& word, int code) : word(word), code(code), frequency(1) {}

void WordEntry::addFrequency() {
    ++this->frequency;
}

void WordEntry::setCode(int newCode) {
    this->code = newCode; 
}

string WordEntry::getWord() { 
    return this->word;
}

int WordEntry::getFrequency() { 
    return this->frequency; 
}

int WordEntry::getCode() { 
    return this->code;
}

bool WordEntry::operator<(const WordEntry& rhs) {
    return this->frequency > rhs.frequency;
}