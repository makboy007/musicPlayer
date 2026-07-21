#ifndef ACCOUNTREPOSITORY_H
#define ACCOUNTREPOSITORY_H

#include"acount.h"
#include "abstractrepository.h"
class AccountRepository : public AbstractRepository<Acount>
{
public:
    virtual optional<Acount> searchByUserName(string username)const=0;
};

#endif // ACCOUNTREPOSITORY_H
