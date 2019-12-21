#include "abstractinterface.h"
#include "logininterface.h"

void AbstractInterface::setUser(User *value)
{
    user_ = value;
}

void AbstractInterface::exitToLoginMenu() const
{
    LoginInterface::getInstance().loginMenu();
}


void AbstractInterface::getStringWithoutWS(string &str)
{
    cin >> ws;
    getline(cin, str);
    while(str.find(" ") < str.length() || str.find('\t') < str.length())
    {
        cout << "Please provide without whitespace!: ";
        cin >> ws;
        getline(cin, str);
    }
}

void AbstractInterface::getConfirmation(string &choice)
{
    cout << "Please confirm (y / n): ";

    cin >> choice;

    while(choice.length() != 1 || (choice != "y" &&
                                         choice != "n"))
    {
        cout << "Please give exactly: 'y' or 'n':";
        cin >> choice;
    }
}

AbstractInterface::AbstractInterface()
{
    //set up the menu

    //first create the menu items

    menuItems_['l'] = "List all estates";
    menuItems_['s'] = "Search by address";
    menuItems_['e'] = "Log out";

    menu_ = new Menu(menuItems_, "Main menu", "Please type the letter of you choice");

}

AbstractInterface::AbstractInterface(const AbstractInterface &other)
{
    *this = other;
}

AbstractInterface::~AbstractInterface()
{
    delete user_;
    delete menu_;
}


void AbstractInterface::searchByAddress() const
{
    string address;
    list<RealEstate*> results;

    cout << "--------------------------------------------------------" << endl;
    cout << "Please provide an address! (zip code, town, etc.."
            " dont need to write exact address)" << endl;

    cin >> address;
    cout << "--------------------------------------------------------" << endl;

    for(auto estate: DataHandler::getInstance().getEstates())
    {
        if(estate->getAddress().substr(0, address.size()) == address)
        {
            results.push_back(estate);
        }
    }

    if(results.size() > 0)
    {
        cout << "--------------------------------------------------------" << endl;
        cout << results.size() << " results: " << endl;
        cout << "--------------------------------------------------------" << endl;

        for(auto e: results)
        {
            printEstate(e);
        }

        if(user_->getPrivilege() == "admin")//in case of user we dont want to go back
            mainMenu();                   //to the main menu because of the further options
    }
    else
    {
        cout << "--------------------------------------------------------" << endl;
        cout << "There is no result for the given address. You will be redirected "
                "to the main menu" << endl;
        cout << "--------------------------------------------------------" << endl;
        mainMenu();
    }
}
void AbstractInterface::mainMenu() const
{
    switch (menu_->show())
    {
    case 'l': listAllEstates();
        break;
    case 's': searchByAddress();
        break;
    case 'b': exitToLoginMenu();
    }
}

void AbstractInterface::listAllEstates() const
{

    if(DataHandler::getInstance().getEstates().size() == 0)
    {
        cout << "0 results" << endl;
        cout << "--------------------------------------------------------" << endl;
    }
    else
    {
        cout << DataHandler::getInstance().getEstates().size() << " results" << endl;
        cout << "--------------------------------------------------------" << endl;
    }


    //get the data from the data handler object
    for(auto estate: DataHandler::getInstance().getEstates())
    {
        printEstate(estate);
    }

    if(user_->getPrivilege() == "admin")//in case of user we dont want to go back
        mainMenu();                   //to the main menu because of the further options
}

void AbstractInterface::printEstate(RealEstate *estate) const
{
    //convert estate string to a QString for a more convenient string processing
    QString estate_string = QString::fromStdString(estate->asString());
    QStringList splitted_string = estate_string.split(",");

    string address = splitted_string[0].toStdString();
    unsigned area_of_land = unsigned(splitted_string[1].toInt());
    unsigned area_of_building = unsigned(splitted_string[2].toInt());
    string heating = splitted_string[3].toStdString();
    unsigned price = unsigned(splitted_string[4].toInt());
    string description = splitted_string[5].toStdString();
    // agent name would be the 6th but we dont want to print that

    cout << "--------------------------------------------------------" << endl
         << "[" << estate->getId() << "]" << endl
         << " Address: " << address << endl
         << " Area of the land: " << area_of_land << endl
         << " Area of the building: " << area_of_building << endl
         << " Type of heating: " << heating << endl
         << " Price (HUF): " << price << endl
         << " Description: " << description << endl
         << "--------------------------------------------------------" << endl;
}
