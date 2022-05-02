#include <iostream>
#include "DataStructures.hpp"

using namespace DataStructures;

int main() {
    std::function<void(int)> show = [](int value) -> void {
        std::cout << value << " "; 
    };
    std::function<bool(int,int)> compare = [](int a, int b) -> bool {
        return a < b;
    };
    DoubleLinkedList<int>* dl = new DoubleLinkedList<int>(show,compare);
    dl->pushBack(5);
    dl->pushFront(8);
    dl->pushFront(9);
    dl->pushFront(10);
    dl->insertInPos(2,2);
    dl->print();
    std::cout << "\nSorted:\n";
    dl->BubleSort();
    //dl->BubleSortConUnCambioLeve();
    dl->print();
    delete dl;

    /* Stack<int>* stack = new Stack<int>;
    stack->push(5);
    stack->push(2);
    stack->push(3);
    std::cout << "\n" << stack->Top(); */

    auto comp = [](int a, int b) -> bool {
        return a < b;
    };
    StackMin<int>* minStack = new StackMin<int>(comp);
    minStack->push(10);
    minStack->push(9);
    minStack->push(2);
    minStack->push(8);
    minStack->push(5);
    std::cout << "\nThe minimum value is " << minStack->getMin() << "\n"; // return -3
    minStack->pop();
    minStack->top();   // return 0
    std::cout << "\nThe minimum value is " << minStack->getMin() << "\n"; // return -2
    return 0;
}