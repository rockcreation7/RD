
#include <string>

#ifndef PERSON_H
#define PERSON_H

class Sword {
private:
    std::string name;
    int age;

public:
    Sword(const std::string &name, int age);
    std::string getName() const;
    int getAge() const;
};

#endif