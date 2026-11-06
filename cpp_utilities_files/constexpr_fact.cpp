#include<iostream>

using namespace std;


template<int N>
constexpr int factorial(){
    static_assert(N>=0, "Error value negative\n");
    int ans{1},i{1};
    for(i=1;i<= N;i++){
        ans*=i;
    }
    return ans;
}


int main(){
    constexpr int res{factorial<9>()};
    cout<<res<<endl;
}