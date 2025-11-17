#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    if (argc < 2){
        printf("ERROR: not engough args");
        return 1;
    }

    // Declare the buffer to use. Do NOT change!
    enum { BUFSIZE = 8 };
    char buffer[BUFSIZE];

    int upper = 0;
    int lower = 0;
    int number = 0;
    int space = 0;
    int other = 0;
    
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1){
        perror("Error opening file");
        return 1;
    }

    ssize_t bytesRead;

    while ((bytesRead = read(fd, buffer, BUFSIZE)) > 0){
        
        for (int i = 0; i < bytesRead; i++){
            unsigned char c = buffer[i];

            if (isupper(c)){
                upper++;
            }
            else if (islower(c)){
                lower++;
            }
            else if (isdigit(c)){
                number++;
            }
            else if (isspace(c)){
                space++;
            }
            else{
                other++;
            }
        }

        if (bytesRead == -1){
            perror("Error reading the file");
            close(fd);
            return 1;
        }
        
    }

    close(fd);

    printf("Upper,%d\nLower,%d\nNumber,%d\nSpace,%d\nOther,%d\n", upper, lower, number, space, other);

    return 0;
}
