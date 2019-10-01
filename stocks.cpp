//
// Created by Josh Capistrano on 5/3/18.
//

#include <string>
#include <fstream>
#include <vector>
#include "stocks.h"
#include "header.h"

stocks::stocks() {
    cout<<"Stocks account created."<<endl;
}

void stocks::menu(Account & account) {

    bool check = true;
    int choice = 0;
    int in = 256;
    char test[in];

    while(check == true){
        cout << "\nPlease select an option" << endl
             << "\t1. Display current price for a stock symbol" << endl
             << "\t2. Buy stock" << endl
             << "\t3. Sell stock" << endl
             << "\t4. Display current portfolio" << endl
             << "\t5. Display transaction history" << endl
             << "\t6. Return to previous menu" << endl;

        cout << "\tYour selection: ";

        cin.getline(test, in);
        cout<<"Balance: $"<<account.balance<<endl;
        choice = atoi(test);

        switch(choice){
            case 1: {
                cout << "\nEnter stock symbol to check current price: " << endl;
                char input[in];
                cin.getline(input, in);
                string company(input);
                stockPrice(company);
                break;
            }

            case 2: {
                cout << "Enter stock to buy (then press space)" << "\nEnter how many shares (press space)" << "\nEnter how much you would like to buy"
                     << endl;
                cout << "Enter: ";
                string inputLine;
                getline(cin, inputLine);
                string blank = " ";

                string companySymbol;
                int numShares;
                double numPrice;
                for (int i = 0; i < 3; i++) {
                    if (i == 0)
                        companySymbol = inputLine.substr(0, inputLine.find(blank));
                    else if (i == 1)
                        numShares = stoi(inputLine.substr(0, inputLine.find(blank)));
                    else if (i == 2)
                        numPrice = stod(inputLine);

                    inputLine = inputLine.substr(inputLine.find(blank) + 1, string::npos);
                }
                buyStock(account, companySymbol, numShares, numPrice);
                break;
            }

            case 3: {
                cout << "Enter stock to sell (then press space)" << "\nEnter how many shares (press space)" << "\nEnter how much you would like to sell"
                     << endl;
                cout << "Enter below please: ";
                string inputLine2;
                getline(cin, inputLine2);
                string in = " ";
                string compSym;
                int numShare;
                double numPrices;

                for (int i = 0; i < 3; i++) {
                    if (i == 0)
                        compSym = inputLine2.substr(0, inputLine2.find(in));
                    else if (i == 1)
                        numShare = stoi(inputLine2.substr(0, inputLine2.find(in)));
                    else if (i == 2)
                        numPrices = stod(inputLine2);

                    inputLine2 = inputLine2.substr(inputLine2.find(in) + 1, string::npos);
                }
                sellStock(account, compSym, numShare, numPrices);
                break;
            }
            case 4:
                displayPortfolio(account);
                break;
            case 5:
                displayTransactions(account);
                break;
            case 6:
                check = false;
                break;
            default:
                cout<<"\nInvalid input please enter valid input."<<endl;
                break;
        }
    }

}

void stocks::stockPrice(string symbol)
{
    cout <<"\nSymbol: " << symbol << endl;

    srand((unsigned int)time(NULL));
    int num = rand() % 4 + 1;
    string name = "stock" + to_string(num) + ".txt";

    ifstream file;
    file.open(name);

    string line;
    while (getline(file, line))
    {
        string delim = "\t";
        vector <string> tokens;
        string stockInfo;
        stockInfo = line;
        string substring;
        substring = line.substr(0, line.find(delim));

        if (substring.compare(symbol) == 0)
        {
            cout << stockInfo << endl;
            string ttime;
            time_t rawtime;
            struct tm * timeinfo;

            time (&rawtime);
            timeinfo = localtime (&rawtime);
            ttime = asctime(timeinfo);
            cout<<"As of: "<<ttime<<endl;

            break;
        }
    }
    file.close();
}

void stocks::buyStock(Account& account, string symbol, int numShare, double price)
{
    cout << "\n\tSymbol: " << symbol << "\n\tShare: " << numShare << "\n\tPrice: $" << price << endl<<"\n";
    Stock port;
    port.amount = numShare;
    port.price = price;
    port.symbol = symbol;
    port.total = price * numShare;

    srand((unsigned int)time(NULL));
    int num = rand() % 4 + 1;
    string name = "stock" + to_string(num) + ".txt";
    ifstream file;
    file.open(name);

    string line;
    while (getline(file, line))
    {
        string delim = "\t";
        vector <string> tokens;
        string stockInfo;
        stockInfo = line;
        string substring;
        substring = line.substr(0, line.find(delim));
        double stockPrice = stod(line.substr(line.rfind(delim) + 1, string::npos));

        if (substring.compare(symbol) == 0)
        {
            cout << stockInfo << endl;
            if (price >= stockPrice)
            {
                line = line.substr(line.find(delim) + 1, string::npos);
                string company = line.substr(0, line.find(delim));
                port.company = company;
                account.portfolioList.push_back(port);
                account.balance -= numShare * price;
                string ttime;
                time_t rawtime;
                struct tm * timeinfo;

                time (&rawtime);
                timeinfo = localtime (&rawtime);
                ttime = asctime(timeinfo);

                string line = "Buy:" + symbol + "\nNumber of shares: " + to_string(numShare) + "\nPrice: $" + to_string(price) + "\nTime and date of purchase: " + ttime + "\n";

                ofstream myfile;
                myfile.open("stock_transaction_history.txt", ios_base::app);
                myfile << line;
                myfile.close();
            }
            else
            {
                cout << "\nTransaction could not be completed." << endl;
            }
            break;
        }
    }
    file.close();
}

void stocks::sellStock(Account& account, string symbol, int numShare, double price)
{
    cout << "\n\tSymbol: " << symbol << "\tShare: " << numShare << "\tPrice: $" << price << endl << "\n";
    Stock port;
    port.amount = numShare;
    port.price = price;
    port.symbol = symbol;
    port.total = price * numShare;


    vector<Stock> portList = account.portfolioList;
    for (size_t j = 0; j < portList.size(); j++)
    {
        if (portList[j].symbol.compare(symbol) == 0)
        {
            if (portList[j].amount >= numShare)
            {
                srand((unsigned int)time(NULL));
                int num = rand() % 4 + 1;
                string name = "stock" + to_string(num) + ".txt";
                ifstream file;
                file.open(name);

                string line;
                while (getline(file, line))
                {
                    string delim = "\t";
                    vector <string> tokens;
                    string stockInfo;
                    stockInfo = line;
                    string substring;
                    substring = line.substr(0, line.find(delim));
                    double stockPrice = stod(line.substr(line.rfind(delim) + 1, string::npos));

                    if (substring.compare(symbol) == 0)
                    {
                        cout << stockInfo << endl;
                        if (price <= stockPrice)
                        {
                            if (portList[j].amount > numShare)
                            {
                                account.balance += numShare * price;
                                portList[j].amount = portList[j].amount - numShare;
                                portList[j].total = portList[j].amount * portList[j].price;
                                account.portfolioList[j] = portList[j];

                                string ttime;
                                time_t rawtime;
                                struct tm * timeinfo;

                                time (&rawtime);
                                timeinfo = localtime (&rawtime);
                                ttime = asctime(timeinfo);

                                string line = "Sell: " + symbol + "\nNumber of shares: " + to_string(numShare) + "\nPrice: $" + to_string(price) + "\nTime and date sold: " + ttime + "\n";

                                ofstream myfile;
                                myfile.open("stock_transaction_history.txt", ios_base::app);
                                myfile << line;
                                myfile.close();
                            }
                            else if (portList[j].amount = numShare) {
                                account.balance += numShare * price;

                                portList.erase(portList.begin() + j);
                                account.portfolioList = portList;
                                string ttime;
                                time_t rawtime;
                                struct tm * timeinfo;

                                time (&rawtime);
                                timeinfo = localtime (&rawtime);
                                ttime = asctime(timeinfo);

                                string line = "Sell: " + symbol + "\nNumber of shares: " + to_string(numShare) + "\nPrice: $" + to_string(price) + "\nTime and date sold: " + ttime + "\n";

                                ofstream myfile;
                                myfile.open("stock_transaction_history.txt", ios_base::app);
                                myfile << line;
                                myfile.close();
                            }
                        }
                        else
                        {
                            cout << "\nTransaction could not be completed" << endl;
                        }
                        break;
                    }
                }
                file.close();

            }
            else
            {
                cout << "Not enough shares" << endl;
            }
        }
        else
        {
            cout << "None of this stock" << endl;
        }
    }
}

void stocks::displayPortfolio(Account& account)
{
    vector<Stock> port = account.portfolioList;
    cout << "\tCash Balance: $" << account.balance << endl;
    double totalbal = 0;
    for (size_t i = 0; i < port.size(); i++)
    {
        cout << "\tSymbol: " << port[i].symbol << "\n\tShare: " << port[i].amount << "\n\tPrice: $"
             << port[i].price << "\n\tCompany: " << port[i].company << "\n\tTotal: $" << port[i].total << endl;
        totalbal += port[i].total;
    }
    cout << "\tTotal Portfolio Value: " << account.balance + totalbal << endl;
}

void stocks::displayTransactions(Account& account)
{
    ifstream file("stock_transaction_history.txt");
    string line;
    while (getline(file, line))
        cout << fixed << setprecision(2) << setfill('0') << line << endl;
    file.close();
}