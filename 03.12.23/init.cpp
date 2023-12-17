#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std;

int main() 
{
    const int sharedMemorySize = 1024; 
    key_t key = ftok("/tmp", 'A');
    int shmid = shmget(key, sharedMemorySize, IPC_CREAT | 0666);
    if (shmid == -1) 
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    int *sharedMemory = (int*)shmat(shmid, NULL, 0);
    if (sharedMemory == (int*)-1) 
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    memset(sharedMemory, 0, sharedMemorySize);
    shmdt(sharedMemory);

    cout << "Общая память успешно инициализирована." << endl;

    return 0;
}

