#include "menu.h"

Menu::Menu(const unordered_map<char, string> menuItems,
           const string& menuName, const string& brief):
    menuItems_(menuItems),
    menuName_(menuName),
    brief_(brief)
{

}

char Menu::show() const
{
    char choice;
    string choice_dummy; //first input into this var, it can accept everything, char would crash if it gets a string
    bool bValidInput = false; //checks if the user gives valid input

    cout << " " <<  menuName_ << endl
         << "  " << brief_ << endl;

    for(auto item: menuItems_)
    {                   //its a simple char      //its a string, remember: map<pair<char, string>, void*>
        cout << "   " << item.first << " - " << item.second << endl;
    }

    do
    {
        cin >> choice_dummy;

        if(choice_dummy.length() == 1)
        {
            for(auto c: menuItems_)
            {
                if(c.first == choice_dummy[0])
                {
                    bValidInput = true;
                    break;
                }
            }
            if(!bValidInput)
            {
                cout << "Please give exactly ";
                for(auto c: menuItems_)
                {
                    if(c == *menuItems_.begin())//if its the first, we dont want write "or" before
                        cout << "'" << c.first << "'";
                    else
                        cout << " or '" << c.first << "'";
                }

                cout << ":" << endl;
            }
        }
        else
        {
            cout << "Please give exactly ";
            for(auto c: menuItems_)
            {
                if(c == *menuItems_.begin())//if its the first, we dont want write "or" before
                    cout << "'" << c.first << "'";
                else
                    cout << " or '" << c.first << "'";
            }

            cout << ":" << endl;
        }
    }
    while (!bValidInput);

    cout << "--------------------------------------------------------" << endl;
    choice = choice_dummy[0]; //finally a valid input
    return choice;
}

void Menu::addMenuItem(const pair<char, string> &menuItem)
{
    menuItems_.insert(menuItem);
}
