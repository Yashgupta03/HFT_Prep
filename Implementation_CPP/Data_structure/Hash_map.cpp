#include<bits/stdc++.h>

using namespace std;

template<typename T_key, typename T_val>
class Hash_map{
    private:
        struct Node{
            T_key key;
            T_val value;
            // Node* prev;
            Node* next;
            Node(T_key k, T_val val): key{k}, value{val}, next{nullptr}{}
        };
        size_t m_bucket_count{1};
        vector<Node*> buckets;
        size_t hashIndex(const T_key& k) const {
            return hash<T_key>{}(k) % m_bucket_count;
        }
        Node* search(T_key k){
            size_t hash_ind = hashIndex(k);
            Node* curr=buckets[hash_ind];
            while(curr!=nullptr){
                if(curr->key == k) return curr;
                curr=curr->next;
            }
            return nullptr;
        }
    public:
        Hash_map(size_t bucket_c=1): m_bucket_count{bucket_c}, buckets{bucket_c,nullptr}{}
        
        Hash_map(const Hash_map&) = delete;
        Hash_map& operator=(Hash_map&obj) = delete;
        
        ~Hash_map(){
            Node *curr{nullptr},*next_node{nullptr};
            for(Node* n : buckets){
                curr=n;
                while(curr!=nullptr){
                    next_node = curr->next;
                    delete curr;
                    curr=next_node;
                }
            }
            buckets.clear();
        }

        void insert(T_key k, T_val val);
        T_val get(T_key k);
        void update(T_key k, T_val val);
        bool contains(T_key k);
        void present_state();
};

template<typename T_key, typename T_val>
void Hash_map<T_key, T_val>::insert(T_key k, T_val val){
    size_t hash_ind = hashIndex(k);
    Node* n = search(k);
    if(n!=nullptr){
        update(k,val);
    }
    else{
        Node* curr = new Node(k,val);
        n=buckets[hash_ind];
        curr->next=n;
        buckets[hash_ind]=curr;
    }
}

template<typename T_key, typename T_val>
void Hash_map<T_key, T_val>::update(T_key k, T_val val){
    size_t hash_ind = hashIndex(k);
    Node* n = search(k);
    if(n==nullptr){
        insert(k,val);
    }
    else{
        n->value = val;
    }
}

template<typename T_key, typename T_val>
T_val Hash_map<T_key, T_val>::get(T_key k){
    size_t hash_ind = hashIndex(k);
    Node* n = search(k);
    if(n==nullptr){
        cout<<"error\n";
        return -1;
    }
    return n->value;
}

template<typename T_key, typename T_val>
bool Hash_map<T_key, T_val>::contains(T_key k){
    size_t hash_ind = hashIndex(k);
    Node* n = search(k);
    if(n==nullptr){
        return false;
    }
    return true;
}

template<typename T_key, typename T_val>
void Hash_map<T_key, T_val>::present_state(){
    Node* curr{nullptr};
    int i{0};
    for(Node* n : buckets){
        curr=n;
        cout<<"bucket: "<<i<<endl;
        while(curr!=nullptr){
            cout<<curr->key<<" "<<curr->value<<endl;
            curr=curr->next;
        }
        i++;
    }
}


int main(){
    Hash_map<int,int> mp(10);
    for(int i=0;i<20;i++){
        mp.insert(i,10*i);
    }
    cout<<"Present state\n";
    mp.present_state();
    cout<<"updateing...\n";
    for(int i=0;i<30;i++){
        mp.update(i,100*i);
    }
    cout<<"Present state\n";
    mp.present_state();
    cout<<"getting\n";
    for(int i=0;i<20;i++){
        cout<<mp.get(i)<<" ";
    }
}