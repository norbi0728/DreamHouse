#ifndef LOGININTERFACE_H
#define LOGININTERFACE_H

#include "datahandler.h"
#include "userinterface.h"
#include "admininterface.h"
#include "agentinterface.h"
#include "menu.h"

#include <iostream>
#include <string>
#include <stdlib.h> //for exit()
#include <exception>

using namespace std;

//this class only provides the login menu, this is the first interaction with the user
//after he logs in the program will select for him the appropriate interface
class LoginInterface
{
    Menu* menu_;
    unordered_map<char, string> menuItems_;
    LoginInterface();
    LoginInterface(const LoginInterface& other);
public:
    ~LoginInterface();
    static LoginInterface& getInstance();
    
    //member functions
    void loginMenu() const;
    void login() const;
    void newUser() const;
};

#endif // LOGININTERFACE_H
