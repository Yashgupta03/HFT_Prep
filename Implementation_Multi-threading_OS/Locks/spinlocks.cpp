#include<bits/stdc++.h>

using namespace std;

class test_and_set_lock{
    private:
        atomic_flag flag{};
    public:
        void lock(){
            while(flag.test_and_set(memory_order_acquire));
        }
        void unlock(){
            flag.clear(memory_order_release);
        }
};

class CAS_lock{
    private:
        atomic<int>flag{0};
    public:
        void lock(){
            int expect=0;
            while(!flag.compare_exchange_strong(expect,1, memory_order_acquire));
        }
        void unlock(){
            flag.store(0,memory_order_release);
        }
};

class ticket_lock{
    private:
        atomic<int> turn{0};
        atomic<int> ticket{0};
    public:
        void lock(){
            int myturn = ticket.fetch_add(1);
            while(turn!=myturn);
        }
        void unlock(){
            turn.fetch_add(1);
        }
};