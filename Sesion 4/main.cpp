#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

using std::cout;
using std::function;


template<class T>
class SortAlgorithms {
     T* arr;
    size_t size;
    void (*ptr)(T);
    bool (*compare)(T,T);
public:
    SortAlgorithms(T* arr, size_t size, void (*ptr)(T), bool (*compare)(T,T)): arr(arr), size(size), ptr(ptr), compare(compare){}
    void print() {
        for(size_t i = 0; i < size; ++i) {
            ptr(arr[i]);
        }
        cout << "\n";
    }
    void mergesort(){
        _mergeSort(0, size - 1);
    }
private:
    void _mergeSort(int i, int f){
        if(i == f)
            return;
        size_t middle = (i + f) / 2;
        _mergeSort(i,middle);
        _mergeSort(middle + 1, f);
        merge(i, middle, f);
    }
    void merge(int i, int middle, int f) {
        size_t size = (f - i) + 1;
        T* aux = new T[size];
        size_t l = i, r = middle + 1, k = 0;
        while(l <= middle && r <= f) {
            if(compare(arr[l],arr[r]))
                aux[k++] = arr[l++];
            else 
                aux[k++] = arr[r++];
        }
        while(l <= middle)
            aux[k++] = arr[l++];
        while(r <= f)
            aux[k++] = arr[r++];
        for(size_t j = 0; j < size; ++j)
            this->arr[i + j] = aux[j];
        delete[] aux;
    }
};

auto main() -> int {
    /*std::vector<int> arr = {4,3,6,1,10};
    std::sort(arr.begin(),arr.end(), [](int a, int b) -> bool { return a < b; });
    for(int v: arr) {
        cout << v << "\n";
    }*/
    int arr[] = {1,7,8,9,2,10,3,7,8,9,21,-2,6,-3};
    SortAlgorithms<int>* sorts = new SortAlgorithms<int>(arr,14,[](int value) -> void { cout << value << " ";},
    [](int a, int b) -> bool { return a < b;});
    sorts->print();
    sorts->mergesort();
    sorts->print();
    cout << "\n" << *(arr) << "\n";
    delete sorts;
    return 0;
}