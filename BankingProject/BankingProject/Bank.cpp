#include "Bank.h"


void Bank::verifyDetails() {
    //This function verifies the latest data from account.
    ifstream read(cardAttempt + ".txt");
    getline(read, cardNumber);
    getline(read, pin);
    getline(read, balance);
    read.close();
}

void Bank::updateDetails(int appendBalance) {
    //This function appends the balance of the account.
    ofstream update;
    update.open(cardAttempt + ".txt");
    update << cardNumber << endl;
    update << pin << endl;
    update << appendBalance << endl;
    update.close();
}

void Bank::updateRec(string recipientAcc, int AmountOut) {
    //This function updates the recipient of the transfers details.
    while (!checkNumber(recipientAcc)) {
        //Checks if the Card number contains letters, and asks for input again.
        cout << "Error: Card number should contain numbers not letters." << endl;
        cin.clear();
        cin.ignore(123, '\n');
        cout << "Enter Recipient Card Number: ";
        cin >> recipientAcc;
    }

    while (recipientAcc.length() != 8) {
        //Checks if the Card number is 8 numbers long, if not asks for input again.
        cout << "Error: Card number length expected 8." << endl;
        cin.clear();
        cin.ignore(123, '\n');
        cout << "Enter Recipient Card Number: ";
        cin >> recipientAcc;
    }

    //Temporarily stores recipients details in string variables below.
    string recc, repin, rebalance;
    //Accesses recipients account
    ifstream getreinfo(recipientAcc + ".txt");

    //If recipient account does not exist, it asks for a valid recipient number.
    if (getreinfo.fail()) {
        cout << "Account does not exist.";
        cout << "Try again.";
        accTransfer();
    }

    //Gets recipients details.
    getline(getreinfo, recc);
    getline(getreinfo, repin);
    getline(getreinfo, rebalance);
    getreinfo.close();


    //Appends recipients balance
    int rewritebalance = stod(rebalance);
    rewritebalance += AmountOut;
    ofstream update(recipientAcc + ".txt", ios::trunc);
    update << recc << endl;
    update << repin << endl;
    update << rewritebalance << endl;
    update.close();

    cout << "Successful Transfer of: " << AmountOut << endl;
}

void Bank::accWithdraw() {
    //This function allows user to withdraw from their account.
    int MoneyOut;
    verifyDetails();
    double currentbalance = stod(balance);
    cout << "Your current balance is: ";
    cout << balance << endl;
    cout << "Please specify withdrawal amount: ";
    cin >> MoneyOut;
    if (MoneyOut <= currentbalance) {
        currentbalance -= MoneyOut;
        updateDetails(currentbalance);
        cout << "The amount withdrew is: " << MoneyOut << endl;
        cout << "New balance is: " << currentbalance << endl;
    }
    else {
        accWithdraw();
    }
}

void Bank::accDeposit() {
    //This function allows the user to deposit to their account.
    int deposit;
    verifyDetails();
    double currentbalance = stod(balance);
    cout << "Your current balance is: " << balance << endl;
    cout << "Please specify deposit amount: ";
    cin >> deposit;
    currentbalance += deposit;
    updateDetails(currentbalance);
    cout << "New Balance is: " << currentbalance << endl;
}

void Bank::accBalance() {
    //This function displays the user's balance
    verifyDetails();
    cout << "Your balance is: " << balance << endl;
}

void Bank::accTransfer() {
    //This function allows the user to transfer money to another account.
    string recipientAcc;
    verifyDetails();
    int TransferAmount;
    cout << "Transfer" << endl;
    cout << "Please enter the amount you wish to Transfer: ";
    cin >> TransferAmount;
    string TA = to_string(TransferAmount);

    while (!checkNumber(TA)) {
        cout << "Error: Please enter a number for Transfer amount." << endl;;
        cout << "Please enter the amount you wish to Transfer: ";
        cin >> TransferAmount;
    }
    double currentbalance = stod(balance);
    if (currentbalance > TransferAmount) {
        currentbalance -= TransferAmount;
        updateDetails(currentbalance);
        cout << "Please enter the CC number of the account to Transfer: " << endl; ;
        cin >> recipientAcc;
        updateRec(recipientAcc, TransferAmount);
    }
    else {
        cout << "Error: Transfer amount exceeds balance" << endl;;
        accTransfer();
    }
}

void Bank::InterestCalc() {
    //This function allows user to calculate interest earned.
    verifyDetails();
    int time;
    double balanceint;
    int Acctype;

    cout << "Calculate the interest gained on balance: " << endl;
    cout << "Your current balance is: " << balance << endl;
    balanceint = stod(balance);
    cout << "Please enter the type of account\n1 for Current Account \n2 for Savings: \n3 for ISA: ";
    cin >> Acctype;

    if (Acctype == 1) {
        //This function allows calculate interest earned on a Current Account.
        cout << "You have selected the Current Account" << endl;
        cout << "The bank have set the Interest Rate at: " << (CurrentAccRate * 100) << endl;
        cout << "Please enter the term you wish to calculate(in years): " << endl;
        cin >> time;
        cout << "Your balance is: " << balanceint << endl;
        cout << "Your calculated interest on the balance is: ";
        balanceint = balanceint + (balanceint * CurrentAccRate * time);
        cout << balanceint << endl;
        cout << "Returning to main menu...";
    }

    if (Acctype == 2) {
        //This function allows calculate interest earned on a Savings Account.
        cout << "You have selected the Savings Account" << endl;
        cout << "The bank have set the Interest Rate at: " << (SavingsAccRate * 100) << endl;
        cout << "Please enter the term you wish to calculate(in years): " << endl;
        cin >> time;
        cout << "Your balance is: " << balanceint << endl;
        cout << "Your calculated interest on the balance is: ";
        balanceint = balanceint + (balanceint * SavingsAccRate * time);
        cout << balanceint << endl;
        cout << "Returning to main menu...";
    }

    if (Acctype == 3) {
        //This function allows calculate interest earned on a ISA Account.
        cout << "You have selected the ISA Account" << endl;
        cout << "The bank have set the Interest Rate at: " << (ISAAccRate * 100) << endl;
        cout << "Please enter the term you wish to calculate(in years): " << endl;
        cin >> time;
        cout << "Your balance is: " << balanceint << endl;
        cout << "Your calculated interest on the balance is: ";
        balanceint = balanceint + (balanceint * ISAAccRate * time);
        cout << balanceint << endl;
        cout << "Returning to main menu...";
    }

    else {
        cout << "You did not select an valid option." << endl;
        cout << "Please try again." << endl;
    }

}

void Bank::adminMenu() {
    //This function is the Administrator/Bank Staff portal
    StaffLogin();
    cout << "Welcome Bank Staff: " << endl;
    cout << "Set the interest rates: " << endl;
    //This allows the Bank Staff to change the interest rates of the accounts.
    cout << "Set Current Account Interest Rate: " << endl;
    cin >> CurrentAccRate;
    cout << "Set Savings Account Interest Rate: " << endl;
    cin >> SavingsAccRate;
    cout << "Set ISA Account Interest Rate: " << endl;
    cin >> ISAAccRate;
    cout << "Back to main menu." << endl;
    cin.clear();
    cin.ignore(123, '\n');
}

void Bank::atmMenu() {
    //This function makes sure that the customer is logged in before accessing ATM Menu.
    CustomerLogin();
    Menu();
}

void Bank::Menu() {
    //The Bank Menu function, allows the user to access the functionalities.
    int menuopt;
    cout << "Welcome to the Banking Menu" << endl;
    cout << "Please enter 1 to check your balance" << endl;
    cout << "Please enter 2 to deposit to account" << endl;
    cout << "Please enter 3 to withdraw from account" << endl;
    cout << "Please enter 4 to transfer money to another account" << endl;
    cout << "Please enter 5 to enter interest calculator" << endl;
    cout << "Please enter 6 to exit program: " << endl;
    cin >> menuopt;
    if (menuopt == 1) {
        system("CLS");
        accBalance();
        Menu();
    }

    if (menuopt == 2) {
        system("CLS");
        accDeposit();
        Menu();
    }

    if (menuopt == 3) {
        system("CLS");
        accWithdraw();
        Menu();
    }

    if (menuopt == 4) {
        system("CLS");
        accTransfer();
        Menu();
    }

    if (menuopt == 5) {
        system("CLS");
        InterestCalc();
        Menu();
    }
    
    if (menuopt == 6) {
        exit(0);
    }

    else {
        cin.clear();
        cin.ignore(123, '\n');
        cout << "Error: Incorrect entry please try again" << endl;
        Menu();
    }
}
