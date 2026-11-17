#include<iostream>
#include<thread>
#include<vector>
#include<semaphore>

using namespace std;

constexpr int MAX{10};
int buffer[MAX];
int put_ptr = 0;
int get_ptr = 0;
int county = 0;
int n = 100;

counting_semaphore<2*MAX> s_full{0},s_empty{MAX};
binary_semaphore s_l{1};

void put(int val){
    buffer[put_ptr] = val;
    put_ptr = (put_ptr+1)%MAX;
    county++;
}

int get(){
    int temp = buffer[get_ptr];
    get_ptr = (get_ptr+1)%MAX;
    county--;
    return temp;
}


void producer(){
    for(int i=0;i<n;i++){
        s_empty.acquire();
        s_l.acquire();
        put(i);
        s_l.release();
        s_full.release();
    }
}

void consumer(){
    for(int i=0;i<n;i++){
        s_full.acquire();
        s_l.acquire();
        cout<<"get: "<<get()<<endl;
        s_l.release();
        s_empty.release();
    }
}

int main(){
    vector<jthread> prod,cons;
    int pc_count{4};
    for(int i=0; i<pc_count; i++) {
        prod.emplace_back(producer);
        cons.emplace_back(consumer);
    }
}