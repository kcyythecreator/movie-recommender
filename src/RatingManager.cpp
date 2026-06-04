#include "RatingManager.h"
#include <iostream>
#include <fstream>   
#include <sstream>   
#include <stdexcept>

void RatingManager::addRating(const Rating& r) {
    ratings.push_back(r);
    std::cout << "평점이 기록되었습니다.\n";
}

void RatingManager::displayRatingsByMovie(int movieId) const {
    bool found = false;
    std::cout << "=== 해당 영화의 평점 기록 ===\n";
    for (const auto& r : ratings) {
        if (r.getMovieId() == movieId) {
            std::cout << "사용자ID: " << r.getUserId() << " | 점수: " << r.getScore() << "\n";
            found = true;
        }
    }
    if (!found) std::cout << "아직 기록된 평점이 없습니다.\n";
}

std::vector<Rating> RatingManager::findByUser(int userId) const {
    std::vector<Rating> result;
    for (const auto& r : ratings) {
        if (r.getUserId() == userId) {
            result.push_back(r);
        }
    }
    return result;
}

void RatingManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 파일을 열 수 없습니다." << std::endl;
        return;
    }

    ratings.clear(); 
    std::string line;
    std::getline(file, line); 

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        try {
            std::stringstream ss(line);
            std::string token;

            std::getline(ss, token, ',');
            int userId = std::stoi(token);

            std::getline(ss, token, ',');
            int movieId = std::stoi(token);

            std::getline(ss, token, ',');
            double score = std::stod(token);

            ratings.push_back(Rating(userId, movieId, score));
        } catch (const std::exception& e) {
            std::cerr << "데이터 파싱 오류 (해당 줄 건너뜀): " << e.what() << std::endl;
            continue;
        }
    }
    file.close();
}

void RatingManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 파일에 저장할 수 없습니다." << std::endl;
        return;
    }

    file << "userId,movieId,score\n";
    
    for (const auto& r : ratings) {
        file << r.getUserId() << "," 
             << r.getMovieId() << "," 
             << r.getScore() << "\n";
    }
    file.close();
}

int RatingManager::size() const {
    return ratings.size();
}