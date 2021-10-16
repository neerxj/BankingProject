#pragma once

#include "LoginSystem.h"
#include <iostream>
#include <fstream>
#include<ctime>
#include <string>
using namespace std;


class Bank:private LoginSystem{
    //The Class Bank is a friend class of the LoginSystem class, this allows us to access the current users data.
private:
    void verifyDetails(); //Verifies the details of the current account.
    void updateDetails(int appendBalance); //Updates details of current account.
    void accBalance(); //Gets the balance of account
    void accDeposit(); //Allows the user to deposit to the account.
    void accWithdraw(); //Allows the user to withdraw from account.
    void accTransfer(); //Allows user to transfer to and from account.
    void InterestCalc(); //Allows the user to calculate future interest gained.
    void updateRec(string recipientAcc, int AmountOut); //Allows user to update the balance of recipient of transfer.
    string balance;
    double CurrentAccRate = 0.015; //rates of interest
    double SavingsAccRate = 0.03;
    double ISAAccRate = 0.05;
    void Menu();
public:
    void adminMenu(); //Public function to access admin menu.
    void atmMenu(); //Public function to access ATM menu, and corresponding functions above.
};
