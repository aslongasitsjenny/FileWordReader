#include "Banking.h"
#include <iostream>


void printMenu() {
        cout << "Please select a number for the option:\n"
              << "1- Login\n"
              << "2- Register\n"
              << "3- Make a transaction\n"
              << "4- Exit\n"
              << "Option: ";
}


int main() {
    int userChoice;
    Person *loggedInUser = nullptr;


    do {
        printMenu();
        cin >> userChoice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (userChoice) {
            case 1:
                loggedInUser = Person::UserLogin();
                break;
            case 2:
                loggedInUser = Person::RegisterUser();
                break;
            case 3:
                if (loggedInUser != nullptr) {
                        loggedInUser->MakeTransaction();
                        loggedInUser->UpdateFile("../test.txt","../test.txt");
                }
                break;
                    case 4:
                        cout << "Exiting the program.\n";
                    delete loggedInUser;
                    return 0;
                    default:
                        cout << "Invalid option. Please try again.\n";
                }
        }
        while (userChoice != 4);
        delete loggedInUser;
        return 0;
    }

