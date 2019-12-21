#include "agentinterface.h"
#include "logininterface.h"

AgentInterface::AgentInterface()
{
    //set up the menu
    menuItems_['l'] = "List my properties";
    menuItems_['s'] = "Search by address";
    menuItems_['r'] = "Read notifications";
    menuItems_['m'] = "Modify estate";
    menuItems_['d'] = "Delete estate";
    menuItems_['a'] = "Add new estate";

    menu_ = new Menu(menuItems_, "Main menu", "Please type the letter of you choice");


    //set te modify menu too

    unordered_map<char, string> modifyMenuItems;

    modifyMenuItems['p'] = "Price";
    modifyMenuItems['l'] = "Land area";
    modifyMenuItems['b'] = "Building area";
    modifyMenuItems['h'] = "Type of heating";
    modifyMenuItems['d'] = "Description";
    modifyMenuItems['a'] = "Address";
    modifyMenuItems['e'] = " Back to main menu";

    modifyMenu = new Menu(modifyMenuItems, "Modification menu", "Please select the attribute"
                          " you want to modify");

}

AgentInterface::AgentInterface(const AgentInterface &other):
    AbstractInterface(other)
{
}

AgentInterface &AgentInterface::instance()
{
    static AgentInterface instance;
    return instance;
}

void AgentInterface::mainMenu() const
{
    cout << "--------------------------------------------------------" << endl;
    cout << "Signed in as " << user_->getName() << " | You have "
         << dynamic_cast<Agent*>(user_)->getAppointments().size() << " unread notifications." << endl;

    switch (menu_->show())
    {
    case 'l': listOwnEstates();
        break;
    case 's': searchOwnEstatesByAddress();
        break;
    case 'a': newEstate();
        break;
    case 'm': modifyEstateMenu();
        break;
    case 'd': deleteEstateMenu();
        break;
    case 'r': readNotifications();
        break;
    case 'e': exitToLoginMenu();
    }
}

void AgentInterface::modifyEstateMenu() const
{
    dynamic_cast<Agent*>(user_)->setModifying(true);//we want to modify, so let
    searchOwnEstatesByAddress();          //the abstract interface know to
                                                  //dont show the main menu after search
    if(hasEstates())
    {
        string choice_dummy;
        unsigned choice = 0;

        cout << "--------------------------------------------------------" << endl;
        cout << " Give the number of the estate which you want to modify: ";

        getNumericalInput(choice_dummy, &AgentInterface::modifyEstateMenu, true);

        choice = unsigned(stoi(choice_dummy));
        checkID(choice, &AgentInterface::modifyEstateMenu, &AgentInterface::modifyEstate);
    }
    else
        dynamic_cast<Agent*>(user_)->setModifying(false);

}

void AgentInterface::modifyEstate(RealEstate* estate) const
{
    cout << "The estate to modify: " << endl;
    //estate id and the agent who owns the estate cant be modified

    printEstate(estate);

    string price, land_area, building_area, heating, description, address;

    switch (modifyMenu->show())
    {
    case 'l':

        cout << "Land area: ";

        getNumericalInput(land_area, &AgentInterface::modifyEstate, estate);

        estate->setArea_of_land(unsigned(stoi(land_area)));

        DataHandler::getInstance().save(//remember to save
                    DataHandler::getInstance().getEstateFilePath());

        modifyEstate(estate);

        break;

    case 'p':

        cout << "Price: ";

        getNumericalInput(price, &AgentInterface::modifyEstate, estate);

        estate->setPrice(unsigned(stoi(price)));

        DataHandler::getInstance().save(//remember to save
                    DataHandler::getInstance().getEstateFilePath());

        modifyEstate(estate);

        break;

    case 'a':
        cout << "Address: "; cin >> ws; getline(cin, address);
        estate->setAddress(address);

        DataHandler::getInstance().save(//remember to save
                    DataHandler::getInstance().getEstateFilePath());

        modifyEstate(estate);

        break;
    case 'h':
        cout << "Type of heating: "; cin >> ws; getline(cin, heating);
        estate->setHeating(heating);

        DataHandler::getInstance().save(//remember to save
                    DataHandler::getInstance().getEstateFilePath());

        modifyEstate(estate);

        break;
    case 'd':
        cout << "Description: "; cin >> ws; getline(cin, description);
        estate->setDescription(description);

        DataHandler::getInstance().save(//remember to save
                    DataHandler::getInstance().getEstateFilePath());

        modifyEstate(estate);

        break;
    case 'b':

        cout << "Building area: ";

        getNumericalInput(building_area, &AgentInterface::modifyEstate, estate);

        estate->setArea_of_building(unsigned(stoi(building_area)));

        DataHandler::getInstance().save(//remember to save
                    DataHandler::getInstance().getEstateFilePath());

        modifyEstate(estate);

        break;

    case 'e': dynamic_cast<Agent*>(user_)->setModifying(false);//we finished, change back to false
                mainMenu();
        break;
    }

}

void AgentInterface::deleteEstateMenu() const
{
    dynamic_cast<Agent*>(user_)->setModifying(true);//we want to modify, so let
    searchOwnEstatesByAddress();                  //the abstract interface know to
                                                  //dont show the main menu after search
    if(hasEstates())
    {
        string choice_dummy;
        unsigned choice;

        cout << "--------------------------------------------------------" << endl;
        cout << " Give the number of the estate which you want to delete: ";

        //reads into choice_dummy and if exception is thrown, class deleteEstateMenu() again
        getNumericalInput(choice_dummy, &AgentInterface::deleteEstateMenu, true);

        choice = unsigned(stoi(choice_dummy));

        checkID(choice, &AgentInterface::deleteEstateMenu,
                &AgentInterface::deleteEstate);
    }
    else
        dynamic_cast<Agent*>(user_)->setModifying(false);

}

void AgentInterface::deleteEstate(RealEstate *estate) const
{
    string choice;
    cout << "--------------------------------------------------------" << endl;
    cout << "The estate to delete: " << endl;
    printEstate(estate);
    cout << "--------------------------------------------------------" << endl;

    AbstractInterface::getConfirmation(choice);

    if(choice == "y")
    {
        cout << "--------------------------------------------------------" << endl;
        cout << "Estate " << estate->getId() << " has been removed successfully!"
                                                " You will be redirected to the main menu" << endl;
        cout << "--------------------------------------------------------" << endl;
        DataHandler::getInstance().removeEstateAndSave(estate);
        dynamic_cast<Agent*>(user_)->setModifying(false); //finished
        mainMenu();
    }
    else if(choice == "n")
    {
        cout << "--------------------------------------------------------" << endl;
        cout << "Your intent to remove estate " << estate->getId() << " was ignored."
             "You will be redirected to the main menu" << endl;
        cout << "--------------------------------------------------------" << endl;
        dynamic_cast<Agent*>(user_)->setModifying(false); //finished
        mainMenu();
    }
}

void AgentInterface::newEstate() const
{
    string choice;
    cout << "--------------------------------------------------------" << endl;
    cout << "Please provide the attributes of the new estate! "
            "If you provide non-numerical value where there is a constraint numerical "
            "you have to start again the whole process." << endl;
    cout << "--------------------------------------------------------" << endl;

    //read into these vars
    string price, land_area, building_area, heating, description, address;

    //the input process will start again if the agent gives bad input
    cout << " Address: ";
    cin >> ws;//consume whitespace
    getline(cin, address);

    cout << " Land area (numerical): ";
    getNumericalInput(land_area, &AgentInterface::newEstate);

    cout << " Building area (numerical): ";
    getNumericalInput(building_area, &AgentInterface::newEstate);

    cout << " Type of heating: ";
    cin >> heating;

    cout << " Price (numerical): ";
    getNumericalInput(price, &AgentInterface::newEstate);

    cout << " Description: ";
    cin >> ws;
    getline(cin, description);

    //after he has given the attributes we print it to check if its okay
    // if he has given non-numerical where he should gave numerical exception will be thrown
    //and the whole process will start again
    RealEstate* _new_estate
            = new RealEstate(address, unsigned(stoi(land_area)),
                             unsigned(stoi(building_area)),
                                heating, unsigned(stoi(price)),
                             description, user_->getName());

    cout << "--------------------------------------------------------" << endl;

    printEstate(_new_estate);

    AbstractInterface::getConfirmation(choice);

    cout << "--------------------------------------------------------" << endl;

    if(choice == "y")
    {
        cout << "--------------------------------------------------------" << endl;
        cout << "Estate " << _new_estate->getId() << " has been successfully created! "
            "You will be redirected to the main menu" << endl;
        cout << "--------------------------------------------------------" << endl;
        DataHandler::getInstance().saveNewEstate(_new_estate);
        mainMenu();
    }
    else if(choice == "n")
    {
        cout << "--------------------------------------------------------" << endl;
        cout << "Your attend to create a new estate was discarded. You will be "
                "redirected to the main menu" << endl;
        cout << "--------------------------------------------------------" << endl;
        delete _new_estate; //memory was allocated
        mainMenu();
    }

}

void AgentInterface::listOwnEstates() const
{
    if(hasEstates())
    {
        for(auto estate: DataHandler::getInstance().getEstates())
        {
            if(estate->getAgent() == user_->getName())
            {
                printEstate(estate);
            }
        }
    }
    else
    {
        cout << "You dont have any estates. You will be redirected to the main menu" << endl;
        dynamic_cast<Agent*>(user_)->setModifying(false);
        mainMenu();
    }

    if(!dynamic_cast<Agent*>(user_)->getModifying()) //if the agent just search or list
    {                                                   // without modification
        mainMenu();
    }
}

void AgentInterface::searchOwnEstatesByAddress() const
{
    if(hasEstates())
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
            if(estate->getAgent() == user_->getName())
            {
                if(estate->getAddress().substr(0, address.size()) == address)
                {
                    results.push_back(estate);
                }
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

            if(!dynamic_cast<Agent*>(user_)->getModifying()) //if the agent just search or list
            {                                                   // without modification
                mainMenu();
            }
        }
        else
        {
            cout << "--------------------------------------------------------" << endl;
            cout << "There is no result for the given address. You will be redirected "
                    "to the main menu" << endl;
            cout << "--------------------------------------------------------" << endl;
            dynamic_cast<Agent*>(user_)->setModifying(false);//failed to find, so modif. mode off
            mainMenu();
        }
    }
    else
    {
        cout << "You dont have any estates. You will be redirected to the main menu" << endl;
        dynamic_cast<Agent*>(user_)->setModifying(false);
        mainMenu();
    }

}

void AgentInterface::readNotifications() const
{
    if(dynamic_cast<Agent*>(user_)->getAppointments().size() != 0)
    {
        for(auto appointment: dynamic_cast<Agent*>(user_)->getAppointments())
        {
            cout << "Call " << appointment.first << " regarding estate "
                 << appointment.second << endl;
        }
        //after he reads the notifications suppose he calls them, so he doesnt need them anymore
        dynamic_cast<Agent*>(user_)->clearAppointments();
        DataHandler::getInstance().save(
                    DataHandler::getInstance().getUserFilePath()); //save
    }
    else
    {
        cout << "You don't have any new notification." << endl;
    }
    mainMenu();
}

bool AgentInterface::hasEstates() const
{
    for(auto estate: DataHandler::getInstance().getEstates())
    {
        if(estate->getAgent() == user_->getName())
        {
            return true; //if have at least one estate, he has estate
        }
    }

    return false;
}

void AgentInterface::getNumericalInput(string &num, void(AgentInterface::*func)()const,
                                       bool withID) const
{
    unsigned choice = 0;
    try
    {
        cin >> num;
        choice = unsigned(stoi(num));//if he gives a character or string
                                               //exception will be thrown
        cout << "--------------------------------------------------------" << endl;
    }
    catch (exception& e)
    {
        if(withID)
        {
            cout << "--------------------------------------------------------" << endl;
            cout << "Please give exactly one id from the list above: ";
        }
        else
        {
            cout << "Please provide numerical value where there is a constraint:" << endl;
        }

        //if he has given a character or a str he can start the input process again
        //until he gives a number
        (this->*func)();
    }
}

void AgentInterface::getNumericalInput(string &num,
                                       void (AgentInterface::*func)(RealEstate *estate) const,
                                       RealEstate *estate, bool withID) const
{
    unsigned choice = 0;
    try
    {
        cin >> num;
        choice = unsigned(stoi(num));//if he gives a character or string
                                               //exception will be thrown
        cout << "--------------------------------------------------------" << endl;
    }
    catch (exception& e)
    {
        if(withID)
        {
            cout << "--------------------------------------------------------" << endl;
            cout << "Please give exactly one id from the list above: ";
        }

        //if he has given a character or a str he can start the input process again
        //until he gives a number
        (this->*func)(estate);
    }
}

void AgentInterface::checkID(unsigned choice,
                             void (AgentInterface::*func)() const,
                             void (AgentInterface::*func2)(RealEstate *) const) const
{
    bool validId = false;

    for(auto e: DataHandler::getInstance().getEstates())
    {
        if(e->getAgent() == user_->getName())
        {
            if(e->getId() == choice)
            {
                (this->*func2)(e);
                validId = true;
                break;
            }
        }
    }

    if(!validId) //not found
    {
        cout << "--------------------------------------------------------" << endl;
        cout << "There is no such estate with the given id, please try again!" << endl;
        cout << "--------------------------------------------------------" << endl;
        (this->*func)();
    }
}
