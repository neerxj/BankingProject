#include "LoginSystem.h"

bool LoginSystem::checkNumber(string validatestr) {
    //Boolean function to verify that the parameter is a string.
    for (int i = 0; i < validatestr.length(); i++) {
        if (isdigit(validatestr[i]) == false)
            return false;
    }
    return true;
}

int LoginSystem::pinGen() {
    srand((unsigned)time(0));//randomizes the number
    int newpin = (rand() % 9999) + 1000; //generates a 4 digit random positive integer;
    return newpin;
}

int LoginSystem::ccGen() {
    srand(time(NULL)); //randomizes the number
    int newcc = rand() % (99999999) + 10000000; //generates a 8 digit random positive integer;
    return newcc;
}

void LoginSystem::AccountMake() {
    //Generates the new accounts, CC Card and Pin numbers.
    int cc = ccGen();
    int pin = pinGen();
    string accountCC = to_string(cc);
    cout << "Your Card Number is: " << cc << endl;
    cout << "Your Pin Number is: " << pin << endl;
    ofstream file;

    //Creates a new file to store account.
    file.open(accountCC + ".txt");
    file << accountCC << endl << pin << endl << '0' << endl;
    file.close();

    //Stores new user details to userinfo file.
    ofstream storeUI;
    storeUI.open("userinfo.csv", ios::out | ios::app);
    storeUI << accountCC << "\n";
    storeUI.close();
}

bool LoginSystem::CustomerLogin() {
    //Asks the User for CC Number
    cout << "Enter Credit Card Number: ";
    cin >> cardAttempt;

    while (!checkNumber(cardAttempt)) {
        //If CC number contains letters, display error, and ask for input again.
        cout << "Error: Card number should contain numbers not letters." << endl;
        cin.clear();
        cin.ignore(123, '\n');
        cout << "Enter Credit Card Number: ";
        cin >> cardAttempt;
    }

    while (cardAttempt.length() != 8) {
        //If CC number length is not 8 display error, and ask for input again.
        cout << "Error: Card number length expected 8." << endl;
        cin.clear();
        cin.ignore(123, '\n');
        cout << "Enter Credit Card Number: ";
        cin >> cardAttempt;
    }

    //Throws error, if the account does not exist.
    ifstream read(cardAttempt + ".txt");
    if (read.fail()) {
        cout << "Account does not exist.";
        cout << "Try again.";
        CustomerLogin();
    }

    //Ask user for the Pin number.
    cout << "Enter PIN Number: ";
    cin >> pinAttempt;

    while (!checkNumber(pinAttempt)) {
        //If Pin number contains letters, throw error, and ask for input again.
        cout << "Error: Pin should contain numbers not letters." << endl;
        cin.clear();
        cin.ignore(123, '\n');
        cout << "Enter PIN Number: ";
        cin >> pinAttempt;
    }

    while (pinAttempt.length() != 4) {
        //If Pin number length is not 4 throw error.
        cout << "Error: Pin length expected 4." << endl;
        cin.clear();
        cin.ignore(123, '\n');
        cout << "Enter PIN Number: ";
        cin >> pinAttempt;
    }

    getline(read, cardNumber);
    getline(read, pin);

    if (cardAttempt == cardNumber && pinAttempt == pin) {
        cout << "Please wait while we bring your account" << endl;
    }
    else {
        cout << "Incorrect Entry, please try again." << endl;
        CustomerLogin();
    }
    //Return true, if customer details correct.
    return true;
}

bool LoginSystem::StaffLogin() {
    //Predefined staff number and staff pin.
    string staffnumber = "43185";
    string staffpin = "2468";
    string staffattempt;
    string staffpinattempt;
    //Prompts user to enter their staff attempt.
    cout << "Enter Staff Number: ";
    cin >> staffattempt;

    //If staff attempt contains letters, prompt user to reinput staff attempt.
    while (!checkNumber(staffattempt)) {
        cout << "Error: Staff Number should contain numbers not letters." << endl;
        cin.clear();
        cin.ignore(123, '\n');
        cout << "Enter Staff Number: ";
        cin >> staffattempt;
    }
    //If the length of staff attempt exceeds 5, prompt user to reinput staff attempt.
    while (staffattempt.length() != 5) {
        cout << "Error: Staff Number length expected 5." << endl;
        cin.clear();
        cin.ignore(123, '\n');
        cout << "Enter Staff Number: ";
        cin >> staffattempt;
    }

    cout << "Enter Staff PIN Number: ";
    cin >> staffpinattempt;

    while (!checkNumber(staffpinattempt)) {
        cout << "Error: Pin should contain numbers not letters." << endl;
        cin.clear();
        cin.ignore(123, '\n');
        cout << "Enter Staff PIN Number: ";
        cin >> staffpinattempt;
    }

    while (staffpinattempt.length() != 4) {
        cout << "Error: Pin length expected 4." << endl;
        cin.clear();
        cin.ignore(123, '\n');
        cout << "Enter PIN Number: ";
        cin >> staffpinattempt;
    }

    if (staffpinattempt == staffnumber && staffpinattempt == staffpin) {
        cout << "Access Granted." << endl;
    }
    //returns true, if customer details entered correctly.
    return true;
}

