#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    int id;
    string name;
    double price;

public:
    //constructor
    Product(int id, string name, double price) : id(id), name(name), price(price) {
        cout << "Product constructed: " << name << endl;
    }

    //destructor
    ~Product() {
        cout << "Product destructed: " << name << endl;
    }

    //printdetails method
    void PrintDetails() const {
        cout << "Product ID: " << id << endl;
        cout << "Product Name: " << name << endl;
        cout << "Product Price: $" << price << endl;
    }
};

int main() {
    Product p1(101, "Laptop", 799.99);
    p1.PrintDetails();
    return 0;
}

/* Knowledge check
Constructors initialize objects when they are created, 
while destructors clean up or display a message when 
objects are destroyed.
-----------------------------------------------------
They all share the class name, have no return type, 
and are essential parts of a class for managing an 
object's lifecycle.
-----------------------------------------------------
Product constructed: Laptop
Product ID: 101
Product Name: Laptop
Product Price: $799.99
Product destructed: Laptop
*/
