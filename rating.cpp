#include "rating.h"
#include <iostream>

Rating::Rating(int uId, int mId, double s)
    : userId(uId), movieId(mId) {
    
    if (s >= 0.0 && s <= 5.0) {
        score = s; 
    } else {
        std::cout << "ERROR(0으로 설정)" << std::endl;
        score = 0.0;
    }
}

int    Rating::getUserId()  const { return userId; }
int    Rating::getMovieId() const { return movieId; }
double Rating::getScore()   const { return score; }

void Rating::display() const {
    std::cout << "사용자 ID: " << userId << std::endl
              << "영화 ID: " << movieId << std::endl
              << "평점: " << score << std::endl;
}