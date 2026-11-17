#include<iostream>
#include<semaphore>
#include<thread>

using namespace std;

binary_semaphore sem1{0},sem2{0};

void foo(){
    sem1.acquire();
    cout<<"in foo -: "<<"thread id: "<<this_thread::get_id()<<endl;
    sem2.release();
}

int main() {
    cout<<"starting..."<<endl;
    jthread jt(foo);
    cout<<"executing main....."<<endl;
    sem1.release();
    sem2.acquire();
    cout<<"execute last....."<<endl;
}