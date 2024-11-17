#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Base class Account
class Account
{
protected:
    int accountNumber;
    string name;
    string password;
    string panCard;
    string phoneNumber;
    string email;
    int balance;

    void writeString(ofstream &outFile, const string &str);
    void readString(ifstream &inFile, string &str);
    static int generateAccountNumber();

public:
    Account();
    virtual void createAccount();
    virtual void displayAccount() const;
    virtual void deposit(int);
    virtual void withdraw(int);
    virtual char getAccountType() const = 0; // Pure virtual function
    int getAccountNumber() const;
    string getPassword() const;
    string getEmail() const;
    int getBalance() const;
    void setBalance(int);
    void setPassword(const string &);
    virtual void writeAccountToFile(ofstream &outFile);
    virtual void readAccountFromFile(ifstream &inFile);
};

// Derived class SavingAccount
class SavingAccount : public Account
{
public:
    void createAccount();
    void displayAccount() const;
    void deposit(int);
    void withdraw(int);
    char getAccountType() const;
    void writeAccountToFile(ofstream &outFile);
    void readAccountFromFile(ifstream &inFile);
};

// Derived class CurrentAccount
class CurrentAccount : public Account
{
public:
    void createAccount();
    void displayAccount() const;
    void deposit(int);
    void withdraw(int);
    char getAccountType() const;
    void writeAccountToFile(ofstream &outFile);
    void readAccountFromFile(ifstream &inFile);
};

// Function definitions for Account class

int Account::generateAccountNumber()
{
    static int lastAccountNumber = 1000; // Starting from 1001
    return ++lastAccountNumber;
}

Account::Account()
{
    accountNumber = generateAccountNumber();
}

void Account::writeString(ofstream &outFile, const string &str)
{
    int length = str.length();
    outFile.write((char *)&length, sizeof(length));
    outFile.write(str.c_str(), length);
}

void Account::readString(ifstream &inFile, string &str)
{
    int length;
    inFile.read((char *)&length, sizeof(length));
    char *buffer = new char[length + 1];
    inFile.read(buffer, length);
    buffer[length] = '\0';
    str = buffer;
    delete[] buffer;
}

void Account::createAccount()
{
    cout << "\nEnter Your Name (no spaces): ";
    cin >> name;
    cout << "Set Your Password: ";
    cin >> password;
    cout << "Enter Your PAN Card Number: ";
    cin >> panCard;
    cout << "Enter Your Phone Number: ";
    cin >> phoneNumber;
    cout << "Enter Your Email: ";
    cin >> email;
    balance = 0; // Initial balance is set in derived classes
}

void Account::displayAccount() const
{
    cout << "\nAccount Details:\n";
    cout << "Account Number: " << accountNumber << "\n";
    cout << "Name: " << name << "\n";
    cout << "PAN Card: " << panCard << "\n";
    cout << "Phone Number: " << phoneNumber << "\n";
    cout << "Email: " << email << "\n";
    cout << "Account Type: " << getAccountType() << "\n";
    cout << "Balance: " << balance << "\n";
}

void Account::deposit(int amount)
{
    balance += amount;
    cout << "\nAmount Deposited Successfully. New Balance: " << balance << "\n";
}

void Account::withdraw(int amount)
{
    balance -= amount;
    cout << "\nAmount Withdrawn Successfully. New Balance: " << balance << "\n";
}

int Account::getAccountNumber() const
{
    return accountNumber;
}

string Account::getPassword() const
{
    return password;
}

string Account::getEmail() const
{
    return email;
}

int Account::getBalance() const
{
    return balance;
}

void Account::setBalance(int newBalance)
{
    balance = newBalance;
}

void Account::setPassword(const string &newPassword)
{
    password = newPassword;
}

void Account::writeAccountToFile(ofstream &outFile)
{
    // Write account type
    char accountType = getAccountType();
    outFile.write(&accountType, sizeof(accountType));

    // Write account number
    outFile.write((char *)&accountNumber, sizeof(accountNumber));

    // Write strings
    writeString(outFile, name);
    writeString(outFile, password);
    writeString(outFile, panCard);
    writeString(outFile, phoneNumber);
    writeString(outFile, email);

    // Write balance
    outFile.write((char *)&balance, sizeof(balance));
}

void Account::readAccountFromFile(ifstream &inFile)
{
    // Account type is already read in main function

    // Read account number
    inFile.read((char *)&accountNumber, sizeof(accountNumber));

    // Read strings
    readString(inFile, name);
    readString(inFile, password);
    readString(inFile, panCard);
    readString(inFile, phoneNumber);
    readString(inFile, email);

    // Read balance
    inFile.read((char *)&balance, sizeof(balance));
}

// Function definitions for SavingAccount class

void SavingAccount::createAccount()
{
    Account::createAccount();
    cout << "Enter Initial Deposit Amount (Minimum 500): ";
    cin >> balance;
    if (balance < 500)
    {
        cout << "Minimum balance for Savings Account is 500. Account not created.\n";
        return;
    }
    cout << "\nSavings Account Created Successfully. Your Account Number is: " << accountNumber << "\n";
}

void SavingAccount::displayAccount() const
{
    Account::displayAccount();
}

void SavingAccount::deposit(int amount)
{
    Account::deposit(amount);
}

void SavingAccount::withdraw(int amount)
{
    if (balance - amount < 500)
    {
        cout << "\nInsufficient Balance. Minimum balance of 500 must be maintained.\n";
        return;
    }
    Account::withdraw(amount);
}

char SavingAccount::getAccountType() const
{
    return 'S';
}

void SavingAccount::writeAccountToFile(ofstream &outFile)
{
    Account::writeAccountToFile(outFile);
}

void SavingAccount::readAccountFromFile(ifstream &inFile)
{
    Account::readAccountFromFile(inFile);
}

// Function definitions for CurrentAccount class

void CurrentAccount::createAccount()
{
    Account::createAccount();
    cout << "Enter Initial Deposit Amount (Minimum 1000): ";
    cin >> balance;
    if (balance < 1000)
    {
        cout << "Minimum balance for Current Account is 1000. Account not created.\n";
        return;
    }
    cout << "\nCurrent Account Created Successfully. Your Account Number is: " << accountNumber << "\n";
}

void CurrentAccount::displayAccount() const
{
    Account::displayAccount();
}

void CurrentAccount::deposit(int amount)
{
    Account::deposit(amount);
}

void CurrentAccount::withdraw(int amount)
{
    if (balance - amount < 1000)
    {
        cout << "\nInsufficient Balance. Minimum balance of 1000 must be maintained.\n";
        return;
    }
    Account::withdraw(amount);
}

char CurrentAccount::getAccountType() const
{
    return 'C';
}

void CurrentAccount::writeAccountToFile(ofstream &outFile)
{
    Account::writeAccountToFile(outFile);
}

void CurrentAccount::readAccountFromFile(ifstream &inFile)
{
    Account::readAccountFromFile(inFile);
}

// Function prototypes
void createNewAccount();
bool login(Account *&accountPtr);
void displayAccountDetails(Account *accountPtr);
void depositMoney(Account *accountPtr);
void withdrawMoney(Account *accountPtr);
void transferMoney(Account *accountPtr);
void modifyAccount(Account *accountPtr);
void deleteAccount(Account *accountPtr);
void resetPassword();

int main()
{
    Account *userAccount = nullptr;
    int choice;
    bool loggedIn = false;

    while (true)
    {
        if (!loggedIn)
        {
            cout << "\n\n\tBANK MANAGEMENT SYSTEM";
            cout << "\n\n\tMAIN MENU";
            cout << "\n\n\t1. Create Account";
            cout << "\n\t2. Login";
            cout << "\n\t3. Forgot Password";
            cout << "\n\t4. Exit";
            cout << "\n\n\tSelect Your Option (1-4): ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                createNewAccount();
                break;
            case 2:
                loggedIn = login(userAccount);
                break;
            case 3:
                resetPassword();
                break;
            case 4:
                return 0;
            default:
                cout << "\nInvalid Option. Try Again.\n";
            }
        }
        else
        {
            cout << "\n\n\tWELCOME, " << userAccount->getEmail();
            cout << "\n\n\t1. View Account Details";
            cout << "\n\t2. Deposit Money";
            cout << "\n\t3. Withdraw Money";
            cout << "\n\t4. Transfer Money";
            cout << "\n\t5. Modify Account";
            cout << "\n\t6. Delete Account";
            cout << "\n\t7. Logout";
            cout << "\n\n\tSelect Your Option (1-7): ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                displayAccountDetails(userAccount);
                break;
            case 2:
                depositMoney(userAccount);
                break;
            case 3:
                withdrawMoney(userAccount);
                break;
            case 4:
                transferMoney(userAccount);
                break;
            case 5:
                modifyAccount(userAccount);
                break;
            case 6:
                deleteAccount(userAccount);
                loggedIn = false;
                delete userAccount;
                userAccount = nullptr;
                break;
            case 7:
                loggedIn = false;
                delete userAccount;
                userAccount = nullptr;
                break;
            default:
                cout << "\nInvalid Option. Try Again.\n";
            }
        }
    }

    return 0;
}

// Function to create a new account
void createNewAccount()
{
    int accountTypeChoice;
    cout << "\nSelect Account Type:";
    cout << "\n1. Savings Account";
    cout << "\n2. Current Account";
    cout << "\nEnter your choice: ";
    cin >> accountTypeChoice;

    Account *newAccount = nullptr;

    if (accountTypeChoice == 1)
    {
        newAccount = new SavingAccount();
    }
    else if (accountTypeChoice == 2)
    {
        newAccount = new CurrentAccount();
    }
    else
    {
        cout << "\nInvalid Account Type. Returning to main menu.\n";
        return;
    }

    newAccount->createAccount();

    // Write account to binary file
    ofstream outFile("accounts.dat", ios::binary | ios::app);
    if (!outFile)
    {
        cout << "Error opening file for writing.\n";
        delete newAccount;
        return;
    }
    newAccount->writeAccountToFile(outFile);
    outFile.close();

    delete newAccount;
}

// Function to login
bool login(Account *&accountPtr)
{
    int accNum;
    string pwd;
    cout << "\nEnter Account Number: ";
    cin >> accNum;
    cout << "Enter Password: ";
    cin >> pwd;

    ifstream inFile("accounts.dat", ios::binary);
    if (!inFile)
    {
        cout << "No accounts found. Please create an account first.\n";
        return false;
    }

    bool loggedIn = false;
    while (!inFile.eof())
    {
        char accountType;
        inFile.read(&accountType, sizeof(accountType));
        if (inFile.eof())
            break;

        Account *tempAccount;
        if (accountType == 'S')
        {
            tempAccount = new SavingAccount();
        }
        else if (accountType == 'C')
        {
            tempAccount = new CurrentAccount();
        }
        else
        {
            cout << "Unknown account type in file.\n";
            break;
        }

        tempAccount->readAccountFromFile(inFile);

        if (tempAccount->getAccountNumber() == accNum && tempAccount->getPassword() == pwd)
        {
            accountPtr = tempAccount;
            loggedIn = true;
            break;
        }
        else
        {
            delete tempAccount;
        }
    }

    inFile.close();

    if (!loggedIn)
    {
        cout << "Invalid account number or password.\n";
    }

    return loggedIn;
}

// Function to display account details
void displayAccountDetails(Account *accountPtr)
{
    accountPtr->displayAccount();
}

// Function to deposit money
void depositMoney(Account *accountPtr)
{
    int amount;
    cout << "\nEnter Amount to Deposit: ";
    cin >> amount;
    accountPtr->deposit(amount);
    modifyAccount(accountPtr);
}

// Function to withdraw money
void withdrawMoney(Account *accountPtr)
{
    int amount;
    cout << "\nEnter Amount to Withdraw: ";
    cin >> amount;
    accountPtr->withdraw(amount);
    modifyAccount(accountPtr);
}

// Function to transfer money
void transferMoney(Account *accountPtr)
{
    int toAccNum, amount;
    cout << "\nEnter Account Number to Transfer To: ";
    cin >> toAccNum;
    cout << "Enter Amount to Transfer: ";
    cin >> amount;

    // Read all accounts from file and update balances
    ifstream inFile("accounts.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);

    if (!inFile || !outFile)
    {
        cout << "Error opening file.\n";
        return;
    }

    bool found = false;
    while (!inFile.eof())
    {
        char accountType;
        inFile.read(&accountType, sizeof(accountType));
        if (inFile.eof())
            break;

        Account *tempAccount;
        if (accountType == 'S')
        {
            tempAccount = new SavingAccount();
        }
        else if (accountType == 'C')
        {
            tempAccount = new CurrentAccount();
        }
        else
        {
            cout << "Unknown account type in file.\n";
            break;
        }

        tempAccount->readAccountFromFile(inFile);

        if (tempAccount->getAccountNumber() == toAccNum)
        {
            tempAccount->deposit(amount);
            found = true;
        }

        if (tempAccount->getAccountNumber() == accountPtr->getAccountNumber())
        {
            tempAccount->withdraw(amount);
            accountPtr->setBalance(tempAccount->getBalance());
        }

        tempAccount->writeAccountToFile(outFile);
        delete tempAccount;
    }

    inFile.close();
    outFile.close();

    if (!found)
    {
        cout << "\nTarget Account Not Found. Transaction Failed.\n";
        return;
    }
    else
    {
        remove("accounts.dat");
        rename("temp.dat", "accounts.dat");
        cout << "\nAmount Transferred Successfully. New Balance: " << accountPtr->getBalance() << "\n";
    }
}

// Function to modify account
void modifyAccount(Account *accountPtr)
{
    // Read all accounts from file and update the current account
    ifstream inFile("accounts.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);

    if (!inFile || !outFile)
    {
        cout << "Error opening file.\n";
        return;
    }

    while (!inFile.eof())
    {
        char accountType;
        inFile.read(&accountType, sizeof(accountType));
        if (inFile.eof())
            break;

        Account *tempAccount;
        if (accountType == 'S')
        {
            tempAccount = new SavingAccount();
        }
        else if (accountType == 'C')
        {
            tempAccount = new CurrentAccount();
        }
        else
        {
            cout << "Unknown account type in file.\n";
            break;
        }

        tempAccount->readAccountFromFile(inFile);

        if (tempAccount->getAccountNumber() == accountPtr->getAccountNumber())
        {
            // Update account details
            tempAccount = accountPtr;
        }

        tempAccount->writeAccountToFile(outFile);
        if (tempAccount != accountPtr)
            delete tempAccount;
    }

    inFile.close();
    outFile.close();

    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");
}

// Function to delete account
void deleteAccount(Account *accountPtr)
{
    // Read all accounts from file and write all except the current account
    ifstream inFile("accounts.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);

    if (!inFile || !outFile)
    {
        cout << "Error opening file.\n";
        return;
    }

    while (!inFile.eof())
    {
        char accountType;
        inFile.read(&accountType, sizeof(accountType));
        if (inFile.eof())
            break;

        Account *tempAccount;
        if (accountType == 'S')
        {
            tempAccount = new SavingAccount();
        }
        else if (accountType == 'C')
        {
            tempAccount = new CurrentAccount();
        }
        else
        {
            cout << "Unknown account type in file.\n";
            break;
        }

        tempAccount->readAccountFromFile(inFile);

        if (tempAccount->getAccountNumber() != accountPtr->getAccountNumber())
        {
            tempAccount->writeAccountToFile(outFile);
        }

        delete tempAccount;
    }

    inFile.close();
    outFile.close();

    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    cout << "\nAccount Deleted Successfully.\n";
}

// Function to reset password
void resetPassword()
{
    string emailID, newPassword;
    cout << "\nEnter Your Registered Email ID: ";
    cin >> emailID;
    cout << "Enter New Password: ";
    cin >> newPassword;

    // Read all accounts from file and update password
    ifstream inFile("accounts.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);

    if (!inFile || !outFile)
    {
        cout << "Error opening file.\n";
        return;
    }

    bool found = false;

    while (!inFile.eof())
    {
        char accountType;
        inFile.read(&accountType, sizeof(accountType));
        if (inFile.eof())
            break;

        Account *tempAccount;
        if (accountType == 'S')
        {
            tempAccount = new SavingAccount();
        }
        else if (accountType == 'C')
        {
            tempAccount = new CurrentAccount();
        }
        else
        {
            cout << "Unknown account type in file.\n";
            break;
        }

        tempAccount->readAccountFromFile(inFile);

        if (tempAccount->getEmail() == emailID)
        {
            tempAccount->setPassword(newPassword);
            found = true;
            cout << "\nPassword Reset Successfully.\n";
        }

        tempAccount->writeAccountToFile(outFile);
        delete tempAccount;
    }

    inFile.close();
    outFile.close();

    if (!found)
    {
        cout << "\nEmail ID not found. Password reset failed.\n";
    }
    else
    {
        remove("accounts.dat");
        rename("temp.dat", "accounts.dat");
    }
}
