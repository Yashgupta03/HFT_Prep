#include<bits/stdc++.h>

using namespace std;

//----------------variadic print------------------------------
template<typename T>
void print_all_var(T arg){
    cout<<arg<<" ";
}

template<typename T, typename... Args>
void print_all_var(T arg1, Args... args){
    cout<<arg1<<" ";
    print_all(args...);
}

//-------------------fold print---------------------------
template<typename... T>
void print_all(T... args){
    // (cout<<...<<args);
    ((cout<<args<<" "),...);
}


//-------------------vector push back variadic---------------------
template<typename T>
void push_all_var(vector<T>& v, T args){
    v.push_back(args);
}

template<typename T, typename... Args>
void push_all_var(vector<T>&v, T arg1, Args... args){
    v.push_back(arg1);
    push_all(v,args...);
}

//-----------------vector push back fold----------------------
template<typename T, typename... Args>
void push_all(vector<T>&v, Args... args){
    (v.push_back(args),...);
}


int main(){
    // print_all_var(1,2,3,4);
    // print_all_var("hello","today","is","coding day");

    // print_all(1,2,3,4);

    vector<int> v;
    // push_all_var(v, 6,5,4,3,2,1);
    push_all(v, 1,2,3,4,5,6);
    for(auto el: v) cout<<el<<" ";
}