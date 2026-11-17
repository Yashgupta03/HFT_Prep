#include<iostream>
#include<thread>

using namespace std;


void foo(int n){
    cout<<"thread: "<<n<<" executing\n";
}


int main() {
    thread t1(foo,1);
    if(t1.joinable()) t1.join();
    thread t2(foo,2);
    
    if(t2.joinable()) t2.join();
    cout<<"master thread\n";
}