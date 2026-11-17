#include<iostream>
#include<mutex>
#include<condition_variable>
#include<thread>

using namespace std;


class zemaphore{
    private:
        int m_val{0};
        mutex m_lock;
        condition_variable m_cv;        
    public:
        void zem_wait(){
            unique_lock<mutex> l(m_lock);
            while(m_val<=0){
                m_cv.wait(l);
            }
            m_val--;
        }
        void zem_post(){
            unique_lock<mutex> l(m_lock);
            m_val++;
            m_cv.notify_one();
        }
};