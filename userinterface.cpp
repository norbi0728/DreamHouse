#include "userinterface.h"
#include "logininterface.h"

UserInterface::UserInterface()
{
    //set up the special menu

    unordered_map<char, string> menuItems;
    menuItems['e'] = "Estimate expected monthly payments";
    menuItems['c'] = "Claim appointment";
    menuItems['l'] = "List again all estates";
    menuItems['b'] = "Back to the main menu";

    furtherOptionsMenu = new Menu(menuItems, "Further options", "Please select what would"
                                                                " you like to do next");
}

UserInterface::UserInterface(const UserInterface &other):
    AbstractInterface(other)
{
}

UserInterface::~UserInterface()
{
    delete furtherOptionsMenu;
}

UserInterface &UserInterface::get_instance()
{
    static UserInterface instance;
    return instance;
}

void UserInterface::mainMenu() const
{

    switch (menu_->show())
    {
    case 'l': listAllEstates();
        break;
    case 's': searchByAddress();
        break;
    case 'e': exitToLoginMenu();
    }
}

void UserInterface::listAllEstates() const
{
    AbstractInterface::listAllEstates();

    if(DataHandler::getInstance().getEstates().size() != 0)
        furtherOptions();
    else
        mainMenu();
}

void UserInterface::estimateExpectedMonthlyPaymentMenu() const
{
    string choice_dummy;
    unsigned choice;

    cout << "--------------------------------------------------------" << endl;
    cout << " Give the number of the estate which expected monthly payment you're "
            "interested in: ";

    getNumericalInput(choice_dummy, &UserInterface::estimateExpectedMonthlyPaymentMenu);

    choice = unsigned(stoi(choice_dummy));

    checkID(choice, &UserInterface::estimateExpectedMonthlyPaymentMenu,
            &UserInterface::monthlyPaymentEstimator);
}

void UserInterface::monthlyPaymentEstimator(unsigned id) const
{
    const unsigned woodPriceInHuf = 29000; //price of 1 cubic meter chopped wood. an average household
                                           // consumes about a half cubic meter per month
    const unsigned ePowerPriceInHuf = 35; // price of electric power per kWh
    const unsigned baseGasPriceInHuf = (13740 / 12); //13740 is the yearly base assign price
    const unsigned gasPriceInHuf = 128; //price of gas per MWh
    const unsigned waterPriceInHuf = 218; //price of 1 cubic meter water
    unsigned estimatedMonthlyPayment = 0;
    auto calculator = [&](RealEstate* estate, bool winter = true)
    {


        estimatedMonthlyPayment += (estate->getAreaOfBuilding() * ePowerPriceInHuf);
        estimatedMonthlyPayment += (waterPriceInHuf * (0.1 * estate->getAreaOfBuilding()));

        if(!winter) return estimatedMonthlyPayment;

        if(estate->getHeating() == "wood")
        {
            estimatedMonthlyPayment += (woodPriceInHuf * (estate->getAreaOfBuilding()*0.002));
            return  estimatedMonthlyPayment;
        }
        else if(estate->getHeating() == "gas")
        {
            estimatedMonthlyPayment += baseGasPriceInHuf;
            estimatedMonthlyPayment += (gasPriceInHuf * estate->getAreaOfBuilding());
            return estimatedMonthlyPayment;
        }
        else
        {
            estimatedMonthlyPayment += (ePowerPriceInHuf * estate->getAreaOfBuilding());
            return estimatedMonthlyPayment;
        }

    };

    cout << "--------------------------------------------------------" << endl;
    cout << "The estimated monthly payment (regarding the public utilities): " << endl;
         for(auto e: DataHandler::getInstance().getEstates())
         {
             if(e->getId() == id)
             {
                 cout << " Heating seasons: " << calculator(e) << endl;
                 estimatedMonthlyPayment = 0;
                 cout << " For the rest: " << calculator(e, false) << endl;
             }
         }
    cout << "You will be redirected to the menu where you can choose further options" << endl;
    cout << "--------------------------------------------------------" << endl;
    furtherOptions();
}

void UserInterface::furtherOptions() const
{
    switch (furtherOptionsMenu->show())
    {
    case 'e': estimateExpectedMonthlyPaymentMenu();
        break;
    case 'c': claimAppointmentMenu();
        break;
    case 'l': listAllEstates();
        break;
    case 'b': mainMenu();
    }
}

void UserInterface::claimAppointmentMenu() const
{
    string choice_dummy;
    unsigned choice = 0;

    cout << "--------------------------------------------------------" << endl;
    cout << " Give the number of the estate which you're "
            "interested in: ";

    getNumericalInput(choice_dummy, &UserInterface::claimAppointmentMenu);

    choice = unsigned(stoi(choice_dummy));

    checkID(choice, &UserInterface::claimAppointmentMenu,
            &UserInterface::claimAppointment);
}

void UserInterface::claimAppointment(unsigned estate_id) const
{
    string phone;
    cout << "--------------------------------------------------------" << endl;
    cout << "Give a phone number that the appropriate "
            "agent can call regarding the appointment: ";

    cin >> phone;
    cout << "--------------------------------------------------------" << endl;

    //search for the estate, if we found it, we will know which agent should we notify
    for(auto e: DataHandler::getInstance().getEstates())
    {
        if(e->getId() == estate_id) //we found the estate
        {
            //we have the desired estate, now just find the agent
            for(auto u: DataHandler::getInstance().getUsers())
            {
                if(u->getName() == e->getAgent()) //we found the proper agent
                {
                    dynamic_cast<Agent*>(u)->setAppointment(phone, estate_id); //set te appointment
                    DataHandler::getInstance().save(
                                DataHandler::getInstance().getUserFilePath());
                    //the user data has been modified (an appointment was added)
                    //so we need to save it
                    cout << "--------------------------------------------------------" << endl;
                    cout << "Your claim was forwarded to the appropriate agent. "
                            "Our college will contact you in 24 hours regarding the appointment. "
                            " You will be redirected to the main menu" << endl;
                    cout << "--------------------------------------------------------" << endl;
                    mainMenu();
                }
            }
        }
    }
}

void UserInterface::searchByAddress() const
{
    AbstractInterface::searchByAddress();
    furtherOptions();
}

void UserInterface::getNumericalInput(string &num, void (UserInterface::*func)() const) const
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

        cout << "--------------------------------------------------------" << endl;
        cout << "Please give exactly one id from the list above: ";

        //if he has given a character or a str he can start the input process again
        //until he gives a number
        (this->*func)();
    }
}

void UserInterface::checkID(unsigned choice,
                            void (UserInterface::*func)() const,
                            void(UserInterface::*func2)(unsigned) const) const
{
    bool validId = false;

    for(auto e: DataHandler::getInstance().getEstates())
    {
        if(e->getId() == choice)
        {
            (this->*func2)(choice);
            validId = true;
            break;
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
