#include <iostream>
#include <string>
#include <algorithm> // For reverse
#include <cctype>    // For tolower and isalpha

using namespace std;

// --- Prototypes ---
int countVowels(string word);
int countConsonants(string word);
bool isPalindrome(string word);
char firstLetter(string word);
string reverseWord(string word); // Renamed from 'reverse' to avoid conflict with std::reverse

int main() {
    string input;
    char repeat = 'y';

    while (tolower(repeat) == 'y') {
        cout << "Enter a word: ";
        cin >> input;

        cout << "\nWord Analysis:" << endl;
        cout << "-------------" << endl;
        cout << "Original word: " << input << endl;
        cout << "Number of vowels: " << countVowels(input) << endl;
        cout << "Number of consonants: " << countConsonants(input) << endl;
        cout << "First letter: " << firstLetter(input) << endl;
        cout << "Reversed: " << reverseWord(input) << endl;
        cout << "Is palindrome: " << (isPalindrome(input) ? "Yes" : "No") << endl;

        cout << "\nWould you like to analyze another word? (y/n): ";
        cin >> repeat;
        cout << endl;
    }

    return 0;
}

// --- Implementation ---

int countVowels(string word) {
    int count = 0;
    string vowels = "aeiou";
    for (char c : word) {
        if (vowels.find(tolower(c)) != string::npos) {
            count++;
        }
    }
    return count;
}

int countConsonants(string word) {
    int count = 0;
    string vowels = "aeiou";
    for (char c : word) {
        char lowerC = tolower(c);
        // Must be a letter AND not a vowel
        if (isalpha(lowerC) && vowels.find(lowerC) == string::npos) {
            count++;
        }
    }
    return count;
}

bool isPalindrome(string word) {
    int left = 0;
    int right = word.length() - 1;
    
    while (left < right) {
        if (tolower(word[left]) != tolower(word[right])) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

char firstLetter(string word) {
    if (word.empty()) return '\0';
    return word[0];
}

string reverseWord(string word) {
    string reversed = "";
    for (int i = word.length() - 1; i >= 0; i--) {
        reversed += word[i];
    }
    return reversed;
}
