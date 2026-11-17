#include<iostream>
#include<semaphore>
#include<thread>
#include<vector>

using namespace std;


class rw_lock{
    private:
        int m_readers_count{0};
        binary_semaphore m_lock{1};
        binary_semaphore m_writer_lock{1};
    public:
        void read_lock_acquire(){
            m_lock.acquire();
            m_readers_count++;
            if(m_readers_count==1){
                m_writer_lock.acquire();
            }
            m_lock.release();
        }
        void read_lock_release(){
            m_lock.acquire();
            m_readers_count--;
            if(m_readers_count==0){
                m_writer_lock.release();
            }
            m_lock.release();
        }
        void write_lock_acquire(){
            m_writer_lock.acquire();
        }
        void write_lock_release(){
            m_writer_lock.release();
        }
};



int main(){
    vector<jthread> readers, writers;
    
}