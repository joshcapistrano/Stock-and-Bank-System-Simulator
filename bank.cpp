//
// Created by Josh Capistrano on 5/3/18.
//
#include <time.h>
#include "header.h"
#include "stocks.h"
#include "bank.h"

bank::bank()
{
    cout << "Bank Account created." << endl;
}

void bank::menu(Account& account)
{
    bool check = true;
    int selection;
    int in = 256;
    char test[in];
    while (check)
    {
        cout << "\nPlease select an option" << endl
             << "\t1. View account balance" << endl
             << "\t2. Deposit money" << endl
             << "\t3. Withdraw money" << endl
             << "\t4. Display transaction history" << endl
             << "\t5. Return to previous menu" << endl;

        cout << "\tYour selection: ";

        cin.getline(test, in);

        selection = atoi(test);

        switch (selection)
        {
            case 1:
                displayPortfolio(account);
                break;
            case 2:
            {
                string line;
                double amount;
                cout << "\n\t Deposit Amount: ";
                getline(cin, line);
                amount = stod(line);
                deposit(account, amount);
                break;
            }
            case 3:
            {
                string line;
                double amount;
                cout << "\n\tWithdraw Amount: ";
                getline(cin, line);
                amount = stod(line);
                withdraw(account, amount);
                break;
            }
            case 4:
                displayTransactions(account);
                break;
            case 5:
                check = false;
                break;
            default:
                cout << "\nInvalid option. Please select an option. " << endl;
                break;
        }
    }
}
void bank::displayPortfolio(Account& account)
{
    vector<Stock> port = account.portfolioList;
    cout << "\tCurrent Cash Balance: $" << account.balance << endl;
    double totalbal=0;
    for (size_t i = 0; i < port.size(); i++)
    {
        cout << "\n\tSymbol: " << port[i].symbol << "\n\tNumber of Shares: " << port[i].amount << "\n\tPrice: $"
             << port[i].price << "\n\tCompany: " << port[i].company << "\nTotal: " << port[i].total << endl;
        totalbal += port[i].total;

    }

    cout << "\tTotal Portfolio Value: " << account.balance + totalbal << endl;


}

void bank::deposit(Account& account, double val)
{
    cout << "\nEnter amount: " << val << endl;
    account.balance += val;
    string ttime;
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    ttime = to_string(rawtime);
    ttime = asctime(timeinfo);

    string line = "Deposit: " + to_string(val) + "\nCurrent balance: $" + to_string(account.balance)+ "\nDate and time of Deposit: " + ttime + "\n";

    ofstream myfile;
    myfile.open("bank_transaction_history.txt", ios_base::app);
    myfile << line;
    cout<<"Deposit successful."<<endl;
    myfile.close();

    //displayPortfolio(account);
}

void bank::withdraw(Account& account, double val)
{
    cout << "\nEnter amount: " << val << endl;
    account.balance -= val;
    string ttime;
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    ttime = asctime(timeinfo);

    string line = "Withdraw: " + to_string(val) + "\nCurrent balance: $" + to_string(account.balance) + "\nDate and time of withdrawal: " + ttime + "\n";

    ofstream myfile;
    myfile.open("bank_transaction_history.txt", ios_base::app);
    myfile << line;
    cout<<"Withdrawal successful."<<endl;
    myfile.close();

    //displayPortfolio(account);

}

void bank::displayTransactions(Account& account)
{

    ifstream file("bank_transaction_history.txt");
    string line;
    while (getline(file, line))
        cout << line << endl;
    file.close();

}

