#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int cwd() {
   char cwd[50];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd);
   } else {
       perror("getcwd() error");
       return 1;
   }
   return 0;
}

 int main(int argc, char *argv[])
 {
    int j;
	FILE *fp = NULL;
	char buf[11]= {0};

    
    //printf("%s\n",getenv("PWD"));
	//setenv("PWD", "/home/sooraj/test", 1);
    //printf("%s\n",getenv("PWD"));
	
	chdir(argv[1]);
	cwd();

    //printf("cwd:%s\n",getwd());
    for (j = 0; j < argc; j++)
        printf("argv[%d]: %s\n", j, argv[j]);

    fp = fopen("test.txt", "r");
	if(!fp)
	{
		printf("Failed to open\n");
		return 0;
	}
	fread(&buf, 11, 1, fp);
	
	printf("%s\n", buf);
	
    exit(EXIT_SUCCESS);
 }