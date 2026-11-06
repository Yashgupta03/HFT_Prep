#include<iostream>
#include<vector>
#include<thread>

using namespace std;


class operation_class{
    int m_val{};
    public:
        operation_class(int init_val=10): m_val{init_val}{}
        void add_op(int val, int&ans){
            // ans = val+m_val;
            // cout<<"ans: "<<ans<<endl;
            cout<<val+m_val<<endl;
        }
        void sub_op(int val, int&ans){
            ans = val-m_val;
            cout<<"ans: "<<ans<<endl;
        }
};


int main() {
    vector<jthread> t;
    int num_threads{4};
    operation_class op{100};
    int ans{};
    for(int i{}; i<num_threads; i++){
        t.emplace_back(&operation_class::add_op, &op, 10*i, ref(ans));
    }
    // for(auto &t1 : t){
    //     if(t1.joinable()) t1.join();
    // }
}