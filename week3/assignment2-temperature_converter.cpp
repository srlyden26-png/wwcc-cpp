#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// --- Prototypes ---
// Uses & to pass by reference for Celsius, Fahrenheit, and Kelvin
void convertTemperature(double val, char unit, double &c, double &f, double &k);
bool isPhysical(double val, char unit, string &warning); // Bonus

int main() {
    double inputTemp, c, f, k;
    char unit;
    string warningMsg = "";

    cout << "Enter a temperature value: ";
    cin >> inputTemp;
    cout << "Enter the unit (C for Celsius, F for Fahrenheit, K for Kelvin): ";
    cin >> unit;
    unit = toupper(unit); // Normalize input to uppercase

    // Bonus: Check for absolute zero and valid units
    if (!isPhysical(inputTemp, unit, warningMsg)) {
        cout << "\nError: " << warningMsg << endl;
        return 1; 
    }

    // Calling the function. c, f, and k will be updated inside the function.
    convertTemperature(inputTemp, unit, c, f, k);

    // Formatting output to 2 decimal places
    cout << fixed << setprecision(2);
    cout << "\nTemperature Conversions:" << endl;
    cout << "Celsius: " << c << "°C" << endl;
    cout << "Fahrenheit: " << f << "°F" << endl;
    cout << "Kelvin: " << k << "K" << endl;

    return 0;
}

// --- Implementation ---

void convertTemperature(double val, char unit, double &c, double &f, double &k) {
    // Step 1: Normalize the input to Celsius first to simplify math
    switch (unit) {
        case 'C': c = val; break;
        case 'F': c = (val - 32.0) * 5.0 / 9.0; break;
        case 'K': c = val - 273.15; break;
    }

    // Step 2: Calculate the other units based on the Celsius value
    f = (c * 9.0 / 5.0) + 32.0;
    k = c + 273.15;
}

// Bonus: Logic for checking physical limits
bool isPhysical(double val, char unit, string &warning) {
    if (unit != 'C' && unit != 'F' && unit != 'K') {
        warning = "Invalid unit! Please use C, F, or K.";
        return false;
    }
    
    // Check for values below absolute zero
    if ((unit == 'C' && val < -273.15) || 
        (unit == 'K' && val < 0) || 
        (unit == 'F' && val < -459.67)) {
        warning = "Temperature can't be below absolute zero! Eh!";
        return false;
    }
    
    return true;
}
