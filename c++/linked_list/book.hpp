#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>
#include <iostream>

struct Book {
    std::string title;
    std::string author;
    std::string publicationDate;

    friend std::ostream& operator << (std::ostream& str, const Book& b) {
        str << "title: " << b.title << "\nauthor: " << b.author << "\n";
        str << "date: " << b.publicationDate;
        return str;
    }
};

#endif // BOOK_HPP
