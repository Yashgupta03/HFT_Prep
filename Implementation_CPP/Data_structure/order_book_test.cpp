#include<bits/stdc++.h>

using namespace std;

using orderID = int;

class OrderBook{
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
        struct PriceLevel{                  // order circular ll
            order* first;
            order* last;
            int size{0};
            int orderCount{0};
            PriceLevel(order* o): first{o}, last{o}, size{1}, orderCount{1} {}
        };

        vector<PriceLevel*> buy;   // buy book -: price vs order
        vector< PriceLevel*> sell;
        unordered_map<orderID, order*> order_hash_map;  // order_id vs order
        int tick_size{1};
        int min_price{0};
        int max_price{100};

        uint64_t bid_mask{0};
        uint64_t ask_mask{0};
        int best_bid_idx{-1};
        int best_ask_idx{-1};

        order* create_order(int id, int price, int quantity, int timestamp, char type){
            order* o = new order(id, price, quantity, timestamp, type);
            return o;
        }
        PriceLevel* create_PriceLevel(order* o){
            PriceLevel* n = new PriceLevel(o);
            return n;
        }
    public:
        OrderBook(int minp, int maxp,int tickp): 
            min_price{minp}, 
            max_price{maxp},   
            tick_size{tickp}, 
            buy{ceil((maxp-minp)/double(tickp)),nullptr}, 
            sell{ceil((maxp-minp)/double(tickp)),nullptr} 
            {}   
        OrderBook(const OrderBook&) = delete;
        OrderBook& operator=(OrderBook&obj) = delete;
        
        ~OrderBook(){
            order* curr,*next_PriceLevel;
            for(PriceLevel* n : buy){
                if(n==nullptr) continue;
                curr=n->first;
                while(curr!=nullptr){
                    next_PriceLevel=curr->next;
                    delete curr;
                    curr=next_PriceLevel;
                }
                delete n;
            }
        }

        void print_order_specs(int id);
        void add_order(order* o);
        void delete_order(int id);
        void modify_order(int id, int new_price, int new_quantity);
        void trade(int id1, int id2, int price, int quantity);
        void show_top_bids(int n);
        void show_top_asks();
        int get_best_bid();
        int get_best_ask();
        int get_spread();
        bool order_exist(int id);
};

bool OrderBook::order_exist(int id){
    return order_hash_map.contains(id);
}

void OrderBook::print_order_specs(int id){
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

void OrderBook::add_order(order* o){
    if(order_exist(o->order_id)) [[unlikely]] {
        cout<<"Order already exist\n";
        return;
    }
    int ind = (o->price - min_price)/tick_size;
    PriceLevel*& level = o->order_type=='B' ? buy[ind] : sell[ind];
    if(level==nullptr){
        PriceLevel* new_PriceLevel = create_PriceLevel(o);
        level = new_PriceLevel;
        new_PriceLevel->size++;
    }
    else{
        o->prev = level->last;
        level->last->next = o;
        level->last = o;
        level->size++;
    }
    order_hash_map[o->order_id] = o;

    if(o->order_type=='B') {
        bid_mask |= (1ULL << ind);
        if(best_bid_idx==-1 || ind > best_bid_idx){
            best_bid_idx=ind;
        }
    }
    else{
        ask_mask |= (1ULL<<ind);
        if(best_ask_idx==-1 || best_ask_idx>ind){
            best_ask_idx = ind;
        }
    }
}

void OrderBook::delete_order(int id) {
    if(!order_exist(id)) [[unlikely]]{
        cout<<"error order does not exist\n";
        return;
    }
    order* o = order_hash_map[id];
    int ind = (o->price - min_price)/tick_size;
    PriceLevel*& level = o->order_type=='B' ? buy[ind] : sell[ind];

    if(o->prev!=nullptr) o->prev->next = o->next;
    else level->first = o->next;

    if(o->next!=nullptr) o->next->prev = o->prev;
    else level->last = o->prev;

    level->size--;

    if(level->size == 0){            // size=1 handled here
        if(o->order_type=='B') {
            bid_mask &= ~(1ULL << ind);
            if(ind==best_bid_idx){
                best_bid_idx = (bid_mask==0) ? -1 : (63 - __builtin_clzll(bid_mask));
            }
        }
        else{
            ask_mask &= ~(1ULL<<ind);
            if(ind==best_ask_idx){
                best_ask_idx = (ask_mask==0) ? -1 : (__builtin_clzll(ask_mask));
            }
        }
        delete level;
        level =  nullptr;
    }

    order_hash_map.erase(o->order_id);
    delete o;
}

void OrderBook::modify_order(int id, int new_price, int new_quantity){
    if(!order_exist(id))[[unlikely]]{
        cout<<"error order does not exist\n";
        return;
    }
    order* o=order_hash_map[id];
    // int ind = (o->price - min_price)/tick_size;
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

void OrderBook::trade(int id1, int id2, int price, int quantity){              //id1-: buyer, id2-: seller
    order* buy_order = order_hash_map[id1];
    order* sell_order = order_hash_map[id2];
    if(buy_order->quanity == quantity) delete_order(id1);
    else buy_order->quanity -=quantity;

    if(sell_order->quanity == quantity) delete_order(id2);
    else sell_order->quanity -=quantity;
}


int OrderBook::get_best_bid(){
    if(best_bid_idx==-1) return 0;
    return best_bid_idx*tick_size + min_price;
}

int OrderBook::get_best_ask(){
    if(best_ask_idx==-1) return 0;
    return best_ask_idx*tick_size + min_price;
}

int OrderBook::get_spread(){
    return get_best_ask() - get_best_bid();
}

void OrderBook::show_top_bids(int levels) {
    std::cout << "\n--- MARKET DEPTH (Top " << levels << ") ---\n";
    // Extracting Top Asks
    uint64_t temp_ask = ask_mask;
    std::vector<uint64_t> top_asks;
    while (temp_ask != 0 && top_asks.size() < levels) {
        int idx = __builtin_ctzll(temp_ask);     // Lowest active ask
        top_asks.push_back(idx*tick_size + min_price);
        temp_ask &= (temp_ask - 1);          
    }

    // Print Asks in reverse (highest price at top, lowest/best ask near spread)
    for (int i = top_asks.size() - 1; i >= 0; --i) {
        std::cout << "ASK :" << std::fixed << std::setprecision(2) 
                    << (top_asks[i] / 100.0) << "\n";
    }

    std::cout << "-----------------------------\n";

    // Extracting Top Bids
    uint64_t temp_bid = bid_mask;
    int count = 0;
    while (temp_bid != 0 && count < levels) {
        int idx = 63 - __builtin_clzll(temp_bid); // Highest active bid
        std::cout << "BID :" << std::fixed << std::setprecision(2) 
                    << ((idx*tick_size + min_price) / 100.0) <<"\n";
        temp_bid &= ~(1ULL << idx);               // Clear that highest bit
        count++;
    }
    std::cout << "-----------------------------\n";
}
