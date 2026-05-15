#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
#include "Book.h"

class Library {
private:
    std::string name;
    std::vector<Book> catalog;

    // Helper for case-insensitive conversions
    std::string toLowerCase(const std::string& str) const;

public:
    Library(const std::string& name);
    
    void addBook(const Book& book);
    
    void displayCatalog() const;
    void searchByAuthor(const std::string& authorName) const;
    void searchByTitle(const std::string& keyword) const;
    void displayStats() const;
    
    // Bonus Actions
    void checkoutBook(const std::string& memberId, const std::string& bookTitle);
    void returnBook(const std::string& memberId, const std::string& bookTitle);
    void displayPatrons() const;
};

#endif
