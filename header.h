//
// Created by Josh Capistrano on 4/26/18.
//

#ifndef PROJECTSTOCKS_HEADER_H
#define PROJECTSTOCKS_HEADER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Stock
{
    string symbol;
    string company;
    int amount;
    double price;
    double total;

};

struct Account
{
    double balance = 10000;
    vector<Stock> portfolioList;
};


#endif //PROJECTSTOCKS_HEADER_H
