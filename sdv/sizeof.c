#include "stdio.h"

#if 0
struct A{
  int i;
  char c;
};

struct A obj;

int main()
{
  struct A *ptr = &obj;
  struct A *ptr2 = ptr+1;
  printf("size = %ld\n", (char *)ptr2-(char*)ptr);
}
#else

int main()
{
	double a = 2.5, b = 2.4;
	printf("%lf %lf\n", a, b);
	
	if(a == 2.5) printf("Yes\n"); else printf("No\n");
	if(b == 2.4) printf("Yes\n"); else printf("No\n");
}

#endif

