#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

// Helper function to strip punctuation from a string
string cleanWord(string word) {
    string cleaned = "";
    for (char c : word) {
        if (!ispunct(c)) {
            cleaned += c;
        }
    }
    return cleaned;
}

int main() {
    string text;
    
    cout << "TEXT ANALYZER" << endl;
    cout << "-------------" << endl;
    cout << "Enter a sentence or paragraph:" << endl;
    getline(cin, text);

    // 1. Character Count
    int charCount = text.length();

    // 2. Sentence Count
    int sentenceCount = 0;
    for (char c : text) {
        if (c == '.' || c == '!' || c == '?') {
            sentenceCount++;
        }
    }

    // 3. Word Analysis using stringstream
    stringstream ss(text);
    string currentWord;
    int wordCount = 0;
    string longestWord = "";
    double totalLetters = 0;

    while (ss >> currentWord) {
        wordCount++;
        
        // Clean word for length/longest comparisons
        string cleaned = cleanWord(currentWord);
        totalLetters += cleaned.length();

        if (cleaned.length() > cleanWord(longestWord).length()) {
            longestWord = cleaned;
        }
    }

    double avgLength = (wordCount > 0) ? (totalLetters / wordCount) : 0;

    // Output Analysis
    cout << fixed << setprecision(1);
    cout << "\nAnalysis:" << endl;
    cout << "  Characters (with spaces): " << charCount << endl;
    cout << "  Word count:               " << wordCount << endl;
    cout << "  Sentence count:           " << sentenceCount << endl;
    cout << "  Longest word:             " << longestWord << endl;
    cout << "  Average word length:      " << avgLength << " characters" << endl;

    // 4. Case Conversions
    string upperText = text;
    string lowerText = text;

    for (int i = 0; i < upperText.length(); i++) {
        upperText[i] = toupper(upperText[i]);
        lowerText[i] = tolower(lowerText[i]);
    }

    cout << "\nUppercase:" << endl;
    cout << "  " << upperText << endl;
    cout << "\nLowercase:" << endl;
    cout << "  " << lowerText << endl;

    return 0;
}
