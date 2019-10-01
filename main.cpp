//
// Created by Albert Joshua Capistrano
// RUID:182004011
// Stock and bank system Project
// 5/5/2018
//

#include "header.h"
#include<iostream>
#include "time.h"
#include "stocks.h"
#include "bank.h"


int main(){

    Account acc;

    stocks a1;
    bank a2;

    bool check = true;
    int selection = 0;
    char test[256];
    string line;
    while (check)
    {
        cout << "Choose one of the options to access:" << endl
             << "\t1. Stock Portfolio Account" << endl
             << "\t2. Bank Account" << endl
             << "\t3. Exit" << endl
             << "\tYour Selection: ";

        cin.getline(test, 256);
        selection = atoi(test);

        switch (selection)
        {
            case 1:
                a1.menu(acc);
                break;
            case 2:
                a2.menu(acc);
                break;
            case 3:
                check = false;
                break;
            default:
                cout << "\nInvalid entry. Please enter an option.\n " << endl;
                break;
        }
    }
    return 0;

}