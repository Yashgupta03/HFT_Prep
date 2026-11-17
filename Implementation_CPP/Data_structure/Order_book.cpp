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
        void print_order_specs(int id);
        void add_order(order* o);
        void delete_order(int id);
        void modify_order();
        void trade();
        void show_top_bids();
        void show_top_asks();
        int get_best_bid();
        int get_best_ask();
        int get_spread();
};

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
    if(o->order_type=='B'){
        int ind = (o->price - min_price)/tick_size;
        if(buy.size() - 1 < ind){
            buy.resize(ind+1);
            buy[ind] = create_node(o);
        }
        else{
            buy[ind]->last->next = o;
            o->prev = buy[ind]->last;
            buy[ind]->last = o;
            buy[ind]->size +=1;
        }
    }
    else{
        int ind = (o->price - min_price)/tick_size;
        if(sell.size() - 1 < ind){
            sell.resize(ind+1);
            sell[ind] = create_node(o);
        }
        else{
            sell[ind]->last->next = o;
            o->prev = sell[ind]->last;
            sell[ind]->last = o;
            sell[ind]->size += 1;
        }
    }
    order_hash_map[o->order_id] = o;
}

void order_book::delete_order(int id) {
    order* o = order_hash_map[id];
    int ind = (o->price - min_price)/tick_size;
    if(o->order_type == 'B'){
        
    }
}












