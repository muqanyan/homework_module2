#include <iostream>
#include <cstdlib>
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

    if (shmctl(shmid, IPC_RMID, NULL) == -1) 
    {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    cout << "Сегмент общей памяти успешно удален." << endl;

    return 0;
}

