#include <iostream>
#include <cstdlib>
#include <cmath>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std;

int main() 
{
    int numberToCheck;
    cout << "Введите число для проверки на простоту:";
    cin >> numberToCheck;

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

    bool isPrime = (numberToCheck <= sqrt(shmid / sizeof(int))) && (sharedMemory[numberToCheck] == 0);

    shmdt(sharedMemory);

    if (isPrime) {
        cout << "Да, " << numberToCheck << " является простым." << endl;
    } 
    else 
    {
        cout << "Нет, " << numberToCheck << " это не простое число." << endl;
    }

    return 0;
}

