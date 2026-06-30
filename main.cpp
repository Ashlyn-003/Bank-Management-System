#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class BankAccount
{
private:
    int accountNumber;
    char name[50];
    float balance;

public:
    void createAccount();
    void showAccount() const;
    void deposit(float);
    void withdraw(float);
    int getAccountNumber() const;
    float getBalance() const;
    void updateBalance(float);
};

void BankAccount::createAccount()
{
    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    cin.ignore();
    cout << "Enter Customer Name: ";
    cin.getline(name, 50);

    cout << "Enter Initial Deposit: ";
    cin >> balance;
}

void BankAccount::showAccount() const
{
    cout << "\n-----------------------------";
    cout << "\nAccount Number : " << accountNumber;
    cout << "\nCustomer Name  : " << name;
    cout << "\nBalance        : Rs. " << balance;
    cout << "\n-----------------------------\n";
}

void BankAccount::deposit(float amount)
{
    balance += amount;
}

void BankAccount::withdraw(float amount)
{
    if (amount <= balance)
    {
        balance -= amount;
        cout << "\nWithdrawal Successful.\n";
    }
    else
    {
        cout << "\nInsufficient Balance!\n";
    }
}

int BankAccount::getAccountNumber() const
{
    return accountNumber;
}

float BankAccount::getBalance() const
{
    return balance;
}

void BankAccount::updateBalance(float amount)
{
    balance = amount;
}

// Create Account
void createNewAccount()
{
    BankAccount acc;

    ofstream file("bank.dat", ios::binary | ios::app);

    acc.createAccount();

    file.write((char *)&acc, sizeof(acc));

    file.close();

    cout << "\nAccount Created Successfully!\n";
}

// Display Account
void displayAccount(int accNo)
{
    BankAccount acc;
    bool found = false;

    ifstream file("bank.dat", ios::binary);

    while (file.read((char *)&acc, sizeof(acc)))
    {
        if (acc.getAccountNumber() == accNo)
        {
            acc.showAccount();
            found = true;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

// Deposit Money
void depositMoney(int accNo)
{
    BankAccount acc;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    bool found = false;
    float amount;

    while (file.read((char *)&acc, sizeof(acc)))
    {
        if (acc.getAccountNumber() == accNo)
        {
            cout << "Enter Amount to Deposit: ";
            cin >> amount;

            acc.deposit(amount);

            int pos = -1 * sizeof(acc);

            file.seekp(pos, ios::cur);
            file.write((char *)&acc, sizeof(acc));

            cout << "\nAmount Deposited Successfully!\n";
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

// Withdraw Money
void withdrawMoney(int accNo)
{
    BankAccount acc;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    bool found = false;
    float amount;

    while (file.read((char *)&acc, sizeof(acc)))
    {
        if (acc.getAccountNumber() == accNo)
        {
            cout << "Enter Amount to Withdraw: ";
            cin >> amount;

            acc.withdraw(amount);

            int pos = -1 * sizeof(acc);

            file.seekp(pos, ios::cur);
            file.write((char *)&acc, sizeof(acc));

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

// Check Balance
void checkBalance(int accNo)
{
    BankAccount acc;
    bool found = false;

    ifstream file("bank.dat", ios::binary);

    while (file.read((char *)&acc, sizeof(acc)))
    {
        if (acc.getAccountNumber() == accNo)
        {
            cout << "\nCurrent Balance: Rs. " << acc.getBalance() << endl;
            found = true;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

int main()
{
    int choice, accountNo;

    while (true)
    {
        cout << "\n========== BANK MANAGEMENT SYSTEM ==========\n";
        cout << "1. Create New Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. View Account Details\n";
        cout << "6. Exit\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createNewAccount();
            break;

        case 2:
            cout << "Enter Account Number: ";
            cin >> accountNo;
            depositMoney(accountNo);
            break;

        case 3:
            cout << "Enter Account Number: ";
            cin >> accountNo;
            withdrawMoney(accountNo);
            break;

        case 4:
            cout << "Enter Account Number: ";
            cin >> accountNo;
            checkBalance(accountNo);
            break;

        case 5:
            cout << "Enter Account Number: ";
            cin >> accountNo;
            displayAccount(accountNo);
            break;

        case 6:
            cout << "\nThank you for using Bank Management System.\n";
            return 0;

        default:
            cout << "\nInvalid Choice!\n";
        }
    }

    return 0;
}