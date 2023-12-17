#include <iostream>
#include <thread>
#include <atomic>

using namespace std;
class BankAccount 
{
public:
    BankAccount() : balance(0) {}

    void debit(int amount) 
    {
        while (lock.test_and_set(memory_order_acquire))
        balance -= amount;
        lock.clear(memory_order_release);
    }

    void credit(int amount) 
    {
        while (lock.test_and_set(memory_order_acquire))
        balance += amount;
        lock.clear(memory_order_release);
    }

    int getBalance() const 
    {
        return balance;
    }

private:
    int balance;
    atomic_flag lock = ATOMIC_FLAG_INIT;
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
    std::thread threads[numThreads];

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

