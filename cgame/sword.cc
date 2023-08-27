#include "sword.h"

Sword::Sword(const std::string &name, int age) : name(name), age(age) {}

std::string Sword::getName() const {
    return name;
}

int Sword::getAge() const {
    return age;
}