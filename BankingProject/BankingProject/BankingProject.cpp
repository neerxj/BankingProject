// BankingProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdlib>
#include "User.h"
#include "LoginSystem.h"
#include "Bank.h"

using namespace std;

int main() {
    //Main function is called at start of program, acts as Main Menu.
    int option;
    string BankName = "Nrj";
    User New;
    LoginSystem Make;
    Bank Customer;
    cout << "Welcome to " << BankName << " Bank!" << endl;
    cout << "Select 1 if you have an account at NrjBank: " << endl;
    cout << "Select 2 if you would like to create an account: " << endl;
    cout << "Select 3 for Staff: " << endl;

    cin >> option;
    if (option == 1) {
        Customer.atmMenu();
    }
    if (option == 2) {
        system("CLS");
        New.getData();
        New.displayData();
        Make.AccountMake();
        main();
    }
    if (option == 3) {
        system("CLS");
        Customer.adminMenu();
        main();
    }
    else {
        cout << "Error: Invalid entry" << endl;
        cout << "Please try again" << endl;
        cin.clear();
        cin.ignore(123, '\n');
    }
}
