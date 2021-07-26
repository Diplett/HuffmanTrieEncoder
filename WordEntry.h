#ifndef WORDENTRY_H
#define WORDENTRY_H
#include <string>

using namespace std;

class WordEntry {
    private:
        string word;
        int frequency;
        int code;
    public:
        WordEntry(const string& word, int code = 0);
        void addFrequency();
        void setCode(int newCode);
        string getWord();
        int getFrequency();
        int getCode();

        bool operator<(const WordEntry& rhs);
};

#endif