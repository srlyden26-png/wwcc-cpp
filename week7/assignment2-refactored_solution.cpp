/**
 * File: assignment2-refactored_solution.cpp
 * Description: Refactored BankAccount class addressing encapsulation, 
 * validation, naming conventions, and const-correctness.
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

/**
 * PROBLEM: Original class name 'account' used lowercase (non-standard).
 * FIX: Renamed to 'BankAccount' using PascalCase.
 */
class BankAccount {
private:
    /**
     * PROBLEM: All data members were public, breaking encapsulation.
     * FIX: Moved all members to private and used 'm_' prefix for clarity.
     */
    std::string m_customerName;
    int m_accountNumber;
    std::string m_accountType;
    double m_balance;
    bool m_isOpen;

    /**
     * PROBLEM: Magic numbers were used directly in the interest logic.
     * FIX: Defined named constants for better maintainability.
     */
    const double SAVINGS_RATE = 0.03;
    const double CHECKING_RATE = 0.01;
    const double BUSINESS_RATE = 0.005;

public:
    /**
     * PROBLEM: Initialization was done via a setup() method.
     * FIX: Replaced setup() with a proper Constructor to ensure valid state upon creation.
     */
    BankAccount(std::string name, int accountNumber, std::string type)
        : m_customerName(name), 
          m_accountNumber(accountNumber), 
          m_accountType(type), 
          m_balance(0.0), 
          m_isOpen(true) {}

    /**
     * PROBLEM: Original deposit() did not check if the amount was negative.
     * FIX: Added validation to ensure amount > 0.
     */
    void deposit(double amount) {
        if (amount <= 0) {
            std::cout << "Error: Deposit amount must be positive.\n";
            return;
        }
        m_balance += amount;
    }

    /**
     * PROBLEM: Original withdraw() allowed negative balances and negative inputs.
     * FIX: Added validation for positive amount and sufficient funds.
     */
    void withdraw(double amount) {
        if (amount <= 0) {
            std::cout << "Error: Withdrawal amount must be positive.\n";
            return;
        }
        if (amount > m_balance) {
            std::cout << "Error: Insufficient funds.\n";
            return;
        }
        m_balance -= amount;
    }

    /**
     * PROBLEM: Original do_interest() used hardcoded strings and magic numbers.
     * FIX: Uses constants and cleaner logic.
     */
    void applyInterest() {
        if (m_accountType == "savings") {
            m_balance += (m_balance * SAVINGS_RATE);
        } else if (m_accountType == "checking") {
            m_balance += (m_balance * CHECKING_RATE);
        } else if (m_accountType == "business") {
            m_balance += (m_balance * BUSINESS_RATE);
        }
    }

    /**
     * PROBLEM: Original print() and get_money() were not const.
     * FIX: Added 'const' qualifier as these methods do not modify the object.
     */
    void displayAccountInfo() const {
        std::cout << "--------------------------\n";
        std::cout << "Account Number: " << m_accountNumber << "\n";
        std::cout << "Customer Name: " << m_customerName << "\n";
        std::cout << "Balance: $" << std::fixed << std::setprecision(2) << m_balance << "\n";
        std::cout << "Account Type: " << m_accountType << "\n";
        std::cout << "Status: " << (m_isOpen ? "Open" : "Closed") << "\n";
        std::cout << "--------------------------\n";
    }

    /**
     * PROBLEM: get_money() was an informal name.
     * FIX: Renamed to getBalance() to follow industry conventions.
     */
    double getBalance() const {
        return m_balance;
    }

    void closeAccount() {
        m_isOpen = false;
    }
};

int main() {
    /**
     * Testing the refactored BankAccount class.
     */
    BankAccount acc1("John Smith", 12345, "savings");

    acc1.deposit(1000.0);
    acc1.withdraw(250.0);
    
    // Testing Validation
    acc1.withdraw(2000.0); // Should trigger insufficient funds hopefully
    acc1.deposit(-50.0);   // Should trigger invalid amount, but if not geez

    acc1.applyInterest();
    acc1.displayAccountInfo();
    
    acc1.closeAccount();

    return 0;
}
