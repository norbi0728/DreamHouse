#include "datahandler.h"

const QString &DataHandler::getUserFilePath() const
{
    return userFilePath_;
}

const QString& DataHandler::getEstateFilePath() const
{
    return estateFilePath_;
}

DataHandler::DataHandler()
{
    try
    {
        loadEstates();
        loadUsers();
    }
    catch(exception& e)
    {
        cout << e.what();
    }
}

DataHandler::DataHandler(const DataHandler &other)
{
    *this = other;
}

DataHandler::~DataHandler()
{

    for(auto e: estates_)
    {
        delete e;
    }

    for(auto u: users_)
    {
        delete u;
    }
}

DataHandler &DataHandler::getInstance()
{
    static DataHandler instance;
    return instance;
}

void DataHandler::save(const QString& save_path) const
{
    QFile output(save_path);
    QTextStream save(&output);
    if(output.open(QIODevice::WriteOnly))
    {
        if(save_path == estateFilePath_)
        {
            for(auto estate: estates_)
            {
                save << QString::fromStdString(estate->asString()) + "\n";
            }
        }
        else
        {
            for(auto user: users_)
            {
                save << QString::fromStdString(user->asString()) + "\n";
            }
        }
    }
    output.close();
}

void DataHandler::saveNewUser(User *user)
{
    users_.push_back(user);
    
    save(userFilePath_);
}

const list<RealEstate *>& DataHandler::getEstates() const
{
    return estates_;
}

const list<User *>& DataHandler::getUsers() const
{
    return users_;
}

void DataHandler::removeEstateAndSave(RealEstate *estate)
{
    estates_.remove(estate);
    save(estateFilePath_);
}

void DataHandler::saveNewEstate(RealEstate *estate)
{
    estates_.push_back(estate);
    save(estateFilePath_);
}

void DataHandler::loadEstates()
{
    QFile estate_data(estateFilePath_);

    if(!estate_data.open(QIODevice::ReadOnly)) // open estate data
        throw NoSuchFileException(estateFilePath_.toStdString());

    QTextStream estate_data_input(&estate_data); //this will read the data

    QString line; // read into this string
    QStringList splitted_line; // split the above string to get the individual data

    string address, description, heating, agent; // read into these
    unsigned area_of_land, area_of_building, price;

    while(!estate_data_input.atEnd())
    {
        line = estate_data_input.readLine();
        splitted_line = line.split(",");

        // deconstruct the line to individual data
        address = splitted_line[0].toStdString();
        area_of_land = unsigned(splitted_line[1].toInt());
        area_of_building = unsigned(splitted_line[2].toInt());
        heating = splitted_line[3].toStdString();
        price = unsigned(splitted_line[4].toInt());
        description = splitted_line[5].toStdString();
        agent = splitted_line[6].toStdString();

        //construct the estate from the individual data and store
        estates_.push_back(new RealEstate(address, area_of_land,
                                         area_of_building, heating,
                                         price, description, agent));
    }
    estate_data.close();
}

void DataHandler::loadUsers()
{
    QFile user_data(userFilePath_);

    if(!user_data.open(QIODevice::ReadOnly))
        throw NoSuchFileException(userFilePath_.toStdString());

    QTextStream user_data_input(&user_data);
    QString line; // read into this string
    QStringList splitted_line; // split the above string to get the individual data

    //read into these vars
    string name, password, privilege;


    while(!user_data_input.atEnd())
    {
        line = user_data_input.readLine();
        splitted_line = line.split(",");


        name = splitted_line[0].toStdString();
        password = splitted_line[1].toStdString();
        privilege = splitted_line[2].toStdString();
        if(privilege == "user")
            users_.push_back(new User(name, password, privilege));
        else if(privilege == "admin")
             users_.push_back(new User(name, password, privilege));
        else if(privilege == "agent")
        {
            Agent *agent = new Agent(name, password, privilege);
            //load the appointments
            unsigned estate_id;
            string phone;
            //start from the third attribute, which is the first phone number
            //step two because one phone - estate id pair mean one contact
            for(int i = 3; i < splitted_line.size() - 1; i += 2)
            {
                phone = splitted_line[i].toStdString();
                estate_id = unsigned(splitted_line[i + 1].toInt());
                agent->setAppointment(phone, estate_id);
            }

            users_.push_back(agent);
        }
    }

    //after we have loaded all user data, we need to pair to them their estates regarding ids
    // if the user is an agent
    for(auto estate: estates_)
    {
        for(auto agent: users_)
        {
            if(Agent* a = dynamic_cast<Agent*>(agent)) //if the current user is an agent
            {                                          // then check if the current estate
                if(estate->getAgent() == a->getName()) // belongs to him (the estates agent
                    a->addEstate(estate->getId());     //            equals to the agent's name)
            }
        }
    }
    
    user_data.close();
}
