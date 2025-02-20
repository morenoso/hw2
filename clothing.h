#include <iostream> 
#include "product.h"

class Clothing : public Product
{
public:
    Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
    ~Clothing();
    virtual std::set<std::string> keywords() const;
    virtual std::string displayString() const;
    virtual void dump(std::ostream& os) const;
private:
    std::string _size;
    std::string _brand;

};