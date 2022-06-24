#include <iostream>
#include <functional>
#include <deque>
#include <stack>
#include <ctime>
#include <list>
#include <vector>


using std::cout;
using std::function;
using std::max;
using std::abs;
using std::cin;
using std::deque;
using std::stack;
using std::srand;
using std::time;
using std::list;
using std::vector;

template<class T>
class AVL {
    class Node {
    public:
        list<T> values;
        T v;
        Node* left;
        Node* right;
        int height;
        Node(T value) : left(nullptr), right(nullptr), height(0), v(value) {
            values.push_back(value);
        }
    };
    Node* root;
    size_t size;
    function<void(T)> show;
    function<bool(T, T)> compare;
    function<bool(T,T)> equals;
public:
    AVL(function<bool(T, T)> compare, function<void(T)> show, function<bool(T,T)> equals) : compare(compare), show(show), equals(equals) {
        root = nullptr;
        size = 0;
    }
    void insert(T value) {
        _insert(root, value);
    }
    void print() {
        _print(root);
    }
private:
    void _print(Node* n) {
        if (!n)
            return;
        show(n->v);
        _print(n->left);
        _print(n->right);
    }
    void _insert(Node*& n, T value) {
        if (!n) {
            n = new Node(value);
            ++size;
            return;
        }
        if(equals(value,n->v)){
            n->values.push_back(value);
            ++size;
            return;
        }
        if (compare(value, n->v))
            _insert(n->left, value);
        else
            _insert(n->right, value);
        setHeight(n);
        balanceSubTree(n);
    }
    int height(Node* n) {
        return (n) ? n->height : -1;
    }
    void setHeight(Node* n) {
        n->height = max(height(n->left), height(n->right)) + 1;
    }
    void balanceSubTree(Node*& n) {
        int criteria = height(n->left) - height(n->right);
        Node* leftChild = n->left;
        Node* rightChild = n->right;
        if (criteria > 1) {
            // Left Heavy
            if (!leftChild->left) {
                leftRotation(n->left);
                rightRotation(n);
            }
            else rightRotation(n);

        }
        else if (criteria < -1) {
            // Right Heavy
            if (!rightChild->right) {
                rightRotation(n->right);
                leftRotation(n);
            }
            else leftRotation(n);
        }
        leftChild = rightChild = nullptr;
    }
    void leftRotation(Node*& n) {
        Node* rightChild = n->right;
        n->right = rightChild->left;
        rightChild->left = n;
        setHeight(n);
        setHeight(rightChild);
        n = rightChild;
    }
    void rightRotation(Node*& n) {
        Node* leftChild = n->left;
        n->left = leftChild->right;
        leftChild->right = n;
        setHeight(n);
        setHeight(leftChild);
        n = leftChild;
    }
public:
    void remove(T value){
        vector<Node*>* s = new vector<Node*>;
        Node* parent;
        Node* current;
        parent = nullptr;
        current = root;
        while(current){
            if(equals(value,current->v))
                break;
            s->push_back(current);
            parent = current;
            if(compare(value,current->v))
                current = current->left;
            else
                current = current->right;
        }
        if(!current)
            cout << "\nThe element doesn't exists\n";
        while(current){
            if(current->left == nullptr && current->right == nullptr){
                if(root == current){
                    delete current;
                    root = nullptr;
                    --size;
                    break;
                }
                else if(parent->left == current)
                    parent->left = nullptr;
                else
                    parent->right = nullptr;
                delete current;
                current = nullptr;
                --size;
            } else if(current->left != nullptr && current->right != nullptr){
                s->push_back(current);
                Node* lowestParent = nullptr;
                Node* lowest = getLowestElement(current->right,lowestParent,s);
                current->v = lowest->v;
                current->values = lowest->values;
                if(lowestParent == lowest)
                    parent = current;
                else
                    parent = lowestParent;
                current = lowest;
            } else if (current->left != nullptr) {
                if(root == current)
                    root = root->left;
                else if (parent->left == current)
                    parent->left = current->left;
                else
                    parent->right = current->left;
                delete current;
                current = nullptr;
                --size;
            } else if (current->right != nullptr) {
                if(root == current)
                    root = root->right;
                else if (parent->left == current)
                    parent->left = current->right;
                else
                    parent->right = current->right;
                delete current;
                current = nullptr;
                --size;
            }
        }
        BalanceInRemoving(s);
        s->clear();
        delete s;
    }
private:
    void BalanceInRemoving(vector<Node*>* s){
        if(s->size() == 1){
            Node* c = (*s)[s->size() - 1];
            setHeight(c);
            balanceSubTree(c);
            c = nullptr;
            return;
        }
        int index = s->size() - 1;
        Node* child = nullptr;
        Node* parent = (*s)[index];
        while(true){
            --index;
            if(index < 0)
                break;
            child = parent;
            parent = (*s)[index];
            setHeight(child);
            if(parent->left == child){
                balanceSubTree(child);
                parent->left = child;
            }else{
                balanceSubTree(child);
                parent->right = child;
            }
        }
        child = parent = nullptr;
    }
    Node* getLowestElement(Node* start, Node*& parent, vector<Node*>* s) {
        Node* current = start;
        parent = start;
        while (current->left != nullptr){
            parent = current;
            s->push_back(current);
            current = current->left;
        }
        return current;
    }
    Node* getHighestElement(Node* start){
        Node* current = start;
        if (current->right == nullptr)
            return current;
        while (current->right->right != nullptr)
            current = current->right;
        return current;
    }
private:
    int _height(Node* node) {
        if (!node)
            return -1;
        return max(_height(node->left), _height(node->right)) + 1;
    }
    void _find(Node* node, T value){
        if(!node)
            return;
        if(equals(value,node->v)){
            for(auto elem: node->values){
                show(elem);
            }
           return;
        }
        if(compare(value,node->v))
            _find(node->left,value);
        else _find(node->right,value);
    }
public:
    int height(){
        return _height(root);
    }
    void find(T value){
        _find(root,value);
    }
};

/*
auto main() -> int {
    srand(100);
    auto compare = [](int a, int b) -> bool { return a < b; };
    auto show = [](int a) -> void { cout << a << " "; };
    auto equals = [](int a, int b) -> bool { return a == b;};
    AVL<int>* avl = new AVL<int>(compare, show,equals);
    avl->insert(1 + rand()% + 50);
    avl->insert(1 + rand()% + 50);
    avl->insert(1 + rand()% + 50);
    avl->insert(1 + rand()% + 50);
    avl->insert(1 + rand()% + 50);
    avl->insert(1 + rand()% + 50);
    avl->insert(1 + rand()% + 50);
    avl->insert(1 + rand()% + 50);
    avl->insert(1 + rand()% + 50);
    avl->insert(1 + rand()% + 50);
    avl->insert(1 + rand()% + 50);
    avl->insert(1 + rand()% + 50);
    avl->insert(1 + rand()% + 50);
    avl->insert(1 + rand()% + 50);
    avl->insert(1 + rand()% + 50);
    avl->insert(1 + rand()% + 50);
    avl->insert(1 + rand()% + 50);
    avl->insert(1 + rand()% + 50);
    avl->print();
    avl->remove(30);
    cout << "\n";
    avl->print();
    avl->remove(32);
    cout << "\n";
    avl->print();
    cout << "\n";
    avl->remove(16);
    avl->print();
    //avl->find(6);
    /*
    avl->insert(35);
    avl->insert(30);
    avl->insert(27);
    avl->insert(11);
    avl->insert(16);
    avl->insert(100);
    avl->insert(50);
    avl->insert(91);
    avl->insert(73);
    avl->insert(5);
    avl->print();
    avl->eraseWithoutParentPointer(30);
    cout << "\n";
    avl->print();
    cout << "\nHeight: " << avl->height() << "\n";
    avl->eraseWithoutParentPointer(35);
    cout << "\n";
    avl->print();
    cout << "\nHeight: " << avl->height() << "\n";
    avl->eraseWithoutParentPointer(100);
    cout << "\n";
    avl->print();
    cout << "\nHeight: " << avl->height() << "\n";
    delete avl;
    return 0;
}*/