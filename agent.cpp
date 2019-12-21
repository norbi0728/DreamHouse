#include "agent.h"

const list<unsigned> &Agent::getEstates() const
{
    return estates_;
}

bool Agent::getModifying() const
{
    return bModifying_;
}

void Agent::setModifying(bool value)
{
    bModifying_ = value;
}

map<string, unsigned> Agent::getAppointments() const
{
    return appointments_;
}

void Agent::clearAppointments()
{
    appointments_.clear();
}

Agent::Agent(const string &name, const string& password, const string &privilege):
    User(name, password, privilege)
{
}

const string Agent::asString() const
{
    string appointment_string = "";
    for(auto a: appointments_)
    {
        appointment_string += "," + a.first + "," + to_string(a.second);
    }
    return User::asString() + appointment_string;
    //                 name, password, privilege,  phone - estate id sequence
}

void Agent::setAppointment(const string &phone, unsigned estate_id)
{
    appointments_[phone] = estate_id;
}

void Agent::addEstate(unsigned estate_id)
{
    estates_.push_back(estate_id);
}
