#include <iostream>

template <typename T>
struct CacheGame{ 
    CacheGame() = default;
    CacheGame( T tablero ): game( tablero ){}
    T game;
};

template <typename T>
CacheGame<T> *ResumeGame(T tablero, int n, CacheGame<T> resume = nullptr){

    if(resume==nullptr){
        return CacheGame<T>(tablero);
    }
    
    CacheGame<T> new_resume = new CacheGame[n+1];

    for(int i = 0; i < n; i++){
        new_resume.game[i] = resume.game[i];
    }

    new_resume[n] = tablero;
    return new_resume;

}
