#include "user_manager.h"
#include <iostream>

void UserManager::addUser(const User& u) {
    users.push_back(u);
    std::cout << "사용자 '" << u.getName() << "'님이 등록되었습니다.\n";
}

void UserManager::displayAllUsers() const {
    if (users.empty()) {
        std::cout << "등록된 사용자가 없습니다.\n";
        return;
    }
    std::cout << "=== 사용자 목록 ===\n";
    for (const auto& u : users) {
        std::cout << "[" << u.getId() << "] " << u.getName() << "\n";
    }
}