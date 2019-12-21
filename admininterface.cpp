#include "admininterface.h"
#include "logininterface.h"

AdminInterface::AdminInterface()
{
    //set up the menu

    //first create the menu items
    pair<char, string> newAgent('a', "Add new agent");
    menu_->addMenuItem(newAgent);

}

AdminInterface::AdminInterface(const AdminInterface &other)
{
    *this = other;
}

AdminInterface::~AdminInterface()
{
}

AdminInterface &AdminInterface::getInstance()
{
    static AdminInterface instance_;
    return instance_;
}

void AdminInterface::mainMenu() const
{
    switch (menu_->show())
    {
    case 'l': listAllEstates();
        break;
    case 's': searchByAddress();
        break;
    case 'a': newAgent();
        break;
    case 'e': exitToLoginMenu();
    }
}

void AdminInterface::newAgent() const
{
    string user_name, password, ID;
    char choice;
    string choice_dummy;
    cout << "--------------------------------------------------------" << endl;
    cout << "Create new agent (Username & password length between 4 - 16,"
            " neither can contain any white spaces)" << endl
         << " Username: ";

    cin >> ws; //getline consumes \n char from the previous endline, so we need to read it

    //dont let username and password contain whitespaces
    AbstractInterface::getStringWithoutWS(user_name);
    cout << "--------------------------------------------------------" << endl;
    //check if the given user name already exists
    // if it does, we will recall this function until he gives an unexisting name
    for(const auto &u: DataHandler::getInstance().getUsers())
    {

        if(u->getName() == user_name)
        {
            cout << " This username is already exists. Please choose another one." << endl;
            newAgent();
        }
    }
    cout << "--------------------------------------------------------" << endl;
    cout << " Password: ";

    AbstractInterface::getStringWithoutWS(password);
    cout << "--------------------------------------------------------" << endl;

    getConfirmation(choice_dummy);
    choice = choice_dummy[0];

   if(choice == 'y')
   {
       if((password.length() >= 4 && password.length() <= 16) &&
               (user_name.length() >= 4 && user_name.length() <= 16))
       {
           //this kind of registration only gives agent acces so the privilege
                         //                                           can be hardwired
           DataHandler::getInstance().saveNewUser(new Agent(user_name, password,
                                                               "agent"));
           cout << "--------------------------------------------------------" << endl;
           cout << "Agent " << user_name << " with password: " << password
              << " has been successfully registered." << endl;
           cout << "--------------------------------------------------------" << endl;
           AdminInterface::mainMenu();
       }
       else if(!(password.length() >= 4 && password.length() <= 16) &&
               !(user_name.length() >= 4 && user_name.length() <= 16))
       {
           cout << "--------------------------------------------------------" << endl;
           cout << "Incorrect size of password and username, please provide password"
                   "and username that "
                   "number of characters between 4 and 16. You will be directed back "
                   "to the menu where you can give your intended login data." << endl;
           cout << "--------------------------------------------------------" << endl;
           newAgent();
       }
       else if(!(password.length() >= 4 && password.length() <= 16))
       {
           cout << "--------------------------------------------------------" << endl;
           cout << "Incorrect size of password, please provide password that "
                   "number of characters between 4 and 16. You will be directed back "
                   "to the menu where you can give your intended login data." << endl;
           cout << "--------------------------------------------------------" << endl;
           newAgent();
       }
       else
       {
           cout << "--------------------------------------------------------" << endl;
           cout << "Incorrect size of username, please provide username that "
                   "number of characters between 4 and 16. You will be redirected "
                   "to the menu where you can give your intended login data." << endl;
           cout << "--------------------------------------------------------" << endl;
           newAgent();
       }
   }
   else if(choice == 'n')
   {
       cout << "--------------------------------------------------------" << endl;
       cout << "Your attend to register the agent is ignored."
               " You will be redirected to the main menu" << endl;
       cout << "--------------------------------------------------------" << endl;
       AdminInterface::mainMenu();
   }
}

