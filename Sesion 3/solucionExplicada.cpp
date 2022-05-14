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
public:
    class Node {
    public:
        T value; // Valor del nodo
        Node* next; //  Puntero al siguiente nodo
        Node(T value, Node* next = nullptr) : value(value), next(next) {}
    };
private:
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
    Node* insertInRange(function<void(T)> insert, int i, int f, Node* n) {
        size_t init = i;
        Node* aux = (!n) ? this->inicio : n;
        for (init; init <= f; ++init) {
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
    function<void(Televisor)> show;
public:
    Solution() {
        this->show = [](Televisor value) -> void {
            std::cout << value.mostrar() << "-->";
        };
        this->items = new List<Televisor>(this->show);
    }
    ~Solution() {
        delete items;
    }
    void read() {
        string line = "";
        ifstream arch("input.txt");
        while (getline(arch, line, ',')) {
            stringstream s(line);
            string aux;
            string marca, color, tecnologia;
            double pulgadas;
            size_t precio;
            getline(s, aux, '|');
            marca = aux;
            getline(s, aux, '|');
            color = aux;
            getline(s, aux, '|');
            tecnologia = aux;
            getline(s, aux, '|');
            pulgadas = stod(aux);
            getline(s, aux, '|');
            precio = stoi(aux);
            Televisor t(marca, color, tecnologia, pulgadas, precio);
            items->pushBack(t);
        }
        arch.close();
        items->print();
        cout << "\nSize: " << items->Size() << "\n";
    }
    void partitionList(int k){

        function<void(List<Televisor>*)> showResult = [](List<Televisor>* value) -> void {
            cout << "\n";
            value->print();
            cout << "\nSub List size: " << value->Size() << "\n";
        };
        List<List<Televisor>*>* result = new List<List<Televisor>*>(showResult);


        size_t size = this->items->Size();
        int res = size % k;
        size_t partitionSize = size / k;
        if(size == res) {
            List<Televisor>::Node* ptr = nullptr;
            for(size_t i = 0; i < size; ++i){
                List<Televisor>* aux = new List<Televisor>(this->show);
                ptr = this->items->insertInRange([&aux](Televisor t) -> void {
                    aux->pushBack(t);
                }, i, i, ptr);
                result->pushBack(aux);
            }
            size_t dif = k - size;
            for(size_t i = 0; i < dif; ++i)
                result->pushBack(new List<Televisor>(this->show));
            result->print();
            delete result;
            return;
        }
        List<Televisor>::Node* ptr = nullptr;
        size_t pos = 0;
        for(size_t i = 0; i < k; ++i){
            List<Televisor>* aux = new List<Televisor>(this->show);
            size_t end = pos + (partitionSize - 1) + (res > 0)?1:0;
            ptr = this->items->insertInRange([&aux](Televisor t) -> void {
                aux->pushBack(t);
            }, pos, end, ptr);
            result->pushBack(aux);
            --res;
        }
        result->print();
        delete result;
    }
};


int main() {
    Solution* sol = new Solution;
    sol->read();
    sol->partitionList(8);
    delete sol;
    return 0;
}
