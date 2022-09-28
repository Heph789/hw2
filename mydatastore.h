#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <map>
#include <list>
#include "datastore.h"

/**
 * DataStore Interface needed for parsing and instantiating products and users
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 *
 * DO NOT EDIT
 */


class MyDataStore : public DataStore {
public:
    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    /**
     * Adds product to uname's cart (pushes to back of list). Return true if adding was a success. False if otherwise.
     */
    bool add(const std::string& uname, Product* p);

    /**
     * Displays cart of uname to passed ostream.
     */
    bool displayCart(std::ostream& out, std::string uname);

    /**
     * "Buys" cart of uname
     */
    bool buycart(std::string uname);

    void print(std::ostream& ofile);

private:
    std::set<Product*> prodSet;
    std::map<std::string, std::set<Product*> > prodMap; // maps keywords to product sets
    std::map<std::string, std::pair<User*, std::list<Product*> > > userMap; // maps users to their carts

    /**
     * Returns second item of userMap[uname] if it exists, null otherwise
     */
    std::pair<User*, std::list<Product*>>* getcart_(std::string uname);
};

#endif
