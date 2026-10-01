#include "movie.h"
#include "util.h"
#include <string>

Movie::Movie(const std::string name, double price, int qty, const std::string genre, const std::string rating) :
    Product("Movie", name, price, qty), 
    genre_(genre), 
    rating_(rating) 
{

}

std::set<std::string> Movie::keywords() const {
    std::set<std::string> word_set = parseStringToWords(getName());
    word_set.insert(genre_);

    // set containing keywords in name of the film + the genre
    return word_set;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const {
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
    Genre: <genre> Rating: <rating>
    <price> <quantity> left.

*/
std::string Movie::displayString() const {
    std::string display = (getName() + "\n" + 
    "Genre: " + genre_ + " Rating: " + rating_ + "\n" + 
    std::to_string(getPrice()) + " " + std::to_string(getQty()) + " left.");

    return display;

}

void Movie::dump(std::ostream& os) const {
    Product::dump(os);
    os << genre_ << "\n" << rating_ << std::endl;
}