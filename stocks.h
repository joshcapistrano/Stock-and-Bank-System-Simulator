//
// Created by Josh Capistrano on 5/3/18.
//

#ifndef PROJECTSTOCKS_STOCKS_H
#define PROJECTSTOCKS_STOCKS_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "header.h"
#include <ctime>
#include <iomanip>

using namespace std;

class stocks
{
public:
    stocks();
    void menu(Account&);
    void stockPrice(string);
    void buyStock(Account&, string, int, double);
    void sellStock(Account&, string, int, double);
    void displayPortfolio(Account&);
    void displayTransactions(Account&);

private:

};




#endif //PROJECTSTOCKS_STOCKS_H
