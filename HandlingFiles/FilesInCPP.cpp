#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sstream>

using std::cout;
using std::cin;
using std::ifstream;
using std::ofstream;
using std::string;
using std::getline;
using std::ios;
using std::stringstream;
using std::stoi;

// Binary Files

struct Foo {
    int x;
    int y;
    const char* msg; // con string hay problemas en binario
    string msg2; // con const char* hay problemas en texto plano
    Foo(int x = 0, int y = 0, const char* msg = ""): x(x), y(y), msg(msg) {}
};

void readFromBinary(){
    Foo arr[3];
    ifstream arch("CPPBin.bin", ios::binary);
    arch.read((char*)arr,sizeof(arr));
    // Metodo explicito
    /*
    std::streampos start = arch.tellg();
    arch.seekg(0,std::ios::end);
    std::streampos end = arch.tellg();
    aux.seekg(0,std::ios::beg);
    arch.read((char*)&arr,end - start); // arr o &arr
    std::cout << end - start << "\n";
    arch.close();
    */
    for(size_t i = 0; i < 3; ++i){
        cout << "\nThe data read is "<< arr[i].x << ", " << arr[i].y << ", " << arr[i].msg;
    }
    arch.close();
}

void writeToBinary(){
    Foo arr[] = { Foo(1,2,"Hi"), Foo(3,4,"My_name_is"), Foo(5,6,"Miguel") };
    ofstream arch("CPPBin.bin", ios::binary);
    arch.write((char*)&arr,sizeof(arr));
    arch.close();
}

// Plain Text Files

void readFromTxt() {
    Foo arr[3];
    string line;
    ifstream arch("CPPPlainTextFile.txt");
    /*
    while(getline(arch,line,',')){
        cout << line << "\n";
    }*/
    size_t i = 0;
    while(arch >> line) {
        stringstream s(line);
        string aux;
        int x;
        int y;
        getline(s,aux,',');
        x = stoi(aux);
        getline(s,aux,',');
        y = stoi(aux);
        getline(s,aux,'\n');
        arr[i] = Foo(x,y);
        arr[i].msg2 = aux;
        ++i;
    }
    for(size_t i = 0; i < 3; ++i){
        cout << "\nThe data read in Txt is "<< arr[i].x << ", " << arr[i].y << ", " << arr[i].msg2;
    }
}

void writeToTxt(){
    Foo arr[] = { Foo(1,2,"Hi"), Foo(3,4,"My_name_is"), Foo(5,6,"Miguel") };
    ofstream arch("CPPPlainTextFile.txt");
    for(size_t i = 0; i < 3; ++i) {
        arch << arr[i].x << "," << arr[i].y << "," << arr[i].msg << "\n";
    }
    arch.close();
}

int main(){
    writeToBinary();
    readFromBinary();
    writeToTxt();
    cout << "\n";
    readFromTxt();
    return 0;
}