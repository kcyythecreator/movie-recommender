#pragma once
#include <vector>
#include <utility> 
#include <string>
#include "MovieManager.h"
#include "RatingManager.h"
#include "UserManager.h"
#include "Rating.h"

class Recommender { 
        
private:
    MovieManager& movieManager;
    RatingManager& ratingManager;
    UserManager& userManager;

public:
    Recommender(MovieManager& mm, RatingManager& rm, UserManager& um);
    int Similaritycalculate(const std::vector<Rating>& ratingsA, const std::vector<Rating>& ratingsB);
    
    // M4 확장 기능: 장르 필터 기본 인자 추가
    std::vector<std::pair<int, int>> recommend(int targetUserId, int K = 5, int N = 3, const std::string& genreFilter = "");
};