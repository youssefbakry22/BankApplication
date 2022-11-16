#include "BankApplicationClass.h"
#include <iostream>
#include <fstream>
using namespace std;

int BankApplication::clientCount = 0;
int BankApplication::accountCount = 0;

BankAccount::BankAccount()
{
    accountId = "0000";
    balance = 0;
    accountType = "Bank Account";
}

BankAccount ::BankAccount(string accountId, double balance)
{
    this->accountId = accountId;
    this->balance = balance;
    this->accountType = "Basic Account";
}

void BankAccount ::setClient(Client *client)
{
    this->client = client;
}

void BankAccount ::setAccountId(string accountId)
{
    this->accountId = accountId;
}

void BankAccount ::setBalance(double balance)
{
    this->balance = balance;
}

string BankAccount ::getAccountId()
{
    return accountId;
}

double BankAccount ::getBalance()
{
    return balance;
}

string BankAccount ::getAccountType()
{
    return accountType;
}

void BankAccount ::deposit(double amount)
{
    balance += amount;
}

void BankAccount ::withdraw(double amount)
{
    balance -= amount;
}

BankAccount ::~BankAccount()
{
    delete client;
}

/*=======================================================================================================*/

SavingBankAccount ::SavingBankAccount()
{
    minimumBalance = 1000;
    accountType = "Saving Account";
}

SavingBankAccount ::SavingBankAccount(string accountId, double balance, double minimumBalance) : BankAccount(accountId, balance)
{
    this->minimumBalance = minimumBalance;
    this->accountType = "Saving Account";
}

void SavingBankAccount ::setMinimumBalance(double minimumBalance)
{
    if (minimumBalance >= 1000)
    {
        this->minimumBalance = minimumBalance;
    }
    else
    {
        cout << "Minimum balance must be greater than or equal to 1000" << endl;
    }
}

double SavingBankAccount ::getMinimumBalance()
{
    return minimumBalance;
}

void SavingBankAccount ::deposit(double amount)
{
    if (amount >= 100)
    {
        BankAccount::deposit(amount);
    }
    else
    {
        cout << "Minimum deposit amount must be greater than or equal to 100" << endl;
    }
}

/*=======================================================================================================*/

Client ::Client()
{
    name = "No Name";
    address = "No Address";
    phone = "No Phone";
}

Client ::Client(string name, string address, string phone)
{
    this->name = name;
    this->address = address;
    this->phone = phone;
}

void Client ::setAccount(BankAccount *account)
{
    this->account = account;
}

void Client ::setName(string name)
{
    this->name = name;
}

void Client ::setAddress(string address)
{
    this->address = address;
}

void Client ::setPhone(string phone)
{
    this->phone = phone;
}

string Client ::getName()
{
    return name;
}

string Client ::getAddress()
{
    return address;
}

string Client ::getPhone()
{
    return phone;
}

Client ::~Client()
{
    delete account;
}

/*=======================================================================================================*/

BankApplication ::BankApplication()
{
    for (int i = 0; i < 100; i++)
    {
        client[i] = NULL;
        account[i] = NULL;
    }
    loadClientsData();
    loadAccountsData();
    linkClientAccount();
}
void BankApplication::loadClientsData()
{
    // this function is used to load the clients data from the file
    ifstream fin;
    fin.open("clients.txt");
    if (fin.is_open())
    {
        string name, address, phone;
        while (getline(fin, name))
        {
            getline(fin, address);
            getline(fin, phone);
            client[clientCount] = new Client(name, address, phone);
            clientCount++;
        }
    }
    else
    {
        cout << "File not found" << endl;
    }
    fin.close();
}

void BankApplication::loadAccountsData()
{
    // this function is used to load the accounts data from the file
    ifstream fin;
    fin.open("accounts.txt");
    if (fin.is_open())
    {
        string accountId, accountType;
        double balance, minimumBalance;
        while (getline(fin, accountId))
        {
            getline(fin, accountType);
            fin >> balance;
            fin.ignore();
            if (accountType == "Basic Account")
            {
                account[accountCount] = new BankAccount(accountId, balance);
            }
            else if (accountType == "Saving Account")
            {
                fin >> minimumBalance;
                fin.ignore();
                account[accountCount] = new SavingBankAccount(accountId, balance, minimumBalance);
            }
            accountCount++;
        }
    }
    else
    {
        cout << "File not found" << endl;
    }
    fin.close();
}

void BankApplication::linkClientAccount()
{
    for (int i = 0; i < clientCount; i++)
    {
        client[i]->setAccount(account[i]);
        account[i]->setClient(client[i]);
    }
}

void BankApplication::run()
{
    cout << "\nWelcome to FCAI Banking Application" << endl;
    int choice;
    while (true)
    {
        displayMenu();
        cout << "\nEnter your choice: ";
        cin >> choice;
        if (choice == 1)
        {
            createAccount();
        }
        else if (choice == 2)
        {
            listClientsAndAccounts();
        }
        else if (choice == 3)
        {
            withdrawMoney();
        }
        else if (choice == 4)
        {
            depositMoney();
        }
        else if (choice == 5)
        {
            saveClientsData();
            saveAccountsData();
            exit(0);
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
    }
}

void BankApplication::displayMenu()
{
    cout << "\n1. Create a new account" << endl;
    cout << "2. List clients and accounts" << endl;
    cout << "3. Withdraw money" << endl;
    cout << "4. Deposit money" << endl;
    cout << "5. Exit" << endl;
}

void BankApplication::createAccount()
{
    // this function is used to create a new account
    string name, address, phone, accountId = "FCAI-" + to_string(accountCount);
    int accountType;
    double balance, minimumBalance;
    cout << "\nEnter the name of the client: ";
    cin >> name;
    cout << "Enter the address of the client: ";
    cin >> address;
    cout << "Enter the phone number of the client: ";
    cin >> phone;
    cout << "What type of account do you like? (1) Basic Account (2) Saving Account: ";
    cin >> accountType;
    cout << "Enter the starting balance: ";
    cin >> balance;

    if (accountType == 1)
    {
        account[accountCount] = new BankAccount(accountId, balance);
    }
    else if (accountType == 2)
    {
        cout << "Enter the minimum balance: ";
        cin >> minimumBalance;

        if (balance >= minimumBalance)
        {
            account[accountCount] = new SavingBankAccount(accountId, balance, minimumBalance);
        }
        else
        {
            cout << "The balance must be greater than or equal to the minimum balance" << endl;
            return; // return from the function and do not create the account
        }
    }

    client[clientCount] = new Client(name, address, phone);
    client[clientCount]->setAccount(account[accountCount]);
    account[accountCount]->setClient(client[clientCount]);
    clientCount++;
    accountCount++;
}

void BankApplication::listClientsAndAccounts()
{
    // this function is used to list all the clients and their accounts
    for (int i = 0; i < clientCount; i++)
    {
        cout << "------------------------" << client[i]->getName() << "------------------------" << endl;
        cout << "Address: " << client[i]->getAddress() << endl;
        cout << "Phone: " << client[i]->getPhone() << endl;
        // this crashes the program because the account is not set for the client yet
        cout << "Account ID: " << account[i]->getAccountId() << " (" << account[i]->getAccountType() << ')' << endl;
        cout << "Balance: " << account[i]->getBalance() << endl;
        cout << endl;
    }
}

void BankApplication::withdrawMoney()
{
    // this function is used to withdraw money from the account
    string accountId;
    double amount;
    cout << "Enter the account ID: ";
    cin >> accountId;

    for (int i = 0; i < accountCount; i++)
    {
        if (account[i]->getAccountId() == accountId)
        {
            cout << "Account ID: " << account[i]->getAccountId() << endl;
            cout << "Account Type: " << account[i]->getAccountType() << endl;
            cout << "Balance: " << account[i]->getBalance() << endl;

            if (account[i]->getAccountType() == "Basic Account")
            {
                while (true)
                {
                    cout << "\nEnter the amount to withdraw: ";
                    cin >> amount;
                    if (amount > account[i]->getBalance())
                    {
                        cout << "You can not withdraw more than the balance" << endl;
                    }
                    else
                    {
                        account[i]->withdraw(amount);
                        cout << "New balance: " << account[i]->getBalance() << endl;
                        break;
                    }
                }
            }
            else if (account[i]->getAccountType() == "Saving Account")
            {
                while (true)
                {
                    cout << "\nEnter the amount to withdraw: ";
                    cin >> amount;
                    if (account[i]->getBalance() - amount > dynamic_cast<SavingBankAccount *>(account[i])->getMinimumBalance()) // dynamic_cast is used to cast the base class pointer to the derived class pointer

                    {
                        account[i]->withdraw(amount);
                        cout << "New balance: " << account[i]->getBalance() << endl;
                        break;
                    }
                    else
                    {
                        cout << "You cannot withdraw this amount becuase the minimum balance" << endl;
                    }
                }
            }
            return;
        }
    }
    cout << "Account not found" << endl;
}

void BankApplication::depositMoney()
{
    // this function is used to withdraw money from the account
    string accountId;
    double amount;
    cout << "Enter the account ID: ";
    cin >> accountId;

    for (int i = 0; i < accountCount; i++)
    {
        if (account[i]->getAccountId() == accountId)
        {
            cout << "Account ID: " << account[i]->getAccountId() << endl;
            cout << "Account Type: " << account[i]->getAccountType() << endl;
            cout << "Balance: " << account[i]->getBalance() << endl;

            if (account[i]->getAccountType() == "Basic Account")
            {
                cout << "\nEnter the amount to deposit: ";
                cin >> amount;
                account[i]->deposit(amount);
                cout << "New balance: " << account[i]->getBalance() << endl;
            }
            else if (account[i]->getAccountType() == "Saving Account")
            {
                while (true)
                {
                    cout << "\nEnter the amount to deposit: ";
                    cin >> amount;
                    if (amount >= 100)
                    {
                        account[i]->deposit(amount);
                        cout << "New balance: " << account[i]->getBalance() << endl;
                        break;
                    }
                    else
                    {
                        cout << "You cannot deposit less than 100" << endl;
                    }
                }
            }
            return;
        }
    }
    cout << "Account not found" << endl;
}

void BankApplication::saveClientsData()
{
    // this function is used to save the clients data to a file
    ofstream file("clients.txt");
    for (int i = 0; i < clientCount; i++)
    {
        file << client[i]->getName() << endl;
        file << client[i]->getAddress() << endl;
        file << client[i]->getPhone() << endl;
    }
    file.close();
}

void BankApplication::saveAccountsData()
{
    // this function is used to save the accounts data to a file
    ofstream file("accounts.txt");
    for (int i = 0; i < accountCount; i++)
    {
        file << account[i]->getAccountId() << endl;
        file << account[i]->getAccountType() << endl;
        file << account[i]->getBalance() << endl;
        if (account[i]->getAccountType() == "Saving Account")
        {
            file << dynamic_cast<SavingBankAccount *>(account[i])->getMinimumBalance() << endl;
        }
    }
    file.close();
}

BankApplication::~BankApplication()
{
    // this function is used to delete the clients and accounts
    for (int i = 0; i < clientCount; i++)
    {
        delete client[i];
    }
    for (int i = 0; i < accountCount; i++)
    {
        delete account[i];
    }
}