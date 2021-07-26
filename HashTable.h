#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "WordEntry.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>

using namespace std;

class HashTable {
    protected:
        int size;
        list<WordEntry>* hashTable;

        virtual int computeHash(WordEntry&) = 0;
    public:
        HashTable(int size);
        void put(WordEntry&);
        virtual bool contains(WordEntry&) = 0;

        void visualizeArray(const string& fileName) {
            ofstream outFS(fileName);
            for (int i = 0; i < size; ++i) {
                outFS << "Array[" << i << "] :" << endl;
                for (WordEntry word : hashTable[i]) {
                    outFS << "   ";
                    outFS << "<";
                    if (word.getWord() == "\n") {
                        outFS << "\n";
                    }
                    else {
                        outFS << word.getWord();
                    }
                    outFS << ", " << word.getCode() << ">" << endl;
                }
            }
        }
};

#endif