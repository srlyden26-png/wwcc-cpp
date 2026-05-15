#include "Library.h"
#include <iostream>
#include <algorithm>
#include <cctype>

Library::Library(const std::string& name) : name(name) {}

std::string Library::toLowerCase(const std::string& str) const {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), [](unsigned char c){ return std::tolower(c); });
    return lowerStr;
}

void Library::addBook(const Book& book) {
    catalog.push_back(book);
}

void Library::addPatron(const Patron& patron) {
    patrons.push_back(patron);
}

void Library::displayCatalog() const {
    std::cout << "\nCATALOG:\n";
    if (catalog.empty()) {
        std::cout << "The catalog is currently empty.\n";
        return;
    }
    int index = 1;
    for (const auto& book : catalog) {
        std::cout << index++ << ". ";
        book.display();
    }
}

void Library::searchByAuthor(const std::string& authorName) const {
    std::string searchTarget = toLowerCase(authorName);
    bool found = false;
    
    std::cout << "Books by " << authorName << ":\n";
    for (const auto& book : catalog) {
        if (toLowerCase(book.getAuthor().getName()).find(searchTarget) != std::string::npos) {
            std::cout << "  - \"" << book.getTitle() << "\" (" << book.getPublicationYear() << ")\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "  No books found matching this author.\n";
    }
}

void Library::searchByTitle(const std::string& keyword) const {
    std::string searchTarget = toLowerCase(keyword);
    bool found = false;
    
    std::cout << "Books matching keyword \"" << keyword << "\":\n";
    for (const auto& book : catalog) {
        if (toLowerCase(book.getTitle()).find(searchTarget) != std::string::npos) {
            std::cout << "  - ";
            book.display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "  No books found matching this title keyword.\n";
    }
}

void Library::displayStats() const {
    std::cout << "\nSTATS:\n";
    std::cout << "  Total books in catalog: " << catalog.size() << "\n";
    int activeCheckouts = 0;
    for (const auto& b : catalog) {
        if (b.getIsCheckedOut()) activeCheckouts++;
    }
    std::cout << "  Active checkouts: " << activeCheckouts << "\n";
}

void Library::checkoutBook(const std::string& memberId, const std::string& bookTitle) {
    // Explicitly use non-const iterator definition
    std::vector<Patron>::iterator patronIt = std::find_if(patrons.begin(), patrons.end(), [&](const Patron& p) { 
        return p.getMemberId() == memberId; 
    });
    
    if (patronIt == patrons.end()) {
        std::cout << "[Error] Patron ID not found.\n";
        return;
    }

    std::string lowerTitle = toLowerCase(bookTitle);
    for (Book& book : catalog) { // Enforce non-const reference item targeting
        if (toLowerCase(book.getTitle()) == lowerTitle) {
            if (book.getIsCheckedOut()) {
                std::cout << "[Error] \"" << book.getTitle() << "\" is already checked out.\n";
                return;
            }
            book.setIsCheckedOut(true);
            patronIt->borrowBook(book.getTitle());
            std::cout << "[Success] \"" << book.getTitle() << "\" successfully checked out to " << patronIt->getName() << ".\n";
            return;
        }
    }
    std::cout << "[Error] Book title exact match not found.\n";
}

void Library::returnBook(const std::string& memberId, const std::string& bookTitle) {
    // Explicitly use non-const iterator definition
    std::vector<Patron>::iterator patronIt = std::find_if(patrons.begin(), patrons.end(), [&](const Patron& p) { 
        return p.getMemberId() == memberId; 
    });

    if (patronIt == patrons.end()) {
        std::cout << "[Error] Patron ID not found.\n";
        return;
    }

    std::string lowerTitle = toLowerCase(bookTitle);
    for (Book& book : catalog) { // Enforce non-const reference item targeting
        if (toLowerCase(book.getTitle()) == lowerTitle) {
            if (!book.getIsCheckedOut()) {
                std::cout << "[Error] This book was not logged as checked out.\n";
                return;
            }
            if (patronIt->returnBook(book.getTitle())) {
                book.setIsCheckedOut(false);
                std::cout << "[Success] \"" << book.getTitle() << "\" successfully returned.\n";
                return;
            }
        }
    }
    std::cout << "[Error] Book checkout history match failed for this patron.\n";
}

void Library::displayPatrons() const {
    std::cout << "\nPATRON REGISTRY:\n";
    if (patrons.empty()) {
        std::cout << "No registered library members.\n";
        return;
    }
    for (const auto& patron : patrons) {
        patron.displayBorrowedBooks();
    }
};
