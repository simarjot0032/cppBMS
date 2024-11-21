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
- using stringstream
- using break continue i.e. jumping statement
*/
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdexcept>
#include <string>
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
    static void saveLastAccountNumber();
    static void loadLastAccountNumber();
    struct SIZE
    {
        int nameSize;
        int emailSize;
        int passwordSize;
        int pancardsizeSize;
    };

public:
    BankAccount() {}
    friend void login(BankAccount &b);

    BankAccount(int accno, long phno, char type, string name, string email, string panno, string pass)
    {
        SIZE size;
        size.nameSize = name.size();
        size.emailSize = email.size();
        size.passwordSize = password.size();
        size.pancardsizeSize = panCardNumber.size();
    }
    void writeDataToFile(int userAccountno, long phno, char acctype, string name, string email, string pancardno, string pass, double intrestRate, double balance)
    {
        ofstream outFile("accounts.dat", ios::app);
        if (!outFile)
        {
            cerr << "Error opening file for writing!" << endl;
            return;
        }
        SIZE size;
        size.nameSize = name.size();
        size.emailSize = email.size();
        size.passwordSize = pass.size();
        size.pancardsizeSize = pancardno.size();
        outFile.write(reinterpret_cast<char *>(&userAccountno), sizeof(userAccountno));
        outFile.write(reinterpret_cast<char *>(&phno), sizeof(phno));
        outFile.write(reinterpret_cast<char *>(&acctype), sizeof(acctype));
        outFile.write(reinterpret_cast<char *>(&size.nameSize), sizeof(size.nameSize));
        outFile.write(name.c_str(), size.nameSize);
        outFile.write(reinterpret_cast<char *>(&size.emailSize), sizeof(size.emailSize));
        outFile.write(email.c_str(), size.emailSize);
        outFile.write(reinterpret_cast<char *>(&size.pancardsizeSize), sizeof(size.pancardsizeSize));
        outFile.write(pancardno.c_str(), size.pancardsizeSize);
        outFile.write(reinterpret_cast<char *>(&size.passwordSize), sizeof(size.passwordSize));
        outFile.write(pass.c_str(), size.passwordSize);
        outFile.write(reinterpret_cast<char *>(&intrestRate), sizeof(intrestRate));
        outFile.write(reinterpret_cast<char *>(&balance), sizeof(balance));
        outFile.close();
        cout << "Account created sucessfully!" << endl;
    }
    void readData(int userInputAccNo)
    {
        ifstream inFile("accounts.dat", ios::binary);
        if (!inFile)
        {
            throw runtime_error("404!");
        }
        else
        {
            while (true)
            {
                SIZE size;

                int raccno;
                double rintrestRate, rBalance;
                long rphoneno;
                string rname, remail, rpancardno, rpassword;
                char racctype;
                if (!inFile.read(reinterpret_cast<char *>(&raccno), sizeof(raccno)))
                {
                    break;
                }

                if (raccno == userInputAccNo)
                {
                    inFile.read(reinterpret_cast<char *>(&rphoneno), sizeof(rphoneno));
                    inFile.read(reinterpret_cast<char *>(&racctype), sizeof(racctype));
                    inFile.read(reinterpret_cast<char *>(&size.nameSize), sizeof(size.nameSize));
                    rname.resize(size.nameSize);
                    inFile.read(&rname[0], size.nameSize);

                    inFile.read(reinterpret_cast<char *>(&size.emailSize), sizeof(size.emailSize));
                    remail.resize(size.emailSize);
                    inFile.read(&remail[0], size.emailSize);

                    inFile.read(reinterpret_cast<char *>(&size.pancardsizeSize), sizeof(size.pancardsizeSize));
                    rpancardno.resize(size.pancardsizeSize);
                    inFile.read(&rpancardno[0], size.pancardsizeSize);

                    inFile.read(reinterpret_cast<char *>(&size.passwordSize), sizeof(size.passwordSize));
                    rpassword.resize(size.passwordSize);
                    inFile.read(&rpassword[0], size.passwordSize);

                    inFile.read(reinterpret_cast<char *>(&rintrestRate), sizeof(rintrestRate));
                    inFile.read(reinterpret_cast<char *>(&rBalance), sizeof(rBalance));

                    cout << raccno << " | " << rphoneno << " | " << racctype << " | "
                         << rname << " | " << remail << " | " << rpancardno << " | "
                         << rpassword << " | " << rintrestRate << " | " << rBalance << endl;
                    // inFile.close();
                    break;
                }
                else
                {

                    if (!inFile.read(reinterpret_cast<char *>(&rphoneno), sizeof(rphoneno)))
                        break;
                    if (!inFile.read(reinterpret_cast<char *>(&racctype), sizeof(racctype)))
                        break;
                    if (!inFile.read(reinterpret_cast<char *>(&size.nameSize), sizeof(size.nameSize)))
                        break;
                    if (!inFile.seekg(size.nameSize, ios::cur))
                        break;
                    if (!inFile.read(reinterpret_cast<char *>(&size.emailSize), sizeof(size.emailSize)))
                        break;
                    if (!inFile.seekg(size.emailSize, ios::cur))
                        break;
                    if (!inFile.read(reinterpret_cast<char *>(&size.pancardsizeSize), sizeof(size.pancardsizeSize)))
                        break;
                    if (!inFile.seekg(size.pancardsizeSize, ios::cur))
                        break;
                    if (!inFile.read(reinterpret_cast<char *>(&size.passwordSize), sizeof(size.passwordSize)))
                        break;
                    if (!inFile.seekg(size.passwordSize, ios::cur))
                        break;
                    if (!inFile.seekg(sizeof(rintrestRate) + sizeof(rBalance), ios::cur))
                        break;
                }
            }

            inFile.close();
        }
    }
    virtual void createAccount(char type)
    {
        loadLastAccountNumber();
        userAccountNumber = generateAccountNumber();

        cout << userAccountNumber << " " << accountNumber << endl;
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
        writeDataToFile(accountNumber, phoneNumber, accountType, name, email, panCardNumber, password, intrestRate, balance);
    }
    virtual void displayAccount(int accno)
    {

        // ifstream inFile("accounts.dat");
        // if (!inFile)
        // {
        //     cerr << "Error opening file for reading!" << endl;
        //     return;
        // }

        cout << "Loading accounts from file:" << endl;
        string line;
        cout << "Account No | Phone No | Account Type | Name | Email | PAN card number | Password | Intrest Rate | Balance" << endl;

        // while (true)
        // {
        //     int raccountNumber;
        //     long rphoneNumber;
        //     char raccountType;
        //     string rname, remail, rpanCardNumber, rpassword;
        //     double rinterestRate, rbalance;
        //     SIZE size;
        //     if (!inFile.read(reinterpret_cast<char *>(&raccountNumber), sizeof(raccountNumber)))
        //         break;

        //     inFile.read(reinterpret_cast<char *>(&rphoneNumber), sizeof(rphoneNumber));
        //     inFile.read(reinterpret_cast<char *>(&raccountType), sizeof(raccountType));
        //     inFile.read(reinterpret_cast<char *>(&size.nameSize), sizeof(size.nameSize));
        //     rname.resize(size.nameSize);
        //     inFile.read(&rname[0], size.nameSize);
        //     inFile.read(reinterpret_cast<char *>(&size.emailSize), sizeof(size.emailSize));
        //     remail.resize(size.emailSize);
        //     inFile.read(&remail[0], size.emailSize);
        //     inFile.read(reinterpret_cast<char *>(&size.pancardsizeSize), sizeof(size.pancardsizeSize));
        //     rpanCardNumber.resize(size.pancardsizeSize);
        //     inFile.read(&rpanCardNumber[0], size.pancardsizeSize);
        //     inFile.read(reinterpret_cast<char *>(&size.passwordSize), sizeof(size.passwordSize));
        //     rpassword.resize(size.passwordSize);
        //     inFile.read(&rpassword[0], size.passwordSize);
        //     inFile.read(reinterpret_cast<char *>(&rinterestRate), sizeof(rinterestRate));
        //     inFile.read(reinterpret_cast<char *>(&rbalance), sizeof(rbalance));

        //     cout << raccountNumber << " | " << rphoneNumber << " | " << raccountType << " | "
        //          << rname << " | " << remail << " | " << rpanCardNumber << " | "
        //          << rpassword << " | " << rinterestRate << " | " << rbalance << endl;
        // }
        // inFile.close();

        readData(accno);
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
    bool authentication;

public:
    SavingAccount(bool auth)
    {
        authentication = auth;
    }
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
    ++accountNumber;
    saveLastAccountNumber();
    return accountNumber;
}
void BankAccount::saveLastAccountNumber()
{
    ofstream outFile("lastAccountNumber.dat");
    if (outFile)
    {
        outFile << accountNumber;
        outFile.close();
    }
}
void BankAccount::loadLastAccountNumber()
{
    ifstream inFile("lastAccountNumber.dat");
    if (inFile)
    {
        inFile >> accountNumber;
    }
    else
    {
        accountNumber = 1000;
    }
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
    BankAccount::displayAccount(1003);
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

    intrestRate = 0;
}
void CurrentAccount::displayAccount()
{
    BankAccount::displayAccount(1003);
    cout << "No intrest of rate avaiable" << endl;
}

struct LOGGEDINDETAILS
{
    int accno;
    long phoneno;
    char acctype;
    string name, email, pan, password;
    double intrest, balance;
};
void typeOfAccCreation()
{
    char userTypeAccCretaion;
    while (true)
    {
        cout << "Which type of account you want to create  enter c for surrent and s for savings account?";
        cin >> userTypeAccCretaion;
        if (userTypeAccCretaion == 's')
        {
            SavingAccount SA(false);
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
void welcome(BankAccount BA)
{
    cout << "Welcome to out Bank!!" << endl;
    cout << "Enter 1 to login" << endl;
    cout << "Enter 2 to create a new bank account" << endl;
    cout << "Enter 3 to exit" << endl;
    cout << "Enter your choice -> " << endl;
    while (true)
    {
        int userInput;
        cin >> userInput;
        switch (userInput)
        {
        case 1:
            login(BA);
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
void loggedIN(BankAccount BA, bool auth)
{
    cout << "Enter the choice from the following" << endl;
    cout << "1. Enter 1 for displaying your account details";
    cout << "2. Enter 2 for depositing money" << endl;
    cout << "3. Enter 3 for withdrawl money" << endl;
    cout << "4. Enter 4 for transfering money" << endl;
    cout << "5. Enter 5 for logout" << endl;
    int userchoice;
    cin >> userchoice;
    LOGGEDINDETAILS lg;
    SavingAccount SA(auth);
    CurrentAccount CA;
    if (auth)
    {
        switch (userchoice)
        {
        case 1:
            if (lg.acctype == 'c')
            {
            }
            if (lg.acctype == 's')
            {
            }
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            welcome(BA);
            break;
        }
    }
}
void login(BankAccount &b)
{
    cout << "Enter your account number";
    int userloginaccnumber;
    cin >> userloginaccnumber;
    cout << "Enter your password";
    string userloginpass;
    cin >> userloginpass;
    ifstream checkFile("accounts.dat");
    if (!checkFile)
    {
        throw runtime_error("ERROR 404!");
    }
    else
    {
        long cphoneno;
        string cname, cemail, cpassword, cpancard;
        int caccno;
        double cintrestrate, cbalance;
        char cacctype;
        BankAccount::SIZE size;
        bool auth = false;
        checkFile.seekg(0, ios::beg);
        while (true)
        {
            if (!checkFile.read(reinterpret_cast<char *>(&caccno), sizeof(caccno)))
            {
                cout << "404!";
                break;
            }

            if (caccno == userloginaccnumber)
            {
                checkFile.read(reinterpret_cast<char *>(&cphoneno), sizeof(cphoneno));
                checkFile.read(reinterpret_cast<char *>(&cacctype), sizeof(cacctype));
                checkFile.read(reinterpret_cast<char *>(&size.nameSize), sizeof(size.nameSize));
                cname.resize(size.nameSize);
                checkFile.read(&cname[0], size.nameSize);
                checkFile.read(reinterpret_cast<char *>(&size.emailSize), sizeof(size.emailSize));
                cemail.resize(size.emailSize);
                checkFile.read(&cemail[0], size.emailSize);
                checkFile.read(reinterpret_cast<char *>(&size.pancardsizeSize), sizeof(size.pancardsizeSize));
                cpancard.resize(size.pancardsizeSize);
                checkFile.read(&cpancard[0], size.pancardsizeSize);
                checkFile.read(reinterpret_cast<char *>(&size.passwordSize), sizeof(size.passwordSize));
                cpassword.resize(size.passwordSize);
                checkFile.read(&cpassword[0], size.passwordSize);
                checkFile.read(reinterpret_cast<char *>(&cintrestrate), sizeof(cintrestrate));
                checkFile.read(reinterpret_cast<char *>(&cbalance), sizeof(cbalance));
                auth = true;
                LOGGEDINDETAILS lg;
                lg.accno = caccno;
                lg.acctype = cacctype;
                lg.phoneno = cphoneno;
                lg.name = cname;
                lg.email = cemail;
                lg.pan = cpancard;
                lg.balance = cbalance;
                lg.intrest = cintrestrate;
                lg.password = cpassword;
                break;
            }
            else
            {

                if (!checkFile.read(reinterpret_cast<char *>(&cphoneno), sizeof(cphoneno)))
                    break;
                if (!checkFile.read(reinterpret_cast<char *>(&cacctype), sizeof(cacctype)))
                    break;

                if (!checkFile.read(reinterpret_cast<char *>(&size.nameSize), sizeof(size.nameSize)))
                    break;
                if (!checkFile.seekg(size.nameSize, ios::cur))
                    break;

                if (!checkFile.read(reinterpret_cast<char *>(&size.emailSize), sizeof(size.emailSize)))
                    break;
                if (!checkFile.seekg(size.emailSize, ios::cur))
                    break;

                if (!checkFile.read(reinterpret_cast<char *>(&size.pancardsizeSize), sizeof(size.pancardsizeSize)))
                    break;
                if (!checkFile.seekg(size.pancardsizeSize, ios::cur))
                    break;

                if (!checkFile.read(reinterpret_cast<char *>(&size.passwordSize), sizeof(size.passwordSize)))
                    break;
                if (!checkFile.seekg(size.passwordSize, ios::cur))
                    break;

                if (!checkFile.seekg(sizeof(cintrestrate) + sizeof(cbalance), ios::cur))
                    break;
            }
        }
        if (auth)
        {
            if (caccno == userloginaccnumber && userloginpass == cpassword)
            {
                cout << "User Found logged in";
                loggedIN(b, auth);
            }
            else
            {
                cout << "user not found";
            }
        }
    }
}
void logout() {}
int main()
{
    BankAccount BA;
    welcome(BA);
}