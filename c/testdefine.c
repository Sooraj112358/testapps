#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>

typedef struct {
    ssize_t         shmem_size;
    int8_t          mode;
}shmem_config;

#define LGIVC_IOCTL_BASE                              'G'
#define LGIVC_IORW(n, t)                              _IOWR(LGIVC_IOCTL_BASE, n, t)
#define LGIVC_IOW(n, t)                               _IOW(LGIVC_IOCTL_BASE, n, t)
#define LGIVC_IOR(n, t)                               _IOR(LGIVC_IOCTL_BASE, n, t)

/** Ioctls*
#define LGIVC_IOCTL_READ_STATUS                       LGIVC_IOR(0x2,  int32_t)
#define LGIVC_IOCTL_ATTACH_SHMEM                      LGIVC_IOW(0x4,  shmem_config)
#define LGIVC_IOCTL_DETACH_SHMEM                      LGIVC_IOW(0x8,  int32_t)
#define LGIVC_IOCTL_GET_BYTES_AVAILABLE_FOR_READ      LGIVC_IOR(0x10, int32_t)
#define LGIVC_IOCTL_GET_CLIENTS_ATTACHED              LGIVC_IOR(0x20, int32_t)
#define LGIVC_IOCTL_NOTIFY_READERS                    LGIVC_IOW(0x40, int32_t)
#define LGIVC_IOCTL_NOTIFY_WRITERS                    LGIVC_IOW(0x80, int32_t)
#define LGIVC_IOCTL_ACKNOWLEDGE_READ                  LGIVC_IOW(0x100, int32_t)
#define LGIVC_IOCTL_INCREMENT_CLIENT_COUNT            LGIVC_IOW(0x200, int32_t)
#define LGIVC_IOCTL_DECREMENT_CLIENT_COUNT            LGIVC_IOW(0x400, int32_t)
*/
#define LGIVC_IOCTL_READ_STATUS                       LGIVC_IOR(0x1,  int32_t)
#define LGIVC_IOCTL_ATTACH_SHMEM                      LGIVC_IOW(0x2,  shmem_config)
#define LGIVC_IOCTL_DETACH_SHMEM                      LGIVC_IOW(0x3,  int32_t)
#define LGIVC_IOCTL_GET_BYTES_AVAILABLE_FOR_READ      LGIVC_IOR(0x4, int32_t)
#define LGIVC_IOCTL_GET_CLIENTS_ATTACHED              LGIVC_IOR(0x5, int32_t)
#define LGIVC_IOCTL_NOTIFY_READERS                    LGIVC_IOW(0x6, int32_t)
#define LGIVC_IOCTL_NOTIFY_WRITERS                    LGIVC_IOW(0x7, int32_t)
#define LGIVC_IOCTL_ACKNOWLEDGE_READ                  LGIVC_IOW(0x8, int32_t)
#define LGIVC_IOCTL_INCREMENT_CLIENT_COUNT            LGIVC_IOW(0x9, int32_t)
#define LGIVC_IOCTL_DECREMENT_CLIENT_COUNT            LGIVC_IOW(0x10, int32_t)

int main()
{
    printf("LGIVC_IOCTL_READ_STATUS=%ld\n", LGIVC_IOCTL_READ_STATUS);
    printf("LGIVC_IOCTL_ATTACH_SHMEM=%ld\n", LGIVC_IOCTL_ATTACH_SHMEM);
    printf("LGIVC_IOCTL_DETACH_SHMEM=%ld\n", LGIVC_IOCTL_DETACH_SHMEM);
    printf("LGIVC_IOCTL_GET_BYTES_AVAILABLE_FOR_READ=%ld\n", LGIVC_IOCTL_GET_BYTES_AVAILABLE_FOR_READ);
    printf("LGIVC_IOCTL_GET_CLIENTS_ATTACHED=%ld\n", LGIVC_IOCTL_GET_CLIENTS_ATTACHED);
    printf("LGIVC_IOCTL_NOTIFY_READERS=%ld\n", LGIVC_IOCTL_NOTIFY_READERS);
    printf("LGIVC_IOCTL_NOTIFY_WRITERS=%ld\n", LGIVC_IOCTL_NOTIFY_WRITERS);
    printf("LGIVC_IOCTL_ACKNOWLEDGE_READ=%ld\n", LGIVC_IOCTL_ACKNOWLEDGE_READ);
    printf("LGIVC_IOCTL_INCREMENT_CLIENT_COUNT=%ld\n", LGIVC_IOCTL_INCREMENT_CLIENT_COUNT);
    printf("LGIVC_IOCTL_DECREMENT_CLIENT_COUNT=%ld\n", LGIVC_IOCTL_DECREMENT_CLIENT_COUNT);

    return 0;
}
