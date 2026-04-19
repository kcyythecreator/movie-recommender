#include "movie_manager.h"
#include <iostream>
#include <algorithm> 

void MovieManager::addMovie(const Movie& m) {
    movies.push_back(m);
    std::cout << "영화 '" << m.getTitle() << "' 가 추가되었습니다.\n";
}

void MovieManager::searchByTitle(const std::string& title) const {
    bool found = false;
    for (const auto& m : movies) {
        if (m == title) { 
            std::cout << "검색 결과: " << m << "\n"; 
            found = true;
        }
    }
    if (!found) std::cout << "해당 제목의 영화를 찾을 수 없습니다.\n";
}

void MovieManager::displayAll() const {
    if (movies.empty()) {
        std::cout << "등록된 영화가 없습니다.\n";
        return;
    }
    std::cout << "=== 전체 영화 목록 ===\n";
    for (const auto& m : movies) {
        std::cout << m << "\n"; 
    }
}

void MovieManager::sortByRating() {
    if (movies.empty()) {
        std::cout << "정렬할 영화가 없습니다.\n";
        return;
    }
    
    std::vector<Movie> sortedMovies = movies;

    std::sort(sortedMovies.rbegin(), sortedMovies.rend());

    std::cout << "=== 평점순 정렬 결과 ===\n";
    for (const auto& m : sortedMovies) {
        std::cout << m << "\n";
    }
}