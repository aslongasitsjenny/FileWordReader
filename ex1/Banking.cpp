#include   "Banking.h"

string ogfilepath = "../test.txt";
/**
*  Handles logic for logging in the user, requires inputting name and password then checking through the file if it matches the values within said file.
 *  Returns loggedInPerson if successful.
*/
Person* Person::UserLogin() {
    //declaration of variables
    ifstream inFile(ogfilepath);
    string password;
    string name;
    string line;
    vector<string> userTransactions;
    string fileUsername, filePassword, filePlaceOfBirth;
    int fileAge;
    double fileBalance;

    cout << "Enter name: " << endl;
    cin >> name;

    cout << "Enter password: " << endl;
    cin >> password;

    //read each line from inFile and create a string stream iss for parsings
    while (getline(inFile, line)) {
        istringstream iss(line);

        //try extract values from the string stream iss into variables,
        //if successful then check if the extracted fileUsername matches name and filePassword matches password.
        //read each line from the inFile into the transaction variable,
        // and append each transaction to the userTransactions vector to put into person object.

        if (iss >> fileUsername >> fileAge >> filePlaceOfBirth >> filePassword >> fileBalance) {
            if (fileUsername == name && filePassword == password) {
                string transaction;
                while (getline(inFile, line) && !line.empty()) {
                    userTransactions.push_back(line);
                }
                //creating a dynamic object, provided with values from the file for initialisation
                Person* loggedInPerson = new Person(fileUsername, fileAge, filePlaceOfBirth, filePassword, fileBalance, userTransactions);

                inFile.close();

                //use operator<< to cout the user information
                cout << *loggedInPerson << endl;
                loggedInPerson->recentTransaction();

                return loggedInPerson;
            }
        }
    }

    cout << "Login failed. Please check your username and password.\n";

    inFile.close();
    return nullptr;
}

/**
*  Handles logic for registering the user, requires inputting name, age, place of birth and password then creates a new Person object with inputted values.
 *  Returns loggedInPerson if successful.
*/
Person *Person::RegisterUser() {
    //declaration of variables
         string name, placeOfBirth, password;
         int age;
         double balance = 0.0;
         vector<string> userTransactions;

         cout << "Enter Name: ";
         cin >> name;

         cout << "Enter Age: ";

        //prompt for a valid integer until int is given, clears errors, clear the input buffer.
        while(!(cin >> age)) {

            cout << "Enter Age: ";
            cin.clear();
            cin.ignore(123,'\n');

         }

             cout << "Enter place of birth: ";
             cin >> placeOfBirth;
             cout << "Enter Password: ";
             cin >> password;

             //creating a dynamic object, provided with values for initialisation
             Person *loggedInPerson = new Person(name, age, placeOfBirth, password, balance, userTransactions);

             loggedInPerson->writeToFile();

             cout << "User registered successfully.\n";

             //return loggedInPerson with values so it isnt null pointer anymore
             return loggedInPerson;
         }



ostream& operator<<(ostream& out, const Person& obj) { //overloading the cout
    char asciipound = 156;

    //print out variables using getters
    out << "Welcome " << obj.getName() << "!" << endl;
    out << "Your age is " << obj.getAge() << endl;
    out << "You were born in " << obj.getPlaceOfBirth() << "." << endl;
    out << "Your balance is " << asciipound <<  obj.getBalance() << "." << endl;
    out << "Your recent transactions are" << endl;


    return out;
}



/**
 * Reads data from the input file specified by 'inputFilePath', updates the balance
 * for the person with matching 'name' and 'password', and writes the modified data
 * to the output file specified by 'outputFilePath'.
 *
 * @param inputFilePath - The path of the input file to be read.
 * @param outputFilePath - The path of the output file to be written.
 */
void Person::UpdateFile(const string& inputFilePath, const string& outputFilePath) {
    //open the file at inputFilePath for both reading and writing
    fstream file(inputFilePath, ios::in | ios::out);

    if (!file.is_open()) {
        cout << "Error opening file: " << inputFilePath << endl;
        return;
    }

    string tempFilePath = "../temp.txt";
    ofstream tempFile(tempFilePath);

    string fileUsername, filePassword, filePlaceOfBirth;
    int fileAge;
    double fileBalance;

    //read data from the file stream into variables, keep looping as long as data exists, and it stops when it reaches matching name, password
    //updates new balance to variable file balance and makes temp file with the rest of unchanged variables. rdbuf() to ensure no other lines are changed
    //close the stream and remove the old file, then attempting to rename the tempfile to the outputfilepath
    while (file >> fileUsername >> fileAge >> filePlaceOfBirth >> filePassword >> fileBalance) {
        if (fileUsername == name && filePassword == password) {
            fileBalance = balance;
        }

        tempFile << fileUsername << " " << fileAge << " " << filePlaceOfBirth << " " << filePassword << " " << fileBalance << endl;
    }

    tempFile << file.rdbuf();

    file.close();
    tempFile.close();
    remove(inputFilePath.c_str());

    if (rename(tempFilePath.c_str(), outputFilePath.c_str()) != 0) {
        cout << "Error replacing the original file." << endl;
        return;
    }
}
/**
 * Appends the person's information to the file specified by 'ogfilepath'.
 * Resets the balance to 0.0 before writing to the file.
 * Provides error handling in case the file cannot be opened.
 */
void Person::writeToFile() {
  ofstream f(ogfilepath, ofstream::app);
    //error handling
     if (!f.is_open()) {
        cout << "Sorry, cannot open file: " << ogfilepath << endl;
        exit(1);
     }
     balance = 0.0;
     //writes values to file
     f  << name <<" " << age << " "<< placeOfBirth << " " << password<< " " << balance << endl;
     f << endl;
     f.close();
     cout << "User information written to file: " << ogfilepath << endl;

     }

/**
 * Processes a transaction by prompting the user for details (amount, sender/recipient, transaction type),
 * updating the transaction history and balance, and writing the updated information to the file.
 */
void Person::MakeTransaction() {
    //declaration of variables
    double amount;
    string senderOrRecipient;
    ifstream inFile(ogfilepath);
    vector<string> linesExist;
    string line;
    char transactionType;
    char asciipound = 156;


    cout << "Enter the name of the sender/recipient: ";
    cin >> senderOrRecipient;

    cout << "Enter Amount: " << endl;

    //prompt for a valid integer until int is given, clears errors, clear the input buffer.
    while(!(cin >> amount)) {

        cout << "Enter Amount: ";
        cin.clear();
        cin.ignore(123,'\n');

    }


    do {
        cout << "Enter '+' for received or '-' for paid: ";
        cin >> transactionType;
    }
    //continue looping until the transactionType is neither + nor -
    while (transactionType != '+' && transactionType != '-');
    //process the transaction based on the transactionType
    //if + is entered, record a received transaction and update the balance
    //if - is entered, record a paid transaction and update the balance
    if (transactionType == '+') {
        transactions.push_back("Received £" + to_string(amount) + " from " + senderOrRecipient);
        balance += amount;
    } else {
        if (balance - amount < -1500) {
            cout << "Transaction denied. Exceeds overdraft limit." << endl;
            return;
        }
        transactions.push_back("Paid £" + to_string(amount) + " to " + senderOrRecipient);
        balance -= amount;
    }

    while (getline(inFile, line)) {
        linesExist.push_back(line);
    }

    //iteration through each element of lineExist vector using index, starting from index 0 and ending before linesExist size
    for (size_t index = 0; index < linesExist.size(); ++index) {
        istringstream iss(linesExist[index]);
        string username, password, placeOfBirth;
        int age;
        double balance;

        //obtain values from input string stream into variables and if username matches objects name, same with password
        //insert the most recent transaction at the next index within linesExist

        if (iss >> username >> age >> placeOfBirth >> password >> balance) {
            if (username == this->name && password == this->password) {
                linesExist[index] = name + " " + to_string(age) + " " + placeOfBirth + " " + password + " " + to_string(this->balance);
                linesExist.insert(linesExist.begin() + index + 1, transactions.back());
                break;
            }
        }
    }

    //iteration through each line in the linesExist and write it to the output file
    ofstream outFile(ogfilepath);
    for (const auto &line : linesExist) {
        outFile << line << endl;
    }

    outFile.close();
    inFile.close();

    cout << "Transaction successful." << endl;
    cout << "New balance: " << asciipound << abs(balance) << endl;
}

void Person::recentTransaction(){
    char asciipound = 156;

    //get a constant reference to the 'transactions' vector using getTransactions method of obj object
    //const vector<string>& transactions = getTransactions();
    //number of transactions
    int numTransactions = transactions.size();

    //display up to the last 3 transactions or all transactions if there are fewer than 3
    for (int i = max(numTransactions - 3, 0); i < numTransactions; ++i) {
        string mod  = transactions[i];
        size_t pos = mod.find("£");
        if(pos != string::npos){
            mod.replace(pos, 2,1, asciipound);

        }
        cout << "    - " << mod << endl;
    }

}