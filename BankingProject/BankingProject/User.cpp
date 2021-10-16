#include "User.h"


bool User::checkNumber(string validatestr) {
    //Boolean function to verify that the parameter is a string.
    for (int i = 0; i < validatestr.length(); i++) {
        if (isdigit(validatestr[i]) == false)
            return false;
    }
    return true;
}


void User::getData() {
    // This is the getData function, it will be used to collect the users information required to create an account.
    cout << "Creating a new account " << endl;
    getName();
    getAddress();
    getPassport();
    getAccountType();
    cleanData();
}

void User::getName() {
    // This is the getName function, it collects the user's name.
    cout << "Please enter your First Name: ";
    cin >> fname;

    //Name should not contain number, hence checkNumber is called.
    while (checkNumber(fname)) { //If the boolean checkNumber is true, then the name contains a number.
        cout << "Error: Please enter characters for name" << endl;
        cout << "Please enter your First Name: ";
        cin >> fname;
    }
    cin.clear();
    cin.ignore(123, '\n');
    cout << "Please enter your Surname: ";
    cin >> lname;
    while (checkNumber(lname)) {
        cout << "Error: Please enter characters for surname" << endl;
        cout << "Please enter your Surname: ";
        cin >> lname;
    }
    cin.clear();
    cin.ignore(123, '\n');
}

void User::getAddress() {
    cout << "Please enter the first line of your address: " << endl;
    getline(cin, address, '\n');

    for (int i = 0; i < address.length(); i++) {
        //The following if statements, checks the ASCII codes, of each character in the address.
        if ((address[i] == 32 || (address[i] >= 48 && address[i] <= 57) || //The statements check if contains ASCII codes, for space, numbers and letters.
            (address[i] >= 65 && address[i] <= 90) ||
            (address[i] >= 97 && address[i] <= 122))) {
            continue;
        }
        else {
            // If a Special Character is found, it asks the user to renter their details.
            cout << "Error: Invalid address, special character input.";
            cin.clear();
            cin.ignore(123, '\n');
            getAddress();
        }
        cin.clear();
        cin.ignore(123, '\n');
    }

    cout << "Please enter the Postcode: " << endl;
    getline(cin, postcode, '\n');

    if (postcode.length() < 6 || postcode.length() > 8) {
        cin.clear();
        cout << "Error: Postcode length in United Kingdom, is 6 - 8." << endl;
        cout << "Please try again." << endl;
        cout << "Please enter the Postcode: " << endl;
        getline(cin, postcode, '\n');
    }
}

void User::getPassport() {
    cout << "Please enter your passport number: " << endl;
    cin >> passportnum;
    int passlength = to_string(passportnum).length();
    //Verify integer input.
    while (!cin >> passportnum) {
        cout << "Error: Numbers only valid for Passport " << endl;
        cin.clear();
        cin.ignore(123, '\n');
        getPassport();
    }
    //Verify the password length.
    if (passlength != 8) {
        cout << "Error: Passport number length expected 8." << endl;
        cin.clear();
        cin.ignore(123, '\n');
        getPassport();
    }
}

void User::getAccountType() {
    cout << "Please enter the type of account\n1 for Current Account \n2 for Savings:\n";
    cin >> typeofaccount;
    //Verify integer input.
    while (!cin >> typeofaccount) {
        cout << "Error: Numbers only valid for type of account. " << endl;
        cin.clear();
        cin.ignore(123, '\n');
        getAccountType();
    }
    cin.clear();
}

void User::cleanData() {
    //The clean data function, makes sure that the user's info is to the right formatting before being written to file.
    //Code below formats name to proper noun formatting.
    for (int i = 0; i < fname.size(); i++) {
        fname[i] = tolower(fname[i]);
    }
    fname[0] = toupper(fname[0]);
    for (int i = 0; i < lname.size(); i++) {
        lname[i] = tolower(lname[i]);
    }
    lname[0] = toupper(lname[0]);
    fullname = fname + " " + lname;

    //Code below Removes unnecessary spaces between postcode
    for (int i = 0; i < postcode.size(); i++) {
        postcode[i] = toupper(postcode[i]);
    }
}

void User::displayData() {
    //Displays the Information entered to confirm, correct input.
    cout << "Your Information." << endl;
    cout << "Name: " << fullname << endl;
    cout << "Address: " << address << endl;
    cout << "postcode: " << postcode << endl;
    cout << "Account type: ";
    if (typeofaccount == 1) {
        cout << "Current Account" << endl;
    }
    if (typeofaccount == 2) {
        cout << "Savings" << endl;
    }

    cout << "Are the details entered correctly: y/yes n/no?" << endl;
    string check;
    cin >> check;

    while (check != "n" && check != "y") {
        cout << "Error: Invalid input.";
        cout << "Are the details entered correctly: y/yes n/no?" << endl;
        cin >> check;
    }
    if (check == "n") {
        getData();
        displayData();
    }
    if (check == "y") {
        storeInfo();
    }
}

void User::storeInfo() {
    //Stores the new users details to the main csv file.
    ofstream storeUI;
    storeUI.open("userinfo.csv", ios::out | ios::app);
    if (!storeUI) {
    }
    else {
        storeUI << typeofaccount << ", ";
        storeUI << fullname << ", ";
        storeUI << address << ", ";
        storeUI << postcode << ", ";
        storeUI << passportnum << ", ";
        storeUI.close();
    }
}
