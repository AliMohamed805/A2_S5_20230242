#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cctype>
#include <sstream>
using namespace std;
class WordFrequency {
public:
    void readFile(const string& fileName);
    void displayFrequencyTable() const;
    void clearFrequencyTable();
private:
    map<string, int> frequencyTable;
    string cleanWord(const string& word) const;
};
string WordFrequency::cleanWord(const string& word) const {
    string cleanedWord;
    for (char c : word) {
        if (isalnum(c) || c == '-') {
            cleanedWord += tolower(c);
        }
    }
    return cleanedWord;
}
void WordFrequency::readFile(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Unable to open the file." << endl;
        return;
    }
    string line, word;
    while (getline(file, line)) {
        stringstream ss(line);
        while (ss >> word) {
            string cleanedWord = cleanWord(word);
            if (!cleanedWord.empty()) {
                frequencyTable[cleanedWord]++;
            }
        }
    }
    file.close();
}
void WordFrequency::displayFrequencyTable() const {
    for (const auto& pair : frequencyTable) {
        cout << pair.first << ": " << pair.second << endl;
    }
}
void WordFrequency::clearFrequencyTable() {
    frequencyTable.clear();
}
void displayFileContents(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Unable to open the file." << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}
int main() {
    WordFrequency wf;
    string fileName;
    char choice;
    do {
        cout << "Enter the file name: ";
        cin >> fileName;
        displayFileContents(fileName);
        wf.readFile(fileName);
        wf.displayFrequencyTable();
        cout << "Do you want to test another file? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            wf.clearFrequencyTable();
        }
    } while (choice == 'y' || choice == 'Y');
    return 0;
}