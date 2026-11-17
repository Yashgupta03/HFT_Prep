#include<iostream>
#include<thread>

using namespace std;


class sum_class{
    int m_var{};
    public:
        sum_class(int var=10): m_var{var}{}

        void fun(int value, int& result){
            cout<<"ans: "<<m_var + value<<endl;
            result = value+m_var;
        }
};



int main() {
    sum_class sum{20};
    int val{50};
    int result{};
    // sum.fun(val);
    thread t1(&sum_class::fun, &sum, val, ref(result));
    if(t1.joinable()) t1.join();
    cout<<"Master thread: "<<result<<endl;
}