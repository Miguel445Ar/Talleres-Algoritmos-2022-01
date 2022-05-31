#include <iostream>
#include <functional>
#include <string>
#include <ctime>

using std::function;
using std::string;
using std::ostream;
using std::cout;
using std::rand;


template<class T>
class CircularDoubleLinkedList {
    class Node {
    public:
        T value;
        Node* next;
        Node* back;
        Node(T value) : value(value), next(nullptr), back(nullptr) {}
        ~Node(){}
    };
    Node* head; // Inicio de la lista;
    Node* top; // Fin de la lista;
    size_t size;
    function<void(T)> show;
    Node* aux;
public:
    CircularDoubleLinkedList(function<void(T)> show) : show(show) {
        head = top = aux = nullptr;
        size = 0;
    }
    ~CircularDoubleLinkedList(){
        while (size > 0)
            popBack();
    }
    void pushBack(T value) {
        Node* newNode = new Node(value);
        if (size == 0) {
            head = top = newNode;
            head->back = top;
            top->next = head;
            ++size;
            return;
        }
        head->back = newNode;
        top->next = newNode;
        newNode->back = top;
        newNode->next = head;
        top = newNode;
        ++size;
    }
    void popBack() {
        if (size == 0)
            return;
        if (size == 1) {
            top->next = nullptr;
            head->back = nullptr;
            delete top;
            top = head = nullptr;
            --size;
            return;
        }
        top->next = nullptr;
        top = top->back;
        head->back = top;
        top->next->back = nullptr;
        delete top->next;
        top->next = head;
        --size;
    }
    class Iterator {
        Node* it;
        int pos;
    public:
        Iterator(Node* it, int pos) : it(it), pos(pos) {}
        void operator++() {
            (it) ? it = it->next : NULL;
            ++pos;
        }
        void operator--() {
            (it) ? it = it->back : NULL;
            --pos;
        }
        T& operator*() {
            return it->value;
        }
        bool operator!=(Iterator i) {
            return this->pos != i.pos;
        }
        Node* operator+() {
            return it;
        }
    };
    Iterator begin() {
        return Iterator(this->head, 0);
    }
    Iterator end() {
        return Iterator(nullptr, size);
    }
    Iterator rbegin() {
        return Iterator(this->top, size - 1);
    }
    Iterator rend() {
        return Iterator(nullptr, -1);
    }
    void print() {
        aux = head;
        for (size_t i = 0; i < size; ++i) {
            show(aux->value);
            aux = aux->next;
        }
    }
};

class Recruit {
    uint32_t code;
    string name;
public:
    Recruit(uint32_t code, string name): code(code), name(name) {}
    friend ostream& operator<<(ostream& os, Recruit& r) {
        os << r.code << "|" << r.name;
        return os;
    }
};

class RecruitManagement {
    CircularDoubleLinkedList<Recruit*>* cdll;
public:
    RecruitManagement() {
        function<void(Recruit*)> show = [] (Recruit* r) -> void { cout << *r << "-->\n";};
        cdll = new CircularDoubleLinkedList<Recruit*>(show);
        generateMockData();
    }
    ~RecruitManagement() {
        delete cdll;
    }
    // Lo continuaré mañana, luego sale video
private:
    void generateMockData() {
        for(size_t i = 0; i < 1420; ++i)
            cdll->pushBack(new Recruit(i + rand()% (20000), generateRandomName(1 + rand()% 10)));
    }
    string generateRandomName(size_t size){
        string res;
        int first = 'A';
        for(size_t i = 0; i < size; ++i)
            res.push_back((char)(first + rand()% (90 - first + 1)));
        return res;
    }
};

int main() {
    srand(time(0));
    RecruitManagement* r = new RecruitManagement;
    delete r;
    return 0;
}