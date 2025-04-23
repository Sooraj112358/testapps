#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
 
int g_num = 0;  // protected by g_num_mutex
std::recursive_mutex g_num_mutex;
 
void slow_increment0(int id) 
{
	for (int i = 0; i < 3; ++i) {
	    g_num_mutex.lock();
	    ++g_num;
	    std::cout << id << " => " << g_num << '\n';

	    std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
 
void slow_increment1(int id) 
{
	for (int i = 0; i < 3; ++i) {
	    g_num_mutex.lock();
	    ++g_num;
	    std::cout << id << " => " << g_num << '\n';
	    g_num_mutex.unlock();

	    std::this_thread::sleep_for(std::chrono::seconds(11));
	}
}
 
int main()
{
    	std::thread t1(slow_increment1, 0);
	std::thread t2(slow_increment0, 1);
    	t1.join();
	t2.join();
}

