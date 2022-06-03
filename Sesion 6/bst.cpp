#include <iostream>
#include "utils.hpp"

using DataStructures::BinarySearchTree;

class Person {
    uint32_t code;
    uint32_t age;
    std::string name;
public:
    Person(uint32_t code = 0, uint32_t age = 0, std::string name = ""): code(code), age(age), name(name) {}
    friend std::ostream& operator<<(std::ostream& os, Person p) {
        os << p.age << "|" << p.code << "|" << p.name;
        return os;
    }
};

int main() {
    BinarySearchTree<int, Person>* bst = new BinarySearchTree<int, Person>(
        [](int a, int b) -> bool { return a < b;},
        [](Person p) -> void { std::cout << p << " "; },
        [](int a, int b) -> bool { return a == b; }
    );
    bst->insert(5,Person(123,45,"Miguel"));
    bst->insert(4,Person(123,45,"Ana"));
    bst->insert(8,Person(123,45,"María"));
    bst->insert(3,Person(123,45,"Juan"));
    bst->insert(1,Person(123,45,"Javier"));
    bst->insert(6,Person(123,45,"Manuel"));
    bst->insert(7,Person(123,45,"Victor"));
    bst->insert(9,Person(123,45,"Daniel"));
    bst->insert(10,Person(123,45,"Eduardo"));
    std::cout << "\nThe value is " << bst->getByKey(8) << "\n";
    bst->display();
    delete bst;
}