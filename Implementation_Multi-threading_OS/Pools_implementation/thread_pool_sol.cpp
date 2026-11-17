#include <chrono>
#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <type_traits>
#include <vector>

// class ThreadPool {
// public:
//     explicit ThreadPool(size_t num_threads = std::thread::hardware_concurrency())
//         : stop_(false) {
//         if (num_threads == 0) {
//             num_threads = 1;
//         }

//         workers_.reserve(num_threads);
//         for (size_t i = 0; i < num_threads; ++i) {
//             // Pass a member function pointer and 'this' instead of a lambda
//             workers_.emplace_back(&ThreadPool::workerLoop, this);
//         }
//     }

//     template <class F, class... Args>
//     auto enqueue(F&& f, Args&&... args)
//         -> std::future<std::invoke_result_t<F, Args...>> {
//         using return_type = std::invoke_result_t<F, Args...>;

//         auto task = std::make_shared<std::packaged_task<return_type()>>(
//             std::bind(std::forward<F>(f), std::forward<Args>(args)...)
//         );

//         std::future<return_type> res = task->get_future();
//         {
//             std::unique_lock<std::mutex> lock(queue_mutex_);

//             if (stop_) {
//                 throw std::runtime_error("Cannot enqueue on a stopped ThreadPool");
//             }

//             // Use a functor struct instead of a lambda to wrap the task
//             tasks_.emplace(TaskWrapper<return_type>(task));
//         }

//         condition_.notify_one();
//         return res;
//     }

//     ~ThreadPool() {
//         {
//             std::unique_lock<std::mutex> lock(queue_mutex_);
//             stop_ = true;
//         }
//         condition_.notify_all();
//         for (std::thread& worker : workers_) {
//             if (worker.joinable()) {
//                 worker.join();
//             }
//         }
//     }

//     ThreadPool(const ThreadPool&) = delete;
//     ThreadPool& operator=(const ThreadPool&) = delete;

// private:
//     // Replaces the condition_variable predicate lambda
//     struct WakePredicate {
//         const ThreadPool* pool;
//         bool operator()() const {
//             return pool->stop_ || !pool->tasks_.empty();
//         }
//     };

//     // Replaces the task-wrapping lambda inside enqueue()
//     template <typename T>
//     struct TaskWrapper {
//         std::shared_ptr<std::packaged_task<T()>> task;

//         explicit TaskWrapper(std::shared_ptr<std::packaged_task<T()>> t)
//             : task(std::move(t)) {}

//         void operator()() const {
//             (*task)();
//         }
//     };

//     // Replaces the worker thread body lambda
//     void workerLoop() {
//         while (true) {
//             std::function<void()> task;

//             {
//                 std::unique_lock<std::mutex> lock(queue_mutex_);
//                 condition_.wait(lock, WakePredicate{this});

//                 if (stop_ && tasks_.empty()) {
//                     return;
//                 }

//                 task = std::move(tasks_.front());
//                 tasks_.pop();
//             }

//             task();
//         }
//     }

//     std::vector<std::thread> workers_;
//     std::queue<std::function<void()>> tasks_;
//     std::mutex queue_mutex_;
//     std::condition_variable condition_;
//     bool stop_;
// };

// // Free function used for demonstration (instead of a lambda task)
// int computeSquare(int x) {
//     std::this_thread::sleep_for(std::chrono::milliseconds(100));
//     return x * x;
// }

// int main() {
//     ThreadPool pool(4);
//     std::vector<std::future<int>> results;

//     for (int i = 0; i < 8; ++i) {
//         results.emplace_back(pool.enqueue(computeSquare, i));
//     }

//     for (std::future<int>& result : results) {
//         std::cout << result.get() << " ";
//     }
//     std::cout << '\n';

//     return 0;
// }











//----------------------------------------difft-------------------------------------
// class ThreadPool {
// public:
//     // Initialize the pool with a specific number of worker threads
//     explicit ThreadPool(size_t num_threads = std::thread::hardware_concurrency()) 
//         : stop_(false) {
//         if (num_threads == 0) {
//             num_threads = 1;
//         }

//         workers_.reserve(num_threads);
//         for (size_t i = 0; i < num_threads; ++i) {
//             workers_.emplace_back([this] {
//                 while (true) {
//                     std::function<void()> task;

//                     {
//                         std::unique_lock<std::mutex> lock(queue_mutex_);
                        
//                         // Wait until there is a task or the pool is stopped
//                         condition_.wait(lock, [this] {
//                             return stop_ || !tasks_.empty();
//                         });

//                         // Exit if stopped and no tasks remain
//                         if (stop_ && tasks_.empty()) {
//                             return;
//                         }

//                         task = std::move(tasks_.front());
//                         tasks_.pop();
//                     }

//                     // Execute the task outside the lock so other threads can access the queue
//                     task();
//                 }
//             });
//         }
//     }

//     // Submit a task with arguments and get a std::future for the return value
//     template <class F, class... Args>
//     auto enqueue(F&& f, Args&&... args) 
//         -> std::future<std::invoke_result_t<F, Args...>> {
//         using return_type = std::invoke_result_t<F, Args...>;

//         // Wrap the callable in a packaged_task managed by a shared_ptr
//         auto task = std::make_shared<std::packaged_task<return_type()>>(
//             std::bind(std::forward<F>(f), std::forward<Args>(args)...)
//         );

//         std::future<return_type> res = task->get_future();
//         {
//             std::unique_lock<std::mutex> lock(queue_mutex_);

//             if (stop_) {
//                 throw std::runtime_error("Cannot enqueue on a stopped ThreadPool");
//             }

//             // Type-erase the packaged_task into a void() lambda
//             tasks_.emplace([task]() { (*task)(); });
//         }

//         condition_.notify_one();
//         return res;
//     }

//     // Gracefully shut down and join all worker threads
//     ~ThreadPool() {
//         {
//             std::unique_lock<std::mutex> lock(queue_mutex_);
//             stop_ = true;
//         }
//         condition_.notify_all();
//         for (std::thread& worker : workers_) {
//             if (worker.joinable()) {
//                 worker.join();
//             }
//         }
//     }

//     // Prevent copying or moving
//     ThreadPool(const ThreadPool&) = delete;
//     ThreadPool& operator=(const ThreadPool&) = delete;

// private:
//     std::vector<std::thread> workers_;
//     std::queue<std::function<void()>> tasks_;
//     std::mutex queue_mutex_;
//     std::condition_variable condition_;
//     bool stop_;
// };

// // Example Usage
// int main() {
//     ThreadPool pool(4); // Create a pool with 4 worker threads

//     std::vector<std::future<int>> results;

//     // Enqueue 8 tasks
//     for (int i = 0; i < 8; ++i) {
//         results.emplace_back(
//             pool.enqueue([i] {
//                 std::this_thread::sleep_for(std::chrono::milliseconds(100));
//                 return i * i;
//             })
//         );
//     }

//     // Retrieve and print results
//     for (auto&& result : results) {
//         std::cout << result.get() << " ";
//     }
//     std::cout << '\n';

//     return 0;
// }
