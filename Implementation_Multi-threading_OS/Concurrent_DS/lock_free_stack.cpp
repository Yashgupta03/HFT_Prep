#include<bits/stdc++.h>

using namespace std;


template<typename T>
class lock_free_stack{
    private:
        struct Node{
            T data;
            Node* next;
            Node(T d): data{d}, next{nullptr}{}
        };
        atomic<Node*> head{nullptr};
        atomic<int> sz{0};
    public:
        lock_free_stack(){

        }
        void push(T d){
            Node* curr = new Node(d);
            curr->next = head.load();
            head.store(curr);
            sz++;
        }
        void pop(){
            if(head == nullptr) return;
            head.store(head.load()->next);
            sz--;
        }
        size_t size(){
            return sz.load();
        }
        const T& top(){
            return head.load()->data;
        }
};