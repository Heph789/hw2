#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string name, double price, int qty,
           const std::string isbn, const std::string author) 
    : Product("book", name, price, qty), isbn_(isbn), author_(author)
{

}

template set<string> setUnion<string>(set<string>&, set<string>&);

std::set<std::string> Book::keywords() const
{
    set<string> keywords;
    // product general
    keywords.insert(category_);
    set<string> parsedName = parseStringToWords(name_);
    // book specific
    keywords.insert(isbn_);
    set<string> parsedAuthor = parseStringToWords(author_);

    keywords = setUnion(keywords, parsedName);
    keywords = setUnion(keywords, parsedAuthor);
    return keywords;
}

std::string Book::displayString() const
{
    return name_ + 
           "\nAuthor: " + author_ + " ISBN: " + isbn_ + "\n" + 
           to_string(price_) + " " + to_string(qty_) + " left.";
}

void Book::dump(std::ostream& os)
{
    string db;
    db = category_ + "\n" +
         name_ + "\n" +
         to_string(price_) + "\n" +
         to_string(qty_) + "\n" +
         isbn_ + "\n" +
         author_ + "\n";
    os << db;
}