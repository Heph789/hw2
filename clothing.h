#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"

class Clothing : public Product {
public:
    Clothing(const std::string name, double price, int qty,
         const std::string size, const std::string brand);
    
    std::set<std::string> keywords();

    bool isMatch(std::vector<std::string>& searchTerms);

    std::string displayString();

    void dump(std::ostream& os);

private:
    std::string size_;
    std::string brand_;
};

#endif