#include<iostream>

using namespace std;

template<typename T>
class Base{
    public:
        void print(){
            if(static_cast<T*>(this) == this){
                cout<<"is base\n";
            }
            else {
                (static_cast<T*>(this)->print());
            }
        }
};

class Derived : public Base<Derived> {
    public:
        void print(){
            cout<<"is Derived\n";s
        }
};




int main(){
    Derived d1{};
    d1.print();
    Base<Base> b{};
    // Base* b{&d1};
}