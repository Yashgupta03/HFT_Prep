#include<iostream>

using namespace std;

template<typename T>
class my_vector{
    T* m_vec{nullptr};
    size_t m_size{};
    size_t m_capacity{};
    
    public:
        my_vector(int s=0, int val=0): m_size{s}, m_capacity{s}{
            if(s){
                m_vec = new T[s];
                for(int i=0;i<s;i++) m_vec[i] = 0;
            }
        }
        my_vector(const my_vector& v){
            T* m_vec = new T[v.m_capacity];
            for(int i=0;i<v.m_size;i++) m_vec[i] = v[i];
        }
        my_vector(const my_vector&& v){
            m_vec = v.m_vec;
            m_capacity = v.m_capacity;
            m_size = v.m_size;
            v.m_capacity=0;
            v.m_size =0;
            v.m_vec = nullptr;
        }
        ~my_vector(){
            delete[] m_vec;
            m_vec = nullptr;
        }
        void resize(int n_cap){
            if(n_cap == m_capacity) return;
            T* data = new T[n_cap];
            for(int i=0;i<m_size;i++){
                data[i] = m_vec[i];
            }
            m_capacity = n_cap;
            delete[] m_vec;
            m_vec = data;
        }
        void pop_back(){
            if(m_size) m_size--;
        }
        void push_back(int num){
            if(m_size==m_capacity){
                int new_cap = !m_capacity? 1 : 2*m_capacity;
                resize(new_cap);
                vec[m_size] = num;
                m_size++;
            }
            else{
                vec[m_size]=num;
                m_size++;
            }
        }
        int size(){ return m_size;}
        int capacity(){ return m_capacity;}
        
        T& operator[](int ind) {
            if(ind>=m_size){
                cout<<"error"
            }
            return m_vec[ind];
        }

};

