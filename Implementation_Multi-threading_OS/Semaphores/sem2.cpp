#include<bits/stdc++.h>

using namespace std;

counting_semaphore<10>sem_count{4};

void foo(){
    sem_count.acquire();
    cout<<"In foo with id: "<<this_thread::get_id()<<endl;
    this_thread::sleep_for(chrono::seconds(2));
    sem_count.release();
}

int main() {
    vector<jthread> threads;
    int t_count = 8;
    for(int i=0; i<t_count; i++){
        threads.emplace_back(foo);
    }
}