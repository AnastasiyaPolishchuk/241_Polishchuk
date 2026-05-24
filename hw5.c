#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        int pipefd[2];
        
        if (pipe(pipefd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        
        if (pid == 0) {
            close(pipefd[0]);
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[1]);
            
            char *cmd_copy = strdup(argv[i]);
            char *args[64];
            int idx = 0;
            char *token = strtok(cmd_copy, " ");
            while (token != NULL && idx < 63) {
                args[idx++] = token;
                token = strtok(NULL, " ");
            }
            args[idx] = NULL;
            
            execvp(args[0], args);
            exit(EXIT_FAILURE);
        }

        close(pipefd[1]);
        
        char buffer[4096];
        ssize_t bytes;
        int total = 0;
        
        while ((bytes = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
            total += bytes;
        }
        
        close(pipefd[0]);
        waitpid(pid, NULL, 0);
        
        printf("%d\n", total);
        fflush(stdout);
    }
    
    return 0;
}