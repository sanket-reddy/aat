#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BankAccount {
private:
    static int nextAccountNumber;
    int accountNumber;
    string accountHolder;
    double balance;
    int pin;

public:
    BankAccount(const string& holder, double initialBalance, int accountPin)
        : accountHolder(holder), balance(initialBalance), pin(accountPin) {
        accountNumber = nextAccountNumber++;
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

    bool verifyPin(int enteredPin) const {
        return (enteredPin == pin);
    }
};

int BankAccount::nextAccountNumber = 1;

void displayOptions() {
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Press 'C' to create a new account : " << endl;
    cout << "Press 'L' to log in : " << endl;
    cout << "Press 'Q' to quit : " << endl;
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
}

void displayActions() {
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Press 'D' to deposit  : " << endl;
    cout << "Press 'W' to withdraw  : " << endl;
    cout << "Press 'S' to display the balance : " << endl;
    cout << "Press 'X' to log out : " << endl;
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
}

int main() {
    vector<BankAccount> accounts;
    bool loggedIn = false;

    char input;

    while (true) {
        if (!loggedIn) {
            displayOptions();
            cin >> input;
        }

        if (input == 'Q') {
            break;
        } else if (input == 'C') {
            string username;
            int newPin;
            double initialBalance;

            cout << "Enter your username: ";
            cin >> username;

            cout << "Enter your 4-digit PIN: ";
            cin >> newPin;

            cout << "Enter initial balance: $";
            cin >> initialBalance;

            accounts.push_back(BankAccount(username, initialBalance, newPin));
            cout << "Account created successfully! Please log in." << endl;
        } else if (input == 'L') {
            string username;
            int pin;

            cout << "Enter your username: ";
            cin >> username;

            for (auto& account : accounts) {
                if (account.getAccountHolder() == username) {
                    cout << "Enter your PIN: ";
                    cin >> pin;

                    if (account.verifyPin(pin)) {
                        loggedIn = true;
                        cout << "Log in successful. Welcome, " << username << "!" << endl;
                        displayActions();

                        while (input != 'X') {
                            cin >> input;

                            if (input == 'D') {
                                double deposit_amount;
                                cout << "Enter the amount to be deposited: ";
                                cin >> deposit_amount;
                                account.deposit(deposit_amount);
                                cout << "Deposit successful. Available Balance: $" << account.getBalance() << endl;
                                displayActions();
                            } else if (input == 'W') {
                                double withdraw_amount;
                                cout << "Enter the amount to be withdrawn: ";
                                cin >> withdraw_amount;

                                if (account.getBalance() >= withdraw_amount) {
                                    account.withdraw(withdraw_amount);
                                    cout << "Withdrawal successful. Available Balance: $" << account.getBalance() << endl;
                                } else {
                                    cout << "Insufficient funds!" << endl;
                                }
                                displayActions();
                            } else if (input == 'S') {
                                account.display();
                                displayActions();
                            } else if (input == 'X') {
                                loggedIn = false;
                                cout << "Logged out successfully." << endl;
                                displayActions();
                            }
                            else {
                                cout << "Invalid key" << endl;
                                displayActions();
                            }
                        }
                    } else {
                        cout << "Incorrect PIN. Try again." << endl;
                        displayOptions();
                    }
                }
            }

            if (!loggedIn) {
                cout << "User not found. Please create a new account or try again." << endl;
            }
        }
    }

    return 0;
}
