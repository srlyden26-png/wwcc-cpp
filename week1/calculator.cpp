#include <iostream>

int main() {
    double num1, num2;

    // 1. Get user input
    std::cout << "Enter the first number: ";
    std::cin >> num1;
    std::cout << "Enter the second number: ";
    std::cin >> num2;

    std::cout << "\nResults:" << std::endl;

    // 2. Perform and print basic math
    std::cout << "Sum:        " << num1 << " + " << num2 << " = " << (num1 + num2) << std::endl;
    std::cout << "Difference: " << num1 << " - " << num2 << " = " << (num1 - num2) << std::endl;
    std::cout << "Product:    " << num1 << " * " << num2 << " = " << (num1 * num2) << std::endl;

    // 3. Handle Division by Zero gracefully
    if (num2 != 0) {
        std::cout << "Quotient:   " << num1 << " / " << num2 << " = " << (num1 / num2) << std::endl;
    } else {
        std::cout << "Quotient:   Error (Division by zero is not allowed)" << std::endl;
    }

    return 0;
}
