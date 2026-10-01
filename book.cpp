#include "book.h"
#include "util.h"
#include <string>
#include <set>

Book::Book(const std::string name, double price, int qty, const std::string author, const std::string isbn) :
    Product("Book", name, price, qty), 
    author_(author), 
    isbn_(isbn) 
{

}

std::set<std::string> Book::keywords() const {
    std::string raw_words = getName() + " " + author_;
    // A large string of key words to be put into a set
    std::set<std::string> word_set = parseStringToWords(raw_words);
    word_set.insert(isbn_);

    return word_set;

}

bool Book::isMatch(std::vector<std::string>& searchTerms) const {
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
    Author: <author> ISBN: <isbn>
    <price> <quantity> left.

*/
std::string Book::displayString() const {
    
    std::string display = (getName() + "\n" + 
    "Author: " + author_ + " ISBN: " + isbn_ + "\n" + 
    std::to_string(getPrice()) + " " + std::to_string(getQty()) + " left.");

    return display;
}

void Book::dump(std::ostream& os) const {
    Product::dump(os);
    os << isbn_ << "\n" << author_ << std::endl;
}