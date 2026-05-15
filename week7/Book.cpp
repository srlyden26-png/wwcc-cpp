#include "Book.h"
#include <iostream>

// Constructor initialization list handles the nested Author object
Book::Book(const std::string& title, int publicationYear, const std::string& isbn, const Author& author)
    : title(title), publicationYear(publicationYear), isbn(isbn), author(author), isCheckedOut(false) {
    if (publicationYear <= 0) {
        std::cout << "[Warning] Invalid publication year. Defaulting to 2026.\n";
        this->publicationYear = 2026;
    }
}

std::string Book::getTitle() const { return title; }
int Book::getPublicationYear() const { return publicationYear; }
std::string Book::getIsbn() const { return isbn; }
Author Book::getAuthor() const { return author; }
bool Book::getIsCheckedOut() const { return isCheckedOut; }

void Book::setPublicationYear(int year) {
    if (year > 0) {
        publicationYear = year;
    } else {
        std::cout << "[Error] Publication year must be positive.\n";
    }
}

void Book::setIsCheckedOut(bool status) {
    isCheckedOut = status;
}

void Book::display() const {
    std::cout << "\"" << title << "\" (" << publicationYear << ")\n";
    std::cout << "   Author: ";
    author.display();
    std::cout << "\n   ISBN: " << isbn;
    if (isCheckedOut) {
        std::cout << " [CHECKED OUT]";
    }
    std::cout << "\n";
}
