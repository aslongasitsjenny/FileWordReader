#ifndef PERSON_H

#define PERSON_H
#include <iostream>

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;


class Person {
private:
    string name;
    int age;
    string placeOfBirth;
    string password; 
    double balance;
    vector<string> transactions;

    Person();

public:

    void writeToFile();
    void UpdateFile(const string& inputFilePath, const string& outputFilePath);
    void recentTransaction();
    static Person* UserLogin();
    static Person* RegisterUser();


    friend ostream& operator<<(ostream& out, const Person& obj);
    Person(const string& n, int a, const string& p, const string& pass, double b, vector<string> t)
            : name(n), age(a), placeOfBirth(p), password(pass), balance(b), transactions(t) {}

    void MakeTransaction();
    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

   string getPlaceOfBirth() const {
        return placeOfBirth;
    }

    double getBalance() const {
        return balance;
    }

};
#endif 