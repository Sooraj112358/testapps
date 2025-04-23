#include<stdio.h>

main()
{
char arr[] = "ABCD";
char *str = "ABCD";
//str[0] = 'E';
char *test;
test = arr;
test[0] = 'E';

printf("%s\n", arr);
}
