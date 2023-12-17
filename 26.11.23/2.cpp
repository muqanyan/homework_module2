#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() 
{
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1) 
    {
        perror("pipe");
        return 1;
    }

    pid_t child_pid = fork();

    if (child_pid == -1) 
    {
        perror("fork");
        return 1;
    }

    if (child_pid == 0) 
    { 
        close(pipe_fd[1]); 

        dup2(pipe_fd[0], STDIN_FILENO);

        close(pipe_fd[0]);

        execlp("wc", "wc", "-l", nullptr);

        perror("execlp");
        return 1;
    } 
    else 
    { 
        close(pipe_fd[0]); 

        dup2(pipe_fd[1], STDOUT_FILENO);

        close(pipe_fd[1]);

        execlp("ls", "ls", nullptr);

        perror("execlp");
        return 1;
    }

    return 0;
}

