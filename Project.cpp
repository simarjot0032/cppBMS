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
struct LOGGEDINDETAILS
{
    int accno;
    long phoneno;
    char acctype;
    string name, email, pan, password;
    double intrest, balance;
};
LOGGEDINDETAILS lg;
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
                    // Added to ignore so it could read multiple reacords
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

        cout << "Account Number -> " << userAccountNumber;
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
            // return;
            exit;
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
    }
    virtual void displayAccount(int accno)
    {

        cout << "Loading accounts from file:" << endl;
        cout << "Account No | Phone No | Account Type | Name | Email | PAN card number | Password | Intrest Rate | Balance" << endl;

        readData(accno);
    }
    virtual void deposit(bool auth)
    {
        if (auth)
        {

            bool updated = false;
            fstream depFile("accounts.dat", ios::in | ios::out);
            while (true)
            {
                int rAccNo;
                long rPhoneNo;
                char rAccType;
                string rName, rEmail, rPanCard, rPassword;
                double rInterestRate, rBalance;
                SIZE size;
                if (!depFile.read(reinterpret_cast<char *>(&rAccNo), sizeof(rAccNo)))
                {
                    cout << "404!";
                    break;
                }

                if (rAccNo == lg.accno)
                {
                    depFile.read(reinterpret_cast<char *>(&rPhoneNo), sizeof(rPhoneNo));
                    depFile.read(reinterpret_cast<char *>(&rAccType), sizeof(rAccType));

                    depFile.read(reinterpret_cast<char *>(&size.nameSize), sizeof(size.nameSize));
                    rName.resize(size.nameSize);
                    depFile.read(&rName[0], size.nameSize);

                    depFile.read(reinterpret_cast<char *>(&size.emailSize), sizeof(size.emailSize));
                    rEmail.resize(size.emailSize);
                    depFile.read(&rEmail[0], size.emailSize);

                    depFile.read(reinterpret_cast<char *>(&size.pancardsizeSize), sizeof(size.pancardsizeSize));
                    rPanCard.resize(size.pancardsizeSize);
                    depFile.read(&rPanCard[0], size.pancardsizeSize);

                    depFile.read(reinterpret_cast<char *>(&size.passwordSize), sizeof(size.passwordSize));
                    rPassword.resize(size.passwordSize);
                    depFile.read(&rPassword[0], size.passwordSize);

                    depFile.read(reinterpret_cast<char *>(&rInterestRate), sizeof(rInterestRate));
                    depFile.read(reinterpret_cast<char *>(&rBalance), sizeof(rBalance));
                    cout << "Enter the amount you want to deposit";
                    cin >> depMoney;
                    rBalance += depMoney;
                    depFile.seekp(-sizeof(rBalance), ios::cur);
                    depFile.write(reinterpret_cast<char *>(&rBalance), sizeof(rBalance));
                    updated = true;
                    lg.balance = rBalance;
                    cout << lg.balance;
                    break;
                }
                else
                {

                    depFile.read(reinterpret_cast<char *>(&rPhoneNo), sizeof(rPhoneNo));
                    depFile.read(reinterpret_cast<char *>(&rAccType), sizeof(rAccType));

                    depFile.read(reinterpret_cast<char *>(&size.nameSize), sizeof(size.nameSize));
                    depFile.seekg(size.nameSize, ios::cur);

                    depFile.read(reinterpret_cast<char *>(&size.emailSize), sizeof(size.emailSize));
                    depFile.seekg(size.emailSize, ios::cur);

                    depFile.read(reinterpret_cast<char *>(&size.pancardsizeSize), sizeof(size.pancardsizeSize));
                    depFile.seekg(size.pancardsizeSize, ios::cur);

                    depFile.read(reinterpret_cast<char *>(&size.passwordSize), sizeof(size.passwordSize));
                    depFile.seekg(size.passwordSize, ios::cur);

                    depFile.seekg(sizeof(rInterestRate) + sizeof(rBalance), ios::cur);
                }
            }
            depFile.close();
            if (updated)
            {
                cout << "Money deposit sucessfull" << endl;
                cout << "The updated balance is -> " << lg.balance;
            }
        }
    }
    virtual void withdraw()
    {
        bool updated = false;

        fstream withFile("accounts.dat", ios::in | ios::out);
        if (!withFile)
        {
            cout << "Error has been occured try again later" << endl;
            return;
        }
        SIZE size;

        while (true)
        {
            int waccno;
            long wphoneno;
            double wintrestRate, wbalance;
            string wname, wemail, wpassword, wpanCardNo;
            char wacctype;

            if (!withFile.read(reinterpret_cast<char *>(&waccno), sizeof(waccno)))
            {
                cout << "404!" << endl;
                break;
            }
            if (waccno == lg.accno)
            {
                withFile.read(reinterpret_cast<char *>(&wphoneno), sizeof(wphoneno));
                withFile.read(reinterpret_cast<char *>(&wacctype), sizeof(wacctype));
                withFile.read(reinterpret_cast<char *>(&size.nameSize), sizeof(size.nameSize));
                wname.resize(size.nameSize);
                withFile.read(&wname[0], size.nameSize);
                withFile.read(reinterpret_cast<char *>(&size.emailSize), sizeof(size.emailSize));
                wemail.resize(size.emailSize);
                withFile.read(&wemail[0], size.emailSize);
                withFile.read(reinterpret_cast<char *>(&size.pancardsizeSize), sizeof(size.pancardsizeSize));
                wpanCardNo.resize(size.pancardsizeSize);
                withFile.read(&wpanCardNo[0], size.pancardsizeSize);
                withFile.read(reinterpret_cast<char *>(&size.passwordSize), sizeof(size.passwordSize));
                wpassword.resize(size.passwordSize);
                withFile.read(&wpassword[0], size.passwordSize);
                withFile.read(reinterpret_cast<char *>(&wintrestRate), sizeof(wintrestRate));
                withFile.read(reinterpret_cast<char *>(&wbalance), sizeof(wbalance));
                cout << "Enter the amount you want to withdraw";
                cin >> witMoney;
                if (lg.acctype == 's')
                {
                    if (wbalance - witMoney >= 2000)
                    {
                        wbalance -= witMoney;
                        withFile.seekp(-sizeof(wbalance), ios::cur);
                        withFile.write(reinterpret_cast<char *>(&wbalance), sizeof(wbalance));
                        updated = true;
                    }
                    else
                    {
                        cout << "Innsufficient Balance" << endl;
                    }
                }
                else if (lg.acctype == 'c')
                {
                    if (wbalance - witMoney >= 5000)
                    {
                        wbalance -= witMoney;
                        withFile.seekp(-sizeof(wbalance), ios::cur);
                        withFile.write(reinterpret_cast<char *>(&wbalance), sizeof(wbalance));
                        updated = true;
                    }
                    else
                    {
                        cout << "Innsufficient Balance" << endl;
                    }
                }
            }
            else
            {
                withFile.read(reinterpret_cast<char *>(&wphoneno), sizeof(wphoneno));
                withFile.read(reinterpret_cast<char *>(&wacctype), sizeof(wacctype));

                withFile.read(reinterpret_cast<char *>(&size.nameSize), sizeof(size.nameSize));
                withFile.seekg(size.nameSize, ios::cur);

                withFile.read(reinterpret_cast<char *>(&size.emailSize), sizeof(size.emailSize));
                withFile.seekg(size.emailSize, ios::cur);

                withFile.read(reinterpret_cast<char *>(&size.pancardsizeSize), sizeof(size.pancardsizeSize));
                withFile.seekg(size.pancardsizeSize, ios::cur);

                withFile.read(reinterpret_cast<char *>(&size.passwordSize), sizeof(size.passwordSize));
                withFile.seekg(size.passwordSize, ios::cur);

                withFile.seekg(sizeof(wintrestRate) + sizeof(wbalance), ios::cur);
            }
        }
    }
    virtual void transfer()
    {

        int recipientAccNo;
        double transferAmount;
        cout << "Enter the recipient's account number: ";
        cin >> recipientAccNo;
        if (recipientAccNo == lg.accno)
        {
            cout << "You cannot transfer money to your own account." << endl;
            return;
        }
        cout << "Enter the amount you want to transfer: ";
        cin >> transferAmount;

        // Check if sufficient balance is available
        if ((lg.acctype == 's' && lg.balance - transferAmount < 2000) ||
            (lg.acctype == 'c' && lg.balance - transferAmount < 5000))
        {
            cout << "Insufficient balance to make the transfer." << endl;
            return;
        }

        // Open the file for reading and writing
        fstream accFile("accounts.dat", ios::in | ios::out | ios::binary);
        if (!accFile)
        {
            cout << "Error opening accounts file." << endl;
            return;
        }

        // Variables to store account information
        bool senderUpdated = false;
        bool recipientUpdated = false;

        while (true)
        {
            int accNo;
            long phoneNo;
            char accType;
            string name, email, panCard, password;
            double interestRate, balance;
            SIZE size;
            streampos recordStartPos = accFile.tellg();

            if (!accFile.read(reinterpret_cast<char *>(&accNo), sizeof(accNo)))
                break;

            accFile.read(reinterpret_cast<char *>(&phoneNo), sizeof(phoneNo));
            accFile.read(reinterpret_cast<char *>(&accType), sizeof(accType));

            accFile.read(reinterpret_cast<char *>(&size.nameSize), sizeof(size.nameSize));
            name.resize(size.nameSize);
            accFile.read(&name[0], size.nameSize);

            accFile.read(reinterpret_cast<char *>(&size.emailSize), sizeof(size.emailSize));
            email.resize(size.emailSize);
            accFile.read(&email[0], size.emailSize);

            accFile.read(reinterpret_cast<char *>(&size.pancardsizeSize), sizeof(size.pancardsizeSize));
            panCard.resize(size.pancardsizeSize);
            accFile.read(&panCard[0], size.pancardsizeSize);

            accFile.read(reinterpret_cast<char *>(&size.passwordSize), sizeof(size.passwordSize));
            password.resize(size.passwordSize);
            accFile.read(&password[0], size.passwordSize);

            accFile.read(reinterpret_cast<char *>(&interestRate), sizeof(interestRate));
            accFile.read(reinterpret_cast<char *>(&balance), sizeof(balance));

            if (accNo == lg.accno && !senderUpdated)
            {
                balance -= transferAmount;
                lg.balance = balance;
                accFile.seekp(-sizeof(balance), ios::cur);
                accFile.write(reinterpret_cast<char *>(&balance), sizeof(balance));
                senderUpdated = true;
                // Reset stream to beginning for next read
                accFile.seekg(0, ios::beg);
                continue;
            }

            if (accNo == recipientAccNo && !recipientUpdated)
            {

                balance += transferAmount;
                accFile.seekp(-sizeof(balance), ios::cur);

                accFile.write(reinterpret_cast<char *>(&balance), sizeof(balance));
                recipientUpdated = true;
                accFile.seekg(0, ios::beg);

                continue;
            }

            if (senderUpdated && recipientUpdated)
            {
                break;
            }
        }

        accFile.close();

        if (senderUpdated && recipientUpdated)
        {
            cout << "Transfer successful. Your updated balance is: " << lg.balance << endl;
        }
        else if (!recipientUpdated)
        {
            cout << "Recipient account not found. Transfer canceled." << endl;

            fstream revertFile("accounts.dat", ios::in | ios::out | ios::binary);
            if (!revertFile)
            {
                cout << "Error opening accounts file to revert transaction." << endl;
                return;
            }
            while (true)
            {
                int accNo;
                long phoneNo;
                char accType;
                string name, email, panCard, password;
                double interestRate, balance;
                SIZE size;
                streampos recordStartPos = revertFile.tellg();

                if (!revertFile.read(reinterpret_cast<char *>(&accNo), sizeof(accNo)))
                    break;

                revertFile.read(reinterpret_cast<char *>(&phoneNo), sizeof(phoneNo));
                revertFile.read(reinterpret_cast<char *>(&accType), sizeof(accType));

                revertFile.read(reinterpret_cast<char *>(&size.nameSize), sizeof(size.nameSize));
                name.resize(size.nameSize);
                revertFile.read(&name[0], size.nameSize);

                revertFile.read(reinterpret_cast<char *>(&size.emailSize), sizeof(size.emailSize));
                email.resize(size.emailSize);
                revertFile.read(&email[0], size.emailSize);

                revertFile.read(reinterpret_cast<char *>(&size.pancardsizeSize), sizeof(size.pancardsizeSize));
                panCard.resize(size.pancardsizeSize);
                revertFile.read(&panCard[0], size.pancardsizeSize);

                revertFile.read(reinterpret_cast<char *>(&size.passwordSize), sizeof(size.passwordSize));
                password.resize(size.passwordSize);
                revertFile.read(&password[0], size.passwordSize);

                revertFile.read(reinterpret_cast<char *>(&interestRate), sizeof(interestRate));
                revertFile.read(reinterpret_cast<char *>(&balance), sizeof(balance));

                if (accNo == lg.accno)
                {

                    balance += transferAmount;
                    lg.balance = balance;

                    revertFile.seekp(-sizeof(balance), ios::cur);

                    revertFile.write(reinterpret_cast<char *>(&balance), sizeof(balance));
                    break;
                }
            }
            revertFile.close();
        }
        else
        {
            cout << "An error occurred during the transfer. Please try again." << endl;
        }
    }

    virtual void deleteacc()
    {
        int raccno;
        double rintrestRate, rBalance;
        long rphoneno;
        string rname, remail, rpancardno, rpassword;
        char racctype, confirmation;
        cout << "Are you sure you want to delete your account?" << endl
             << "This action cannot be undone. (y/n): ";
        cin >> confirmation;
        if (confirmation != 'y' && confirmation != 'Y')
        {
            cout << "Account deletion canceled." << endl;
            return;
        }

        ifstream inFile("accounts.dat", ios::binary);
        ofstream outFile("accounts_temp.dat", ios::binary);
        if (!inFile || !outFile)
        {
            cout << "Error opening file!" << endl;
            return;
        }

        bool found = false;
        SIZE size;
        while (true)
        {
            if (!inFile.read(reinterpret_cast<char *>(&raccno), sizeof(raccno)))
                break;

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

            if (raccno == lg.accno)
            {
                found = true;

                continue;
            }
            else
            {
                outFile.write(reinterpret_cast<char *>(&raccno), sizeof(raccno));
                outFile.write(reinterpret_cast<char *>(&rphoneno), sizeof(rphoneno));
                outFile.write(reinterpret_cast<char *>(&racctype), sizeof(racctype));

                outFile.write(reinterpret_cast<char *>(&size.nameSize), sizeof(size.nameSize));
                outFile.write(rname.c_str(), size.nameSize);

                outFile.write(reinterpret_cast<char *>(&size.emailSize), sizeof(size.emailSize));
                outFile.write(remail.c_str(), size.emailSize);

                outFile.write(reinterpret_cast<char *>(&size.pancardsizeSize), sizeof(size.pancardsizeSize));
                outFile.write(rpancardno.c_str(), size.pancardsizeSize);

                outFile.write(reinterpret_cast<char *>(&size.passwordSize), sizeof(size.passwordSize));
                outFile.write(rpassword.c_str(), size.passwordSize);

                outFile.write(reinterpret_cast<char *>(&rintrestRate), sizeof(rintrestRate));
                outFile.write(reinterpret_cast<char *>(&rBalance), sizeof(rBalance));
            }
        }

        inFile.close();
        outFile.close();

        if (found)
        {

            if (remove("accounts.dat") != 0)
            {
                cout << "Error deleting the original file!" << endl;
                return;
            }
            if (rename("accounts_temp.dat", "accounts.dat") != 0)
            {
                cout << "Error renaming the temporary file!" << endl;
                return;
            }
            cout << "Your account has been successfully deleted." << endl;
        }
        else
        {
            cout << "Account not found. Please try again." << endl;

            remove("accounts_temp.dat");
        }
    }
    virtual void changepass()
    {
        string currentPassword, newPassword, confirmPassword;
        cout << "Enter your current password: ";
        cin >> currentPassword;

        if (currentPassword != lg.password)
        {
            cout << "Incorrect current password. Password change aborted." << endl;
            return;
        }

        cout << "Enter your new password (minimum 8 characters): ";
        cin >> newPassword;

        if (newPassword.length() < 8)
        {
            cout << "Password must be at least 8 characters long. Password change aborted." << endl;
            return;
        }

        cout << "Confirm your new password: ";
        cin >> confirmPassword;

        if (newPassword != confirmPassword)
        {
            cout << "Passwords do not match. Password change aborted." << endl;
            return;
        }

        fstream accFile("accounts.dat", ios::in | ios::out | ios::binary);
        if (!accFile)
        {
            cout << "Error opening accounts file." << endl;
            return;
        }

        bool passwordUpdated = false;

        while (true)
        {
            int accNo;
            long phoneNo;
            char accType;
            string name, email, panCard, password;
            double interestRate, balance;
            SIZE size;
            streampos recordStartPos = accFile.tellg();

            if (!accFile.read(reinterpret_cast<char *>(&accNo), sizeof(accNo)))
                break;

            accFile.read(reinterpret_cast<char *>(&phoneNo), sizeof(phoneNo));
            accFile.read(reinterpret_cast<char *>(&accType), sizeof(accType));

            accFile.read(reinterpret_cast<char *>(&size.nameSize), sizeof(size.nameSize));
            name.resize(size.nameSize);
            accFile.read(&name[0], size.nameSize);

            accFile.read(reinterpret_cast<char *>(&size.emailSize), sizeof(size.emailSize));
            email.resize(size.emailSize);
            accFile.read(&email[0], size.emailSize);

            accFile.read(reinterpret_cast<char *>(&size.pancardsizeSize), sizeof(size.pancardsizeSize));
            panCard.resize(size.pancardsizeSize);
            accFile.read(&panCard[0], size.pancardsizeSize);

            accFile.read(reinterpret_cast<char *>(&size.passwordSize), sizeof(size.passwordSize));
            password.resize(size.passwordSize);
            accFile.read(&password[0], size.passwordSize);

            if (accNo == lg.accno)
            {
                int totalBytesToMoveBack = size.passwordSize + sizeof(size.passwordSize);
                accFile.seekp(-totalBytesToMoveBack, ios::cur);
                size.passwordSize = newPassword.size();
                accFile.write(reinterpret_cast<char *>(&size.passwordSize), sizeof(size.passwordSize));
                accFile.write(newPassword.c_str(), size.passwordSize);
                passwordUpdated = true;
                lg.password = newPassword;
                cout << "Password changed successfully." << endl;
                break;
            }
        }

        if (!passwordUpdated)
        {
            cout << "An error occurred while changing the password." << endl;
        }

        accFile.close();
    }
};

class SavingAccount : public BankAccount
{
protected:
    int min = 2000;
    bool authentication;

public:
    SavingAccount() {}
    SavingAccount(bool auth)
    {
        authentication = auth;
    }
    void createAccount(char type);
    void displayAccount(int accno);
    void deposit()
    {
        BankAccount::deposit(authentication);
    }
    void withdraw()
    {
        BankAccount::withdraw();
    }
    void deleteacc()
    {
        BankAccount::deleteacc();
    }
};
class CurrentAccount : public BankAccount
{
protected:
    int min = 5000;
    bool authentication;

public:
    CurrentAccount() {}
    CurrentAccount(bool auth)
    {
        authentication = auth;
    }
    void createAccount(char type);
    void displayAccount(int accno);
    void deposit()
    {
        BankAccount::deposit(authentication);
    }
    void withdraw()
    {
        BankAccount::withdraw();
    }
    void deleteacc()
    {
        BankAccount::deleteacc();
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
    intrestRate = 3.0;
    cout << "The rate of intrest is 3%" << endl;
    BankAccount::writeDataToFile(accountNumber, phoneNumber, accountType, name, email, panCardNumber, password, intrestRate, balance);
}
// Saving account display function
void SavingAccount::displayAccount(int accno)
{
    if (authentication)
    {
        cout << "Loading accounts from file:" << endl;
        cout << "Account No | Phone No | Account Type | Name | Email | PAN card number | Password | Intrest Rate | Balance" << endl;
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

                if (raccno == lg.accno)
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

                    break;
                }
                else
                {
                    // Add to ignore so it could read multiple recods
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
}

// Current account functions
// Current account creation function
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
    BankAccount::writeDataToFile(accountNumber, phoneNumber, accountType, name, email, panCardNumber, password, intrestRate, balance);
}
void CurrentAccount::displayAccount(int accno)
{
    cout << "Loading accounts from file:" << endl;
    cout << "Account No | Phone No | Account Type | Name | Email | PAN card number | Password | Intrest Rate | Balance" << endl;
    if (authentication)
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

                if (raccno == lg.accno)
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
}

// Structure for logged in details
void typeOfAccCreation()
{
    char userTypeAccCretaion;
    while (true)
    {
        cout << "Which type of account you want to create  enter c for surrent and s for savings account?";
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
void welcome(BankAccount BA)
{
    cout << "Welcome to out Bank!!" << endl;
    cout << "Enter 1 to login" << endl;
    cout << "Enter 2 to create a new bank account" << endl;
    cout << "Enter 3 to exit" << endl;
    cout << "Enter your choice -> ";
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

void loggedIN(bool auth)
{
    cout << "Enter the choice from the following:- " << endl;
    cout << "1. Enter 1 for displaying your account details." << endl;
    cout << "2. Enter 2 for depositing money." << endl;
    cout << "3. Enter 3 for withdrawl money." << endl;
    cout << "4. Enter 4 for transfering money." << endl;
    cout << "5. Enter 5 for change password" << endl;
    cout << "6. Enter 6 for deleting account" << endl;
    cout << "7. Enter 7 for logout." << endl;
    cout << "Enter you choice-> ";
    int userchoice;
    cin >> userchoice;

    if (auth)
    {
        BankAccount BA;
        SavingAccount SA(auth);
        CurrentAccount CA(auth);
        switch (userchoice)
        {
        case 1:

            if (lg.acctype == 's')
            {
                SA.displayAccount(lg.accno);
            }
            if (lg.acctype == 'c')
            {
                CA.displayAccount(lg.accno);
            }
            break;
        case 2:
            if (lg.acctype == 's')
            {
                SA.deposit();
            }
            if (lg.acctype == 'c')
            {
                CA.deposit();
            }
            break;
        case 3:
            if (lg.acctype == 's')
            {
                SA.withdraw();
            }
            if (lg.acctype == 'c')
            {
                CA.withdraw();
            }
            break;
        case 4:
            BA.transfer();
            break;

        case 5:
            BA.changepass();
            break;
        case 6:
            BA.deleteacc();
            break;
        case 7:
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
                cout << "404!" << endl;
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
                loggedIN(auth);
            }
            else
            {
                cout << "user not found";
            }
        }
    }
}
void logout()
{
    BankAccount BA;
    welcome(BA);
}
int main()
{

    BankAccount BA;
    welcome(BA);
}