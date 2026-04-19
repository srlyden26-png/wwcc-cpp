#include <iostream>
#include <iomanip>  // For setw()
using namespace std;

int main() {
    int start, end;

    cout << "Multiplication Table Generator" << endl << endl;

    cout << "Enter starting number: ";
    cin >> start;

    cout << "Enter ending number: ";
    cin >> end;

    if (start > end) {
        cout << "Error: Starting number must be less than ending number." << endl;
        return 1;
    }

    cout << endl;

    // Header Row (Top numbers)
    cout << "    |";
    for (int i = start; i <= end; i++) {
        cout << setw(4) << i << "|";
    }
    cout << endl;

    // Separator Line
    cout << "----|";
    for (int i = start; i <= end; i++) {
        cout << "----|";
    }
    cout << endl;

    // Nested Loops for Table Body
    for (int i = start; i <= end; i++) {
        cout << setw(3) << i << " |"; // Row Header
        for (int j = start; j <= end; j++) {
            cout << setw(4) << (i * j) << "|"; // Multiplied Value
        }
        cout << endl;
    }

    return 0;
}
