#include "user.h"

string User::getName() const
{
    return name_;
}

string User::getPrivilege() const
{
    return privilege_;
}

void User::setPrivilege(const string &value)
{
    privilege_ = value;
}

string User::getPassword() const
{
    return password_;
}

User::User(const string &name, const string &password, const string &privilege):
    name_(name),
    password_(password),
    privilege_(privilege)
{
}

User::~User()
{

}

const string User::asString() const
{
    return name_ + "," + password_ + "," + privilege_;
}
