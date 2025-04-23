#include<stdio.h>

main()
{
  int arr[5]; int(*parr)[5];
  parr = &arr;

 printf("%d\n", sizeof(*parr));
 printf("%d\n", sizeof(**parr));
}
