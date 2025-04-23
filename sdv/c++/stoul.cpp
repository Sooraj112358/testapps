#include<iostream>

int main(int argc, char *argv[])
{
  uint64_t tgtDeviceCallerId = std::stoul(argv[1]);
  std::cout << "tgtDeviceCallerId: " << tgtDeviceCallerId << std::endl;
  return 0;
}
