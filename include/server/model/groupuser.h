#ifndef GROUPUSER_H_
#define GROUPUSER_H_

#include "user.h"

class GroupUser : public User
{

public:
    void setRole(string role) { this->role = role;}
    string getRole() {return this->role;}
private:
    string role;
};



#endif