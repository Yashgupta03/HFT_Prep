#include<iostream>
#include<mutex>
#include<thread>

using namespace std;


int counter{0};
mutex m1;

// void foo(int num){
//     m1.lock();
//     cout<<"inside: "<<num<<endl;
//     counter++;
//     cout<<"counter: "<<counter<<endl;
//     cout<<"outside: "<<num<<endl;
//     m1.unlock();
// }


// void foo(int num){
//     lock_guard<mutex> l(m1);
//     cout<<"inside: "<<num<<endl;
//     counter++;
//     cout<<"counter: "<<counter<<endl;
//     cout<<"outside: "<<num<<endl;
// }

// void foo(int num){
//     unique_lock<mutex> l(m1);
//     cout<<"inside: "<<num<<endl;
//     counter++;
//     cout<<"counter: "<<counter<<endl;
//     cout<<"outside: "<<num<<endl;
// }


void foo(int num){
    unique_lock<mutex> l(m1, defer_lock);
    l.lock();
    cout<<"inside: "<<num<<endl;
    counter++;
    cout<<"counter: "<<counter<<endl;
    cout<<"outside: "<<num<<endl;
    l.unlock();
}


int main() {
    jthread jt1(foo, 1);
    jthread jt2(foo, 2);
    cout<<"master\n";
}