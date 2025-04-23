#include <iostream>
#include <thread>

using namespace std;
class Sample1 {
   public:
      Sample1() {
         cout << "Construct an Object of sample1" << endl;
      }
      ~Sample1() {
         cout << "Destruct an Object of sample1" << endl;
      }
};
class Sample2 {
   public:
      Sample2() {

         cout << "Construct an Object of sample2" << endl;

         throw "Construct an Object of sample2 failed";
		 cout << "shouldn't come here" << endl;
      }
      ~Sample2() {
         cout << "Destruct an Object of sample2" << endl;
      }
    static Sample2& GetInstance()
    {
        try
        {
            static Sample2 obj;
            return obj;
        }
        /*catch(char const *msg)
        {
			 cout << "Message catched and rethrown" << endl;
            throw;
        }*/
        catch(const std::exception& e)
        {
			cout << "Message catched and rethrown" << endl;
            std::cerr << e.what() << '\n';
            throw;
        }
    }
};
int main() {
   try {
      //Sample1 s1;
      //Sample2 s2;
	  Sample2::GetInstance();
       while(1)
        {
        // BLB cServiceManager::PrintMonitoringInformation((const std::string) "");
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }
   } /*catch(int i) {
      cout << "Caught " << i << endl;
   }*/
	catch(char const *msg) {
		 cout << "Message catched" << endl;
      cout << msg << endl;
   }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}