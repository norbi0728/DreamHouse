#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User
{
    string name_;
    string password_;
    string privilege_; //user, admin, agent
public:
    User(const string& name_, const string& password_, const string& privilege_);
    virtual ~User();

    //member functions
    virtual const string asString() const;
    string getName() const;
    string getPrivilege() const;
    void setPrivilege(const string &value);
    string getPassword() const;
};

#endif // USER_H
