#pragma once

#include <iostream>
#include <fstream>
#include<ctime>
#include <string>
using namespace std;

class LoginSystem { //This is the LoginSystem class
private:
    //These are the private attributes of the class, and will be used in the functions below.
    string pinAttempt;
    string pin;
    string cardAttempt;
    string cardNumber;
    int pinGen();
    int ccGen();
    bool CustomerLogin();
    bool StaffLogin();

public:
    void AccountMake();
    bool checkNumber(string validatestr);
    friend class Bank;
};
