#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    string accountHolder;
    double balance;
    int pin; // Added PIN attribute

public:
    BankAccount(const string& holder, double initialBalance, int num, int accountPin)
        : accountHolder(holder), balance(initialBalance), pin(accountPin) {
        accountNumber = num;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    string getAccountHolder() const {
        return accountHolder;
    }

    double getBalance() const {
        return balance;
    }

    int getPin() const {
        return pin;
    }

    void deposit(double amount) {
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        } else {
            cout << "Insufficient funds!" << endl;
        }
    }

    void display() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Balance: $" << balance << endl;
    }

    // Added function to verify PIN
    bool verifyPin(int enteredPin) const {
        return (enteredPin == pin);
    }
};

int main() {
    vector<BankAccount> accounts;

    char input;

    while (input != 'Q') {
        cout << "---------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Press 'Q' to quit : " << endl;
        cout << "Press 'C' to create a new user : " << endl;
        cout << "Press 'D' to deposit  : " << endl;
        cout << "Press 'W' to withdraw  : " << endl;
        cout << "Press 'S' to display the balance : " << endl;
        cin >> input;

        if (input == 'C') {
            string accountHolder;
            double initialBalance;
            int pin; // Added variable for PIN

            cout << "---------------------------------------------------------------------------------------------------------------" << endl;
            cout << "Enter account holder name: ";
            cin >> accountHolder;

            cout << "Enter initial balance: ";
            cin >> initialBalance;

            cout << "Enter PIN for the account: ";
            cin >> pin;

            int no_of_accounts = accounts.size();
            accounts.push_back(BankAccount(accountHolder, initialBalance, no_of_accounts + 1, pin));
            cout << "---------------------------------------------------------------------------------------------------------------" << endl;
            cout << "The user has been successfully created " << endl;
            cout << "Account Number: " << accounts.back().getAccountNumber() << endl;
            cout << "Username: " << accountHolder << endl;
            cout << "Current balance: $" << initialBalance << endl;
            cout << "---------------------------------------------------------------------------------------------------------------" << endl;
        } else if (input == 'D' || input == 'W' || input == 'S') {
            int account_number;
            int enteredPin;

            cout << "Enter the account number: ";
            cin >> account_number;

            // Check if the account number is within the valid range
            if (account_number >= 0 && account_number < accounts.size()) {
                cout << "Enter PIN for the account: ";
                cin >> enteredPin;

                const BankAccount& curr = accounts[account_number];

                // Verify PIN before proceeding
                if (curr.verifyPin(enteredPin)) {
                    if (input == 'D') {
                        double deposit_amount;
                        cout << "Enter the amount to be deposited: ";
                        cin >> deposit_amount;
                        accounts[account_number].deposit(deposit_amount);
                        cout << "Deposit successful. Available Balance: $" << accounts[account_number].getBalance() << endl;
                    } else if (input == 'W') {
                        double withdraw_amount;
                        cout << "Enter the amount to be withdrawn: ";
                        cin >> withdraw_amount;

                        if (accounts[account_number].getBalance() >= withdraw_amount) {
                            accounts[account_number].withdraw(withdraw_amount);
                            cout << "Withdrawal successful. Available Balance: $" << accounts[account_number].getBalance() << endl;
                        } else {
                            cout << "Insufficient Funds" << endl;
                        }
                    } else if (input == 'S') {
                        cout << "Balance: $" << accounts[account_number].getBalance() << endl;
                    }
                } else {
                    cout << "Invalid PIN!" << endl;
                }
            } else {
                cout << "Invalid account number!" << endl;
            }
        }
    }

    // Display final account information
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Final Account Information:" << endl;
    for (const auto& account : accounts) {
        cout << "---------------------------------------------------------------------------------------------------------------" << endl;
        cout << endl;
        account.display();
        cout << endl;
    }
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;

    return 0;
}
