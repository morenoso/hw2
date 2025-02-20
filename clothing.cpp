#include <iostream>
#include "clothing.h"
#include "util.h"

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand)
: Product(category, name, price, qty) 
{
    _size = size;
    _brand = brand;
}

Clothing::~Clothing()
{


}

std::set<std::string> Clothing::keywords() const 
{
    std::set<std::string> brandWords = parseStringToWords(_brand);
    std::set<std::string> nameWords = parseStringToWords(name_);
    return setUnion(brandWords,nameWords);
}

std::string Clothing::displayString() const 
{
    std::string output = name_ + "\n";
    output += "Size: " + _size + " Brand: " + _brand + "\n";
    output += std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    return output;
}

void Clothing::dump(std::ostream& os) const {
    Product::dump(os);
    os << _size << "\n" << _brand << std::endl;
}