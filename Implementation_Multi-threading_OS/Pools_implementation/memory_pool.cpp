#include<bits/stdc++.h>

using namespace std;


template<typename T, size_t blocks_count>
class Memory_pool{
    private:
        union chunk{
            char storage[sizeof(T)];
            chunk* next;
        };
        chunk* m_pool;
        chunk* m_head_fl;
    public:
        Memory_pool(){
            m_pool = new chunk[blocks_count];
            m_head_fl = m_pool;
            for(int i=0;i<blocks_count-1; i++){
                m_pool[i].next = &(m_pool[i+1]);
            }
            m_pool[blocks_count-1].next = nullptr;
        }
        ~Memory_pool(){
            delete[] m_pool;
        }
        void* allocate(){
            if(m_head_fl == nullptr) throw::bad_alloc();
            chunk* curr = m_head_fl;
            m_head_fl = m_head_fl->next;
            return static_cast<void*>(curr->storage);
        }
        void deallocate(void* ptr){
            if(ptr = nullptr) return;
            chunk* curr = static_cast<chunk*>ptr;
            curr->next = m_head_fl;
            m_head_fl = curr;
        }

        template <typename... Args>
        T* construct(Args&&... args) {
            void* rawMem = allocate();
            return ::new (rawMem) T(forward<Args>(args)...);
        }

        void destruct(T* ptr) {
            if (ptr == nullptr) return;
            ptr->~T();         
            deallocate(ptr);    
        }
};




// ---------------------------------------AI-------------------------

// #include <iostream>
// #include <cstddef>
// #include <utility>
// #include <new>

// template <typename T, std::size_t BlockCount>
// class MemoryPool {
// private:
//     // A chunk can either store the actual object data or a pointer to the next free chunk.
//     // This allows us to maintain a free list without wasting extra memory per object.
//     union Chunk {
//         alignas(T) char storage[sizeof(T)];
//         Chunk* nextFree;
//     };

//     Chunk* m_poolBuffer;    // The large contiguous block of memory
//     Chunk* m_headFree;      // Head of the singly linked free list

// public:
//     // Pre-allocate the complete block on the heap during initialization
//     MemoryPool() {
//         m_poolBuffer = new Chunk[BlockCount];
//         m_headFree = m_poolBuffer;

//         // Link all chunks together into the free list
//         for (std::size_t i = 0; i < BlockCount - 1; ++i) {
//             m_poolBuffer[i].nextFree = &m_poolBuffer[i + 1];
//         }
//         // The last chunk marks the end of the free list
//         m_poolBuffer[BlockCount - 1].nextFree = nullptr;
//     }

//     // Clean up the entire memory block at once
//     ~MemoryPool() {
//         delete[] m_poolBuffer;
//     }

//     // Disable copy semantics to prevent double-free bugs
//     MemoryPool(const MemoryPool&) = delete;
//     MemoryPool& operator=(const MemoryPool&) = delete;

//     // Support move semantics
//     MemoryPool(MemoryPool&& other) noexcept 
//         : m_poolBuffer(std::exchange(other.m_poolBuffer, nullptr)), 
//           m_headFree(std::exchange(other.m_headFree, nullptr)) {}

//     MemoryPool& operator=(MemoryPool&& other) noexcept {
//         if (this != &other) {
//             delete[] m_poolBuffer;
//             m_poolBuffer = std::exchange(other.m_poolBuffer, nullptr);
//             m_headFree = std::exchange(other.m_headFree, nullptr);
//         }
//         return *this;
//     }

//     // Allocate a raw chunk in O(1) time
//     void* allocate() {
//         if (m_headFree == nullptr) {
//             throw std::bad_alloc(); // Out of memory chunks
//         }

//         // Pop the front chunk off the free list
//         Chunk* availableChunk = m_headFree;
//         m_headFree = m_headFree->nextFree;

//         return static_cast<void*>(availableChunk->storage);
//     }

//     // Return a chunk back to the pool in O(1) time
//     void deallocate(void* ptr) {
//         if (ptr == nullptr) return;

//         // Cast raw pointer back to a Chunk block
//         Chunk* returnedChunk = reinterpret_cast<Chunk*>(ptr);

//         // Push the chunk back to the front of the free list
//         returnedChunk->nextFree = m_headFree;
//         m_headFree = returnedChunk;
//     }

//     // Helper construct function (perfect forwarding to object constructor)
//     template <typename... Args>
//     T* construct(Args&&... args) {
//         void* rawMem = allocate();
//         // Placement new to construct the object in-place inside the pool memory
//         return ::new (rawMem) T(std::forward<Args>(args)...);
//     }

//     // Helper destroy function
//     void destroy(T* ptr) {
//         if (ptr == nullptr) return;
//         ptr->~T();          // Explicitly invoke the object destructor
//         deallocate(ptr);    // Reclaim raw chunk memory
//     }
// };


// struct Particle {
//     float x, y, z;
//     int id;

//     Particle(float x, float y, float z, int id) : x(x), y(y), z(z), id(id) {
//         std::cout << "Particle " << id << " created.\n";
//     }
//     ~Particle() {
//         std::cout << "Particle " << id << " destroyed.\n";
//     }
// };

// int main() {
//     // Instantiate a pool that manages up to 3 Particle objects
//     MemoryPool<Particle, 3> particlePool;

//     // Construct objects using the pool
//     Particle* p1 = particlePool.construct(1.0f, 2.0f, 3.0f, 101);
//     Particle* p2 = particlePool.construct(4.0f, 5.0f, 6.0f, 102);

//     // Reclaim an object's space back into the pool
//     particlePool.destroy(p1);

//     // Allocation happens deterministically in O(1), utilizing the slot freed by p1
//     Particle* p3 = particlePool.construct(7.0f, 8.0f, 9.0f, 103);

//     // Clean up remaining allocations
//     particlePool.destroy(p2);
//     particlePool.destroy(p3);

//     return 0;
// }










int main(){
    return 0;
}