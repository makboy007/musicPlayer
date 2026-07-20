#include "acount.h"
#include "idgenerator.h"
Acount:: Acount(string Fullname,string Username,bool Role,string Password,string Biography)
{
    this->FullName=Fullname;
    this->UserName=Username;
    this->Biography=Biography;
    this->Role=Role;
    this->Password=Password;
    this->ID=IdGenerator::generateAccountId();
}
