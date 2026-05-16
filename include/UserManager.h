#pragma once
#include "BaseManager.h"
#include "User.h"
#include <vector>
#include <string>

class UserManager : public BaseManager {
private:
    std::vector<User> users;

public:
    void addUser(const User& u);
    void displayAllUsers() const;
    std::vector<int> getAllUserIds() const;

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};