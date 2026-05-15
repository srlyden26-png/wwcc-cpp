#include <iostream>
#include <string>
#include "Library.h"
#include "Author.h"
#include "Book.h"

void displayMenu() {
    std::cout << "\n1. Add Book\n";
    std::cout << "2. Display All Books\n";
    std::cout << "3. Search by Author\n";
    std::cout << "4. Search by Title\n";
    std::cout << "5. Show Stats\n";
    std::cout << "6. Exit\n";
    std::cout << "Enter choice: ";
}

int main() {
    Library myLibrary("Central City Library");

    // Pre-populate sample catalog data
    Author fScott("F. Scott Fitzgerald", 1896);
    Author gOrwell("George Orwell", 1903);
    myLibrary.addBook(Book("The Great Gatsby", 1925, "9780743273565", fScott));
    myLibrary.addBook(Book("1984", 1949, "9780451524935", gOrwell));
    myLibrary.addBook(Book("Animal Farm", 1945, "9780451526342", gOrwell));

    std::cout << "LIBRARY MANAGEMENT SYSTEM\n";
    std::cout << "--------------------------\n";
    std::cout << "Library: Central City Library\n";

    int choice = 0;
    while (choice != 6) {
        displayMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid entry. Enter a number.\n";
            continue;
        }
        std::cin.ignore(); // Clear newline buffer

        if (choice == 1) {
            std::string title, authName, isbn;
            int bYear, pYear;

            std::cout << "Enter Title: ";
            std::getline(std::cin, title);
            std::cout << "Enter Author Name: ";
            std::getline(std::cin, authName);
            std::cout << "Enter Author Birth Year: ";
            std::cin >> bYear;
            std::cout << "Enter Book Publication Year: ";
            std::cin >> pYear;
            std::cin.ignore();
            std::cout << "Enter ISBN: ";
            std::getline(std::cin, isbn);

            Author author(authName, bYear);
            myLibrary.addBook(Book(title, pYear, isbn, author));
            std::cout << "Book successfully cataloged!\n";

        } else if (choice == 2) {
            myLibrary.displayCatalog();

        } else if (choice == 3) {
            std::string authorQuery;
            std::cout << "Search by author: ";
            std::getline(std::cin, authorQuery);
            myLibrary.searchByAuthor(authorQuery);

        } else if (choice == 4) {
            std::string titleQuery;
            std::cout << "Search by title keyword: ";
            std::getline(std::cin, titleQuery);
            myLibrary.searchByTitle(titleQuery);

        } else if (choice == 5) {
            myLibrary.displayStats();

        } else if (choice == 6) {
            std::cout << "Goodbye!\n";
        } else {
            std::cout << "Invalid choice selection.\n";
        }
    }
    return 0;
}
