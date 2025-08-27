#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Transaction Class
class Transaction {
public:
    string type;   // Deposit, Withdraw, Transfer
    double amount;
    string details;

    Transaction(string t, double a, string d) {
        type = t;
        amount = a;
        details = d;
    }

    void display() const {
        cout << type << " | Amount: " << amount << " | " << details << endl;
    }
};

// Account Class
class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> history;

public:
    Account(int accNo, double initialBalance = 0.0) {
        accountNumber = accNo;
        balance = initialBalance;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
        history.push_back(Transaction("Deposit", amount, "Money deposited"));
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient Balance!" << endl;
            return false;
        }
        balance -= amount;
        history.push_back(Transaction("Withdraw", amount, "Money withdrawn"));
        return true;
    }

    bool transfer(Account& toAccount, double amount) {
        if (withdraw(amount)) {
            toAccount.deposit(amount);
            history.push_back(Transaction("Transfer", amount, "Transferred to A/C " + to_string(toAccount.getAccountNumber())));
            return true;
        }
        return false;
    }

    void showTransactions() const {
        cout << "Transaction History for A/C " << accountNumber << ":\n";
        for (auto& t : history) {
            t.display();
        }
    }

    void displayInfo() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: " << balance << endl;
    }
};

// Customer Class
class Customer {
private:
    string name;
    int customerId;
    vector<Account> accounts;

public:
    Customer(int id, string n) {
        customerId = id;
        name = n;
    }

    void addAccount(int accNo, double initialBalance = 0.0) {
        accounts.push_back(Account(accNo, initialBalance));
    }

    Account* getAccount(int accNo) {
        for (auto& acc : accounts) {
            if (acc.getAccountNumber() == accNo) {
                return &acc;
            }
        }
        return nullptr;
    }

    void displayCustomer() {
        cout << "Customer ID: " << customerId << " | Name: " << name << endl;
        cout << "Accounts:\n";
        for (auto& acc : accounts) {
            acc.displayInfo();
        }
    }
};

// Main Function
int main() {
    // Create Customers
    Customer c1(101, "Qasim");
    c1.addAccount(1001, 5000);

    Customer c2(102, "Ali");
    c2.addAccount(1002, 3000);

    // Access Accounts
    Account* acc1 = c1.getAccount(1001);
    Account* acc2 = c2.getAccount(1002);

    // Transactions
    if (acc1) acc1->deposit(2000);
    if (acc1) acc1->withdraw(1500);
    if (acc1 && acc2) acc1->transfer(*acc2, 1000);

    // Display Information
    cout << "\n--- Customer Details ---\n";
    c1.displayCustomer();
    c2.displayCustomer();

    cout << "\n--- Transaction History ---\n";
    if (acc1) acc1->showTransactions();
    if (acc2) acc2->showTransactions();

    return 0;
}


