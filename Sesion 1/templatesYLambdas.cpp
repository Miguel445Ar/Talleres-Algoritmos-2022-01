#include <iostream>
#include <functional>
#include <vector>
#include <string>

#define print(value) std::cout << value << "\n";


int suma(int a, int b) {
    int res = a + b;
    return res;
}

template<typename T>
void doSomething(T value, std::function<void(T)> show){
    show(value);
}

class Persona {
    std::string name;
public:
    Persona(std::string name): name(name) {}
    std::string getName(){
        return this->name;
    }
};



int main(){
    int v = 6;
    int a =6;
    std::vector<int> arr = {4,5,6,8};
    int (*punterito)(int,int) = [](int a, int b) -> int { return a + b;};
    std::function<int(int,int)> funObj = [&v](int a, int b) -> int { return a + b;};
    auto funObj2 = [&v,a,&arr](int a, int b) -> int { 
        arr.clear();
        return a + b;
    };
    //unterito = suma;
    std::cout << punterito(5,6) << "\n";
    doSomething<Persona>(Persona("Piero"),[](Persona a) -> void { std::cout << a.getName() << "\n";});
    return 0;
}
