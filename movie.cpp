#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string name, double price, int qty,
           const std::string genre, const std::string rating) 
    : Product("movie", name, price, qty), genre_(genre), rating_(rating)
{

}

template set<string> setUnion<string>(set<string>&, set<string>&);

std::set<std::string> Movie::keywords() const
{
    set<string> keywords;
    // product general
    set<string> parsedName = parseStringToWords(name_);
    // movie specific
    keywords.insert(convToLower(genre_));

    keywords = setUnion(keywords, parsedName);
    return keywords;
}

std::string Movie::displayString() const
{
    return name_ + 
           "\nAuthor: " + rating_ + " ISBN: " + genre_ + "\n" + 
           to_string(price_) + " " + to_string(qty_) + " left.";
}

void Movie::dump(std::ostream& os) const
{
    Product::dump(os);
    os << genre_ + "\n"
       << rating_ + "\n";
}