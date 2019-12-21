#include "logininterface.h"

LoginInterface::LoginInterface()
{
    //set up the menu
    menuItems_['l'] = "Log in";
    menuItems_['c'] = "Create new account";
    menuItems_['e'] = "Exit";

    menu_ = new Menu(menuItems_, "DreamHouse", " Welcome! Please type the letter of your choice!");
}

LoginInterface::LoginInterface(const LoginInterface &other)
{
    *this = other;
}

LoginInterface::~LoginInterface()
{
}

LoginInterface &LoginInterface::getInstance()
{
    static LoginInterface instance;
    return instance;
}

void LoginInterface::loginMenu() const
{
    switch (menu_->show())
    {
    case 'l': login();
        break;
    case 'c': newUser();
        break;
    case 'e': exit(0);
    }
}

void LoginInterface::login() const
{
    string user_name;
    string password;
    cout << "--------------------------------------------------------" << endl;
    cout << "Please provide your username and password to log in!" << endl
         << " Username: ";

    //cin >> ws; //getline consumes \n char from the previous endline, so we need to read it

    //dont let username and password contain whitespaces
    AbstractInterface::getStringWithoutWS(user_name);
    cout << "--------------------------------------------------------" << endl;
    cout << " Password: ";

    AbstractInterface::getStringWithoutWS(password);
    cout << "--------------------------------------------------------" << endl;
    //check the username - password pair
    bool successful_login = false;
    for(const auto &u: DataHandler::getInstance().getUsers())
    {
        if(u->getName() == user_name)
        {
            if(u->getPassword() == password)
            {
                if(u->getPrivilege() == "user")
                {
                    successful_login = true;
                    cout << "Welcome back " << u->getName() << "!" << endl;
                    UserInterface::get_instance().setUser(u);
                    UserInterface::get_instance().mainMenu();
                }
                else if(u->getPrivilege() == "admin")
                {
                    successful_login = true;
                    cout << "Welcome back " << u->getName() << "!" << endl;
                    AdminInterface::getInstance().setUser(u);
                    AdminInterface::getInstance().mainMenu();
                }
                else if(u->getPrivilege() == "agent")
                {
                    successful_login = true;
                    cout << "Welcome back " << u->getName() << "!" << endl;
                    AgentInterface::instance().setUser(u);
                    AgentInterface::instance().mainMenu();
                }
            }
        }
    }
    cout << "--------------------------------------------------------" << endl;
    if(!successful_login)
    {
        cout << "Wrong username or password! Please try again!" << endl;
        login();
    }
    cout << "--------------------------------------------------------" << endl;
}

void LoginInterface::newUser() const
{
    string user_name, password;
    char choice;
    string choice_dummy;
    cout << "--------------------------------------------------------" << endl;
    cout << "Create new user (Username & password length between 4 - 16, neither can contain any white spaces)" << endl
         << " Username: ";


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
            newUser();
        }
    }
    cout << "--------------------------------------------------------" << endl;
    cout << " Password: ";

    AbstractInterface::getStringWithoutWS(password);
    cout << "--------------------------------------------------------" << endl;


    AbstractInterface::getConfirmation(choice_dummy);

    choice = choice_dummy[0];

   if(choice == 'y')
   {
       if((password.length() >= 4 && password.length() <= 16) &&
               (user_name.length() >= 4 && user_name.length() <= 16))
       {
           //this kind of registration only gives ordinary user acces so the privilege
                         //                                           can be hardwired
           DataHandler::getInstance().saveNewUser(new User(user_name, password, "user"));
           cout << "--------------------------------------------------------" << endl;
           cout << "User: " << user_name << " with password: " << password
              << " has been successfully registered. Please log in!" << endl;
           cout << "--------------------------------------------------------" << endl;
           loginMenu();
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
           newUser();
       }
       else if(!(password.length() >= 4 && password.length() <= 16))
       {
           cout << "--------------------------------------------------------" << endl;
           cout << "Incorrect size of password, please provide password that "
                   "number of characters between 4 and 16. You will be directed back "
                   "to the menu where you can give your intended login data." << endl;
           cout << "--------------------------------------------------------" << endl;
           newUser();
       }
       else
       {
           cout << "--------------------------------------------------------" << endl;
           cout << "Incorrect size of username, please provide username that "
                   "number of characters between 4 and 16. You will be redirected "
                   "to the menu where you can give your intended login data." << endl;
           cout << "--------------------------------------------------------" << endl;
           newUser();
       }
   }
   else if(choice == 'n')
   {
       cout << "--------------------------------------------------------" << endl;
       cout << "Your attend to register is ignored."
               " You will be redirected to the main menu" << endl;
       cout << "--------------------------------------------------------" << endl;
       loginMenu();
   }
}

