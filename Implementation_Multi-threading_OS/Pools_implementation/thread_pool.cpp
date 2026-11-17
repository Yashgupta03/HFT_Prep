#include<bits/stdc++.h>

using namespace std;


class Thread_pool{
    private:
        vector<thread> m_threads;
        queue<function<void()>> m_tasks;
        condition_variable cv;
        mutex m;
        bool stop{false};
    public:
        Thread_pool(size_t num_threads = 4): stop{false}{
            if(num_threads==0) num_threads=1;
            m_threads.reserve(num_threads);
            for(size_t i=0; i<num_threads; i++){
                m_threads.emplace_back(&Thread_pool::worker, this);
            }
        }
        Thread_pool(const Thread_pool&) = delete;
        Thread_pool& operator=(const Thread_pool&) = delete;

        ~Thread_pool(){
            unique_lock<mutex> l(m);
            stop=true;
            l.unlock();
            cv.notify_all();
            for(auto& t : m_threads){
                if(t.joinable()) t.join();
            }
        }
        template<typename T>
        void enque_tasks(T&&task){        //enque_tasks(function<void()>&task)
            unique_lock<mutex> l(m);
            m_tasks.push(forward<T>(task));
            l.unlock();
            cv.notify_one();
        }
        void worker(){
            while(true){
                unique_lock<mutex> l(m);
                while(!stop && m_tasks.empty()){     // stop(false) then only depend on tasks.empty
                    cv.wait(l);                    // stop(true) then if tasks is not empty -: do pending tasks
                }                                  // stop(true) and tasks = empty-: now reurn to join

                if(stop && m_tasks.empty()) return;
                
                auto task = move(m_tasks.front());
                m_tasks.pop();
                l.unlock();
                task();
            }
        }
};


void foo(){
    cout<<"foo is running by thread: "<<this_thread::get_id()<<endl;
    this_thread::sleep_for(chrono::seconds(2));
}


int main(){
    Thread_pool my_pool(4);
    int count =8;
    for(int i=0;i<count; i++){
        my_pool.enque_tasks(foo);
    }
}