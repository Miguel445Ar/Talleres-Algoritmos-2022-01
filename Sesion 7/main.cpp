#include <iostream>
#include <functional>
#include <stack>
    
    template<class K, class T>
    class BinarySearchTree {
        struct Entity {
            K key;
            T value;
            Entity(K key, T value): key(key), value(value) {}
        };
        class Node {
        public:
            Entity value;
            Node* left;
            Node* right;
            Node(Entity value): value(value), left(nullptr), right(nullptr) {}
        };
        Node* root;
        size_t size;
        std::function<bool(K,K)> compare;
        std::function<bool(K,K)> equals;
        std::function<void(T)> show;
    public:
        BinarySearchTree(std::function<bool(K,K)> compare, std::function<void(T)> show, std::function<bool(K,K)> equals): compare(compare), show(show), equals(equals) {
            root = nullptr;
            size = 0;
        }
        void insert(K key, T value) {
            Node* aux = root;
            if(!root) {
                root = new Node(Entity(key,value));
                ++size;
                return;
            }
            while (true) {
                if(compare(key, aux->value.key)){
                    if(!aux->left){
                        aux->left = new Node(Entity(key,value));
                        ++size;
                        return;
                    }
                    aux = aux->left;
                } else {
                    if(!aux->right){
                        aux->right = new Node(Entity(key,value));
                        ++size;
                        return;
                    }
                    aux = aux->right;
                }
            }
        }
        void display() {
            this->_display(this->root);
        }
        T getByKey(K key) {
            Node* aux = root;
            if(aux->value.key == key)
                return aux->value.value;
            while(true) {
                if(!aux) return T();
                if(equals(key, aux->value.key))
                    return aux->value.value;
                if(compare(key, aux->value.key))
                    aux = aux->left;
                else
                    aux = aux->right;
            }
        }
        void insertToCollection(std::function<void(T)> insertToCollection) {
            _insertToCollection(root, insertToCollection);
        }
        int findByRange(std::function<int(T)> isInRange) {
            return _findByRange(this->root, isInRange);
        }
        void IterativeInOrder(){
            std::stack<Node*>* s = new std::stack<Node*>;
            Node* aux = root;
            int k = 0;
            while(aux != nullptr || s->empty() == false) {
                // Izquierda hasta más no poder
                while(aux != nullptr) {
                    s->push(aux);
                    aux = aux->left;
                }

                // Sacamos un nodo de la pila
                Node* last = s->top();
                this->show(last->value.value);
                s->pop();

                // Vamos al hijo derecho del nodo que acabamos de sacar
                aux = last->right;
            }
        }
        int height(){
            int result = _height(this->root);
            return (result == 0)? 0 : result - 1;
        }
    private:
        int _findByRange(Node* n, std::function<int(T)> isInRange) {
            if(!n) return 0;

            int count = 0;
            switch (isInRange(n->value.value))
            {
            case 1:
                count = 1 + _findByRange(n->right,isInRange);
                break;
            case 2:
                count = 1 + _findByRange(n->left,isInRange);
                break;
            case 3:
                count = 1 + _findByRange(n->left,isInRange) + _findByRange(n->right,isInRange);
                break;
            }
            return count;
        }
        void _display(Node* n) {
            if(!n) return;
            show(n->value.value);
            _display(n->left);
            _display(n->right);
        }
        void _insertToCollection(Node* n, std::function<void(T)> insertToCollection) {
            if(!n) return;
            insertToCollection(n->value.value);
            _insertToCollection(n->left, insertToCollection);
            _insertToCollection(n->right, insertToCollection);
        }
        int _height(Node* n){
            if(!n) return -1;
            if(n->left == nullptr && n->right == nullptr) return 0;
            return 1 + std::max(_height(n->left), _height(n->right));
        }
    };

int main() {
    // [2 - 8]
    auto comp = [](int v) -> int  {
       if(v == 2) return 1;
       if(v == 8) return 2;
       if(v > 2 && v < 8) return 3;
       return 0;
    };
    BinarySearchTree<int,int>* bst = new BinarySearchTree<int,int>(
        [](int k1, int k2) -> bool {
            return k1 < k2;
        },
        [](int v) -> void {
            std::cout << v << " ";
        },
        [](int k1, int k2) -> bool {
            return k1 == k2;
        }
    );
    bst->insert(5,5);
    bst->insert(2,2);
    bst->insert(8,8);
    bst->insert(1,1);
    bst->insert(3,3);
    bst->insert(4,4);
    bst->insert(7,7);
    bst->insert(6,6);
    bst->insert(9,9);
    bst->insert(10,10);
    bst->display();
    std::cout << "\nCount in range is: " << bst->findByRange(comp) << "\n";
    bst->IterativeInOrder();
    std::cout << "\nThe height is: " << bst->height() << "\n";
    return 0;
}