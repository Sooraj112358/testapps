#include <iostream>
#include <string>
#include <bits/stdc++.h> 



uint64_t string_to_mac(std::string const& s) {
    unsigned char a[6];
    int last = -1;
    int rc = sscanf(s.c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx%n",
                    a + 0, a + 1, a + 2, a + 3, a + 4, a + 5,
                    &last);
    if(rc != 6 || s.size() != last)
        throw std::runtime_error("invalid mac address format " + s);
    return
        uint64_t(a[0]) << 40 |
        uint64_t(a[1]) << 32 | ( 
            // 32-bit instructions take fewer bytes on x86, so use them as much as possible.
            uint32_t(a[2]) << 24 | 
            uint32_t(a[3]) << 16 |
            uint32_t(a[4]) << 8 |
            uint32_t(a[5])
        );
}


int main()
{
  std::string mac="b0:18:86:04:4e:ed";
  int n;
  unsigned long long devid = 0x193619374132973;
  //std::stringstream ss;
  //std::istringstream(mac) >> std::hex >> n;
  //std::cout << "hex mac: " << n  << std::endl;
  //ss << std::dec << mac;
  std::cout << "string_to_mac:" << string_to_mac(mac) << " : " << devid << std::endl;
  
  return 0;
}
