#include<iostream>
#include<pthread.h>

using namespace std;

typedef struct { int a; int b; } myarg_t;
typedef struct { int x; int y; } myret_t;


void *mythread(void *arg) {
    myret_t *rvals = (myret_t*)malloc(sizeof(myret_t));
    myarg_t *args = (myarg_t*)arg;
    // cout<<"in func "<<args->a<<" "<<args->b<<endl;
    rvals->x = args->a;
    rvals->y = args->b;
    return (void *) rvals;
}



int main(int argc, char *argv[]) {
    pthread_t p;
    myret_t *rvals;
    myarg_t args = { 10, 20 };
    pthread_create(&p, NULL, mythread, &args);
    pthread_join(p, (void **) &rvals);
    printf("returned %d %d\n", rvals->x, rvals->y);
    free(rvals);
    return 0;
}