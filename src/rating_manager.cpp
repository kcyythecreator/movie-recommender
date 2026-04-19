#include "rating_manager.h"
#include <iostream>

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