#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define SIZE 25

class Virus {
    std::string name;
    std::string type;
public:
    Virus(std::string name, std::string type): name(name), type(type) {}
    std::string getName() {
        return this->name;
    }
    std::string getType() {
        return this->type;
    }
};

class Trie {
    class Node {
    public:
        char value;
        bool endOfWord;
        Node** children;
        size_t childCount;
        Virus* virus;
        Node(char value, bool endOfWord = false, Virus* virus = nullptr): value(value), endOfWord(endOfWord), childCount(0), virus(virus) {
            children = new Node*[SIZE];
            for(size_t i = 0; i < SIZE; ++i)
                children[i] = nullptr;
        }
        ~Node() {
            if(children) {
                for(size_t i = 0; i < SIZE; ++i){
                    if(children[i])
                        delete children[i];
                }
                delete[] children;
                children = nullptr;
            }
        }
        void increaseChildCount() {
            ++childCount;
        }
        Virus* getVirus() {
            return this->virus;
        }
    };
    Node* root;
    size_t size;
public:
    Trie() {
        root = new Node('.');
        size = 0;
    }
    void insert(const std::string word, Virus* virus) {
        Node* aux = this->root;
        const int begin = static_cast<int>('A');
        for(size_t i = 0; i < word.size(); ++i) {
            int pos = static_cast<int>(word[i]) - begin;
            if(!aux->children[pos]) {
                aux->children[pos] = new Node(word[i], (i == word.size() - 1)? true: false, (i == word.size() - 1)? virus: nullptr);
                aux->increaseChildCount();
            } else if (i == word.size() - 1) {
                aux->endOfWord = true;
            }
            aux = aux->children[pos];
        }
        aux = nullptr;
        ++size;
    }
    size_t Size() {
        return this->size;
    }
};

class Solution {
    Trie* trie;
    std::ifstream input;
public:
    Solution(std::string filePath) {
        trie = new Trie;
        this->_readInput(filePath);
    }
    ~Solution() {
        
    }
private:
    void _readInput(std::string filePath) {
        input.open(filePath);
        if(!input.is_open())
            return;
        std::string line;
        while( std::getline(input,line,'\n') ) {
            std::stringstream s(line);
            std::string aux, name, type, word;
            getline(s,aux,' ');
            word = aux;
            getline(s,aux,' ');
            name = aux;
            getline(s,aux,'\n');
            type = aux;
            Virus* virus = new Virus(name, type);
            this->trie->insert(word,virus);
        }
        input.close();
        std::cout << this->trie->Size() << "\n";
    }
};

auto main() -> int {
    Solution* sol = new Solution("input.txt");
    delete sol;
}