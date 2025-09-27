#include <iostream>

/**
 * *std::thread t1(func1);
 * *std::thread t(func2, 42, 42.0, "42");
 * *std::thread t2([]() {
 *      std::cout << "thread func without params" << '\n'; });
 * *t.join(); -> To wait for a thread to finish its execution
 * *t.detach(); -> To allow a thread to continue its execution independently of the current thread object
 * *std::thread t(func3, std::ref(n)); -> To pass arguments by reference to a function thread, 
 *      wrap them in either 'std::ref' or 'std::cref'
 * *std::this_thread::sleep_for(2s); -> To stop the execution of a thread for a specified duration
 * *std::this_thread::sleep_until() -> To stop the execution of a thread until a specified moment in time
 * *std::this_thread::yield() -> To suspend the execution of the current thread and provide an opportunity 
 *      for another thread to perform the execution
 * *ignores any value that is directly returned by the function -> If it has to return a value, 
 *      it can do so using a shared variable or a function argument (using promises and futures)
 * 
 * 
 */