#include <iostream>
#include <vector>
#include <queue>
#include "mydatastore.h"
#include "util.h"

void MyDataStore::addProduct(Product* p){
    //not done yet, check again, have to shower right now


    //set of keywords that our product has
    //may need to specify the keywords func more, not sure yet
    std::set<std::string> keywords = p->keywords();

    //iterate through each keyword
    for(std::set<std::string>::iterator it = keywords.begin(); it!= keywords.end(); ++it){
        //if keyword isn't in our mapping
        if(keyWordProdMapping.find(*it) == keyWordProdMapping.end()){
            //add our new keyword and product to the mapping
            std::set<Product*> keyProds;
            keyProds.insert(p);
            keyWordProdMapping.insert(make_pair(*it, keyProds));
        }else{
            //if keyword is in the mapping, just add the product to the vector that belongs to the keyword
            keyWordProdMapping.find(*it)->second.insert(p);
        }
    }
    products.push_back(p);
}

void MyDataStore::addUser(User* u){
    //check if user exists in our map of carts
    if(userCarts.find(convToLower(u->getName()))==userCarts.end()){
        //if they don't, make them a cart associated with username
        std::queue<Product*> cart;
        userCarts.insert(make_pair(convToLower(u->getName()), cart));
        users.push_back(u);
        nameAcctLink.insert(make_pair(convToLower(u->getName()), u));
    }
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    std::vector<Product*> results;
    std::set<Product*> firstSet;
    //AND search
    if(type == 0)
    {
        //for each term in the search
        for(size_t i = 0; i < terms.size(); i++){
            if(i==0){
                //get a set of products that belong to our first term
                firstSet = keyWordProdMapping.find(terms[i])->second;
            }else{
                //get the set that has the products found under the i-1 term and i/current term
                firstSet = setIntersection(firstSet,keyWordProdMapping.find(terms[i])->second);
            }
            
        }
    }
    //OR search
    else{
        //for each term in the search
        for(size_t i = 0; i < terms.size(); i++){
            if(i == 0){
                //get set of products that belong to first term
                firstSet = keyWordProdMapping.find(terms[i])->second;
            }else{
                //find the set of products that includes products under our last and current term
                firstSet = setUnion(firstSet,keyWordProdMapping.find(terms[i])->second);
            }
        }
    }
    //create the vector we will return, which has all the products in the set the search found
    for(std::set<Product*>::iterator it = firstSet.begin(); it != firstSet.end(); ++it){
        results.push_back(*it);
    }
    return results;
}


void MyDataStore::dump(std::ostream& ofile){
    ofile << "<products>" << std::endl;
    for(size_t i = 0; i < products.size(); i++) {
        products[i]->dump(ofile);
    }
    ofile << "</products>" << std::endl;
    ofile << "<users>" << std::endl;
    for(size_t i = 0; i < users.size(); i++) {
        users[i]->dump(ofile);
    }
    ofile << "</users>";
}





bool MyDataStore::userCartAdd(std::string username, int hit_result_idx, std::vector<Product*> hits){
    //if we can find the user in our map of carts
    if(userCarts.find(convToLower(username))!= userCarts.end() && (hit_result_idx >= 0 && hit_result_idx < (int)hits.size())){
        //add the item the user wants into the cart
        userCarts.find(username)->second.push(hits[hit_result_idx]);
        return true;
    }
    return false;


 }

 bool MyDataStore::viewCart(std::string username) {
    if(userCarts.find(convToLower(username)) == userCarts.end()){
        return false;
    }

    int cartNo = 1;
    //iterator purely for reading clarity
    std::map<std::string, std::queue<Product*> >::iterator it = userCarts.find(convToLower(username));
    std::queue<Product*> temp = it->second;

    for(size_t i = 0; i < it->second.size(); i++){
        std::cout << cartNo << ": " << temp.front()->getName() << std::endl;
        temp.pop();
        cartNo++;
    }
    return true;
 }

 bool MyDataStore::buyCart(std::string username) {
    if(userCarts.find(convToLower(username)) != userCarts.end()) {
        std::queue<Product*> copy;  
        User* acct = nameAcctLink.find(convToLower(username))->second;
        while(! (userCarts.find(convToLower(username))->second.empty()) ) {
            Product* temp = userCarts.find(convToLower(username))->second.front();
            if(acct->getBalance() > temp->getPrice() && temp->getQty() > 0){
                acct->deductAmount(temp->getPrice());
                temp->subtractQty(1);
            }else{
                copy.push(userCarts.find(convToLower(username))->second.front());
            }
            userCarts.find(convToLower(username))->second.pop();
        }
        userCarts.find(convToLower(username))->second = copy;
        return true;
    }
    return false;
 }


 void MyDataStore::clearUsers() {
    int len = (int)users.size();
    for(int i = len-1; i >= 0; i--) {
        delete products[i];
        products.pop_back();
    }
    //clean up any hanging threads
    std::map<std::string, User*>empty;
    nameAcctLink = empty;
 }

 void MyDataStore::clearProducts() {
    int len = (int)products.size();
    //get rid of our products
    for(int i = len-1; i >= 0; i--){
        delete products[i];
        products.pop_back();
    }
    //clean up any hanging threads
    std::map<std::string, std::set<Product*> > empty;
    keyWordProdMapping = empty;
    std::map<std::string, std::queue<Product*> > empty2;
    userCarts = empty2;
 }