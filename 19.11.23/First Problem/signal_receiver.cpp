#include <iostream>
#include <csignal>
#include <unistd.h>

volatile sig_atomic_t usr2Count = 0;

void signalHandler(int signalNumber) 
{
    if (signalNumber == SIGUSR2) 
    {
        ++usr2Count;
    } 
    else if (signalNumber == SIGINT) 
    {
        std::cout << "Total number of SIGUSR2 signals received: " << usr2Count << std::endl;
        exit(0);
    }
}


int main() 
{
    signal(SIGUSR1, SIG_IGN); 
    signal(SIGUSR2, signalHandler);
    signal(SIGINT, signalHandler);

    while (true) 
    {
        std::cout << "I am still alive!!" << std::endl;
        sleep(5);
    }

    return 0;
}

