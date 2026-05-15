#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>

class Author {
private:
    std::string name;
    int birthYear;

public:
    Author(); // Default constructor for vector/placeholder compliance
    Author(const std::string& name, int birthYear);
    
    std::string getName() const;
    int getBirthYear() const;
    void display() const;
};

#endif
