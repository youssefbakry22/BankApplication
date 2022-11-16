#ifndef BANKAPPLICATIONCLASS_H
#define BANKAPPLICATIONCLASS_H
#include <iostream>
using namespace std;

class Client;

class BankAccount
{
protected:
    string accountId;
    double balance;
    string accountType;
    Client *client;

public:
    BankAccount();
    BankAccount(string accountId, double balance);
    void setClient(Client *client);
    void setAccountId(string accountId);
    void setBalance(double balance);
    string getAccountId();
    double getBalance();
    string getAccountType();
    void withdraw(double amount);
    virtual void deposit(double amount);
    ~BankAccount();
};

/*=======================================================================================================*/

class SavingBankAccount : public BankAccount
{
private:
    double minimumBalance;

public:
    SavingBankAccount();
    SavingBankAccount(string accountId, double balance, double minimumBalance = 1000);
    void setMinimumBalance(double minimumBalance);
    double getMinimumBalance();
    void deposit(double amount);
    ~SavingBankAccount();
};

/*=======================================================================================================*/

class Client
{
private:
    string name;
    string address;
    string phone;
    BankAccount *account;

public:
    Client();
    Client(string name, string address, string phone);
    void setAccount(BankAccount *account);
    void setName(string name);
    void setAddress(string address);
    void setPhone(string phone);
    string getName();
    string getAddress();
    string getPhone();
    ~Client();
};

/*=======================================================================================================*/

class BankApplication
{
private:
    Client *client[100];
    BankAccount *account[100];

public:
    static int clientCount;
    static int accountCount;
    BankApplication();
    void loadClientsData();
    void loadAccountsData();
    void linkClientAccount();
    void createAccount();
    void listClientsAndAccounts();
    void withdrawMoney();
    void depositMoney();
    void saveClientsData();
    void saveAccountsData();
    void displayMenu();
    void run();
    ~BankApplication();
};

#endif // BANKAPPLICATIONCLASS_H