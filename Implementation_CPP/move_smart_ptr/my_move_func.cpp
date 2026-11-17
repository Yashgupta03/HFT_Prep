#include<iostream>
#include<type_traits>

using namespace std;


template<typename T>
remove_reference<T>&& my_move(T&& arg){
    return static_cast<remove_reference<T>&&> arg;
}