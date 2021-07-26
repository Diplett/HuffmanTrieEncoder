#ifndef ENCODER_H
#define ENCODER_H
#include "HashTable.h"

class Encoder : public HashTable {
    private:
        int computeHash(WordEntry&) override;
    public:
        Encoder(int size, const vector<WordEntry>& vec);
        bool contains(WordEntry&) override;
        int search(WordEntry&);
        int search(const string&);
};

#endif