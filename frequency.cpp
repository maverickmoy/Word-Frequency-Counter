#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Convert string to lowercase
void toLowerCase(string &str) { 
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

// Remove punctuation and numbers
void removePunctuationAndNumbers(string &str) { 
    str.erase(remove_if(str.begin(), str.end(), [](char c) { return !isalpha(c) && !isspace(c); }), str.end());
}

// Count word frequencies
vector<pair<string, int>> countWordFrequencies(const string &filename) { 
    ifstream file(filename);
    vector<pair<string, int>> wordCountVector;
    string word;

    while (file >> word) {
        toLowerCase(word);
        removePunctuationAndNumbers(word);
        if (!word.empty()) {
            auto it = find_if(wordCountVector.begin(), wordCountVector.end(), [&word](const pair<string, int>& element) { return element.first == word; });
            if (it != wordCountVector.end()) {
                it->second++;
            } else {
                wordCountVector.push_back(make_pair(word, 1));
            }
        }
    }

    return wordCountVector;
}

// Write frequencies to file
void writeFrequenciesToFile(const vector<pair<string, int>> &wordCountVector, const string &outputFilename) {
    ofstream outFile(outputFilename);
    for (const auto &entry : wordCountVector) {
        outFile << entry.first << ": " << entry.second << endl;
    }
}

int main() {
    string basePath = "/Users/maverickmoy/Documents/cs111/Word Frequency Counter/";
    string inputFilename = basePath + "input.txt";
    string outputFilename = basePath + "output.txt";

    vector<pair<string, int>> wordCountVector = countWordFrequencies(inputFilename);

    // Optional: Sort the vector by frequency in descending order
    sort(wordCountVector.begin(), wordCountVector.end(), [](const pair<string, int> &a, const pair<string, int> &b) {
        return b.second < a.second;
    });

    cout << "Total unique words: " << wordCountVector.size() << endl;
    cout << "Word frequencies: " << endl;
    for (const auto &entry : wordCountVector) {
        cout << entry.first << ": " << entry.second << endl;
    }


    // Save sorted word frequencies to file
    writeFrequenciesToFile(wordCountVector, outputFilename);

    return 0;
}