#include<iostream>
#include<chrono>
#include <string.h>

#define BUF_SIZE 11*1024*1024
class timer
{
    public:
        std::chrono::_V2::system_clock::time_point start, end;
        std::chrono::duration<float> duration;
        std::string funcName;
        timer(const char *func="Unknown")
        {
            funcName = func;
            startTime();
        }
        ~timer()
        {
            stopTime();
        }
        void startTime()
        {
            start = std::chrono::high_resolution_clock::now();
        }
        void stopTime(const char* loc="unknown point")
        {
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "Execution time of "<< funcName <<" function at " << loc <<" is " << duration.count() * 1000.0f <<" ms" << std::endl;
        }
};

char* allocateBuffer(uint32_t size)
{
	char* buffer = (char *)malloc (size*sizeof(uint8_t));
	int i;
	for (i=0; i<size; i++)
	{
		buffer[i]=(rand()%100)+1;
	}
	printf("Address of buffer = %p\n", buffer);
	return buffer;
}

int main()
{
	timer t(__func__);
	char *buffer1 = allocateBuffer(BUF_SIZE);
	t.stopTime("test1");
	char *buffer2 = allocateBuffer(BUF_SIZE);
	t.stopTime("test2");
	memcpy(buffer2, buffer1, BUF_SIZE);
}