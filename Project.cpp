/*
Topics used this project
- herichary inheritance
- file handling
- string handling
- excption handling
- static keywords
- runtime error
- virtual function
- polymorphism
- constructors
- function defination inside the class i.e. inline
- also functioni defination using scpoe resoultion operator
*/
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdexcept>
using namespace std;
class BankAccount
{
protected:
    int userAccountNumber;
    long phoneNumber;
    char accountType;
    string name;
    string password;
    string panCardNumber;
    string email;
    double intrestRate;
    double balance;
    static int accountNumber;
    static int generateAccountNumber();
    double witMoney;
    double depMoney;

public:
    BankAccount()
    {
        userAccountNumber = generateAccountNumber();
    }
    BankAccount(int accno, long phno, char type, string name, string email, string panno, string pass)
    {
    }
    virtual void createAccount(char type)
    {
        cout << "Enter your name -> ";
        cin >> name;
        cout << "Enter your phone number -> ";
        cin >> phoneNumber;
        cout << "Enter your email -> ";
        cin >> email;
        cout << "Enter your pancard number -> ";
        accountType = type;
        balance = 0;
        intrestRate = 0;

        try
        {
            cin >> panCardNumber;
            if (panCardNumber.length() != 10)
            {
                throw runtime_error("");
            }
        }
        catch (runtime_error)
        {
            cout << "Enter a valid PAN number" << endl;
            return;
        }
        cout << "Enter your password (Minimum 8 characters long) -> ";
        try
        {
            cin >> password;
            if (password.length() < 8)
            {
                throw "e";
            }
        }
        catch (char e)
        {
            cout << "Password should be 8 characters long";
        }
        ofstream outFile("accounts.dat", ios::app);
        if (!outFile)
        {
            cerr << "Error opening file for writing!" << endl;
            return;
        }

        outFile << userAccountNumber << " " << phoneNumber << " " << accountType << " " << name << " " << email << " " << panCardNumber << " " << password << " " << intrestRate << " " << balance << endl;

        outFile.close();
        cout << "Account created sucessfully!" << endl;
    }
    virtual void displayAccount()
    {

        ifstream inFile("accounts.dat");
        if (!inFile)
        {
            cerr << "Error opening file for reading!" << endl;
            return;
        }

        cout << "Loading accounts from file:" << endl;
        string line;
        cout << "Account No | Phone No | Account Type | Name | Email | PAN card number | Password | Intrest Rate | Balance" << endl;
        while (getline(inFile, line))
        {
            cout << line << endl;
        }
        inFile.close();
    }
    virtual void deposit()
    {
        cout << "Enter the amount you want to deposit";

        cin >> depMoney;
        balance += depMoney;

        cout << "Money deposit sucessfull" << endl;
        cout << "The updated balance is -> " << balance;
    }
    virtual void withdraw()
    {
        cout << "Enter the amount you want to withdraw";
        cin >> witMoney;
    }
};

class SavingAccount : public BankAccount
{
protected:
    int min = 2000;

public:
    void createAccount(char type);
    void displayAccount();
    void deposit()
    {
        BankAccount::deposit();
    }
    void withdraw()
    {
        BankAccount::withdraw();
        while (true)
        {
            if (witMoney + min < balance)
            {
                balance -= witMoney;
                cout << "Withdrawal sucessfull";
                break;
            }
            else
            {
                cout << "Insufficient balance" << endl;
                cout << "Enter the amount you want to withdraw";
                cin >> witMoney;
            }
        }
    }
};
class CurrentAccount : public BankAccount
{
protected:
    int gstnumber;
    int min = 5000;

public:
    void createAccount(char type);
    void displayAccount();
    void deposit()
    {
        BankAccount::deposit();
    }
    void withdraw()
    {
        BankAccount::withdraw();
        while (true)
        {
            if (witMoney + min < balance)
            {
                balance -= witMoney;
                cout << "Withdrawal sucessfull";
                break;
            }
            else
            {
                cout << "Insufficient balance" << endl;
                cout << "Enter the amount you want to withdraw";
                cin >> witMoney;
            }
        }
    }
};

int BankAccount ::accountNumber = 1000;

int BankAccount::generateAccountNumber()
{
    return ++accountNumber;
}

// Saving account functions
void SavingAccount::createAccount(char t = 's')
{
    BankAccount::createAccount(t);
    cout << "Enter the balance (minimun 2000)-> ";
    try
    {
        cin >> balance;
        if (balance < min)
        {
            throw runtime_error("");
        }
    }
    catch (runtime_error)
    {
        cout << "Minimum balance is 2000" << endl;
    }
    cout << "The rate of intrest is 3%" << endl;
    intrestRate = 3.0;
}

void SavingAccount::displayAccount()
{
    BankAccount::displayAccount();
    cout << "Intrest of rate -> " << intrestRate << endl;
    cout << "Minimum Balance -> " << min;
}

// Current account functions

void CurrentAccount::createAccount(char t = 'c')
{
    BankAccount::createAccount(t);
    cout << "Enter the balance (minimum 5000)-> ";
    try
    {
        cin >> balance;
        if (balance < min)
        {
            throw runtime_error("");
        }
    }
    catch (runtime_error)
    {
        cout << "Minimum balance is 5000" << endl;
    }

    cout << "No rate of intrest is available on current account" << endl;
    intrestRate = 0;
    cout << "Enter you GST number";
    cin >> gstnumber;
}
void CurrentAccount::displayAccount()
{
    BankAccount::displayAccount();
    cout << "No intrest of rate avaiable" << endl;
    cout << "Minimum Balance -> " << min;
    cout << "GST Number -> " << gstnumber << endl;
}
void login()
{
    cout << "Enter your account number";
    int userloginaccnumber;
    cin >> userloginaccnumber;
    cout << "Enter your password";
    string userloginpass;
    cin >> userloginpass;
}
void logout() {}
void typeOfAccCreation()
{
    char userTypeAccCretaion;
    while (true)
    {
        cout << "Which type of account you want to create ?" << endl;
        cin >> userTypeAccCretaion;
        if (userTypeAccCretaion == 's')
        {
            SavingAccount SA;
            SA.createAccount('s');
            break;
        }
        else if (userTypeAccCretaion == 'c')
        {
            CurrentAccount CA;
            CA.createAccount('c');
            break;
        }
        else
        {
            cout << "Invalid Input try again " << endl;
            continue;
        }
    }
}
void welcome()
{
    cout << "Welcome to out Bank!!" << endl;
    cout << "Enter 1 to login" << endl;
    cout << "Enter 2 to create a new bank account" << endl;
    cout << "Enter 2 to exit" << endl;

    while (true)
    {
        int userInput;
        cin >> userInput;
        switch (userInput)
        {
        case 1:
            login();
            break;
        case 2:
            typeOfAccCreation();
            break;
        case 3:
            break;
        }
        break;
    }
}
int main()
{
    BankAccount BA;
    welcome();
}