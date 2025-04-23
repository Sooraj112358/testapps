#include<stdio.h>
#include<stdint.h>

void f2(void** a){
  printf("f2(a) address = %p \n",a);
  printf("f2(a) address = %d \n",**(int**)a);
  memset(a, 0x0, 1);
}


void f1(void** a){
  printf("f1(a) address = %p \n",a);
  *a = (void*)(int*)malloc(sizeof(int));

  printf("a address = %p \n",a);
  **(int**)a = 3;

  printf("data = %d\n",**(int**)a);
}

void f(void){
  void *a1;
  printf("a1 address = %p \n",a1);

  f1(&a1);

  printf("a1 address = %p \n",&a1);
  printf("Data.a1 = %d\n",*(int*)a1);
  f2(&a1);
  printf("Data.a1 = %d\n",*(int*)a1);
}

main()
{
  f();
}
