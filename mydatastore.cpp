#include "mydatastore.h"
#include "util.h"

using namespace std;


MyDataStore::~MyDataStore()
{

}

/**
 * Adds a product to the data store
 */
void MyDataStore::addProduct(Product* p)
{
    prodSet.insert(p);
    set<string> kwords = p->keywords();
    set<string>::iterator kit;
    for(kit = kwords.begin(); kit != kwords.end(); kit++) {
        map<string, set< Product*> >::iterator ele = prodMap.find(*kit);
        // if the keyword is already set in map, add product to element
        if (ele != prodMap.end()) {
            set<Product*> &prodSet = ele->second;
            prodSet.insert(p);
        }
        // else, create new set with product in it and insert it with keyword
        else {
            set<Product*> newProdSet;
            newProdSet.insert(p);
            prodMap.insert(pair<string, set<Product*> >(*kit, newProdSet));
        }
    }
    
}

/**
 * Adds a user to the data store
 */
void MyDataStore::addUser(User* u)
{
    string uname = u->getName();
    map<string, pair<User*, list<Product*> > >::iterator uit = userMap.find(uname);
    // if user does not already exist in map, add it
    if (uit == userMap.end()) {
        pair<User*, list<Product*> > cart;
        cart.first = u;
        userMap.insert(pair<string, pair<User*, list<Product*> > >(uname, cart));
    }
}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    if (terms.empty()) {
        return vector<Product*>(prodSet.begin(), prodSet.end()); // calling AND/OR without search terms will just return the entire product set
    }
    
    set<Product*> base;
    for(size_t i = 0; i < terms.size(); ++i) {
        string &term = terms[i];
        std::map<std::string, std::set<Product*> >::iterator setIt = prodMap.find(term);

        // if this is the first valid term, set it to base
        if (i == 0) {
            base = setIt->second; // NOTE: this might not work since setIt->first might come off stack leaving base pointing to junk
        }
        else {
            if (!type) { // AND
                base = setIntersection(base, setIt->second);
                if(base.empty()) { // since the first time and intersection yields an empty set, we know that every term afterwards doesn't matter
                    break;
                }
            }
            else { // OR
                base = setUnion(base, setIt->second);
            }
        }
    }

    if (base.empty()) {
        return vector<Product*>(0);
    }
    return vector<Product*>(base.begin(), base.end()); // copies base into vector
}

/**
 * Reproduce the database file from the current Products and User values
 */
void MyDataStore::dump(std::ostream& ofile)
{
    set<Product*>::iterator sit;
    ofile << "<products>\n";
    for(sit = prodSet.begin(); sit != prodSet.end(); sit++) {
        (*sit)->dump(ofile);
    }
    ofile << "</products>\n<users>\n";
    
    std::map<std::string, std::pair<User*, std::list<Product*> > >::iterator uit;
    for(uit = userMap.begin(); uit != userMap.end(); uit++) {
        uit->second.first->dump(ofile);
    }
}

/**
 * Returns second item of userMap[uname] if it exists, null otherwise
 */
std::pair<User*, std::list<Product*>>* MyDataStore::getcart_(std::string uname) {
    map<string, pair<User*, list<Product*> > >::iterator uit = userMap.find(uname);
    // if user does not exist, return false
    if (uit == userMap.end()) {
        return nullptr;
    }
    return &(uit->second);
}

bool MyDataStore::add(const std::string& uname, Product* p) {
    pair<User*, list<Product*>>* cartPair = getcart_(uname);
    // if user does not exist, return false
    if (cartPair == nullptr) {
        return false;
    }
    list<Product*>& cart = cartPair->second;
    cart.push_back(p);
    return true;
}

/**
 * Displays cart to passed ostream. Code repurposed from displayProducts function.
 */
bool MyDataStore::displayCart(std::ostream& out, string uname) {
    pair<User*, list<Product*>>* cartPair = getcart_(uname);
    // if user does not exist, return false
    if (cartPair == nullptr) {
        return false;
    }
    list<Product*>& cart = cartPair->second;

    int resultNo = 1;

    if (cart.empty()) {
    	out << uname << "'s cart is empty!" << endl;
    	return true;
    }
    for(list<Product*>::iterator it = cart.begin(); it != cart.end(); ++it) {
        out << "Item " << resultNo << endl;
        out << (*it)->displayString() << endl;
        out << endl;
        resultNo++;
    }
    return true;
}

/**
 * "Buys" cart of uname
 */
bool MyDataStore::buycart(std::string uname) {
    pair<User*, list<Product*>>* cartPair = getcart_(uname);
    // if user does not exist, return false
    if (cartPair == nullptr) {
        return false;
    }
    list<Product*>& cart = cartPair->second;
    User* user = cartPair->first;

    for(list<Product*>::iterator it = cart.begin(); it != cart.end(); it++) {
        Product* p = *it;
        if (user->getBalance() >= p->getPrice() && p->getQty() > 0) {
            user->deductAmount(p->getPrice());
            p->subtractQty(1);
            cart.erase(it--);
        }
    }
    return true;
}



#ifdef DEBUG
void MyDataStore::print(std::ostream& ofile)
{
    map<string, set<Product*> >::iterator pit;
    cout << "Products from keywords" << endl;
    for(pit = prodMap.begin(); pit != prodMap.end(); pit++) {
        cout << "Keyword: " << pit->first << endl;
        cout << "Products:";
        
        set<Product*> prodSet = pit->second;
        set<Product*>::iterator psit;
        for(psit = prodSet.begin(); psit != prodSet.end(); psit++) {
            cout << " \"" << (*psit)->getName() << "\" |";
        }
        cout << endl;
    }

    cout << endl << "Users:" << endl;
    map<string, pair<User*, list<Product*> > >::iterator uit;
    for(uit = userMap.begin(); uit != userMap.end(); uit++) {
        User* u = (uit->second).first;
        cout << "User: '" << uit->first << "' " << u->getBalance() << endl;
        cout << "\tCart:";
        list<Product*> prodList = (uit->second).second;
        list<Product*>::iterator plit;
        for(plit = prodList.begin(); plit != prodList.end(); plit++) {
            cout << " \"" << (*plit)->getName() << "\" |";
        }
        cout << endl;
    }
}
#endif
