#include<iostream>
#include<unordered_map>

using namespace std;

template<typename T_key, typename T_val>
class LRU_cache{
    private:
        struct Node{
            T_key key;
            T_val value;
            Node* prev;
            Node* next;
            Node(T_key k, T_val val): key{k}, value{val}, prev{nullptr}, next{nullptr}{}
        };
        unordered_map<T_key,Node*> key_to_node_mp;
        Node* head{nullptr};
        Node* tail{nullptr};
        size_t m_capacity{0};
        size_t m_size{0};
        void update(T_key k, T_val val){
            Node* n = key_to_node_mp[k];
            n->value = val;
            if(head == n) return;    //size 1 handled here
            else if(tail == n){
                n->prev->next = nullptr;
                tail = n->prev;
            }
            else{
                n->prev->next = n->next;
                n->next->prev = n->prev;
            }
            n->prev = nullptr;
            n->next = head;
            head->prev = n;
            head = n;
        }
        void insert(T_key k, T_val val){
            Node* n = new Node(k,val);
            n->next = head;
            if(m_size!=0){
                head->prev = n;
                if(m_size == m_capacity){
                    Node* tail_n = tail;
                    tail->prev->next = nullptr;
                    tail= tail->prev;
                    key_to_node_mp.erase(tail_n->key);
                    tail_n->prev = nullptr;
                    delete tail_n;
                    m_size--;
                }
            }
            else{
                tail = n;
            }
            head = n;
            key_to_node_mp[k]=n;
            m_size++;
        }
    public:
        LRU_cache(size_t sz=0): m_capacity{sz}{}
        
        LRU_cache(const LRU_cache&) = delete;
        LRU_cache& operator=(LRU_cache& obj) = delete;
        
        LRU_cache(LRU_cache&& obj){
            key_to_node_mp=move(obj.key_to_node_mp);
            head=move(obj.head);
            tail=move(obj.tail);
            m_capacity=obj.m_capacity;
            m_size=obj.m_size;
            obj.head=nullptr;
            obj.tail=nullptr;
        }
        LRU_cache& operator=(LRU_cache&&obj){
            if(this==&obj) return *this;
            Node* n=head;
            while(n!=nullptr){
                Node* curr=n->next;
                delete n;
                n=curr;
            }
            key_to_node_mp.clear();
            key_to_node_mp=move(obj.key_to_node_mp);
            head=move(obj.head);
            tail=move(obj.tail);
            m_capacity=obj.m_capacity;
            m_size=obj.m_size;
            obj.head=nullptr;
            obj.tail=nullptr;
            return *this;
        }
        
        ~LRU_cache(){
            Node* n=head;
            while(n!=nullptr){
                Node* curr=n->next;
                delete n;
                n=curr;
            }
        }

        void set(T_key k, T_val val);
        T_val get(T_key k);

        int size(){ return m_size;}
        int capacity(){return m_capacity;}
        void present_state();
};

template<typename T_key, typename T_val>
void LRU_cache<T_key, T_val>::set(T_key k, T_val val){
    if(key_to_node_mp.contains(k)){
        update(k,val);
    }
    else{
        insert(k,val);
    }
}
template<typename T_key, typename T_val>
T_val LRU_cache<T_key,T_val>::get(T_key k){
    if(!key_to_node_mp.contains(k)){
        cout<<"error\n";
        return -1;
    }
    Node* n = key_to_node_mp[k];
    update(k,n->value);
    return n->value;
}
template<typename T_key, typename T_val>
void LRU_cache<T_key, T_val>::present_state(){
    Node* n=head;
    while(n!=nullptr){
        cout<<n->key<<" "<<n->value<<endl;
        n=n->next;
    }
}


int main(){
    LRU_cache<int,int> cache(10);
    // cache.set(1,10);
    // cache.set(2,20);
    // cout<<cache.get(1)<<" "<<cache.get(2)<<endl;
    // cache.set(3,30);
    // cout<<cache.get(3)<<" "<<cache.get(2)<<" "<<cache.get(1)<<endl;
    // cache.present_state();
    for(int i=0;i<10;i++){
        cache.set(i,10*i);
    }
    cout<<"setted and present state\n";
    cache.present_state();
    cout<<"updated\n";
    for(int i=10;i<15;i++){
        cache.set(i,10*i);
    }
    cout<<"new state\n";
    cache.present_state();
}