#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

using namespace std;

void executeCommand(const char* cmd)
{
    system(cmd);
}


int main(int argc, char* argv[]) 
{
    if (argc < 4) 
    {
        cerr << "Использование: " << argv[0] << " команда 1 оператор команда 2" << endl;
        return 1;
    }

    const char* command1 = argv[1];
    const char* op = argv[2];
    const char* command2 = argv[3];

    if (strcmp(op, "&&") == 0)
    {
        int status;
        if (fork() == 0) 
	{
            executeCommand(command1);
            exit(0);
        }       
	else 
	{
            wait(&status);
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
	    {
                executeCommand(command2);
            }
        }
    }
    else if (strcmp(op, "||") == 0)
    {
        int status;
        if (fork() == 0)
       	{ 
            executeCommand(command1);
            exit(0);
        }
       	else
       	{
            wait(&status);
            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) 
	    { 
                executeCommand(command2);
            }
        }
    }
    else if (strcmp(op, ">") == 0)
    {
        int fd = open(command2, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        executeCommand(command1);
    } 
    else if (strcmp(op, ">>") == 0)
    {
        int fd = open(command2, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	dup2(fd, STDOUT_FILENO);
        close(fd);
        executeCommand(command1);
    } 
    else 
    {
        cerr << "Недопустимый оператор: " << op << endl;
        return 1;
    }

    return 0;
}
