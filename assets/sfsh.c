// A shell, in one big file

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define ARGS_LEN 4096
#define CWD_LEN 4096

void print_prompt();
void get_args(char* line, char** args);
void free_args(char** args);

int is_cd(char* command);
int change_directory(char** args);

char *cwd = NULL;

int main(int argc, char* argv) {

    char *args[ARGS_LEN];
    char *command = NULL;
    char *line = NULL;
    size_t line_len = 0;


    while(1) {
        print_prompt();
        if(getline(&line, &line_len, stdin) < 0) {
            exit(0);
        }

        get_args(line, args);
        command = args[0];
        if( command == NULL ) {
            continue;
        }

        // Is it cd? 
        if(is_cd(command)) {
            change_directory(args);
            continue;
        }

        pid_t rv = fork();
        if(rv == 0) {
            // I am child
            // beep boop subshell environment
            
            execvp(command, args);

            perror("execvp");
            exit(1);
        } else if( rv > 0 ) {
            // I am parent
            
            wait(NULL); // Wait for child process to terminate
        } else {
            perror("fork");
        }

        free_args(args);
    }
}

// Print current working directory, and
// $ for normal user
// # for root 
// (don't use this program as root please)
void print_prompt() {

    if( cwd == NULL ) {
        cwd = malloc(CWD_LEN);
        assert(cwd);
    }

    if(getcwd(cwd, CWD_LEN) == NULL) {
        perror("getcwd");
        exit(1);
    }

    printf("%s %c ", cwd, getuid() == 0 ? '#' : '$');

    return;
}

size_t get_arg_len(char* line) {
    size_t i = 0;
    while(line[i] && line[i] != ' ' && line[i] != '\n')
        i++;

    return i;
}

size_t count_leading_spaces(char* line) {
    int i = 0;
    while( line[i] == ' ' )
        ++i;

    return i;
}

void get_args(char* line, char** args) {
    size_t args_i = 0;
    size_t arg_len = 0;

    line += count_leading_spaces(line);

    while( (arg_len = get_arg_len(line)) > 0) {
        args[args_i] = malloc(arg_len + 1);
        assert(args[args_i]);

        strncpy(args[args_i], line, arg_len);
        args[args_i][arg_len] = '\0';

        line += arg_len;
        ++args_i;

        line += count_leading_spaces(line);

        if( args_i == ARGS_LEN - 1) 
            break;
    }

    args[args_i] = NULL;

    return;
}

// Return true if command is cd, false otherwise
int is_cd(char* command) {
    if(strcmp(command, "cd") == 0) {
        return 1;
    } else {
        return 0;
    }
}

int change_directory(char** args ) {
    int rv = 0;
    if(args[1] == NULL) {
        rv = chdir(getenv("HOME"));
    } else {
        rv = chdir(args[1]);
    }

    return rv;
}

void free_args(char **args) {
    size_t i = 0;
    while( args[i] != NULL) {
        free(args[i++]);
    }

    return;
}
