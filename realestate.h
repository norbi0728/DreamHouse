#ifndef REALESTATE_H
#define REALESTATE_H

#include "string"

using namespace std;

class RealEstate
{
    static unsigned s_Counter; //every counstruction will increment this var provides unique ids
    unsigned id_; //unique identifier of the property
    string address_;
    string heating_; //wood, gas, electronic, central if its a flat
    unsigned areaOfLand_; //0 if its a flat
    unsigned areaOfBuilding_;
    unsigned price_;
    string description_;
    string agent_; //identifies the agent who advertises the property
public:
    RealEstate(const string &address_,
               unsigned areaOfLand_, unsigned areaOfBuilding_,
              const string &heating_, unsigned price_,
              const string &description_, string agent_);
    ~RealEstate();

    //member functions
    const string asString() const;
    unsigned getId() const;
    const string& getAgent() const;
    unsigned getPrice() const;
    string getAddress() const;
    void setHeating(const string &value);
    void setArea_of_land(const unsigned &value);
    void setArea_of_building(const unsigned &value);
    void setPrice(const unsigned &value);
    void setDescription(const string &value);
    void setAddress(const string &value);
    string getHeating() const;
    unsigned getAreaOfBuilding() const;
    void setAreaOfBuilding(const unsigned &areaOfBuilding);
};

#endif // REALESTATE_H
