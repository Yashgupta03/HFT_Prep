#include<iostream>

using namespace std;

template<typename T>
constexpr void type_of(T&& x){
    cout<<"rvalue "<<typeid(T).name()<<endl;
}

template<typename T>
constexpr void type_of(T& x){
    cout<<"lvalue "<<typeid(T).name()<<endl;
}


int main() {
    constexpr int x{1};
    type_of(x);
    type_of(5);
}