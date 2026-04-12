#include <iostream>
#include <iomanip> // Helpful for formatting decimal places

int main() {
    double temperature;
    char unit;

    std::cout << "Temperature Converter" << std::endl;
    
    // 1. Get the value
    std::cout << "Enter temperature value: ";
    std::cin >> temperature;

    // 2. Get the unit
    std::cout << "Enter unit (C for Celsius, F for Fahrenheit): ";
    std::cin >> unit;

    // 3. Logic for conversion
    if (unit == 'C' || unit == 'c') {
        double fahrenheit = (temperature * 9/5) + 32;
        std::cout << temperature << "°C is equal to " << fahrenheit << "°F" << std::endl;
    } 
    else if (unit == 'F' || unit == 'f') {
        double celsius = (temperature - 32) * 5/9;
        std::cout << temperature << "°F is equal to " << celsius << "°C" << std::endl;
    } 
    else {
        std::cout << "Invalid unit entered." << std::endl;
    }

    return 0;
}
