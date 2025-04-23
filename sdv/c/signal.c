#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int childExitStatus;
    bool wait = true;
	int pid = 363;
    if(pid)
    {
        printf("%d\n", kill(pid, SIGTERM));

        while(true == wait)
        {
            printf("Waiting %d\n", pid);
            pid_t pid_stat = waitpid( pid, &childExitStatus, WNOHANG | WUNTRACED);
            printf("Status = %d %d %d %d\n", WEXITSTATUS(childExitStatus), WIFEXITED(childExitStatus), WIFSIGNALED(childExitStatus), WTERMSIG(childExitStatus));
            if(pid_stat == -1)
            {
                printf("bridge process still alive pid = %d childExitStatus = %d\n", pid, childExitStatus);
            }
            else if (pid_stat == pid)
            {
                printf("waitpid() exited with Status= %d %d\n", WEXITSTATUS(childExitStatus), childExitStatus);
                wait = false;
                break;
            }
            printf("%d\n", kill(pid, SIGTERM));
            sleep(1);
        }
    }
    return 0;
}