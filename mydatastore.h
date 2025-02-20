#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include "datastore.h"
#include "util.h"



class MyDataStore : public DataStore {
public:    
    /**
     * Adds a product to the data store
     */
    virtual void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    virtual void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);


    /**
     * Reproduce the database file from the current Products and User values
     */
    virtual void dump(std::ostream& ofile);



    bool userCartAdd(std::string username, int hit_result_idx, std::vector<Product*> hits);


    bool viewCart(std::string username);

    //if username invalid return false
    //if username valid, iterate through queue

    //1)make a new queue
    //2)as we iterate with (front() and pop()) if the item is NOT being removed fromt he cart
    //we will copy it to the new queue
    //3) if an item IS being removed from the cart we don't copy it to the new queue
    //4) once done iterating(queue is empty) we set the cart queue belonging to that user equal to our new queue
    //that way we have a queue that's been iterated over, while still using a queue itself
    bool buyCart(std::string username);


    //methods used at the end to free all the memory we allocated
    void clearUsers();

    void clearProducts();
    
private:
    std::vector<Product*> products;
    std::vector<User*> users;
    std::map<std::string, std::set<Product*> > keyWordProdMapping;
    std::map<std::string, std::queue<Product*> > userCarts;
    std::map<std::string, User*> nameAcctLink;
};