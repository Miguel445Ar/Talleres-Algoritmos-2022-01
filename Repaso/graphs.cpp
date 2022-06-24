#include <iostream>
#include <list>
#include <string>
#include <map>

class UndirectedGraph {
    class Vertex {
        char id;
    public:
        Vertex(char id): id(id) {}
        char getId() {
            return this->id;
        }
    };
    std::list<Vertex>* adjList;
    std::map<char, int> verticesDict;
    size_t verticesCount;
public:
    UndirectedGraph(size_t verticesCount): verticesCount(verticesCount) {
        adjList = new std::list<Vertex>[verticesCount];
        verticesDict.insert(std::pair<char,int>('A', 0));
        verticesDict.insert(std::pair<char,int>('B', 1));
        verticesDict.insert(std::pair<char,int>('C', 2));
        verticesDict.insert(std::pair<char,int>('D', 3));
        verticesDict.insert(std::pair<char,int>('E', 4));
    }
    void addVertex(char a, char b) {
        Vertex v = Vertex(a);
        Vertex u = Vertex(b);
        adjList[verticesDict.at(v.getId())].push_back(u);
        adjList[verticesDict.at(u.getId())].push_back(v);
    }
    void print() {

    }
};

auto main() -> int {
    UndirectedGraph graph(5);
    graph.addVertex('A','B');
    return 0;
}