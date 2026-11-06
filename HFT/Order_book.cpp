#include<bits/stdc++.h>

using namespace std;


struct order{
    int order_id{};
    int price{};
    int quanity{};
    int timestamp{};
    char order_type{'B'}; //buy or sell
    order* prev{};
    order* next{};
};

class order_book{
    private:
        vector<int,order*> 
};