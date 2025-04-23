#include <iostream>
#include <memory>
#include <unistd.h>
#include <mutex>

using namespace std;

class MyClass {
public:
    MyClass(string x) : name(x) {cout<<"C->"<<name<<endl;};
    ~MyClass() {cerr<<"D->"<<name<<endl;};
    string name;
};

std::mutex  m_ptreeMutex;
shared_ptr<MyClass> a;
//unique_ptr<MyClass> a;

void* tfunc(void*) {
  while(1){
   {
      {
      std::lock_guard<std::mutex> lock(m_ptreeMutex);
      //shared_ptr<MyClass> s = a;
      }
      //unique_ptr<MyClass> s = a;
      usleep(5000000);
   }
  }
}

int main(void) {
    pthread_t threadid;
    
    make_shared<MyClass>("a");
    //a = make_unique<MyClass>("a");
    if(pthread_create(&threadid, NULL, tfunc, NULL)) {
        cout<<"pthread_create error"<<endl;
        return -1;
    }
    while(1){
      usleep(5000000);
      {
      std::lock_guard<std::mutex> lock(m_ptreeMutex);
      a = make_shared<MyClass>("b");
      }
    }

    pthread_join(threadid, NULL);
    return 0;
}
