#ifndef AGENT_H
#define AGENT_H

#include "user.h"

#include <list>
#include <map>

class Agent: public User
{
    bool bModifying_ = false; //utility var helps to decide how to call the interfaces list and search methods
    list<unsigned> estates_;
    map<string, unsigned> appointments_; // phone number - estate id
public:
    Agent(const string& name_, const string& password_, const string& privilege_);

    //member functions
    const string asString() const;
    void setAppointment(const string& phone, unsigned estate_id);
    void addEstate(unsigned estate_id); //used when load user data from file
    unsigned getId() const;
    const list<unsigned>& getEstates() const;
    bool getModifying() const;
    void setModifying(bool value);
    map<string, unsigned> getAppointments() const;
    void clearAppointments();
};

#endif // AGENT_H
