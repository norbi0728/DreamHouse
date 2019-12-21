#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "abstractinterface.h"
#include "user.h"


class UserInterface: public AbstractInterface
{
    Menu* furtherOptionsMenu;
    UserInterface();
    UserInterface(const UserInterface& other);
public:
    ~UserInterface();
    static UserInterface& get_instance();
    void mainMenu() const;
    void listAllEstates() const;
    void estimateExpectedMonthlyPaymentMenu() const;
    void monthlyPaymentEstimator(unsigned id) const;

    void furtherOptions() const; //menu of the user specific options
    void claimAppointmentMenu() const;
    void claimAppointment(unsigned estate_id) const;
    void searchByAddress() const;
    //utility, throws exception if it gets non numerical val
    void getNumericalInput(string& num, void(UserInterface::*func)()const) const;
    void checkID(unsigned choice, void(UserInterface::*func)()const,
                 void(UserInterface::*func2)(unsigned)const) const;


};

#endif // USERINTERFACE_H
