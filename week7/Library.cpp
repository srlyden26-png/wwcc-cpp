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
}
