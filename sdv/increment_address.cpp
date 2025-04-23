
#include<arpa/inet.h>
#if 0
#include<stdio.h>
char* increment_address(const char* address_string)
{
    // convert the input IP address to an integer
    in_addr_t address = inet_addr(address_string);

    printf("increment_address1 = %d\n", address);
    // add one to the value (making sure to get the correct byte orders)
    address = ntohl(address);
    printf("increment_address2 = %d\n", address);
    address += 1;
    printf("increment_address3 = %d\n", address);
    address = htonl(address);
    printf("increment_address4 = %d\n", address);
    // pack the address into the struct inet_ntoa expects
    struct in_addr address_struct;
    address_struct.s_addr = address;

    // convert back to a string
    return inet_ntoa(address_struct);
}

main()
{
    char *address = "10.11.12.13";
	
	printf("%s\n", increment_address(address));
}

#else
#include<iostream>
std::string increment_address(std::string address_string)
{
    // convert the input IP address to an integer
    in_addr_t address = inet_addr((char *)address_string.c_str());

    printf("increment_address1 = %d\n", address);
    // add one to the value (making sure to get the correct byte orders)
    address = ntohl(address);
    printf("increment_address2 = %d\n", address);
    address += 1;
    printf("increment_address3 = %d\n", address);
    address = htonl(address);
    printf("increment_address4 = %d\n", address);
    // pack the address into the struct inet_ntoa expects
    struct in_addr address_struct;
    address_struct.s_addr = address;

    // convert back to a string
    return inet_ntoa(address_struct);
}

int main()
{
    std::string address = "10.11.12.13";
    std::string& oSlot = address;

    for(int i = 0; i < 11; i++)
    {
	  oSlot = increment_address(oSlot);
	  std::cout << "inc " << oSlot << std::endl;
	}
}
#endif