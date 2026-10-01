#include "datastore.h"
#include "product.h"
#include <map>
#include <queue>

class MyDataStore : public DataStore {
    public:
        MyDataStore();
        ~MyDataStore();

        void addProduct(Product* p);
        void addUser(User* u);

        std::vector<Product*> search(std::vector<std::string>& terms, int type);
        void dump(std::ostream& ofile);

        std::vector<Product*> getProducts() const { return products_; }
        std::vector<User*> getUsers() const { return users_; }

        User* findUser(const std::string& username) const {
            for (size_t i = 0; i < users_.size(); ++i) {
                if (users_[i]->getName() == username) {
                    return users_[i];
                }
            }
            return nullptr;
        }
        void addToCart(const std::string& username, Product* product);


        void viewCart(const std::string& username);
        void buyCart(const std::string& username);

    private:
        std::vector<Product*> products_;
        std::vector<User*> users_;
        std::map<User*, std::queue<Product*> > userCarts_;

};