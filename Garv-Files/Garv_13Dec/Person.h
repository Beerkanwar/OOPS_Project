#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name, dob, email, gender;

public:
    Person(string name, string dob, string email, string gender)
        : name(name), dob(dob), email(email), gender(gender) {}

    virtual ~Person() = default;
    virtual string getUniqueID() const = 0;
};

#endif // PERSON_H