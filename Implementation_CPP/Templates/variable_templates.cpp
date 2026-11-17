#include<bits/stdc++.h>
using namespace std;


template<typename T>
T my_const = T(2.3456789123456789);


int main() {
    cout<<my_const<int><<endl;
    cout<<my_const<float><<endl;
    cout<<my_const<double><<endl;
    cout<<my_const<long long int><<endl;

    my_const<char> = 'c';    
    cout<<my_const<char><<endl;
}