#ifndef MENU_H
#define MENU_H

#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;
class Menu
{
    unordered_map<char, string> menuItems_; //input <char - string>
    string menuName_; //e.g. Main Menu, Login Menu etc.
    string brief_; //e.g. "Please type the letter of your choice"

public:
    Menu(const unordered_map<char, string> menuItems,
         const string& menuName, const string& brief);
    char show() const; //shows the menu
    void addMenuItem(const pair<char, string>& menuItem);
};

#endif // MENU_H
