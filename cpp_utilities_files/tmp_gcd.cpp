#include<iostream>

using namespace std;

template<int a, int b>
struct my_gcd{
    inline static constexpr int value = my_gcd<b,a%b>::value;
};

template<int a>
struct my_gcd<a,0>{
    inline static constexpr int value = a;
};


int main() {
    cout<<my_gcd<84,60>::value;
}