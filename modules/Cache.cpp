#include <iostream>

template <typename T>
struct CacheGame{ 
    int size = 0;
    T *cache = nullptr;
    CacheGame() = default;
    void add(T tablero){
        if(size==0){
            cache = new T(tablero);
        }else{
            T *new_cache = new T[size+1];
            for(int i=0; i<size; i++){
                new_cache[i] = cache[i];
            }
            new_cache[size] = tablero;
            delete[] cache;
            cache = new_cache;
        }
        size++;
    }
};
