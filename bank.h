//
// Created by Josh Capistrano on 5/3/18.
//
#include "stocks.h"
#include "header.h"

#ifndef PROJECTSTOCKS_BANK_H
#define PROJECTSTOCKS_BANK_H

class bank
{
public:
    bank();
    void displayPortfolio(Account&);
    void displayTransactions(Account&);
    void menu(Account&);
    void deposit(Account&, double);
    void withdraw(Account&, double);

private:

};



#endif //PROJECTSTOCKS_BANK_H
