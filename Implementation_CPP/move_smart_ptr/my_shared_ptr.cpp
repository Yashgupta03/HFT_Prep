#include<iostream>

using namespace std;

//-------move semantics----------


template<typename T>
class my_shared_ptr {
    private:
        T* m_ptr{};
        int* count{};

    public:
        my_shared_ptr(): m_ptr{new T},count{new int}{
            *count=1;
            cout<<"constructed\n";
        }
        ~my_shared_ptr(){
            *count = *count -1;
            if(!(*count)){
                delete m_ptr;
                delete count;
            }
            cout<<"destructed\n";
        }
        my_shared_ptr(my_shared_ptr& ptr) {
            count = ptr.count;
            *count = *count +1;
            m_ptr = ptr.m_ptr;
        }

        my_shared_ptr& operator=(my_shared_ptr& ptr){
            if(&ptr == this) return &this;
            *count = *count -1;
            if(!(*count)){
                delete m_ptr;
                delete count;
            }
            count = ptr.count;
            *count = *count +1;
            m_ptr = ptr.m_ptr;
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
    my_shared_ptr<int> ptr1;
    *ptr1 = 10;
    cout<<"earlier value of ptr1 "<<*ptr1<<endl;
    my_shared_ptr<int> ptr2(ptr1);
    cout<<"now ptr2: "<<*ptr2<<endl;
    my_shared_ptr<int>ptr3;
    ptr3 = ptr2;
    cout<<"ptr3 "<<*ptr3<<endl;
}