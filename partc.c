#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    
    if (argc < 2){
        printf("ERROR: not enough args");
        return 1;
    }

    int pipefd[2];
    if ( pipe(pipefd) == -1){
        perror("ERROR: pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid > 0){
        //parent

        close(pipefd[0]);

        int fd = dup2(pipefd[1], STDOUT_FILENO);
        if (fd == -1){
            perror("ERROR: dup2 parent");
            close(pipefd[0]);
            return 1;
        }

        close(pipefd[1]);

        execv("./parta", argv);
        perror("ERROR: execv ./parta");
        return 1;
    }
    else if(pid == 0){
        //child

        close(pipefd[1]);

        int fd = dup2(pipefd[0], STDIN_FILENO);
        if (fd == -1){
            perror("ERROR: dup2 child");
            return 1;
        }

        close(pipefd[0]);

        char *args[] = {"sort", "-t", "-k2", "-n"};

        execv("sort", args);
        perror("ERROR: execv sort");
        return 1;

    }
    else{
        printf("ERROR: Child process didn't execute properly\n");
        return 1;
    }

    return 0;
}
