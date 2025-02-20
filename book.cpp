#include <iostream>
#include "book.h"
#include "util.h"
#include "product.h"

Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author)
 : Product(category,name,price,qty){
    this->isbn = isbn;
    this->author = author;
}

Book::~Book(){

}

std::set<std::string> Book::keywords() const{
    std::set<std::string> bookName = parseStringToWords(getName());
    std::set<std::string> authorNames = parseStringToWords(author);
    std::set<std::string> keywords = setUnion(bookName,authorNames);
    keywords.insert(isbn);
    return keywords;
}

std::string Book::displayString() const{
    std::string output;
    output = name_ + "\n";
    output += "Author: " + author + " ISBN: " + isbn + "\n";
    output += std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    return output;
}

void Book::dump(std::ostream& os) const{
    Product::dump(os);
    os << isbn << "\n" << author << std::endl;
}