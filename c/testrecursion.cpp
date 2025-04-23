#include<stdio.h>

unsigned long long calculate(unsigned long long n) {
        unsigned long long ret;
        const unsigned int M = 1000000007;
        if(n == 1)
            return 1;
        ret =  (n * calculate(n-1)) % M;
        return ret;
}

main()
{
    printf("calculate:%d\n", calculate(3*2));
}
