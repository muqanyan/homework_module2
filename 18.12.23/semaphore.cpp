#include <iostream>
#include <thread>
#include <semaphore.h>

using namespace std;
class BankAccount 
{
public:
    BankAccount() : balance(0) 
    {
        sem_init(&mutex, 0, 1); 
    }

    void debit(int amount) 
    {
        sem_wait(&mutex);
        balance -= amount;
        sem_post(&mutex);
    }

    void credit(int amount) 
    {
        sem_wait(&mutex);
        balance += amount;
        sem_post(&mutex);
    }

    int getBalance() const 
    {
        return balance;
    }

private:
    int balance;
    sem_t mutex;
};

void conductTransaction(BankAccount& account, int amount, bool isDebit) 
{
    if (isDebit) 
    {
        account.debit(amount);
    } 
    else 
    {
        account.credit(amount);
    }
}

int main() 
{
    BankAccount account;

    const int numThreads = 10;
    thread threads[numThreads];

    for (int i = 0; i < numThreads; ++i) 
    {
        threads[i] = thread(conductTransaction, ref(account), 100, i % 2 == 0);
    }

    for (int i = 0; i < numThreads; ++i) 
    {
        threads[i].join();
    }

    cout << "Final Balance: " << account.getBalance() << endl;
    return 0;
}

