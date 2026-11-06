#include<iostream>
#include<thread>
#include<condition_variable>

using namespace std;

mutex m1;
condition_variable cv1, cv2;
int county{}; 


void foo1(int num){
    unique_lock<mutex> l(m1);
    cout<<"thread id: "<<this_thread::get_id()<<endl;
    for(int i{};i<num;i++) {
        while(county>=1){
            cv1.wait(l);
        }
        cout<<"foo1 "<<" iteration: "<<i<<endl;
        county++;
        cv2.notify_one();
    }
}

void foo2(int num){
    unique_lock<mutex> l(m1);
    cout<<"thread id: "<<this_thread::get_id()<<endl;
    for(int i{};i<num;i++) {
        while(county<=0){
            cv2.wait(l);
        }
        cout<<"foo2 "<<" iteration: "<<i<<endl;
        county--;
        cv1.notify_one();
    }
}


int main() {
    jthread jt1(foo1, 4);
    jthread(foo2,4);
}