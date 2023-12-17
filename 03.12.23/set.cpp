#include <iostream>
#include <cstdlib>
#include <cmath>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std;

int main() 
{
    key_t key = ftok("/tmp", 'A');
    int shmid = shmget(key, 0, 0);

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

    int n = sqrt(shmid / sizeof(int));
    for (int i = 2; i <= n; ++i) 
    {
        if (sharedMemory[i] == 0) 
        {
            for (int j = i * i; j <= n; j += i) 
            {
                sharedMemory[j] = 1;
            }
        }
    }

    shmdt(sharedMemory);

    cout << "Решето Эратосфена, построенное успешно." << endl;

    return 0;
}

