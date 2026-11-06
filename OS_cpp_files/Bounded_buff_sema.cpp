#include<iostream>
#include<pthread.h>
#include<semaphore.h>

using namespace std;


const int MAX = 10;
int buffer[MAX];
int put_ptr = 0;
int get_ptr = 0;
int count = 0;
int n = 100;

sem_t lock, empt, full;
int rc = sem_init(&lock,0,1);
int rc1 = sem_init(&empt,0,MAX);
int rc2 = sem_init(&full,0,0);

void put(int val){
    buffer[put_ptr] = val;
    put_ptr = (put_ptr+1)%MAX;
}

int get(){
    int temp = buffer[get_ptr];
    get_ptr = (get_ptr+1)%MAX;
    return temp;
}

void producer(){
    for(int i=0;i<n;i++){
        sem_wait(&empt);
        sem_wait(&lock);
        put(i);
        sem_post(&lock);
        sem_post(&full);
    }
}

void consumer(){
    for(int i=0;i<n;i++){
        sem_wait(&full);
        sem_wait(&lock);
        cout<<"get: "<<get()<<endl;
        sem_post(&lock);
        sem_post(&empt);
    }
}

int main(){

}