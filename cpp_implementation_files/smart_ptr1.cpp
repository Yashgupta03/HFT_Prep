#include<iostream>


using namespace std;

//--------delete copy and assignment constructor-------

template<typename T>
class Autoptr1 {
    private:
        T* m_ptr{};
    public: 
        Autoptr1(): m_ptr{new T}{
            cout<<"ptr created\n";
        }

        ~Autoptr1(){
            delete m_ptr;
            cout<<"ptr deleted\n";
        }

        Autoptr1(const Autoptr1 &ptr) = delete;

        Autoptr1& operator =(Autoptr1& ptr) = delete;

        T& operator *()const{
            return *m_ptr;
        }
        T* operator ->()const{
            return m_ptr;
        }
};


int main(){
    Autoptr1<int> ptr;
    *ptr = 11;
    cout<<*ptr<<endl;
}