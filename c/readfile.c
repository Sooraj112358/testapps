#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

main()
{
    int cnt = 0;
    DIR *dirp = NULL;
    struct dirent *dp =NULL;

    dirp = opendir("/dev/");

    while (dirp) {
        if ((dp = readdir(dirp)) != NULL) {
            if (strstr(dp->d_name, "uio")) {
                cnt++;
            }
        } else {
            closedir(dirp);
            goto err;
        }
    }
err:
    printf("devcnt=%d\n", cnt);
    return 0;
}

