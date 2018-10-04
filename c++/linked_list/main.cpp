#include <iostream>
#include "book.hpp"
#include "linkedlist.hpp"
#include <fstream>
#include <functional>
#include <sstream>


void enter_field(const std::string& desc,
                 std::string& destination,
                 std::istream& istream=std::cin,
                 std::ostream& ostream=std::cout)
{
    ostream << "enter " << desc << ":";
    std::getline(istream, destination);
}


template <class T>
struct PrintValue {
private:
    std::string _prefix;
    std::string _postfix;
    std::ostream* _stream;
public:
    PrintValue(const std::string& prefix,
               const std::string& postfix,
               std::ostream& stream=std::cout) {
        _prefix = prefix;
        _postfix = postfix;
        _stream = &stream;
    }

    void operator()(const T& val) {
        (*_stream) << _prefix;
        (*_stream) << val;
        (*_stream) << _postfix;
    }
};


struct AuthorIs {
private:
    std::string author;
public:
    AuthorIs(const std::string& a) {
        author = a;
    }

    bool operator () (const Book& b) {
        return b.author == author;
    }
};


struct TitleIs {
private:
    std::string title;
public:
    TitleIs(const std::string& t) {
        title = t;
    }

    bool operator () (const Book& b) {
        return b.title == title;
    }
};


void delete_if(LList::LinkedList<Book>& list,
               const std::function<bool(const Book&)>& predicate) {
    try {
        list.find_and_del(predicate);
    } catch (const LList::NotFound& ex) {
        std::cout << ex.what() << std::endl;
    }
}


void find_by(LList::LinkedList<Book>& list,
             const std::function<bool(const Book&)>& criteria) {
    try {
        std::pair<int, Book> pair = list.find(criteria);
        int ops = pair.first;
        std::cout << "Search took " << ops << " operations" << std::endl;;
    } catch (const LList::NotFound& ex) {
        std::cout << ex.what() << std::endl;
    }
}


int main(int argc, const char* argv[]) {
    LList::LinkedList<Book> list;

    if (argc < 2) {
        std::cout << "no input file provided" << std::endl;
        std::cout << "usage: " << argv[0] << " {infile}" << std::endl;
        return 0;
    }

    std::ofstream nullStream("out.txt");

    std::ifstream infile(argv[1]);
    if (!infile.is_open()) {
        std::cout << argv[1] << ": file not found" << std::endl;
        return 0;
    }

    while(!infile.eof()) {
        Book book;
        std::string fakeStr;
        enter_field("title", book.title, infile, nullStream);
        enter_field("author", book.author, infile, nullStream);
        enter_field("date", book.publicationDate, infile, nullStream);
        std::getline(infile, fakeStr);
        list.push_back(book);
    }

    std::ofstream dotfile("list.dot");
    list.to_dot(dotfile, [](const Book& b) {
            std::ostringstream ss;
            ss << b << "\n";
            return ss.str();
    });

    std::cout << "\n\nbooks:\n\n";

    bool exit = false;
    while (!exit) {
        list.for_each( PrintValue<Book>( "=======\n", "\n=======\n" ) );
        std::cout << "\n";

        std::cout << "choose one of the options:\n";
        std::cout << " 1. Delete by author\n 2. Delete by title\n";
        std::cout << " 3. Find by author\n 4. Find by title\n";
        std::cout << " 5. Delete first\n 4. Delete last\n";
        std::cout << " -1. Exit\n";

        int option;

        std::cin >> option;
        std::cin.ignore();

        switch (option) {
        case -1: {
            exit = true;
            break;
        } case 1: {
            std::string authorToDel;
            enter_field("enter author name to delete his books", authorToDel);
            delete_if(list, AuthorIs(authorToDel));
            break;
        } case 2: {
            std::string titleToDel;
            enter_field("enter book title to delete", titleToDel);
            delete_if(list, TitleIs(titleToDel));
            break;
        } case 3: {
            std::string authorToFind;
            enter_field("enter author name to find his book", authorToFind);
            find_by(list, AuthorIs(authorToFind));
            break;
        } case 4: {
            std::string titleToFind;
            enter_field("enter book title to find", titleToFind);
            find_by(list, TitleIs(titleToFind));
            break;
        } case 5: {
            list.pop_front();
            break;
        } case 6: {
            list.pop_back();
            break;
        } default: {
            break;
        }
        }
    }

    return 0;
}
