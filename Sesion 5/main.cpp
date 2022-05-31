#include <iostream>
#include <functional>
#include <string>
#include <cmath>



template<class T>
class DoubleLinkedList {
    class Node {
        public:
        T value;
        Node* next;
        Node* back;
        Node(T value, Node* next = nullptr, Node* back = nullptr) : value(value), next(next), back(back) {}
    };
    Node* head; // Inicia de la lista;
    Node* top; // Fin de la lista;
    size_t size;
    std::function<void(T)> show;
    Node* aux;
public:
    DoubleLinkedList(std::function<void(T)> show) : show(show) {
        head = top = aux = nullptr;
        size = 0;
    }
    ~DoubleLinkedList() {
        while (size > 0)
            popBack();
    }
    void pushFront(T value) {
        Node* newNode = new Node(value);
        if (size == 0) {
            head = top = newNode;
            ++size;
            return;
        }
        newNode->next = head;
        head->back = newNode;
        head = newNode;
        ++size;
    }
    void pushBack(T value) {
        Node* newNode = new Node(value);
        if (size == 0) {
            head = top = newNode;
            ++size;
            return;
        }
        top->next = newNode;
        newNode->back = top;
        top = newNode;
        ++size;
    }
    void popBack() {
        if (size == 0)
            return;
        if (size == 1) {
            delete top;
            top = head = nullptr;
            --size;
            return;
        }
        top = top->back;
        top->next->back = nullptr;
        delete top->next;
        top->next = nullptr;
        --size;
    }
    void popFront() {
        if (size == 0)
            return;
        if (size == 1) {
            delete top;
            top = head = nullptr;
            --size;
            return;
        }
        // Nos movemos al siguiente del inicio
        head = head->next;
        // Desconectamos el nodo a eliminar
        head->back->next = nullptr;
        // Eliminamos el nodo
        delete head->back;
        // Seteamos a nullptr el puntero back del head
        head->back = nullptr;
        --size;
    }
    void insertInPos(T value, size_t pos) {
        if (pos <= 0) {
            pushFront(value);
            return;
        }
        if (pos >= size) {
            pushBack(value);
            return;
        }
        aux = head;
        for (size_t i = 0; i < pos - 1; ++i)
            aux = aux->next;
        Node* newNode = new Node(value);
        newNode->back = aux;
        newNode->next = aux->next;
        aux->next = newNode;
        newNode->next->back = newNode;
        ++size;
    }
    void eraseInPos(int pos) {
        if (pos == 0) {
            popFront();
            return;
        }
        if (pos == size - 1) {
            popBack();
            return;
        }
        if (pos >= size || pos < 0)
            throw "This is not possible";
        aux = head;
        for (size_t i = 0; i < pos - 1; ++i)
            aux = aux->next;
        Node* nodeToErase = aux->next;
        // Preparamos a la lista
        aux->next = nodeToErase->next;
        nodeToErase->next->back = aux;
        // Desconectamos el nodo
        nodeToErase->next = nodeToErase->back = nullptr;
        delete nodeToErase;
        --size;
    }
    void print() {
        aux = head;
        while (aux != nullptr) {
            this->show(aux->value);
            aux = aux->next;
        }
        std::cout << "nullptr\n";
    }
    class Iterator {
        Node* it;
        int pos;
    public:
        Iterator(Node* it, int pos): it(it), pos(pos) { }
        void operator++(){
            if(!it) throw "Node out range";
            it = it->next;
            ++pos;
        }
        void operator--(){
            if(!it) throw "Node out range";
            it = it->back;
            --pos;
        }
        T operator*() {
            return it->value;
        }
        bool operator!=(Iterator i){
            return this->pos != i.pos;
        }
        Node* operator+(){
            return this->it;
        }
        void setNode(Node* n) {
            return this->it = n;
        }
    };
    Iterator begin(){
        return Iterator(this->head,0);
    }
    Iterator end(){
        return Iterator(nullptr,size);
    }
    Iterator rbegin(){
        return Iterator(this->top,size - 1);
    }
    Iterator rend(){
        return Iterator(nullptr,-1);
    }
    int eraseByIterator(Iterator& it) {
        if(it.pos < 0 || it.pos >= size)
            throw "Iterator out of range";
        if(it.pos == size - 1){
            Node* aux = (+it);
            aux = aux->back;
            popBack();
            if(!aux) return 2;
            it.setNode(aux);
            return 1;
        }
        if(it.pos == 0){
            Node* aux = (+it);
            aux = aux->next;
            popFront();
            if(!aux) return 2;
            it.setNode(aux);
            return 0;
        }
        Node* aux = +it;
        aux = aux->back;
        aux->next = aux->next->next;
        delete (+it);
        it.setNode(aux);
        return 1;
    }
};

template<class T>
class HashTable {
    struct Entity {
        std::string key;
        T value;
        Entity(std::string key, T value): key(key), value(value) {}
    };
    DoubleLinkedList<Entity>** ht;
    size_t bucketSize;
    std::function<void(Entity)> show;
public:
    HashTable(std::function<void(T)> show, size_t capacity): bucketSize(capacity){
        ht = new DoubleLinkedList<Entity>*[capacity];
        for(size_t i = 0; i < bucketSize; ++i)
            ht[i] = nullptr;
        this->show = [&show](Entity e) -> void {
            show(e.value);
        };
    }

    void insert(std::string key, T value) {
        size_t index = HashFunction(key);
        if(!ht[index])
            ht[index] = new DoubleLinkedList<Entity>(this->show);
        ht[index]->pushBack(Entity(key,value));
    }
    void print(){
        for(size_t i = 0; i < bucketSize; ++i){
            std::cout << "\nIndex " << i << "\n";
            if(ht[i])
                ht[i]->print();
        }
    }
private:
    size_t HashFunction(std::string key) {
        size_t p = 0;
        for(size_t i = 0; i < key.length(); ++i) {
            int asciiValue = key[i];
            p += pow(asciiValue,i + 1);
        }
        return p % bucketSize;
    }
    // En hash tables sin listas
    size_t cuadraticProbing(size_t index) {
        size_t p = 1;
        size_t currentIndex = index;
        while(ht[index] != nullptr){
            currentIndex = index;
            currentIndex += pow(p,2);
            if(currentIndex >= bucketSize)
                currentIndex %= bucketSize;
        }
        return currentIndex;
    }
};

int main() {
    HashTable<int> ht([](int v) -> void {std::cout << v << "-->";},30);
    ht.insert("Hola",5);
    ht.print();
    return 0;
}