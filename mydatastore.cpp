#include "mydatastore.h"
#include "util.h"


MyDataStore::MyDataStore() {
    products_ = {};
    users_ = {};
}

MyDataStore::~MyDataStore() {
    for (size_t i = 0; i < products_.size(); ++i) {
        delete products_[i];
    }
    for (size_t i = 0; i < users_.size(); ++i) {
        delete users_[i];
    }
}

void MyDataStore::addProduct(Product* p) {
    
    products_.push_back(p);
}

void MyDataStore::addUser(User* u) {
    users_.push_back(u);
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    if (!terms.size()) {
        return products_;
    }
    std::vector<Product*> results;
    if (type == 1) { // OR
        std::vector<Product*> results;
        for (size_t i = 0; i < products_.size(); ++i) {
            if (products_[i]->isMatch(terms)) {
                results.push_back(products_[i]);
            }
        }
        return results;
    }
    else { // if (type == 0) AND
        for (size_t i = 0; i < products_.size(); ++i) {
            bool match = true;
            std::set<std::string> key_words = products_[i]->keywords();
            for (size_t j = 0; j < terms.size(); ++j) {
                if (!(key_words.find(terms[j]) != key_words.end())) {
                    match = false;
                    break;
                }
            }
            if (match) {
                results.push_back(products_[i]);
            }
        }
        return results;
    }
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << std::endl;
    for (size_t i = 0; i < products_.size(); ++i) {
        products_[i]->dump(ofile);
    }
    ofile << "</products>" << std::endl;
    ofile << "<users>" << std::endl;
    for (size_t i = 0; i < users_.size(); ++i) {
        users_[i]->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}


void MyDataStore::addToCart(const std::string& username, Product* product) {
    if (!findUser(username)) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    User* user = findUser(username);
    userCarts_[user].push(product);
    std::cout << "Added " << product->getName() << " to " << user->getName() << "'s cart." << std::endl;
}


void MyDataStore::viewCart(const std::string& username)  {
    // std::cout << "Viewing cart for " << user->getName() << std::endl;
    if (!findUser(username)) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    User* user = findUser(username);
    if (userCarts_[user].empty()) {
        std::cout << "Your cart is empty." << std::endl;
        return;
    }
    std::queue<Product*> cart = userCarts_[user];
    int itemNumber = 1;

    while (!cart.empty()) {
        std::cout << itemNumber << ". " << cart.front()->displayString() << std::endl;
        cart.pop();
        itemNumber++;
    }
}

void MyDataStore::buyCart(const std::string& username) {
    if (!findUser(username)) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    User* user = findUser(username);
    std::queue<Product*>& cart = userCarts_[user]; // shorthand alias
    std::queue<Product*> final_cart = {}; // final cart to store items that cannot be purchased

    // std::cout << "cart size " << std::to_string(cart.size()) << std::endl;
    size_t len = cart.size();
    for(size_t i = 0; i < len; ++i) {
        Product* item = cart.front();
        double item_cost = item->getPrice();
        // std::cout << "current balance " << std::to_string(user->getBalance()) << std::endl;
        if (user->getBalance() >= item_cost && item->getQty() > 0) {
            user->deductAmount(item_cost);
            item->subtractQty(1);
            // std::cout << "Purchased " << item->getName() << " for " << std::to_string(item_cost) << std::endl;
            std::cout << item->displayString() << std::endl << std::endl;
        }
        else {
            // std::cout << "Could not purchase " << item->getName() << std::endl;
            final_cart.push(item);
        }
        cart.pop();
    }
    userCarts_[user] = final_cart;
}