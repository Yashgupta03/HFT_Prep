#include<iostream>

using namespace std;

//-------move semantics----------


template<typename T>
class my_unique_ptr {
    private:
        T* m_ptr{};

    public:
        my_unique_ptr(): m_ptr{new T}{
            cout<<"constructed\n";
        }
        ~my_unique_ptr(){
            delete m_ptr;
            cout<<"destructed\n";
        }
        my_unique_ptr(my_unique_ptr& ptr) {
            m_ptr = ptr.m_ptr;
            ptr.m_ptr = nullptr;
        }

        my_unique_ptr& operator=(my_unique_ptr& ptr){
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


template<typename T>
class my_unique_ptr<T[]> {
    private:
        T* m_ptr{};

    public:
        my_unique_ptr(T*ptr=nullptr): m_ptr{ptr}{
            cout<<"constructed\n";
        }
        ~my_unique_ptr(){
            delete[] m_ptr;
            cout<<"destructed\n";
        }
        my_unique_ptr(my_unique_ptr& ptr) {
            m_ptr = ptr.m_ptr;
            ptr.m_ptr = nullptr;
        }

        my_unique_ptr& operator=(my_unique_ptr& ptr){
            if(&ptr == this) return &this;
            delete[] m_ptr;
            m_ptr = ptr.m_ptr;
            ptr.m_ptr = nullptr;
            return *this;
        }

        T& operator[](int ind){
            return m_ptr[ind];
        }
        // T* operator ->(){
        //     return m_ptr;
        // }
};


int main(){
    my_unique_ptr<int> ptr1;
    *ptr1 = 10;
    cout<<"earlier value of ptr1 "<<*ptr1<<endl;
    my_unique_ptr<int> ptr2(ptr1);
    cout<<"now ptr2: "<<*ptr2<<endl;
    my_unique_ptr<int>ptr3;
    ptr3 = ptr2;
    cout<<"ptr3 "<<*ptr3<<endl;
}