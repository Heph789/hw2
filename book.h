#ifndef BOOK_H
#define BOOK_H
#include "product.h"

class Book : public Product {
public:
    Book(const std::string name, double price, int qty,
         const std::string isbn, const std::string author);
    
    std::set<std::string> keywords();

    bool isMatch(std::vector<std::string>& searchTerms);

    std::string displayString();

    void dump(std::ostream& os);

private:
    std::string isbn_;
    std::string author_;
};

#endif