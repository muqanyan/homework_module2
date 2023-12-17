#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

using namespace std;
int main() 
{
    pid_t childPID = fork();

    if (childPID == -1) 
    {
        perror("Ошибка во время fork");
        exit(EXIT_FAILURE);
    }

    if (childPID == 0) 
    { 
        sleep(2); 
        pid_t parentPID = getppid();

        cout << "Дочерний процесс, пытающийся завершить работу своего родительского (PID: " << parentPID << ")" << endl;

        if (kill(parentPID, SIGTERM) == 0) 
        {
            cout << "Сигнал отправлен успешно." << endl;
        } else 
        {
            perror("Сигнал отправки ошибки");
        }

        exit(EXIT_SUCCESS);
    } 
    else 
    { 
        cout << "Родительский процесс (PID: " << getpid() << ") созданный дочерний процесс (PID: " << childPID << ")." << endl;
        cout << "Родительский процесс продолжает выполняться." << endl;

        for (int i = 0; i < 10; ++i) 
        {
            cout << "Родительский процесс работает..." << endl;
            sleep(1);
        }

        cout << "Родительский процесс завершил выполнение." << endl;
    }

    return 0;
}

