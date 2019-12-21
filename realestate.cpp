#include "realestate.h"

unsigned RealEstate::s_Counter = 0;

unsigned RealEstate::getId() const
{
    return id_;
}

const string& RealEstate::getAgent() const
{
    return agent_;
}

unsigned RealEstate::getPrice() const
{
    return price_;
}

string RealEstate::getAddress() const
{
    return address_;
}

void RealEstate::setHeating(const string &value)
{
    heating_ = value;
}

void RealEstate::setArea_of_land(const unsigned &value)
{
    areaOfLand_ = value;
}

void RealEstate::setArea_of_building(const unsigned &value)
{
    areaOfBuilding_ = value;
}

void RealEstate::setPrice(const unsigned &value)
{
    price_ = value;
}

void RealEstate::setDescription(const string &value)
{
    description_ = value;
}

void RealEstate::setAddress(const string &value)
{
    address_ = value;
}

string RealEstate::getHeating() const
{
    return heating_;
}

unsigned RealEstate::getAreaOfBuilding() const
{
    return areaOfBuilding_;
}

void RealEstate::setAreaOfBuilding(const unsigned &areaOfBuilding)
{
    areaOfBuilding_ = areaOfBuilding;
}

RealEstate::RealEstate(const string &address,
                       unsigned area_of_land, unsigned area_of_building,
                       const string &heating, unsigned price,
                       const string &description, string agent):
    address_(address),
    heating_(heating),
    areaOfLand_(area_of_land),
    areaOfBuilding_(area_of_building),
    price_(price),
    description_(description),
    agent_(agent)

{
    id_ = ++s_Counter;
}

RealEstate::~RealEstate()
{
    s_Counter--;
}

const string RealEstate::asString() const
{
    return  address_ + "," + to_string(areaOfLand_) + "," +
            to_string(areaOfBuilding_) + "," + heating_  + "," +
            to_string(price_) + "," + description_ + "," + agent_;
}

