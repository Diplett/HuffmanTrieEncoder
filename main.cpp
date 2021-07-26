#include "Encoder.h"
#include "Decoder.h"
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

void printVector(const vector<WordEntry>& inputVector) {
    ofstream outFS("CodeWordFrequency.txt");
    outFS << " Code | Word | Frequency " << endl;
    for (WordEntry word : inputVector) {
        outFS << word.getCode() << ": ";
        if (word.getWord() == "\n") {
            outFS << "\\n";
        }
        else {
            outFS << word.getWord();
        }
        outFS << " " << word.getFrequency() << endl;
    }
}

void addWordEntry(vector<WordEntry>& inputVector, const string& input) {
    bool found = false;
    for (WordEntry& word : inputVector) {
        if (word.getWord() == input) {
            word.addFrequency();
            found = true;
            return;
        }
    }
    if (found == false) {
        inputVector.push_back(WordEntry(input));
    }
}

vector<WordEntry> passThroughData(const string& inputFile) {
    ifstream inFS(inputFile);
    string input;
    string lineInput;
    vector<WordEntry> wordsInFile;
    string punctuationChars = "_-,.!?`'~\";:><@#$%^&*()[]{}\\|=-/";
    int count;

    if (inFS.is_open() == false) {
        cout << "Error Opening File" << endl;
        exit(1);
    }

    bool isFirst = false;
    while (getline(inFS, lineInput)) {
        if (isFirst == true) {
            addWordEntry(wordsInFile, "\n");
        }
        isFirst = true;

        istringstream strStream(lineInput);
        count = 0;
        while (strStream >> input) {
            count += input.size();

            for (int i = 0; i < lineInput.size(); ++i) {
                if (lineInput.at(i) != ' ') {
                    break;
                }
                addWordEntry(wordsInFile, " ");
                ++count;
            }

            int punctuationIndex = input.find_first_of(punctuationChars);
            while (punctuationIndex != -1) {
                if (punctuationIndex != 0) {
                    addWordEntry(wordsInFile, input.substr(0, punctuationIndex));
                }
                addWordEntry(wordsInFile, input.substr(punctuationIndex, 1));
                input = input.substr(punctuationIndex + 1, input.size());
                punctuationIndex = input.find_first_of(punctuationChars);
            }
            if (input != "") {
                addWordEntry(wordsInFile, input);
            }

            for (int i = count; i < lineInput.size(); ++i) {
                if (lineInput.at(i) != ' ') {
                    break;
                }
                addWordEntry(wordsInFile, " ");
                ++count;
            }
        }
    }
    inFS.close();

    sort(wordsInFile.begin(), wordsInFile.end());
    for (unsigned int i = 1; i < wordsInFile.size() + 1; ++i) {
        wordsInFile.at(i - 1).setCode(i);
    }
    printVector(wordsInFile);
    return wordsInFile;
}

void encodeFile(Encoder& encoder, const string& inputFile, const string& outputEncryption) {
    ifstream inFS(inputFile);
    ofstream outFS(outputEncryption);
    string input;
    string lineInput;
    string punctuationChars = "_-,.!?`'~\";:><@#$%^&*()[]{}\\|=-/";
    int count;

    if (inFS.is_open() == false) {
        cout << "Error Opening File" << endl;
        exit(1);
    }

    bool isFirst = false;
    while (getline(inFS, lineInput)) {
        if (isFirst == true) {
            outFS << encoder.search("\n") << " ";
        }
        isFirst = true;

        istringstream strStream(lineInput);
        count = 0;
        while (strStream >> input) {
            count += input.size();

            for (int i = 0; i < lineInput.size(); ++i) {
                if (lineInput.at(i) != ' ') {
                    break;
                }
                outFS << encoder.search(" ") << " ";
                ++count;
            }

            int punctuationIndex = input.find_first_of(punctuationChars);
            while (punctuationIndex != -1) {
                if (punctuationIndex != 0) {
                    outFS << encoder.search(input.substr(0, punctuationIndex)) << " ";
                }
                outFS << encoder.search(input.substr(punctuationIndex, 1)) << " ";
                input = input.substr(punctuationIndex + 1, input.size());
                punctuationIndex = input.find_first_of(punctuationChars);
            }
            if (input != "") {
                outFS << encoder.search(input) << " ";
            }

            for (int i = count; i < lineInput.size(); ++i) {
                if (lineInput.at(i) != ' ') {
                    break;
                }
                outFS << encoder.search(" ") << " ";
                ++count;
            }
        }
    }
    inFS.close();
    outFS.close();
}

void decodeFile(Decoder& decoder, const string& encryptedFile, const string& outputDecryption) {
    ifstream inFS(encryptedFile);
    ofstream outFS(outputDecryption);
    int input;
    while (inFS >> input) {
        outFS << decoder.search(input);
    }
}

int main() {
    clock_t startTime;
    clock_t endTime;
    string inputFile = "TestFile.txt";
    string outputEncoded = "outputEncoded.txt";
    string outputDecoded = "outputDecoded.txt";
    
    cout << "Enter File Name: ";
    cout << inputFile << endl;

    vector<WordEntry> TokensWithCodes = passThroughData(inputFile);
    
    int encoderSize = TokensWithCodes.size();
    startTime = clock();
    Encoder myEncoder(encoderSize, TokensWithCodes);
    endTime = clock();
    cout << "Made Encoder of size " << encoderSize << " in " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;

    int decoderSize = TokensWithCodes.size();
    startTime = clock();
    Decoder myDecoder(decoderSize, TokensWithCodes);
    endTime = clock();
    cout << "Made Decoder of size " << decoderSize << " in " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;

    startTime = clock();
    encodeFile(myEncoder, inputFile, outputEncoded);
    endTime = clock();
    cout << "Encoded File in " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;

    startTime = clock();
    decodeFile(myDecoder, outputEncoded, outputDecoded);
    endTime = clock();
    cout << "Decoded File in " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;

    myEncoder.visualizeArray("encoderArray.txt");
    myDecoder.visualizeArray("decoderArray.txt");
}