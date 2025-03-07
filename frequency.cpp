

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

// Requirments:
// 1. convert string to lowercae
// analyze text files
// count word frequencies
// write to file
// 2. Removing punctuation characters and any numbers using ‘isalnum‘ which acts like ’isalpha’.
// Output the results
// storing word frequencies using an array or a vector
// 3. Sort the words by frequenc

// 1. convert string to lowercase
void toLowerCase(string &str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void removePunctuationAndNumbers(string &str) {
    str.erase(remove_if(str.begin(), str.end(), [](char c) { return !isalpha(c); }), str.end());
}

map<string, int> countWordFrequencies(const string &filename) {
    ifstream file(filename);
    map<string, int> wordCount;
    string word;

    while (file >> word) {
        toLowerCase(word);
        removePunctuationAndNumbers(word);
        if (!word.empty()) {
            wordCount[word]++;
        }
    }

    return wordCount;
}

void writeFrequenciesToFile(const map<string, int> &wordCount, const string &outputFilename) {
    ofstream outFile(outputFilename);
    for (const auto &entry : wordCount) {
        outFile << entry.first << ": " << entry.second << endl;
    }
}

// 2. Remove punctuation from characters and numbers


// 3. Count word frequency


int main() {
    string inputFilename = "/Users/maverickmoy/Documents/cs111/Word Frequency Counter/input.txt";
    string outputFilename = "/Users/maverickmoy/Documents/cs111/Word Frequency Counter/output.txt";

    map<string, int> wordCount = countWordFrequencies(inputFilename);
    writeFrequenciesToFile(wordCount, outputFilename);

    return 0;
}

