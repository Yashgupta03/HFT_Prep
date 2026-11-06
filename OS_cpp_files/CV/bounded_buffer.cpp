#include<iostream>
#include<thread>
#include<condition_variable>
#include<mutex>
#include<vector>

using namespace std;


int counts{0}, fill_ptr{0}, use_ptr{0}, MAX{10};
vector<int> buffer(MAX,0);
mutex m1;
condition_variable m_empty, m_full;

void put(int num) {
    buffer[fill_ptr] = num;
    fill_ptr = (fill_ptr+1)%MAX;
    cout<<"putting value: "<<num<<" by "<<this_thread::get_id<<endl;
}

void get() {
    int ans = buffer[use_ptr];
    use_ptr = (use_ptr+1)%MAX;
    cout<<"getting value: "<<ans<<" by "<<this_thread::get_id<<endl;
}

void producer(){
    unique_lock<mutex> l(m1);
    for(int i{};i<2*MAX; i++){
        while(counts>=MAX){
            m_empty.wait(l);
        }
        put(i);
        counts++;
        m_full.notify_one();
    }
}

void consumer(){
    unique_lock<mutex> l(m1);
    for(int i{};i<2*MAX;i++){
        while(counts<=0){
            m_full.wait(l);
        }
        get();
        counts--;
        m_empty.notify_one();
    }
}

int main() {
    vector<jthread> prod,cons;
    for(int i=0;i<3;i++){
        prod.emplace_back(producer);
        cons.emplace_back(consumer);
    }
}