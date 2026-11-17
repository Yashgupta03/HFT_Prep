#include<iostream>
#include<cmath>

using namespace std;


// template<int a, int d>
// struct is_prime_util{
//     inline static constexpr int value = (a%d != 0) && (is_prime_util<a,d-1>::value);
// };

// template<int a>
// struct is_prime_util<a,2>{
//     inline static constexpr int value = (a%2 != 0);
// };

// template<int N>
// struct is_prime{
//     inline static constexpr int val = is_prime_util<N,N/2>::value;
// };

// template<>
// struct is_prime<1>{
//     inline static constexpr int val = 0;
// };

// template<>
// struct is_prime<2>{
//     inline static constexpr int val = 1;
// };

// template<>
// struct is_prime<3>{
//     inline static constexpr int val = 1;
// };


// int main() {
//     cout<<is_prime<50>::val;
// }


template<int a, int d>
struct is_prime_util{
    inline static constexpr int value = (a%d != 0) && (is_prime_util<a,d-1>::value);
};

template<int a>
struct is_prime_util<a,2>{
    inline static constexpr int value = (a%2 != 0);
};

template<int N>
struct is_prime{
    inline static constexpr int val = is_prime_util<N,int(sqrt(N))>::value;
};

template<>
struct is_prime<1>{
    inline static constexpr int val = 0;
};

template<>
struct is_prime<2>{
    inline static constexpr int val = 1;
};

template<>
struct is_prime<3>{
    inline static constexpr int val = 1;
};


int main() {
    cout<<is_prime<97>::val;
}