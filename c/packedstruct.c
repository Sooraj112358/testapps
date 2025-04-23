#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>

typedef struct lgivc_bkm {
    ssize_t                                dataSize;
    uint32_t                               ackStatus;
    uint32_t                               attachedClients;
    uint32_t                               intendedClients;
    bool                                   dirty;
//}__attribute__((packed, aligned(8))) lgivc_bkm;
}lgivc_bkm;


int main()
{
    printf("sizeof=%d\n", sizeof(lgivc_bkm));
    sleep(11);
    return 0;
}
