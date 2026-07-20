#ifndef ABSTRACTREPOSITORY_H
#define ABSTRACTREPOSITORY_H

#include <optional>

using namespace std;

template <class T>
class AbstractRepository
{
public:
    virtual int  save(const T& data)=0;
    virtual bool remove(int id)=0;
    virtual optional<T> search(int id) const =0;


};

#endif // ABSTRACTREPOSITORY_H
