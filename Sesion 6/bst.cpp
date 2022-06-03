#include <iostream>
#include "utils.hpp"

using DataStructures::BinarySearchTree;

class Person {
    uint32_t code;
    uint32_t age;
    std::string name;
public:
    Person(uint32_t code, uint32_t age, std::string name): code(code), age(age), name(name) {}
    friend std::ostream& operator<<(std::ostream& os, Person p) {
        os << p.age << "|" << p.code << "|" << p.name;
        return os;
    }
};

int main() {
    BinarySearchTree<int, Person>* bst = new BinarySearchTree<int, Person>(
        [](int a, int b) -> bool { return a < b;},
        [](Person p) -> void { std::cout << p << " "; }
    );
    bst->insert(5,Person(123,45,"Miguel"));
    bst->insert(4,Person(123,45,"Ana"));
    bst->insert(8,Person(123,45,"María"));
    bst->display();
    delete bst;
}