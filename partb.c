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
    
    int fd = open ("partb_file1_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0770);
    if (fd == -1){
        perror("Error opening file");
        return 1;
    }

    dup2(fd, STDOUT_FILENO);
    printf("Category,Count\n");
    fflush(stdout);

    int eret = execv("./parta", argv);
    
    return 0;
}
