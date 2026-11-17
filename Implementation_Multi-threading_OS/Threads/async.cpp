#include<iostream>
#include<thread>
#include<future>


using namespace std;


int foo(int x, int y){
    return x+y;
}

int main() {
    future<int> res = async(launch::async, foo, 2,3);
    future<int> res_deferred = async(launch::deferred, foo, 3,4);

    cout<<res.get()<<" "<<res_deferred.get()<<endl;
}