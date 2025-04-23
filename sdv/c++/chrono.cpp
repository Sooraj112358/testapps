#include<iostream>
#include<thread>
#include<chrono>

class timer
{
    public:
        std::chrono::_V2::system_clock::time_point start, end;
        std::chrono::duration<float> duration;
        timer()
        {
            start = std::chrono::high_resolution_clock::now();
        }
        ~timer()
        {
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "Execution time of " << __func__ << "is  " << duration.count() * 1000.0f << " ms\n";
        }
};

int main()
{
	timer t;
	std::this_thread::sleep_for(std::chrono::milliseconds(2));
	return 0;
}