#ifndef __DATA_STRUCTURES_HPP__
#define __DATA_STRUCTURES_HPP__

#include <iostream>
#include <functional>

namespace DataStructures {
    template<class T>
    class DoubleLinkedList{
        class Node {
        public:
            T value;
            Node* next;
            Node* back;
            Node(T value, Node* next = nullptr, Node* back = nullptr): value(value), next(next), back(back){}
        };
        Node* head; // Inicia de la lista;
        Node* top; // Fin de la lista;
        size_t size;
        std::function<void(T)> show;
        std::function<bool(T,T)> compare;
        Node* aux;
        public:
        DoubleLinkedList(std::function<void(T)> show, std::function<bool(T,T)> compare): show(show), compare(compare) {
        head = top = aux = nullptr;
        size = 0;
    }
        ~DoubleLinkedList(){
        while(size > 0)
            popBack();
    }
        void pushFront(T value){
        Node* newNode = new Node(value);
        if(size == 0){
            head = top = newNode;
            ++size;
            return;
        }
        newNode->next = head;
        head->back = newNode;
        head = newNode;
        ++size;
    }
        void pushBack(T value){
        Node* newNode = new Node(value);
        if(size == 0){
            head = top = newNode;
            ++size;
            return;
        }
        top->next = newNode;
        newNode->back = top;
        top = newNode;
        ++size;
    }
        void popBack(){
        if(size == 0)
            return;
        if(size == 1){
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
        void popFront(){
        if(size == 0)
            return;
        if(size == 1){
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
        void insertInPos(T value, size_t pos){
        if(pos <= 0){
            pushFront(value);
            return;
        }
        if (pos >= size){
            pushBack(value);
            return;
        }
        aux = head;
        for(size_t i = 0; i<pos-1;++i)
            aux = aux->next;
        Node* newNode = new Node(value);
        newNode->back = aux;
        newNode->next = aux->next;
        aux->next = newNode;
        newNode->next->back = newNode;
        ++size;
    }
        void eraseInPos(int pos){
        if (pos == 0){
            popFront();
            return;
        }
        if (pos == size - 1){
            popBack();
            return;
        }
        if(pos >= size || pos < 0)
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
        void print(){
            using std::cout;
            aux = head;
            while(aux != nullptr){
                this->show(aux->value);
                aux = aux->next;
            }
            cout << "nullptr\n";
        }
        void BubleSort(){
            Node* aux1 = head;
            if(!aux1) return;
            Node* aux2 = head->next;
            while(aux1 != nullptr && aux2 != nullptr){
                if(compare(aux1->value,aux2->value)){
                    aux1 = aux1->next;
                    aux2 = aux2->next;
                    continue;
                }
                this->swap(aux1,aux2);
                if(!aux1->back){
                    aux1 = aux1->next;
                    aux2 = aux2->next;
                    continue;
                }
                aux1 = aux1->back;
                aux2 = aux2->back;
            }
        }
        void BubleSortConUnCambioLeve(){
            Node* aux1 = head;
            if(!aux1) return;
            Node* aux2 = head->next;
            while(aux1 != nullptr && aux2 != nullptr){
                if(compare(aux1->value,aux2->value)){
                    aux1 = aux1->next;
                    aux2 = aux2->next;
                    continue;
                }
                this->swap(aux1,aux2);
                if(!aux1->back)
                    continue;
                aux1 = aux1->back;
                aux2 = aux2->back;
            }
        }
    private:
        void swap(Node* v1, Node* v2){
            T c = v1->value;
            v1->value = v2->value;
            v2->value = c;
        }
    };

    template<class T>
    class Stack{
        class Node {
        public:
            T value;
            Node* next;
            Node* back;
            Node(T value, Node* next = nullptr, Node* back = nullptr): value(value), next(next), back(back){}
        };
        Node* head; // Inicia de la lista;
        Node* top; // Fin de la lista;
        size_t size;
        Node* aux;
    public:
        Stack(){
            head = top = aux = nullptr;
            size = 0;
        }
        ~Stack(){
            while(size > 0)
                pop();
        }
        void push(T value){
            Node* newNode = new Node(value);
            if(size == 0){
                head = top = newNode;
                ++size;
                return;
            }
            top->next = newNode;
            newNode->back = top;
            top = newNode;
            ++size;
        }
        void pop(){
            if(size == 0)
                throw "There's no elements to remove";
            if(size == 1){
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
        T Top(){
            if(size == 0)
                throw "There's no elements to return";
            return this->top->value;
        }
        size_t Size(){
            return this->size;
        }
    };
    template<class T>
    class StackMin {
        Stack<T>* values;
        Stack<T>* record;
        std::function<bool(T,T)> compare;
    public:
        StackMin(std::function<bool(T,T)> compare): compare(compare) {
            values = new Stack<T>;
            record = new Stack<T>;
        }
        ~StackMin(){
            delete values;
            delete record;
        }
        void push(T value){
            this->values->push(value);
            if(this->record->Size() == 0){
                this->record->push(value);
                return;
            }
            if (compare(value,this->record->Top()))
                this->record->push(value);
            else 
                this->record->push(this->record->Top());
        }
        void pop(){
            this->values->pop();
            this->record->pop();
        }
        T top(){
            return this->values->Top();
        }
        T getMin(){
            return this->record->Top();
        }
    };

    template<class T>
    class Queue {
        class Node {
        public:
            T value;
            Node* next;
            Node* back;
            Node(T value, Node* next = nullptr, Node* back = nullptr): value(value), next(next), back(back){}
        };
        Node* head; // Inicia de la lista;
        Node* top; // Fin de la lista;
        size_t size;
        std::function<void(T)> show;
        Node* aux;
        public:
        Queue(std::function<void(T)> show): show(show) {
            head = top = aux = nullptr;
            size = 0;
        }
        ~Queue(){
            while(size > 0)
                pop();
        }
        void push(T value){
            Node* newNode = new Node(value);
            if(size == 0){
                head = top = newNode;
                ++size;
                return;
            }
            top->next = newNode;
            newNode->back = top;
            top = newNode;
            ++size;
        }
        void pop(){
            if(size == 0)
                return;
            if(size == 1){
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

    };
}


#endif