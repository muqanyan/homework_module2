#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
class BankAccount 
{
public:
    BankAccount() : balance(0) {}

    void debit(int amount) 
    {
        lock_guard<mutex> lock(account_mutex);
        balance -= amount;
    }

    void credit(int amount) 
    {
        lock_guard<mutex> lock(account_mutex);
        balance += amount;
    }

    int getBalance() const 
    {
        return balance;
    }

private:
    int balance;
    mutex account_mutex;
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

    cout << "Окончательный баланс: " << account.getBalance() << endl;
    return 0;
}

