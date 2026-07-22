#ifndef ACOUNT_H
#define ACOUNT_H

#include <iostream>
#include <string>

using namespace std;
class Acount
{
private:
    string FullName;
    string UserName;
    string Biography;
    int ID;
    bool Role;
    string Password;
public:
    Acount(string Fullname,string Username,bool Role,string Password,string Biography=" ");
    Acount(string Fullname,string Username,bool Role,string Password,string Biography,int ID);

    string getFullName()const { return FullName; }
    void setFullName(string value) { FullName = value; }

    string getUserName() const { return UserName; }
    void setUserName(string value) { UserName = value; }

    string getBiography()const { return Biography; }
    void setBiography(string value) { Biography = value; }

    int getID()const { return ID; }
    void setID(int value) { ID = value; }

    bool getRole()const { return Role; }
    void setRole(bool value) { Role = value; }

    string getPassword()const { return Password; }
    void setPassword(string value) { Password = value; }


};

#endif // ACOUNT_H
