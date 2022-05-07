#include <iostream>
#include <functional>
#include <string>
#include <sstream>
#include <fstream>
#include <string.h>


using std::function;
using std::cout;
using std::string;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::stoi;
using std::stod;


template<class T>
class List {
    class Node {
    public:
        T value; // Valor del nodo
        Node* next; //  Puntero al siguiente nodo
        Node(T value, Node* next = nullptr) : value(value), next(next) {}
    };
    Node* inicio;
    Node* fin;
    unsigned long size;
    function<void(T)> mostrar;
public:
    List(function<void(T)> mostrar) : mostrar(mostrar) {
        inicio = fin = nullptr;
        size = 0;
    }
    ~List() {
        while (size > 0) {
            popFront();
        }
        inicio = fin = nullptr;
    }
    void eraseAll() {
        while (size > 0) {
            popFront();
        }
        inicio = fin = nullptr;
    }
    void print() {
        cout << "\n";
        if (size == 0) {
            cout << "\nnullptr";
            return;
        }
        _print(inicio);
    }
private:
    void _print(Node* n) {
        if (n == nullptr) return;
        mostrar(n->value);
        _print(n->next);
    }
public:
    void pushBack(T value) {
        if (size == 0) {
            Node* n = new Node(value);
            inicio = n;
            fin = n;
            ++size;
        }
        else {
            Node* n = new Node(value);
            fin->next = n;
            fin = n;
            ++size;
        }
    }
    void popFront() {
        if (size == 0) return;
        Node* aux = inicio;
        if (size == 1) inicio = fin = nullptr;
        else inicio = inicio->next;
        delete aux;
        --size;
    }
    unsigned long Size() {
        return size;
    }
    Node* insertInRange(function<void(T)> insert, int i, int f, Node* n){
        size_t init = i;
        Node* aux = n;
        for(init; init <= f; ++init){
            insert(aux->value);
            aux = aux->next;
        }
        return aux;
    }
};


class Televisor {
    string marca, color, tecnologia;
    double pulgadas;
    size_t precio;
public:
    Televisor(string marca = "", string color = "", string tecnologia = "", double pulgadas = 0, size_t precio = 0)
        : marca(marca), color(color), tecnologia(tecnologia), pulgadas(pulgadas), precio(precio) {
    }
    string mostrar() {
        return "\nMarca: " + marca + ", Color: " + color + ", Tecnologia: " + tecnologia +
            ", Pulgadas: " + std::to_string(pulgadas) + ", Precio: " + std::to_string(precio);
    }
};

class Solution {
    List<Televisor>* items;
public:
    Solution(){
        auto show = [](Televisor value) -> void {
            cout << value.mostrar() << "-->";
        };
        this->items = new List<Televisor>(show);
    }
    void read(int k) {
        string line = "";
        ifstream arch("input.txt");
        while(getline(arch,line,',')){
            stringstream s(line);
            string aux;
            string marca, color, tecnologia;
            double pulgadas;
            size_t precio;
            getline(s,aux,'|');
            marca = aux;
             getline(s,aux,'|');
             color = aux;
             getline(s,aux,'|');
            tecnologia = aux;
             getline(s,aux,'|');
            pulgadas = stod(aux);
             getline(s,aux,'|');
            precio = stoi(aux);
            Televisor t(marca,color,tecnologia,pulgadas,precio);
            items->pushBack(t);
        }
        arch.close();
        items->print();
    }
};


int main() {
    Solution sol;
    sol.read(8);
    return 0;
}