#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Transaction Class
class Transaction {
public:
    string type;    // deposit, withdraw, transfer
    double amount;
    string details;

    Transaction(string t, double a, string d) {
        type = t;
        amount = a;
        details = d;
    }

    void display() const {
        cout << type << " of " << amount << " | " << details << endl;
    }
};

// Account Class
class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accNo, double initialBalance = 0.0) {
        accountNumber = accNo;
        balance = initialBalance;
    }

    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount, "Amount credited"));
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            transactions.push_back(Transaction("Withdrawal", amount, "Amount debited"));
        }
        else {
            cout << "Insufficient balance!\n";
        }
    }

    void transfer(Account& receiver, double amount) {
        if (amount <= balance) {
            balance -= amount;
            receiver.balance += amount;
            transactions.push_back(Transaction("Transfer", amount, "Sent to account " + to_string(receiver.getAccountNumber())));
            receiver.transactions.push_back(Transaction("Transfer", amount, "Received from account " + to_string(accountNumber)));
        }
        else {
            cout << "Insufficient balance for transfer!\n";
        }
    }

    void showTransactions() const {
        cout << "\nTransaction history for Account " << accountNumber << ":\n";
        if (transactions.empty()) cout << "No transactions yet.\n";
        else for (auto& t : transactions) t.display();
    }

    void displayAccountInfo() const {
        cout << "\n--- Account Info ---\n";
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: " << balance << endl;
        showTransactions();
    }
};

// Customer Class
class Customer {
private:
    string name;
    int customerID;
    vector<Account> accounts;

public:
    Customer(string n, int id) {
        name = n;
        customerID = id;
    }

    string getName() const { return name; }
    int getCustomerID() const { return customerID; }

    void addAccount(int accNo, double initialBalance = 0.0) {
        accounts.push_back(Account(accNo, initialBalance));
        cout << "Account created successfully!\n";
    }

    Account* getAccount(int accNo) {
        for (auto& acc : accounts) {
            if (acc.getAccountNumber() == accNo) return &acc;
        }
        return nullptr;
    }

    void displayCustomerInfo() const {
        cout << "\n--- Customer Info ---\n";
        cout << "Name: " << name << endl;
        cout << "Customer ID: " << customerID << endl;
        cout << "Number of Accounts: " << accounts.size() << endl;
    }
};

// Main Program
int main() {
    vector<Customer> customers;
    int choice, custID, accNo;
    double amount;
    string name;

    while (true) {
        cout << "\n=== Banking System Menu ===\n";
        cout << "1. Create Customer\n";
        cout << "2. Create Account\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Transfer Funds\n";
        cout << "6. View Account Info\n";
        cout << "7. View Customer Info\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
        case 1: {
            cout << "Enter Customer ID: ";
            cin >> custID;
            cout << "Enter Customer Name: ";
            cin.ignore();
            getline(cin, name);
            customers.push_back(Customer(name, custID));
            cout << "Customer created!\n";
            break;
        }
        case 2: {
            cout << "Enter Customer ID: ";
            cin >> custID;
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Initial Balance: ";
            cin >> amount;

            bool found = false;
            for (auto& c : customers) {
                if (c.getCustomerID() == custID) {
                    c.addAccount(accNo, amount);
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Customer not found!\n";
            break;
        }
        case 3: {
            cout << "Enter Customer ID: ";
            cin >> custID;
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Deposit Amount: ";
            cin >> amount;

            bool found = false;
            for (auto& c : customers) {
                if (c.getCustomerID() == custID) {
                    Account* acc = c.getAccount(accNo);
                    if (acc) {
                        acc->deposit(amount);
                        cout << "Deposit successful!\n";
                    }
                    else cout << "Account not found!\n";
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Customer not found!\n";
            break;
        }
        case 4: {
            cout << "Enter Customer ID: ";
            cin >> custID;
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Withdrawal Amount: ";
            cin >> amount;

            bool found = false;
            for (auto& c : customers) {
                if (c.getCustomerID() == custID) {
                    Account* acc = c.getAccount(accNo);
                    if (acc) {
                        acc->withdraw(amount);
                    }
                    else cout << "Account not found!\n";
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Customer not found!\n";
            break;
        }
        case 5: {
            int custID2, accNo2;
            cout << "Enter Sender Customer ID: ";
            cin >> custID;
            cout << "Enter Sender Account Number: ";
            cin >> accNo;
            cout << "Enter Receiver Customer ID: ";
            cin >> custID2;
            cout << "Enter Receiver Account Number: ";
            cin >> accNo2;
            cout << "Enter Transfer Amount: ";
            cin >> amount;

            Account* sender = nullptr, * receiver = nullptr;
            for (auto& c : customers) {
                if (c.getCustomerID() == custID) sender = c.getAccount(accNo);
                if (c.getCustomerID() == custID2) receiver = c.getAccount(accNo2);
            }
            if (sender && receiver) {
                sender->transfer(*receiver, amount);
                cout << "Transfer complete!\n";
            }
            else cout << "Sender or Receiver account not found!\n";
            break;
        }
        case 6: {
            cout << "Enter Customer ID: ";
            cin >> custID;
            cout << "Enter Account Number: ";
            cin >> accNo;

            bool found = false;
            for (auto& c : customers) {
                if (c.getCustomerID() == custID) {
                    Account* acc = c.getAccount(accNo);
                    if (acc) acc->displayAccountInfo();
                    else cout << "Account not found!\n";
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Customer not found!\n";
            break;
        }
        case 7: {
            cout << "Enter Customer ID: ";
            cin >> custID;

            bool found = false;
            for (auto& c : customers) {
                if (c.getCustomerID() == custID) {
                    c.displayCustomerInfo();
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Customer not found!\n";
            break;
        }
        default:
            cout << "Invalid choice!\n";
        }
    }

    cout << "Exiting Banking System. Goodbye!\n";
    return 0;
}
