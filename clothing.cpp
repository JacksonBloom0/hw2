#include "clothing.h"
#include "util.h"
#include <string>

Clothing::Clothing(const std::string name, double price, int qty, std::string size, std::string brand) :
    Product("clothing", name, price, qty), 
    size_(size), 
    brand_(brand) 
{

}

std::set<std::string> Clothing::keywords() const {
    std::set<std::string> words = parseStringToWords(brand_ + " " + getName());

    return words;
    
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const {
    std::set<std::string> word_set = keywords();
    for (size_t i = 0; i < searchTerms.size(); ++i) {
        if (word_set.find(convToLower(searchTerms[i])) != word_set.end()) {
            return true;
        }
    }
    return false;
}
/*
Displays as:

    <name>
    Size: <size> Brand: <brand>
    <price> <quantity> left.

*/
std::string Clothing::displayString() const {
    std::string display = (getName() + "\n" +
    "Size: " + size_ + " Brand: " + brand_ + "\n" +
    std::to_string(getPrice()) + " " + std::to_string(getQty()) + " left.");

    return display;
}

void Clothing::dump(std::ostream& os) const {
    Product::dump(os);
    os << size_ << "\n" << brand_ << std::endl;
}