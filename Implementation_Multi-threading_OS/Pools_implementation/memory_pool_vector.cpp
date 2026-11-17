#include<bits/stdc++.h>

using namespace std;


template<typename T, size_t blocks_count>
class Memory_pool_vector{
    private:
        vector<void*> m_freelist;
        char* m_storage;
    public:
        Memory_pool_vector(){
            m_storage = new char[sizeof(T)*blocks_count];
            m_freelist.reserve(blocks_count);
            for(int i=0;i<blocks_count;i++){
                m_freelist.push_back(m_storage+i*sizeof(T));
            }
        }
        ~Memory_pool_vector(){
            delete[] m_storage;
        }
        void* allocate(){
            if(m_freelist.empty()) throw::bad_alloc();
            void* el = m_freelist.back();
            m_freelist.pop_back();
            return el;
        }
        void deallocate(void* ptr){
            if(ptr == nullptr) return;
            m_freelist.push_back(ptr);
        }
};

int main(){
    return 0;
}