#include <iostream>
#include <csignal>
#include <unistd.h>

using namespace std;
void sigusr1Handler(int sig) 
{
    pid_t sendingPID = getpid();

    cout << "Received SIGUSR1 signal:" << endl;
    cout << "Sending Process PID: " << sendingPID << endl;
    cout << "EIP: (not available)" << endl;
    cout << "EAX: (not available)" << endl;
    cout << "EBX: (not available)" << endl;
}

int main() 
{
    pid_t myPID = getpid();
    cout << "My PID: " << myPID << std::endl;
    
    signal(SIGUSR1, sigusr1Handler);

    while (true) 
    {
        sleep(10);
    }

    return 0;
}

