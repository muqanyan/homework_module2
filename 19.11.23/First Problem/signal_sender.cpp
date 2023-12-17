#include <iostream>
#include <csignal>
#include <cstdlib>
#include <unistd.h>

void signalHandler(int signalNumber) 
{
    
}

int main(int argc, char *argv[]) 
{
    if (argc != 3) 
    {
        std::cerr << "Usage: " << argv[0] << " <signal_number> <pid>" << std::endl;
        return 1;
    }

    int signalNumber = std::atoi(argv[1]);
    pid_t targetPID = std::atoi(argv[2]);

    if (kill(targetPID, signalNumber) == -1) 
    {
        perror("Error sending signal");
        return 1;
    }

    return 0;
}

