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
    std::uint32_t salary;
    double loan;
public:
    Employee(std::string name, uint32_t salary)
    :name(name), salary(salary) {}
    friend std::ostream& operator<<(std::ostream& os, Employee e) {
        os << e.name << "|" << e.salary << "|" << e.loan;
        return os;
    }
    void setLoan(std::uint32_t loanPercentaje) {
        this->loan = ((double)(this->salary * (100 +  loanPercentaje))) / 100.0;
    }
};

class Enterprise {
    std::string name;
    std::uint32_t c1;
    std::uint32_t c2;
    std::uint32_t c3;
    double result; // calculo;
    char category; // categoria
    vector<Employee*>* employees;
    std::uint32_t loanPercentage;
public:
    Enterprise(std::string name, std::uint32_t c1 = 0, std::uint32_t c2 = 0, std::uint32_t c3 = 0):
    name(name), c1(c1), c2(c2), c3(c3) {
        this->employees = new vector<Employee*>;
    }
    friend std::ostream& operator<<(std::ostream& os, Enterprise e) {
        os << "\n"<< e.name << "|" << e.c1 << "|" << e.c2 << "|" << e.c3 << "|" << e.result << "|" << e.category << "\n";
        for(Employee* e: *(e.employees))
            os << "\t" << *e << "\n";
        os << "-------\n";
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
        if( this->result >= 0 && this->result <= 43){
            this->category = 'A';
            this->loanPercentage = 10;
        }
        else if (this->result >= 44 && this->result <= 86){
            this->category = 'B';
            this->loanPercentage = 15;
        }
        else if (this->result >= 87 && this->result <= 130){
            this->category = 'C';
            this->loanPercentage = 25;
        }
        else if (this->result >= 131 && this->result <= 173){
            this->category = 'D';
            this->loanPercentage = 40;
        }
    }
    void addEmployee(Employee* e) {
        this->employees->push_back(e);
    }
    std::uint32_t getLoanPercentage() {
        return this->loanPercentage;
    }
    void displayEmployees() {
        for(Employee* e: *(employees))
            std::cout << "\t" << *e << "\n";
    }
};

class Solution {
    std::list<Enterprise*>* enterprises;
    AVL<Enterprise*>* avl;
public:
    Solution() {
        this->enterprises = new std::list<Enterprise*>;
        this->avl = new AVL<Enterprise*>(
            [](Enterprise* a, Enterprise* b) -> bool {
                return *a < *b;
            },
            [] (Enterprise* a) -> void {
                std::cout << *a << "\n";
            },
            [] (Enterprise* a, Enterprise* b) -> bool {
                return *a == *b;
            }
        );
        this->_readEnterpriseInput();
        this->_readEmployeesInput();
    }
    void getEmployeesByEnterpriseName(std::string enterpriseName) {
        Enterprise* enterprise = new Enterprise(enterpriseName);
        std::cout << "\nEmployees in " << enterpriseName << "\n";
        this->avl->find(enterprise,
            [](Enterprise* en) -> void {
                en->displayEmployees();
            }
        );
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
            enterprises->push_back(new Enterprise(name,c1,c2,c3));
        }
        for(Enterprise* enterprise: *(this->enterprises)) {
            enterprise->setResult();
            enterprise->setCategory();
            this->avl->insert(enterprise);
        }
        arch.close();
    }
    void _readEmployeesInput() {
        std::ifstream arch("trabajadores.csv");
        std::string line;
        while(getline(arch,line,'\n')) {
            std::string aux;
            std::string enterpriseName;
            std::string name;
            std::uint32_t salary;
            std::stringstream s(line);
            getline(s,aux,' ');
            enterpriseName = aux;
            getline(s,aux,' ');
            name = aux;
            getline(s,aux,' ');
            salary = std::stoi(aux);
            Employee* employee = new Employee(name,salary);
            Enterprise* enterprise = new Enterprise(enterpriseName);
            this->avl->find(enterprise,
                [&employee](Enterprise* en) -> void {
                    employee->setLoan(en->getLoanPercentage());
                    en->addEmployee(employee);
                }
            );
        }
        arch.close();
        this->avl->print();
    }
};

auto main() -> int {
    Solution* solution = new Solution();
    solution->getEmployeesByEnterpriseName("Empresa_2");
    delete solution;
    return 0;
}