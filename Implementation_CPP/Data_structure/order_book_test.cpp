#include<bits/stdc++.h>

using namespace std;


class order_book{
    private:
        struct order{
            int order_id{};
            int price{};
            int quanity{};
            int timestamp{};
            char order_type{'B'}; //buy or sell
            order* prev{};
            order* next{};
            order(int id, int price, int quantity, int timestamp, char type): 
                order_id{id}, 
                price{price}, 
                quanity{quanity},
                timestamp{timestamp},
                order_type{type},
                prev{nullptr},
                next{nullptr}
            {}
        };
        struct Node{                  // order circular ll
            order* first;
            order* last;
            int size{0};
            Node(order* o): first{o}, last{o}, size{1} {}
        };

        vector<Node*> buy;   // buy book -: price vs order
        vector< Node*> sell;
        unordered_map<int, order*> order_hash_map;  // order_id vs order
        int tick_size{1};
        int min_price{0};
        int max_price{100};

        order* create_order(int id, int price, int quantity, int timestamp, char type){
            order* o = new order(id, price, quantity, timestamp, type);
            return o;
        }
        Node* create_node(order* o){
            Node* n = new Node(o);
            return n;
        }
    public:
        order_book(int minp, int maxp,int tickp): 
            min_price{minp}, 
            max_price{maxp},   
            tick_size{tickp}, 
            buy{ceil((maxp-minp)/double(tickp)),nullptr}, 
            sell{ceil((maxp-minp)/double(tickp)),nullptr} 
            {}   
        order_book(const order_book&) = delete;
        order_book& operator=(order_book&obj) = delete;
        
        ~order_book(){
            order* curr,*next_node;
            for(Node* n : buy){
                if(n==nullptr) continue;
                curr=n->first;
                while(curr!=nullptr){
                    next_node=curr->next;
                    delete curr;
                    curr=next_node;
                }
                delete n;
            }
        }

        void print_order_specs(int id);
        void add_order(order* o);
        void delete_order(int id);
        void modify_order(int id, int new_price, int new_quantity);
        void trade(int id1, int id2, int price, int quantity);
        void show_top_bids();
        void show_top_asks();
        int get_best_bid();
        int get_best_ask();
        int get_spread();
        bool order_exist(int id);
};

bool order_book::order_exist(int id){
    return order_hash_map.contains(id);
}

void order_book::print_order_specs(int id){
    if(!order_hash_map.contains(id)) {
        cout<<"not exist\n";
        return;
    }
    order* o = order_hash_map[id];
    cout<<"ID: "<<o->order_id<<endl;
    cout<<"PRICE: "<<o->price<<endl;
    cout<<"QUANTITY: "<<o->quanity<<endl;
    cout<<"TYPE: "<<o->order_type<<endl;
    cout<<"TIMESTAMP: "<<o->timestamp<<endl;
}

void order_book::add_order(order* o){
    if(order_exist(o->order_id)) {
        cout<<"Order already exist\n";
        return;
    }
    else if(o->order_type=='B'){
        int ind = (o->price - min_price)/tick_size;
        if(buy[ind]==nullptr){
            Node* new_node = create_node(o);
            buy[ind] = new_node;
            new_node->size++;
        }
        else{
            Node* curr_node = buy[ind];
            o->prev = curr_node->last;
            curr_node->last->next = o;
            curr_node->last = o;
            curr_node->size++;
        }
    }
    else if(o->order_type=='S'){
        int ind = (o->price - min_price)/tick_size;
        if(sell[ind]==nullptr){
            Node* new_node = create_node(o);
            sell[ind] = new_node;
            new_node->size++;
        }
        else{
            Node* curr_node = sell[ind];
            o->prev = curr_node->last;
            curr_node->last->next = o;
            curr_node->last = o;
            curr_node->size++;
        }
    }
    order_hash_map[o->order_id] = o;
}

void order_book::delete_order(int id) {
    if(!order_exist(id)) {
        cout<<"error order does not exist\n";
        return;
    }
    order* o = order_hash_map[id];
    int ind = (o->price - min_price)/tick_size;
    if(o->order_type == 'B'){
        Node* curr_node = buy[ind];
        if(curr_node->size == 1){            // size=1 handled here
            order_hash_map.erase(o->order_id);
            delete o;
            delete curr_node;
            buy[ind] =  nullptr;
        }
        else if(curr_node->first == o){
            o->next->prev = nullptr;
            curr_node->first = o->next;
            curr_node->size--;
            order_hash_map.erase(o->order_id);
            delete o;
        }
        else if(curr_node->last == o){
            o->prev->next = nullptr;
            curr_node->last = o->prev;
            curr_node->size--;
            order_hash_map.erase(o->order_id);
            delete o;
        }
        else {
            o->prev->next = o->next;
            o->next->prev = o->prev;
            curr_node->size--;
            order_hash_map.erase(o->order_id);
            delete o;
        }
    }
    else if(o->order_type == 'S'){
        Node* curr_node = sell[ind];
        if(curr_node->size == 1){            // size=1 handled here
            order_hash_map.erase(o->order_id);
            delete o;
            delete curr_node;
            sell[ind] =  nullptr;
        }
        else if(curr_node->first == o){
            o->next->prev = nullptr;
            curr_node->first = o->next;
            curr_node->size--;
            order_hash_map.erase(o->order_id);
            delete o;
        }
        else if(curr_node->last == o){
            o->prev->next = nullptr;
            curr_node->last = o->prev;
            curr_node->size--;
            order_hash_map.erase(o->order_id);
            delete o;
        }
        else {
            o->prev->next = o->next;
            o->next->prev = o->prev;
            curr_node->size--;
            order_hash_map.erase(o->order_id);
            delete o;
        }
    }   
}

void order_book::modify_order(int id, int new_price, int new_quantity){
    if(!order_exist(id)){
        cout<<"error order does not exist\n";
        return;
    }
    order* o=order_hash_map[id];
    int ind = (o->price - min_price)/tick_size;
    if(o->price == new_price && o->quanity >= new_quantity){
        o->quanity = new_quantity;
        return;
    }
    else{
        order* new_order = create_order(o->order_id, new_price, new_quantity, o->timestamp, o->order_type);
        delete_order(id);
        add_order(new_order);
    }
}

void order_book::trade(int id1, int id2, int price, int quantity){              //id1-: buyer, id2-: seller
    order* buy_order = order_hash_map[id1];
    order* sell_order = order_hash_map[id2];
    if(buy_order->quanity == quantity) delete_order(id1);
    else buy_order->quanity -=quantity;

    if(sell_order->quanity == quantity) delete_order(id2);
    else sell_order->quanity -=quantity;
}

// void order_book::show_top_bids(int n){
    
// }
