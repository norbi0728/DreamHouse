#ifndef ADMININTERFACE_H
#define ADMININTERFACE_H

#include "abstractinterface.h"

class AdminInterface: public AbstractInterface
{
    AdminInterface();
    AdminInterface(const AdminInterface &other);
public:
    ~AdminInterface();

    //member functions
    static AdminInterface& getInstance();
    void mainMenu() const;
    void newAgent() const;
};

#endif // ADMININTERFACE_H
