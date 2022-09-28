#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string name, double price, int qty,
                   const std::string size, const std::string brand) 
                   : Product("clothing", name, price, qty), size_(size), brand_(brand)
{

}

template set<string> setUnion<string>(set<string>&, set<string>&);

std::set<std::string> Clothing::keywords() const
{
    set<string> keywords;
    // product general
    set<string> parsedName = parseStringToWords(name_);
    // clothing specific
    set<string> parsedBrand = parseStringToWords(brand_);

    keywords = setUnion(keywords, parsedName);
    keywords = setUnion(keywords, parsedBrand);
    return keywords;
}

std::string Clothing::displayString() const
{
    return name_ + 
           "\nSize: " + size_ + " Brand: " + brand_ + "\n" + 
           to_string(price_) + " " + to_string(qty_) + " left.";
}

void Clothing::dump(std::ostream& os) const
{
    Product::dump(os);
    os << size_ + "\n"
       << brand_ + "\n";
}