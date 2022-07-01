#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <list>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cmath>
#include "avl.hpp"


class Employee {
    std::string name;
    double salary;
    double loan;
public:
    //Employee()
};

class Enterprise {
    std::string name;
    std::uint32_t c1;
    std::uint32_t c2;
    std::uint32_t c3;
    double result; // calculo;
    char category; // categoria
    vector<Employee>* employees;
public:
    Enterprise(std::string name, std::uint32_t c1, std::uint32_t c2, std::uint32_t c3):
    name(name), c1(c1), c2(c2), c3(c3) {
        this->employees = new vector<Employee>;
    }
    std::uint32_t getC1() {
        return c1;
    }
    std::uint32_t getC2() {
        return c2;
    }
    std::uint32_t getC3() {
        return c3;
    }
    friend std::ostream& operator<<(std::ostream& os, Enterprise e) {
        os << e.name << "|" << e.c1 << "|" << e.c2 << "|" << e.c3 << "|" << e.result << "|" << e.category;
        return os;
    }
    bool operator<(Enterprise b) {
        return this->name < b.name;
    }
    bool operator==(Enterprise b) {
        return this->name.compare(b.name) == 0;
    }
    void setResult() {
        this->result = sqrt((double)(pow(c1,2) + pow(c2,2) + pow(c3,2)));
    }
    void setCategory() {
        if( this->result >= 0 && this->result <= 43)
            this->category = 'A';
        else if (this->result >= 44 && this->result <= 86)
            this->category = 'B';
        else if (this->result >= 87 && this->result <= 130)
            this->category = 'C';
        else if (this->result >= 131 && this->result <= 173)
            this->category = 'D';
    }
};

class Solution {
    std::list<Enterprise>* enterprises;
    AVL<Enterprise>* avl;
public:
    Solution() {
        this->enterprises = new std::list<Enterprise>;
        this->avl = new AVL<Enterprise>(
            [](Enterprise a, Enterprise b) -> bool {
                return a < b;
            },
            [] (Enterprise a) -> void {
                std::cout << a << "\n";
            },
            [] (Enterprise a, Enterprise b) -> bool {
                return a == b;
            }
        );
        this->_readEnterpriseInput();
    }
private:
    void _readEnterpriseInput() {
        std::ifstream arch("empresas.csv");
        std::string line;
        while(getline(arch,line,'\n')) {
            std::string aux;
            std::string name;
            std::uint32_t c1;
            std::uint32_t c2;
            std::uint32_t c3;

            std::stringstream s(line);
            getline(s,aux,' ');
            name = aux;
            getline(s,aux,' ');
            c1 = std::stoi(aux);
            getline(s,aux,' ');
            c2 = std::stoi(aux);
            getline(s,aux,' ');
            c3 = std::stoi(aux);
            enterprises->push_back(Enterprise(name,c1,c2,c3));
        }
        for(Enterprise& enterprise: *(this->enterprises)) {
            enterprise.setResult();
            enterprise.setCategory();
            this->avl->insert(enterprise);
        }
        this->avl->print();
        arch.close();
    }
    void readEmployeesInput() {
        
    }
};

auto main() -> int {
    Solution* solution = new Solution();
    delete solution;
    return 0;
}