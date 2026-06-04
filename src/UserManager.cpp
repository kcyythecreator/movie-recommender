#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

void UserManager::addUser(const User& u) {
    users.push_back(u);
}

void UserManager::displayAllUsers() const {
    std::cout << "\n--- 전체 사용자 목록 ---" << std::endl;
    for (const auto& u : users) {
        std::cout << u << std::endl;
    }
}

std::vector<int> UserManager::getAllUserIds() const {
    std::vector<int> ids;
    for (const auto& u : users) {
        ids.push_back(u.getId());
    }
    return ids;
}

void UserManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 파일을 열 수 없습니다." << std::endl;
        return;
    }

    users.clear();
    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        try {
            std::stringstream ss(line);
            std::string token;

            std::getline(ss, token, ',');
            int id = std::stoi(token);

            std::getline(ss, token, ',');
            std::string name = token;

            std::getline(ss, token, ',');
            std::string email = token;

            users.push_back(User(id, name, email));
        } catch (const std::exception& e) {
            std::cerr << "데이터 파싱 오류 (해당 줄 건너뜀): " << e.what() << std::endl;
            continue;
        }
    }
    file.close();
}

void UserManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 파일에 저장할 수 없습니다." << std::endl;
        return;
    }

    file << "id,name,email\n";
    for (const auto& u : users) {
        file << u.getId() << ","
             << u.getName() << ","
             << u.getEmail() << "\n";
    }
    file.close();
}

int UserManager::size() const {
    return users.size();
}