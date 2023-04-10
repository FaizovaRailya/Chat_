#include <iostream>
#include "User.h"


User::User(const std::string& name, const std::string& login, uint* password) :
    name_(name), login_(login), password_(password) {}

const std::string& User::getName() const { return name_; }
const std::string& User::getLogin() const { return login_; }
uint* User::getPassword() const { return password_; }

std::fstream& operator >>(std::fstream& is, User& user) {
    unsigned int* _pw = new unsigned int[5];
    is >> user.name_;
    is >> user.login_;
    for (int hash_block = 0; hash_block < 5; hash_block++) {
        is >> _pw[hash_block];
    }
    user.password_ = _pw;
    return is;
}

std::ostream& operator <<(std::ostream& os, const User& user) {
    os << user.getName();
    os << ' ';
    os << user.getLogin();
    os << ' ';
    const unsigned int* _pw = user.getPassword();
    for (int hash_block = 0; hash_block < 4; hash_block++)
        os << _pw[hash_block] << ' ';
    os << _pw[4];
    os << endl;
    return os;
}