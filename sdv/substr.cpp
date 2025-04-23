#include <string.h> 
#include <iostream> 
using namespace std; 
  
int main() 
{ 
    // Take any string 
    string s1 = "Slot[2]_IP[10.25.12.89]_Brand[SamsungTechwin]_Model[QNV-6070R]"; 
  
    // Copy three characters of s1 (starting  
    // from position 1) 
    string r = s1.substr(5, 1); 
  
    // prints the result 
    cout << "String is: " << r << std::endl; 
  
    return 0; 
} 