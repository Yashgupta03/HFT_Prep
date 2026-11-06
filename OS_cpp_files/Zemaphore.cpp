#include<iostream>
#include<pthread.h>

using namespace std;


class zemaphore{
    private:
        int val{};
        pthread_mutex_t lock;
        pthread_cond_t cond;
    public:
        zemaphore(int value=1) : val{value}{
            int rc = pthread_mutex_init(&lock,nullptr);
            int rc1 = pthread_cond_init(&cond,nullptr);
        } 

        void zem_wait(){
            pthread_mutex_lock(&lock);
            while(val<=0)
                pthread_cond_wait(&cond,&lock);
            val--;
            pthread_mutex_unlock(&lock);
        }
        void zem_post(){
            pthread_mutex_lock(&lock);
            val++;
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&lock);
        }
};
