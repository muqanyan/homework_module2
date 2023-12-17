#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() 
{
    int channel1[2], channel2[2];

    if (pipe(channel1) == -1 || pipe(channel2) == -1) 
    {
        perror("pipe");
        return 1;
    }

    pid_t child1 = fork();
    if (child1 == -1) 
    {
        perror("fork");
        return 1;
    }

    if (child1 == 0) 
    { 
        close(channel1[0]); 
        close(channel2[1]); 

        pid_t child1_pid = getpid();
        write(channel1[1], &child1_pid, sizeof(child1_pid));

        pid_t parent_pid;
        read(channel2[0], &parent_pid, sizeof(parent_pid));

        std::cout << "Дочерний процесс 1: Мой PID - " << child1_pid << ", PID родителя - " << parent_pid << std::endl;

        close(channel1[1]);
        close(channel2[0]);

        return 0;
    }

    pid_t child2 = fork();
    if (child2 == -1) 
    {
        perror("fork");
        return 1;
    }

    if (child2 == 0) 
    { 
        close(channel1[1]); 
        close(channel2[0]); 

        pid_t child2_pid = getpid();
        write(channel2[1], &child2_pid, sizeof(child2_pid));

        pid_t parent_pid;
        read(channel1[0], &parent_pid, sizeof(parent_pid));

        std::cout << "Дочерний процесс 2: Мой PID - " << child2_pid << ", PID родителя - " << parent_pid << std::endl;

        close(channel1[0]);
        close(channel2[1]);

        return 0;
    }

    close(channel1[1]); 
    close(channel2[0]); 

    waitpid(child1, nullptr, 0);
    waitpid(child2, nullptr, 0);

    close(channel1[0]);
    close(channel2[1]);

    return 0;
}

