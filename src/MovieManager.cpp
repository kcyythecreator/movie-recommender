#include "MovieManager.h"
#include "Movie.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>

void MovieManager::addMovie(const Movie& movie) {
    movies.push_back(movie);
}

void MovieManager::displayAll() const {
    std::cout << "\n--- 전체 영화 목록 ---" << std::endl;
    for (const auto& m : movies) {
        std::cout << m << std::endl;
    }
}

void MovieManager::searchByTitle(const std::string& title) const {
    bool found = false;
    for (const auto& m : movies) {
        if (m.getTitle().find(title) != std::string::npos) {
            std::cout << m << std::endl;
            found = true;
        }
    }
    if (!found) std::cout << "검색 결과가 없습니다." << std::endl;
}

void MovieManager::sortByRating() {
    std::sort(movies.begin(), movies.end()); 
    std::cout << "\n평점순으로 정렬되었습니다." << std::endl;
}

void MovieManager::updateMovieRating(int movieId, double score) {
    for (auto& m : movies) {
        if (m.getId() == movieId) {
            m.addRating(score);
            return;
        }
    }
    std::cout << "해당 ID의 영화를 찾을 수 없습니다." << std::endl;
}

void MovieManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 파일을 열 수 없습니다." << std::endl;
        return;
    }

    movies.clear();
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
            std::string title = token;

            std::getline(ss, token, ',');
            std::string genre = token;

            std::getline(ss, token, ',');
            int year = std::stoi(token);

            std::getline(ss, token, ',');
            double rating = std::stod(token);

            movies.push_back(Movie(id, title, genre, year, rating));
        } catch (const std::exception& e) {
            std::cerr << "데이터 파싱 오류 (해당 줄 건너뜀): " << e.what() << std::endl;
            continue;
        }
    }
    file.close();
}

void MovieManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 파일에 저장할 수 없습니다." << std::endl;
        return;
    }

    file << "id,title,genre,year,rating\n";
    for (const auto& m : movies) {
        file << m.getId() << "," 
             << m.getTitle() << "," 
             << m.getGenre() << ","
             << m.getReleaseYear() << ","
             << m.getRating() << "\n";
    }
    file.close();
}

int MovieManager::size() const {
    return movies.size();
}