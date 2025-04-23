#include<stdio.h>

#define SIZE (8*1024 *1024)
func2()
{
  char buf[SIZE] = {0};
  printf("%s %d\n", __FUNCTION__, __LINE__);
}

func()
{
  printf("%s %d\n", __FUNCTION__, __LINE__);
  func2();
  printf("%s %d\n", __FUNCTION__, __LINE__);
}

main()
{
  printf("%s %d\n", __FUNCTION__, __LINE__);
    func();
  printf("%s %d\n", __FUNCTION__, __LINE__);
}
