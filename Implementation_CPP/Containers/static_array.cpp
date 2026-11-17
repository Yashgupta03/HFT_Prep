#include<iostream>

using namespace std;

template<typename T, int N>
class static_array{
    T m_arr[N]{};
    int m_size{N};
    public:
        static_array() = default;
        ~static_array() = default;
        T& at(int ind) {
            if(ind>=N) cout<<"error";
            else return m_arr[ind]; 
        }
};