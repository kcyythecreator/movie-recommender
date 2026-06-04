#include "Recommender.h"
#include "SimilarityCalculator.h"
#include <cstdlib>
#include <algorithm> 
#include <set>
#include <map>
#include <iostream>
#include <chrono>
#include <string>

class Timer {
    std::chrono::high_resolution_clock::time_point start;
    std::string label;
public:
    Timer(const std::string& l) : label(l) {
        start = std::chrono::high_resolution_clock::now();
    }
    ~Timer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "[" << label << "] " << us.count() << " us\n";
    }
};

Recommender::Recommender(MovieManager& mm, RatingManager& rm, UserManager& um)
    : movieManager(mm), ratingManager(rm), userManager(um) {}

int Recommender::Similaritycalculate(const std::vector<Rating>& ratingsA, const std::vector<Rating>& ratingsB) {
    int commonCount = 0;
    int scoreDiffSum = 0;

    for (const auto& rA : ratingsA) { 
        for (const auto& rB : ratingsB) {
            if (rA.getMovieId() == rB.getMovieId()) {
                commonCount++;
                scoreDiffSum += std::abs(rA.getScore() - rB.getScore());
            }
        }
    }

    if (commonCount == 0) {
        return SimilarityCalculator::NO_COMMON_MOVIE;
    }
    return (commonCount * SimilarityCalculator::WEIGHT) - scoreDiffSum;
}

std::vector<std::pair<int, int>> Recommender::recommend(int targetUserId, int K, int N) {
    Timer t("recommend");

    std::vector<std::pair<int, int>> recommendations;
    std::vector<Rating> myRatings = ratingManager.findByUser(targetUserId);

    if (myRatings.empty()) {
        return recommendations;
    }

    std::set<int> myMovieIds; 
    for (const auto& r : myRatings) { 
        myMovieIds.insert(r.getMovieId()); 
    }

    std::vector<std::pair<int, int>> similarities; 
    std::vector<int> allUserIds = userManager.getAllUserIds(); 

    for (int otherId : allUserIds) {
        if (otherId == targetUserId) continue; 

        std::vector<Rating> otherRatings = ratingManager.findByUser(otherId);
        int sim = SimilarityCalculator::calculate(myRatings, otherRatings);
        
        // 공통 영화가 없어 예외 값(-100)이 반환된 유저는 유사도 목록에서 제외
        if (sim != SimilarityCalculator::NO_COMMON_MOVIE) {
            similarities.push_back({otherId, sim}); 
        }
    }

    // 취향이 가장 비슷한 상위 유저를 뽑기 위해 유사도(second)를 기준으로 내림차순(>) 정렬
    std::sort(similarities.begin(), similarities.end(),
        [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second > b.second; 
        });
    
    int limitK = std::min(K, (int)similarities.size()); 
    if (limitK == 0) {
        return recommendations; 
    }

    std::map<int, int> movieScores;

    for (int i = 0; i < limitK; ++i) {
        int similarUserId = similarities[i].first; 
        std::vector<Rating> simUserRatings = ratingManager.findByUser(similarUserId);

         for (const auto& r : simUserRatings) { 
            // 타겟 유저가 아직 보지 않은 영화(set에 없는 영화)만 골라서 추천 점수 누적
            if (myMovieIds.find(r.getMovieId()) == myMovieIds.end()) {
                movieScores[r.getMovieId()] += r.getScore();
            }
        }
    }

    std::vector<std::pair<int, int>> sortedScores(movieScores.begin(), movieScores.end());
    
    // 점수가 누적된 추천 후보 영화들 중 상위 N개를 뽑기 위해 내림차순(>) 정렬
    std::sort(sortedScores.begin(), sortedScores.end(),
        [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second > b.second;
        });
        
    int limitN = std::min(N, (int)sortedScores.size());
    if (limitN == 0) {
        return recommendations; 
    }

    for (int i = 0; i < limitN; ++i) { 
        recommendations.push_back(sortedScores[i]);
    }

    return recommendations; 
}