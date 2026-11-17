#include<iostream>
#include<vector>
#include<thread>
#include<condition_variable>
#include<mutex>

using namespace std;


template<typename T, size_t N>
class MPMC_queue{
    private:
        mutex m;
        condition_variable m_empty, m_full;
        vector<T> m_buffer;
        int fill_ptr{};
        int use_ptr{};
        int count{};
    public:
        void put(int val=0){
            unique_lock<mutex> l(m);
            while(count>=N) {
                m_empty.wait(l);
            }
            m_buffer[fill_ptr] = val;
            fill_ptr = (fill_ptr+1)%N;
            count++;
            m_full.notify_one();
        }
        T get(){
            unique_lock<mutex> l(m);
            while(count<=0){
                m_full.wait(l);
            }
            T val = m_buffer[use_ptr];
            use_ptr = (use_ptr+1)%N;
            count--;
            m_empty.notify_one();
            return val;
        }
};


int main() {
    MPMC_queue<int, 10> q;
    
}