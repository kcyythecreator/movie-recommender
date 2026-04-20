#include "../include/movie_manager.h"
#include <iostream>
#include <algorithm>

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