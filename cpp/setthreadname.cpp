#include <thread>
#include <iostream>
#include <pthread.h>
 
using namespace std;

void foo(string s) 
{
    char name[16];
    
     pthread_setname_np(pthread_self(), s.c_str()); // set the name (pthread_self() returns the pthread_t of the current thread)    
     pthread_getname_np(pthread_self(), &name[0], sizeof(name));   
     cout << name << endl;
}

int main() 
{
    thread t1(&foo, "threaddysdfsdd");
 
    t1.join();
    return 0;
}
