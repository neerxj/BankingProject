#pragma once

#include <iostream>
#include <fstream>
#include<ctime>
#include <string>
using namespace std;


class User { //This is the User Class
private:
    //These are the private attributes of the class, and will be used in the functions below.
    string fname;
    string lname;
    string fullname;
    string address;
    string postcode;
    int passportnum;
    int typeofaccount;
    int pin;

public:
    // These are the class member functions.
    void getData();// This function gets the users input data.
    void getName(); //This function is called in getData(), and is used to get the user's name.
    void getAddress(); //This function is called in getData(), and is used to get the Address.
    void getPassport(); //This function is called in getData(), and is used to get the Passport number.
    void getAccountType(); //This function is called in getData(), and is used to get the Account Type.
    void cleanData(); // This function cleans the users data, ready for output to userinfo file.
    void displayData(); // This function displays the users input data, to verify correct input.
    void storeInfo(); // This function stores the users data.
    bool checkNumber(string validatestr);

};


