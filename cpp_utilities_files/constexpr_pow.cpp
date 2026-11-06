#include<iostream>

using namespace std;

template<typename T>
consteval T my_pow_it(T a, T e){     //a^e
    T res{1};
    while(e){
        if(e&1) {
            res*=a;
        }
        a*=a;
        e>>=1;
    }
    return res;
}

template<typename T>
consteval T my_pow_r(const T a, const int e){
    if(e==0) return 1;
    if(e==1) return a;
    T res = my_pow_r(a,e/2);
    res*=res;
    if(e&1) res*=a;
    return res;
}


int main(){
    constexpr int a{2};
    constexpr int e{10};
    constexpr int ans_it{my_pow_it<int>(a,e)};
    constexpr int ans_r{my_pow_r<int>(a,e)};
    cout<<ans_it<<" "<<ans_r<<endl;
}