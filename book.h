#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include <string>
#include <set>

class Book : public Product {
    public:
        Book(const std::string name, double price, int qty, const std::string author, const std::string isbn);

        /**
        * Functions to override 
        */
        std::set<std::string> keywords() const;

        bool isMatch(std::vector<std::string>& searchTerms) const;

        std::string displayString() const;

        void dump(std::ostream& os) const;

    private:
        std::string author_;
        std::string isbn_;

};

#endif