
/*#include <iostream>
#include <string>
#include <fstream>
#include "utils.hpp"



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
    static Person createMockPerson() {
        return Person(Utils::generateMockNumber(1000,9999),Utils::generateMockNumber(25,80), Utils::generateRandomString(15));
    }
};

class PersonRepository {
    std::string path;
    std::ofstream file;
public:
    PersonRepository(std::string path): path(path) {
        this->file.open(path);
    }
    ~PersonRepository() {
        this->file.close();
    }
    void generateAndSaveMockData(size_t quantity) {
        for(size_t i = 0; i < quantity; ++i)
            file << Person::createMockPerson() << "\n";
    }
};


int main() {
    PersonRepository* repo = new PersonRepository("output.txt");
    repo->generateAndSaveMockData(100);
    delete repo;
    return 0;
}*/