#include <stdio.h>
int main() {
    FILE *fp;
    char path[1035];

    fp = popen("ls", "r");
    if (fp == NULL) {
        perror("Failed to run command");
        return 1;
    }

    while (fgets(path, sizeof(path), fp) != NULL) {
        printf("%s", path);
    }

    fclose(fp);
    return 0;
}

