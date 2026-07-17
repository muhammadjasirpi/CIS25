#include <iostream>
#include <string>
using namespace std;

//struct
struct Patient {
    int id;
    string name;
    int age;
};

int main() {
    //regular patient variable
    Patient p;

    //values with regular variable
    p.id = 1;
    p.name = "John Doe";
    p.age = 30;

    //pointer that stores the address of p
    Patient* ptr = &p;

    //use pointer to display patient information
    cout << "Patient ID: " << ptr->id << endl;
    cout << "Patient Name: " << ptr->name << endl;
    cout << "Patient Age: " << ptr->age << endl;

    return 0;
}

/* Knowledge check
A pointer is a variable that stores the memory address
of another variable. I declared Patient* 
ptr as a pointer to a Patient 
struct. I used it to store the address of the 
regular patient variable (p) and then accessed 
the patient's information using the pointer and 
the -> operator.
------------------------------------------------------
The & operator is the address-of
operator. &p is used to 
obtain the memory address of the variable p 
and assign it to the pointer ptr.
------------------------------------------------------
Patient ID: 1
Patient Name: John Doe
Patient Age: 30
*/
