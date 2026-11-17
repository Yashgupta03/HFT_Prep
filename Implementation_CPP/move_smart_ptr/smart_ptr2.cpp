#include<iostream>

using namespace std;

//-------move semantics----------


template<typename T>
class Autoptr2 {
    private:
        T* m_ptr{};

    public:
        Autoptr2(): m_ptr{new T}{
            cout<<"constructed\n";
        }
        ~Autoptr2(){
            delete m_ptr;
            cout<<"destructed\n";
        }
        Autoptr2(Autoptr2& ptr) {
            m_ptr = ptr.m_ptr;
            ptr.m_ptr = nullptr;
        }

        Autoptr2& operator=(Autoptr2& ptr){
            if(&ptr == this) return &this;
            delete m_ptr;
            m_ptr = ptr.m_ptr;
            ptr.m_ptr = nullptr;
            return *this;
        }

        T& operator *(){
            return *m_ptr;
        }
        T* operator ->(){
            return m_ptr;
        }
};


int main(){
    Autoptr2<int> ptr1;
    *ptr1 = 10;
    cout<<"earlier value of ptr1 "<<*ptr1<<endl;
    Autoptr2<int> ptr2(ptr1);
    cout<<"now ptr2: "<<*ptr2<<endl;
    Autoptr2<int>ptr3;
    ptr3 = ptr2;
    cout<<"ptr3 "<<*ptr3<<endl;
}