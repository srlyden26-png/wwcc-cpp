#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "Author.h"

class Book {
private:
    std::string title;
    int publicationYear;
    std::string isbn;
    Author author;
    bool isCheckedOut;

public:
    Book(const std::string& title, int publicationYear, const std::string& isbn, const Author& author);
    
    std::string getTitle() const;
    int getPublicationYear() const;
    std::string getIsbn() const;
    Author getAuthor() const;
    bool getIsCheckedOut() const;
    
    void setPublicationYear(int year);
    void setIsCheckedOut(bool status);
    void display() const;
};

#endif