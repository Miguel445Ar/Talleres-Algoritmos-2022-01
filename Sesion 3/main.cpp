#include <iostream>

using std::cout;


struct Node {
    int value;
    Node* next;
    Node(int value): value(value), next(nullptr) {}
};

int getKthFromTheEnd(Node* head, int k) {
    if(k <= 0) return -100000;
    static bool achived = false;
    static Node* init = head;
    if(head == nullptr)
        return k - 1;
    int res = getKthFromTheEnd(head->next,k);
    if(achived)
        return res;
    if(res == 0){
        achived = true;
        return head->value;
    }
    if(init == head) return -10000;
    
    return res - 1;
}

void print(Node* head){
    Node* aux = head;
    while(aux){
        cout << aux->value << "-->";
        aux = aux->next;
    }
    cout << "nullptr\n";
}


int main() {
    Node* head = new Node(8);
    head->next = new Node(7);
    Node* current = head->next;
    current->next = new Node(3);
    current = current->next;
    current->next = new Node(4);
    current = current->next;
    current->next = new Node(9);
    current = current->next;
    current->next = new Node(5);
    current = current->next;
    current->next = new Node(2);
    current = nullptr;
    print(head);
    cout << "\n The 3rd value from the end is: " << getKthFromTheEnd(head,5);
    return 0;
}