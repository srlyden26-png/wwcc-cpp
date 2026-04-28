#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// --- Global Static Tracker ---
// We use a helper function to manage the count centrally
int& conversionTracker() {
    static int count = 0;
    return count;
}

// --- Prototypes ---
double dollarToEuro(double amount);
double dollarToPound(double amount);
double dollarToYen(double amount);
int getConversionCount();

int main() {
    int choice;
    double usdAmount;
    char repeat = 'y';

    cout << fixed << setprecision(2);

    while (tolower(repeat) == 'y') {
        cout << "\nCURRENCY CONVERTER" << endl;
        cout << "------------------" << endl;
        cout << "1. Convert USD to Euro (EUR)" << endl;
        cout << "2. Convert USD to British Pound (GBP)" << endl;
        cout << "3. Convert USD to Japanese Yen (JPY)" << endl;
        cout << "4. Exit" << endl;
        
        cout << "\nEnter your choice (1-4): ";
        cin >> choice;

        if (choice == 4) break;

        if (choice < 1 || choice > 3) {
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        cout << "Enter amount in USD: ";
        cin >> usdAmount;

        switch (choice) {
            case 1:
                cout << usdAmount << " USD = " << dollarToEuro(usdAmount) << " EUR" << endl;
                break;
            case 2:
                cout << usdAmount << " USD = " << dollarToPound(usdAmount) << " GBP" << endl;
                break;
            case 3:
                cout << usdAmount << " USD = " << dollarToYen(usdAmount) << " JPY" << endl;
                break;
        }

        cout << "\nNumber of conversions performed: " << getConversionCount() << endl;
        cout << "Would you like to perform another conversion? (y/n): ";
        cin >> repeat;
    }

    cout << "Thank you for using the Currency Converter!" << endl;
    return 0;
}

// --- Implementation ---

double dollarToEuro(double amount) {
    conversionTracker()++; // Increment static counter
    return amount * 0.85;
}

double dollarToPound(double amount) {
    conversionTracker()++; // Increment static counter
    return amount * 0.74;
}

double dollarToYen(double amount) {
    conversionTracker()++; // Increment static counter
    return amount * 110.33;
}

int getConversionCount() {
    return conversionTracker();
}
