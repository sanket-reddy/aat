#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

class Person {
protected:
    string username;
    int pin;

public:
    Person(const string& name, int newPin)
        : username(name), pin(newPin) {}

    virtual ~Person() {}

    const string& getUsername() const {
        return username;
    }

    int getPin() const {
        return pin;
    }
};

class BankAccount : public Person {
private:
    static int nextAccountNumber;
    int accountNumber;
    double balance;

public:
    BankAccount(const string& holder, int newPin, double initialBalance)
        : Person(holder, newPin), balance(initialBalance) {
        accountNumber = nextAccountNumber++;
    }

    ~BankAccount() {}

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
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

     BankAccount operator+(const BankAccount& other) const {
        BankAccount result = *this;
        result.balance += other.balance;
        return result;
    }
    void mergeAccounts(BankAccount& other) {
        int mergingPin;
        cout << "Enter the PIN of the account you want to merge: ";
        cin >> mergingPin;

        if (other.verifyPin(mergingPin)) {
            *this = *this + other;  // Use the overloaded + operator for merging
            cout << "Accounts merged successfully. New balance: $" << fixed << setprecision(2) << balance << endl;

            // Remove the merged account
            other.balance = 0.0;  // Set balance to zero (you may want to handle this differently)
        } else {
            cout << "Incorrect PIN. Merge failed." << endl;
        }
    }


    void display() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << getUsername() << endl;
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    void transfer(BankAccount& recipient, double amount) {
        if (amount <= balance) {
            withdraw(amount);
            recipient.deposit(amount);
            cout << "Transfer successful. Available Balance: $" << fixed << setprecision(2) << balance << endl;
        } else {
            cout << "Insufficient funds!" << endl;
        }
    }


    bool verifyPin(int userPin) const {
        return pin == userPin;
    }
};

int BankAccount::nextAccountNumber = 1;

template <typename T>
void displayOptions(const T& accounts) {
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Press 'C' to create a new account : " << endl;
    cout << "Press 'L' to log in : " << endl;
    cout << "Press 'Q' to quit : " << endl;
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
}

template <typename T>
void displayActions(const T& account) {
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Press 'D' to deposit  : " << endl;
    cout << "Press 'W' to withdraw  : " << endl;
    cout << "Press 'S' to display the balance : " << endl;
    cout << "Press 'T' to transfer funds : " << endl;
    cout << "Press 'M' to merge account : " << endl;
    cout << "Press 'X' to log out : " << endl;
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
}

template <typename T>
void displayAccounts(const T& accounts) {
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Final Account Information:" << endl;
    for (const auto& account : accounts) {
        cout << "---------------------------------------------------------------------------------------------------------------" << endl;
        cout << endl;
        account.display();
        cout << endl;
    }
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
}

int main() {
    vector<BankAccount> accounts;
    bool loggedIn = false;
    char input;

    while (true) {
        if (!loggedIn) {
            displayOptions(accounts);
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

            accounts.push_back(BankAccount(username, newPin, initialBalance));
            cout << "Account created successfully! Please log in." << endl;
        } else if (input == 'L') {
            string username;
            int pin;

            cout << "Enter your username: ";
            cin >> username;

            for (auto& account : accounts) {
                if (account.getUsername() == username) {
                    cout << "Enter your PIN: ";
                    cin >> pin;

                    if (account.verifyPin(pin)) {
                        loggedIn = true;
                        cout << "Log in successful. Welcome, " << username << "!" << endl;
                        displayActions(account);

                        while (input != 'X') {
                            cin >> input;

                            if (input == 'D') {
                                double deposit_amount;
                                cout << "Enter the amount to be deposited: ";
                                cin >> deposit_amount;
                                account.deposit(deposit_amount);
                                displayActions(account);
                            } else if (input == 'W') {
                                double withdraw_amount;
                                cout << "Enter the amount to be withdrawn: ";
                                cin >> withdraw_amount;

                                if (account.getBalance() >= withdraw_amount) {
                                    account.withdraw(withdraw_amount);
                                } else {
                                    cout << "Insufficient funds!" << endl;
                                }
                                displayActions(account);
                            } else if (input == 'S') {
                                account.display();
                                displayActions(account);
                            } else if (input == 'T') {
                                int recipientAccountNumber;
                                double transfer_amount;

                                cout << "Enter the recipient's account number: ";
                                cin >> recipientAccountNumber;
                                
                                for (auto& recipient : accounts) {
                                    if (recipient.getAccountNumber() == recipientAccountNumber) {
                                        cout << "Enter the amount to transfer: ";
                                        cin >> transfer_amount;

                                        account.transfer(recipient, transfer_amount);
                                    }
                                }
                                displayActions(account);
                            }else if(input == 'M'){
                                 int mergeAccountNumber;
                    cout << "Enter the account number you want to merge: ";
                    cin >> mergeAccountNumber;

                    if (mergeAccountNumber >= 0 && mergeAccountNumber < accounts.size()) {
                        account.mergeAccounts(accounts[mergeAccountNumber]);
                    } else {
                        cout << "Invalid account number." << endl;
                    }
                            }
                             else if (input == 'X') {
                                loggedIn = false;
                                cout << "Logged out successfully." << endl;
                                displayOptions(accounts);
                            }
                        }
                    } else {
                        cout << "Incorrect PIN. Try again." << endl;
                        displayOptions(accounts);
                    }
                }
            }

            if (!loggedIn) {
                cout << "User not found. Please create a new account or try again." << endl;
            }
        }
    }

    displayAccounts(accounts);

    return 0;
}
