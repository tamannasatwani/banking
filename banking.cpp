#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Base Class: BankAccount
class BankAccount {
protected:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(int accNum, string holderName, double initialBalance)
        : accountNumber(accNum), accountHolderName(holderName), balance(initialBalance) {}

    virtual ~BankAccount() {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: " << amount << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: " << amount << endl;
        } else {
            cout << "Invalid withdrawal amount or insufficient balance!" << endl;
        }
    }

    double getBalance() const {
        return balance;
    }

    virtual void displayAccountInfo() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder Name: " << accountHolderName << endl;
        cout << "Balance: " << balance << endl;
    }

    virtual void calculateInterest() const {
        cout << "No interest calculation for base account." << endl;
    }
};

// Derived Class: SavingsAccount
class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(int accNum, string holderName, double initialBalance, double rate)
        : BankAccount(accNum, holderName, initialBalance), interestRate(rate) {}

    void calculateInterest() const override {
        double interest = balance * (interestRate / 100);
        cout << "Interest (Savings): " << interest << endl;
    }

    void displayAccountInfo() const override {
        BankAccount::displayAccountInfo();
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }
};

// Derived Class: CheckingAccount
class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CheckingAccount(int accNum, string holderName, double initialBalance, double overdraft)
        : BankAccount(accNum, holderName, initialBalance), overdraftLimit(overdraft) {}

    void withdraw(double amount) override {
        if (amount > 0 && balance - amount >= -overdraftLimit) {
            balance -= amount;
            cout << "Withdrawn: " << amount << endl;
        } else {
            cout << "Withdrawal exceeds overdraft limit!" << endl;
        }
    }

    void displayAccountInfo() const override {
        BankAccount::displayAccountInfo();
        cout << "Overdraft Limit: " << overdraftLimit << endl;
    }
};

// Derived Class: FixedDepositAccount
class FixedDepositAccount : public BankAccount {
private:
    int term; // in months
    double interestRate;

public:
    FixedDepositAccount(int accNum, string holderName, double initialBalance, int duration, double rate)
        : BankAccount(accNum, holderName, initialBalance), term(duration), interestRate(rate) {}

    void calculateInterest() const override {
        double interest = balance * (interestRate / 100) * (term / 12.0);
        cout << "Interest (Fixed Deposit): " << interest << endl;
    }

    void displayAccountInfo() const override {
        BankAccount::displayAccountInfo();
        cout << "Term: " << term << " months" << endl;
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }
};

// Menu-driven interface
void menu() {
    vector<BankAccount*> accounts;
    int choice;

    do {
        cout << "\n--- Banking System Menu ---" << endl;
        cout << "1. Add Savings Account" << endl;
        cout << "2. Add Checking Account" << endl;
        cout << "3. Add Fixed Deposit Account" << endl;
        cout << "4. View All Accounts" << endl;
        cout << "5. Perform Deposit" << endl;
        cout << "6. Perform Withdrawal" << endl;
        cout << "7. Calculate Interest" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int accNum;
            string name;
            double balance, rate;
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Account Holder Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Initial Balance: ";
            cin >> balance;
            cout << "Enter Interest Rate: ";
            cin >> rate;
            accounts.push_back(new SavingsAccount(accNum, name, balance, rate));
            cout << "Savings Account Added!" << endl;
            break;
        }
        case 2: {
            int accNum;
            string name;
            double balance, overdraft;
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Account Holder Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Initial Balance: ";
            cin >> balance;
            cout << "Enter Overdraft Limit: ";
            cin >> overdraft;
            accounts.push_back(new CheckingAccount(accNum, name, balance, overdraft));
            cout << "Checking Account Added!" << endl;
            break;
        }
        case 3: {
            int accNum, term;
            string name;
            double balance, rate;
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Account Holder Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Initial Balance: ";
            cin >> balance;
            cout << "Enter Term (in months): ";
            cin >> term;
            cout << "Enter Interest Rate: ";
            cin >> rate;
            accounts.push_back(new FixedDepositAccount(accNum, name, balance, term, rate));
            cout << "Fixed Deposit Account Added!" << endl;
            break;
        }
        case 4:
            for (size_t i = 0; i < accounts.size(); i++) {
                cout << "\nAccount " << i + 1 << " Details:" << endl;
                accounts[i]->displayAccountInfo();
            }
            break;
        case 5: {
            int accIndex;
            double amount;
            cout << "Enter Account Index to Deposit: ";
            cin >> accIndex;
            cout << "Enter Amount: ";
            cin >> amount;
            if (accIndex > 0 && accIndex <= accounts.size()) {
                accounts[accIndex - 1]->deposit(amount);
            } else {
                cout << "Invalid Account Index!" << endl;
            }
            break;
        }
        case 6: {
            int accIndex;
            double amount;
            cout << "Enter Account Index to Withdraw: ";
            cin >> accIndex;
            cout << "Enter Amount: ";
            cin >> amount;
            if (accIndex > 0 && accIndex <= accounts.size()) {
                accounts[accIndex - 1]->withdraw(amount);
            } else {
                cout << "Invalid Account Index!" << endl;
            }
            break;
        }
        case 7:
            for (size_t i = 0; i < accounts.size(); i++) {
                cout << "\nAccount " << i + 1 << " Interest Calculation:" << endl;
                accounts[i]->calculateInterest();
            }
            break;
        case 8:
            cout << "Exiting the system. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 8);

    // Clean up memory using traditional for loop
    for (size_t i = 0; i < accounts.size(); i++) {
        delete accounts[i];
    }
    accounts.clear();
}

int main() {
    menu();
    return 0;
}

