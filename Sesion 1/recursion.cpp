#include <iostream>
#include <vector>
#include <string>
#include <functional>


int count7(int n){
    if(n == 0) return 0;
    int num = n % 10;
    return ((num == 7)?1:0) + count7(n/10);
}

void sortArray(std::vector<int>& arr){
    static size_t index = 0;
    if(index == arr.size() - 1) return;
    for(size_t i = index + 1; i < arr.size(); ++i){
        if(arr[i] < arr[index] ){
            size_t v = arr[i];
            arr[i] = arr[index];
            arr[index] = v;
        }
    }
    ++index;
    sortArray(arr);
}

// Euclides Algorithm
int mcd(int m, int n){
    if(n == 0 ) return m;
    return mcd(n,m % n);
}


template<class T>
class LinkedList {
    class Node {
    public:
        T value;
        Node* next;
        Node(T value): value(value), next(nullptr) {}
    };
    typedef unsigned int us;
    std::function<void(T)> show;
    Node* head;
    Node* top;
    us size;
public:
    LinkedList(std::function<void(T)> show): show(show) {
        head = nullptr;
        top = nullptr;
        size = 0;
    }
    void pushFront(T value) {
        Node* newNode = new Node(value);
        if (size == 0) {
            head = newNode;
            top = newNode;
            ++size;
            return;
        }
        newNode->next = head;
        head = newNode;
        ++size;
    }
    void pushBack(T value){
        Node* newNode = new Node(value);
        if (size == 0) {
            head = newNode;
            top = newNode;
            ++size;
            return;
        }
        top->next = newNode;
        top = newNode;
        ++size;
    }
    void print(){
        Node* aux = head;
        while (aux != nullptr) {
            show(aux->value);
            aux = aux->next;
        }
        std::cout << "nullptr\n";
    }
private:
    void _printWithRecursion(Node* n){
        if(n == nullptr)
            return;
        show(n->value);
        _printWithRecursion(n->next);
    }
    Node* _invertir(Node* n){ // Hacerlo con bucles. Consejo: usen 3 punteros auxiliares
        if(n->next == nullptr)
            return n;
        Node* res = _invertir(n->next);
        res->next = n;
        return n;
    }
public:
    void printWithRecursion(){
        _printWithRecursion(head);
    }
    void invertir(){
        Node* res = _invertir(head);
        res->next = nullptr;
        head = top;
        top = res;
    }
};

class Persona {
    unsigned int dni;
    std::string nombre;
public:
    Persona(unsigned int dni, std::string nombre): dni(dni), nombre(nombre) {}
    std::string mostrar(){
        return std::to_string(dni) + " " + nombre;
    }
    std::string getName(){
        return this->nombre;
    }
};

int main(){
    /*std::vector<int> arr = { 5,6,7,1,4,9,2};
    std::cout << count7(71707077) << "\n";
    std::cout << "\n";
    sortArray(arr);
    for(int v: arr){
        std::cout << v << "\n";
    }
    std::cout << "\nMCD 25 - 10\n";
    std::cout << "\n" << mcd(25,10) << "\n";*/
    auto show = [](Persona a) -> void { std::cout << a.mostrar() << " ";};
    LinkedList<Persona>* l = new LinkedList<Persona>(show);
    l->pushBack(Persona(43545,"Miguel"));
    l->pushBack(Persona(5667,"Diego"));
    l->pushBack(Persona(565656,"Ana"));
    l->print();
    std::cout << "\n";
    l->printWithRecursion();
    l->invertir();
    std::cout << "\n";
    l->printWithRecursion();
    delete l;
    return 0;
}