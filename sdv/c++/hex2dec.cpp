#include<iostream>
#include<string>
#include <sstream> 

static uint64_t string_to_mac(std::string s) {
    unsigned char a[6];
    int last = -1;
    int rc = 0;
    std::cout << "string_to_mac: " << s << std::endl;
    if(s.find(':') != std::string::npos)
    {
        std::cout << "with : " << s << std::endl;

    }
    else
    {
        std::cout << "without : " << s << std::endl;
		int i = 0;
		std::string::iterator iter = s.insert(s.begin()+2, ':');
		while(i < 4)
		{
			iter = s.insert(iter+3, ':');
			i++;
		}
		std::cout << "After: " << s << std::endl;

    }
        rc = sscanf(s.c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx%n",
                        a + 0, a + 1, a + 2, a + 3, a + 4, a + 5,
                        &last);
		std::cout << "vals: " << rc << " : " << last << " : " << s.size() << std::endl;
		std::cout << "a: " << +a[0] << " : " << +a[1] << " : " << +a[2] << " : " <<  +a[3] << " : " <<  +a[4] << " : " <<  +a[5] << std::endl;
        if(rc != 6 || s.size() != last)
            throw ("invalid mac address format " + s);
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

main()
{
	std::cout << "return with :" << string_to_mac("b0:18:86:04:4E:55") << std::endl;
	std::cout << "return without :" << string_to_mac("b01886044E55") << std::endl;
}
