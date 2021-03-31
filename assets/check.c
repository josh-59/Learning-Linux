#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

/*
processes.html#process-creation
 */
int main() {
        pid_t rv = fork();      // One process executes this line
        if(rv == 0) {           // Two processes execute this line
            printf("Child proc PID = %zu\n", getpid());
        } else if (rv > 0) {
            printf("Parent proc PID = %zu\n", getpid());
        }

        return 0;
}

/*
processes.html#file-descriptors

int main() {
    int fd = open("./rubber_ducky", O_RDONLY);
    printf("fd = %d\n", fd);

    if( fd == -1 ) {
        perror("open");
        exit(1);
    }

    int buff_size = 4096;
    char *buff = malloc(buff_size);
    if( buff == NULL ) {
        perror("malloc");
        exit(2);
    }

    int num_bytes_read = read(fd, buff, buff_size);
    printf("num_bytes_read = %zu\n", num_bytes_read);

    return 0;
}
*/


/*
processes.html#executing-a-different-program

int main() {
    pid_t rv = fork();
    if( rv == 0 ) {
        char *args[] = {"ls", "-l", NULL};
        execv("/bin/ls", args);
        
        perror("execv"); // These lines are only executed if execv failed
        exit(1);
    } else if ( rv > 0 ) {
        wait(NULL);
        printf("Child process %zu exited!\n", (unsigned long) rv);
    } 
}
*/
