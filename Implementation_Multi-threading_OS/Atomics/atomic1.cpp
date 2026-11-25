#include<iostream>
#include<atomic>
#include<thread>
#include<chrono>

using namespace std;

atomic<int>g_sum{0};

void foo1(){
    for(int i=0;i<10;i++) {
        g_sum.fetch_add(i);
    }
    cout<<this_thread::get_id<<" sum is: "<<g_sum.load()<<endl;
}

void foo2(){
    for(int i=0;i<10;i++) {
        g_sum.fetch_add(i);
    }
    cout<<this_thread::get_id<<" sum is: "<<g_sum.load()<<endl;
}

int main() {
    jthread t1(foo1);
    // this_thread::sleep_for(chrono::seconds(2));
    jthread t2(foo2);
    
}