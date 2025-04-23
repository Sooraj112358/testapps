#include <stdio.h>
#include <stdlib.h>
//#include <sys/resource.h>

//int who = RUSAGE_SELF;
//struct rusage usage;
//int ret;

void getMemory() {


    int currRealMem; int peakRealMem;
    int currVirtMem; int peakVirtMem;
    // stores each word in status file
    char buffer[1024] = "";

    // linux file contains this-process info
    FILE* file = fopen("/proc/self/status", "r");

    // read the entire file
    while (fscanf(file, " %1023s", buffer) == 1) {

        if (strcmp(buffer, "VmRSS:") == 0) {
            fscanf(file, " %d", &currRealMem);
        }
        if (strcmp(buffer, "VmHWM:") == 0) {
            fscanf(file, " %d", &peakRealMem);
        }
        if (strcmp(buffer, "VmSize:") == 0) {
            fscanf(file, " %d", &currVirtMem);
        }
        if (strcmp(buffer, "VmPeak:") == 0) {
            fscanf(file, " %d", &peakVirtMem);
        }
    }
	printf("%d %d %d %d\n", currRealMem, peakRealMem, currVirtMem, peakVirtMem);
    fclose(file);
}


int main()
{
while(1)
{
//ret = getrusage(who, &usage);
//printf("Mem usage = %ld %ld %ld %ld\n", usage.ru_maxrss, usage.ru_ixrss, usage.ru_idrss, usage.ru_isrss);
getMemory();
void *ptr = malloc(11*1024*1024);
sleep(1);
}
return 0;
}
