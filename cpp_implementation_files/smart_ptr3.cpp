#include<iostream>

using namespace std;


template<typename T>
class Autoptr3 {
    private:
        T* m_ptr{};

    public:
        Autoptr3(): m_ptr{new T}{
            cout<<"constructed\n";
        }
        ~Autoptr3(){
            delete m_ptr;
            cout<<"destructed\n";
        }
        Autoptr3(const Autoptr3& ptr){
            m_ptr = new T;
            *m_ptr = *(ptr.m_ptr);
        }

        Autoptr3& operator =(const Autoptr3& ptr){
            if(&ptr == this) return *this;
            delete m_ptr;
            m_ptr = new T;
            *m_ptr = *(ptr.m_ptr);
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
    Autoptr3<int> ptr1;
    *ptr1 = 10;
    cout<<"earlier value of ptr1 "<<*ptr1<<endl;
    Autoptr3<int> ptr2(ptr1);
    cout<<"now ptr2: "<<*ptr2<<endl;
    Autoptr3<int>ptr3;
    ptr3 = ptr2;
    cout<<"ptr3 "<<*ptr3<<endl;
}