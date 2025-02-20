#include <iostream>
#include "movie.h"
#include "util.h"
#include "product.h"

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating)
: Product(category, name, price, qty) {
    this->genre = genre;
    this->rating = rating;
}

Movie::~Movie(){

}

std::set<std::string> Movie::keywords() const{
    std::set<std::string> movieKey = parseStringToWords(name_);
    movieKey.insert(genre);
    return movieKey;
}

std::string Movie::displayString() const {
    std::string output = name_ + "\n";
    output += "Genre: " + genre + " Rating: " + rating + "\n";
    output += std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    return output;
}

void Movie::dump(std::ostream& os) const{
    Product::dump(os);
    os << genre << "\n" << rating << std::endl;
}

