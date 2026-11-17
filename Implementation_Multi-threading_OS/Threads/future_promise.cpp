#include<iostream>
#include<thread>
#include<future>


using namespace std;

void foo(promise<int>&&res, int x, int y){
    res.set_value(x+y);
}

int main(){
    promise<int> sum_promise;
    future<int> future = sum_promise.get_future();
    jthread jt(foo, move(sum_promise), 2, 3);
    cout<<future.get()<<endl;
}