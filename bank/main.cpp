#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BankAccount {
private:
//    static int nextAccountNumber;   Static variable to generate unique account numbers
    int accountNumber;             // Account number attribute
    string accountHolder;
    double balance;

public:
    // Constructor
    BankAccount(const string& holder, double initialBalance, int num)
        : accountHolder(holder), balance(initialBalance) {
        accountNumber = num;
    }

    // Member function to get account number
    int getAccountNumber() const {
        return accountNumber;
    }

    // Member function to get account holder name
    string getAccountHolder() const {
        return accountHolder;
    }

    // Member function to get account balance
    double getBalance() const {
        return balance;
    }

    // Member function to deposit money
    void deposit(double amount) {
        balance += amount;
    }

    // Member function to withdraw money
    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        } else {
            cout << "Insufficient funds!" << endl;
        }
    }

    // Operator overloading for adding two accounts
    BankAccount operator+(const BankAccount& other) const {
        BankAccount result = *this;
        result.balance += other.balance;
        return result;
    }

    // Function overloading to display account information
    void display() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Balance: $" << balance << endl;
    }
};

// Initializing the static variable
//int BankAccount::nextAccountNumber = 1;

int main() {
    vector<BankAccount> accounts;

    char input;

    while (input != 'Q') {
        cout << "---------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Press 'Q' to quit : " << endl;
        cout << "Press 'C' to create a new user : " << endl;
        cout << "Press 'D' to deposit  : " << endl;
        cout << "Press 'W' to withdraw  : " << endl; 
        cout<< "Press 'S' to display the balance : " << endl;
        cin >> input;

        if (input == 'C') {
            // Get user details
            string accountHolder;
            double initialBalance;

            cout << "---------------------------------------------------------------------------------------------------------------" << endl;
            cout << "Enter account holder name: ";
            cin >> accountHolder;

            cout << "Enter initial balance: ";
            cin >> initialBalance;

            // Create a new BankAccount object and add it to the vector
            int no_of_accounts = accounts.size();
            accounts.push_back(BankAccount(accountHolder, initialBalance, no_of_accounts));
            cout << "---------------------------------------------------------------------------------------------------------------" << endl;
            cout << "The user has been successfully created " << endl;
            cout << "Account Number: " << accounts.back().getAccountNumber() << endl;
            cout << "Username: " << accountHolder << endl;
            cout << "Current balance: $" << initialBalance << endl;
            cout << "---------------------------------------------------------------------------------------------------------------" << endl;
        }
        else if (input == 'D') {
            int account_number;
            double deposit_amount;
            cout << "Enter the account number: ";
            cin >> account_number;
            ;
            // Check if the account number is within the valid range
            if (account_number >= 0 && account_number < accounts.size()) {
                BankAccount& curr = accounts[account_number];
                string name = curr.getAccountHolder();
                
                cout << "Account Holder Name: " << name << endl;
                cout << "Enter the amount to be deposited : " <<endl;
                cin >> deposit_amount;
                curr.deposit(deposit_amount);
                cout << "the deposit has been succesfully done " <<endl;
                cout << "Avaliable Balance : " << curr.getBalance() << endl;
            } else {
                cout << "Invalid account number!" << endl;
            }
        }
        else if(input == 'W'){
                int account_number;
                double withdraw_amount;
                 cout << "Enter the account number: ";
            cin >> account_number;
             if (account_number >= 0 && account_number < accounts.size()) {
                BankAccount& curr = accounts[account_number];
                string name = curr.getAccountHolder();
                double balance = curr.getBalance();
                cout << "Account Holder Name: " << name << endl;
                cout << "Enter the amount to be withdrawen : " <<endl;
                cin >> withdraw_amount;
                if(balance >= withdraw_amount){
                    curr.withdraw(withdraw_amount);
                    cout << "the withdraw has been succesfully done " <<endl;
                    cout << "Avaliable Balance : " << curr.getBalance() << endl;
                }
                else{
                    cout << "Insufficient Funds" <<endl;
                }
                
            } else {
                cout << "Invalid account number!" << endl;
            }
            }
            
            else if(input == 'S'){
                 int account_number;
                 cout << "Enter the account number: ";
                 cin >> account_number;
                 if (account_number >= 0 && account_number < accounts.size()) {
                BankAccount& curr = accounts[account_number];
                curr.display();
                     }
                 else{
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
