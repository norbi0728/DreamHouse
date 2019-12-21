#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <exception>
#include <iostream>
#include <list>
#include <QFile>
#include <QTextStream>

#include "realestate.h"
#include "agent.h"
#include "user.h"

class DataHandler
{
    list<RealEstate*> estates_;
    list<User*> users_;
    QString estateFilePath_ = "real_estate_data.txt";
    QString userFilePath_ = "user_data.txt";
    //singleton
    DataHandler();
    DataHandler(const DataHandler& other);
public:
    ~DataHandler();
    static DataHandler& getInstance();

    //member functions
    void listEstates() const;
    void listUsers() const;
    void save(const QString &save_path = nullptr) const;
    void saveNewUser(User* user);
    const list<RealEstate*>& getEstates() const;
    const list<User*>& getUsers() const;
    void removeEstateAndSave(RealEstate* estate);
    void saveNewEstate(RealEstate* estate);
    void loadEstates();
    void loadUsers();
    const QString& getUserFilePath() const;
    const QString& getEstateFilePath() const;

    //exceptions
    class NoSuchFileException: public exception
    {
        string filePath_;
        string errString_;
    public:
        NoSuchFileException(const string& filePath):
            filePath_(filePath)
        {
            errString_ = "There is no such file: " + filePath;
        }

        const char * what() const noexcept
        {
            return errString_.c_str();
        }
    };
};

#endif // DATAHANDLER_H
