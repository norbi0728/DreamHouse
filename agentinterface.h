#ifndef AGENTINTERFACE_H
#define AGENTINTERFACE_H

#include "abstractinterface.h"


class AgentInterface: public AbstractInterface
{
    AgentInterface();
    AgentInterface(const AgentInterface& other);
    Menu* modifyMenu;
public:

    //member functions
    static AgentInterface& instance();
    void mainMenu() const override;
    void modifyEstateMenu() const;
    void modifyEstate(RealEstate* estate) const;
    void deleteEstateMenu() const;
    void deleteEstate(RealEstate* estate) const;
    void newEstate() const;
    void listOwnEstates() const;
    void searchOwnEstatesByAddress() const;
    void readNotifications() const;
    bool hasEstates() const;

    void getNumericalInput(string& num, void(AgentInterface::*func)()const,
                           bool withID = false) const; //utility, throws exception if it gets non numerical val
    //if you call it where id is needed, set withID to true, default is false

    void getNumericalInput(string& num, void(AgentInterface::*func)(RealEstate* )const,
                           RealEstate* estate, bool withID = false) const; //need another, it does the same the
                                                       //another, but gets a RE param

    //checks if exists estate with the given id, if so, it calls the 2nd function
    //if not, 1st will be called
    void checkID(unsigned choice, void(AgentInterface::*func)()const,
                 void(AgentInterface::*func2)(RealEstate* )const) const;
};

#endif // AGENTINTERFACE_H
