#include<iostream>

using namespace std;

consteval int my_gcd(int n, int m) {
    if(m==0) return n;
    return my_gcd(m, n%m);
}

int main() {
    cout<<my_gcd(420,2500);
}
