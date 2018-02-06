#include <iostream>
#include "book.hpp"
#include "linkedlist.hpp"
#include <fstream>


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


int main(int argc, const char* argv[]) {
    LList::LinkedList<Book> list;

    if (argc < 2) {
        std::cout << "no input file provided" << std::endl;
        std::cout << "usage: " << argv[0] << " {infile}" << std::endl;
        return 0;
    }

    std::ofstream nullStream("out.txt");
    std::ifstream infile(argv[1]);

    while(!infile.eof()) {
        Book book;
        std::string fakeStr;
        enter_field("title", book.title, infile, nullStream);
        enter_field("author", book.author, infile, nullStream);
        enter_field("date", book.publicationDate, infile, nullStream);
        std::getline(infile, fakeStr);
        list.push_back(book);
    }

    std::cout << "\n\nbooks:\n\n";

    list.for_each(
                PrintValue<Book>(
                    "==================\n",
                    "\n==================\n"
                    )
                );

    std::string authorToDel;
    enter_field("enter author name to delete his books", authorToDel);

    try {
        list.find_and_del(AuthorIs(authorToDel));

        std::cout << "\n\nbooks after deletion:\n\n";

        list.for_each(
                    PrintValue<Book>(
                        "*****************\n",
                        "\n*****************\n"
                        )
                    );
    } catch (const LList::NotFound& ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}
