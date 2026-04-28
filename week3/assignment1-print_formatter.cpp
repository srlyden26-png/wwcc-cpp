#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

// --- Prototypes ---
string format(int num);
string format(double num);
string format(double num, int precision);
string format(string text);
string format(string text, bool toUpper); // Bonus

int main() {
    // 1. Integer Test that should not fail but you never know, I checked and now I am not so sure.
    int bigInt = 1234567;
    cout << "Integer formatting:\nOriginal: " << bigInt << "\nFormatted: " << format(bigInt) << "\n\n";

    // 2. Double Test (Default)
    double pi = 45.6789;
    cout << "Double formatting (default 2):\nOriginal: " << pi << "\nFormatted: " << format(pi) << "\n\n";

    // 3. Double Test (Custom)
    cout << "Double formatting (custom precision 3):\nOriginal: " << pi << "\nFormatted: " << format(pi, 3) << "\n\n";

    // 4. String Test
    string phrase = "hello world of c++ programming";
    cout << "String formatting:\nOriginal: " << phrase << "\nFormatted: " << format(phrase) << "\n\n";

    // 5. Bonus Test
    cout << "Bonus (Uppercase): " << format("c++ is fun", true) << endl;

    return 0;
}

// --- Implementation ---

// Integer with commas
string format(int num) {
    string s = to_string(abs(num));
    int insertPosition = s.length() - 3;
    while (insertPosition > 0) {
        s.insert(insertPosition, ",");
        insertPosition -= 3;
    }
    return (num < 0) ? "-" + s : s;
}

// Double with 2 decimal places
string format(double num) {
    return format(num, 2); // Reuses the precision function below
}

// Double with custom precision
string format(double num, int precision) {
    ostringstream out;
    out << fixed << setprecision(precision) << num;
    return out.str();
}

// Capitalize first letter of each word
string format(string text) {
    if (text.empty()) return text;
    
    for (int i = 0; i < text.length(); i++) {
        // Capitalize if it's the first char or preceded by a space
        if (i == 0 || text[i-1] == ' ') {
            text[i] = toupper(text[i]);
        }
    }
    return text;
}

// Bonus: All upper or all lower
string format(string text, bool toUpper) {
    for (char &c : text) {
        c = toUpper ? toupper(c) : tolower(c);
    }
    return text;
}
