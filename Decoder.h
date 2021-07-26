#ifndef DECODER_H
#define DECODER_H
#include "HashTable.h"

class Decoder : public HashTable {
    private:
        int computeHash(WordEntry&) override;
    public:
        Decoder(int size, const vector<WordEntry>& vec);
        bool contains(WordEntry&) override;
        string search(WordEntry&);
        string search(int);
};

#endif