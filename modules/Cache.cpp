#include "Tablero.cpp"
#include <iostream>

struct CacheGame{ 
    int size = 0;
    Tablero *cache = nullptr;
    CacheGame() = default;
    void add(Tablero tablero){
        if(size==0){
            cache = new Tablero(tablero);
        }else{
            Tablero *new_cache = new Tablero[size+1];
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
