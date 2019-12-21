#ifndef AbstractInterface_H
#define AbstractInterface_H

#include "datahandler.h"
#include "user.h"
#include "menu.h"

#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;
//this class will provide the interaction with the program
//there would be 3 types of it, one specific for each type of user
class AbstractInterface
{
protected:
    Menu* menu_;
    User* user_;
    unordered_map<char, string> menuItems_;
public:
    AbstractInterface();
    AbstractInterface(const AbstractInterface& other);
    virtual ~AbstractInterface();

    //member functions
    virtual void mainMenu() const = 0;
    void searchByAddress() const;
    void listAllEstates() const;
    void printEstate(RealEstate* estate) const; //utility function which prints formatted an estate
    void setUser(User *value);
    void exitToLoginMenu() const;

    //utility functions //static because
    //login interface uses it too
    static void getStringWithoutWS(string& str);
    static void getConfirmation(string& choice);
};

#endif // AbstractInterface_H
