#include<iostream>
#include<pthread.h>
#include<semaphore.h>


using namespace std;


class rwlock{
    private:
        int readers{};
        sem_t lock;
        sem_t writelock;
    public:
        rwlock(): readers{0}{
            int rc = sem_init(&lock,0,1);
            int rc1 = sem_init(&writelock,0,1);
        }

        void read_lock(){
            sem_wait(&lock);
            readers++;
            if(readers == 1){
                sem_wait(&writelock);
            }
            sem_post(&lock);
        }
        void read_unlock(){
            sem_wait(&lock);
            readers--;
            if(readers == 0){
                sem_post(&writelock);
            }
            sem_post(&lock);
        }

        void write_lock(){
            sem_wait(&writelock);
        }
        void write_unlock(){
            sem_post(&writelock);
        }
};