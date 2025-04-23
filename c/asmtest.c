#include<stdio.h>
#include<stdint.h>

static uint64_t rdtscp(void)
{
    uint32_t rax, rdx, aux;
    asm volatile ( "rdtscp" : "=a" (rax), "=d" (rdx), "=c" (aux) : : );
    return ((uint64_t)rdx << 32U) | rax;
}

main()
{
    printf("ret=%d\n", rdtscp());
}
